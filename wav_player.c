#include <stm32.h>
#include <gpio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "buttons.h"
#include "pcm.h"
#include "irq.h"
#include "usart.h"

// Timer for scheduling samples
#define TIM_SAMPLE TIM2
// Timer for playing samples
#define TIM_PWM TIM3
// Timer for waiting until bouncing ends
#define TIM_BOUNCE TIM5

#define STM_CLOCKING_MHZ 16
#define STM_CLOCKING_HZ (1000000 * STM_CLOCKING_MHZ)
#define BOUNCING_DELAY_MS 5 // 5 ms should suffice
#define REPEAT_DELAY_MS 500 // 0.5 s seems reasonable

volatile size_t sample_idx; // Index of the currently played sample.

#define VOLUME_DIVISOR 20
// The value the currently played sample is multiplied by
// before being divided by VOLUME_DIVISOR, in order to scale volume.
volatile size_t volume_factor = VOLUME_DIVISOR;

#ifdef DEBUG
static bool const DEBUG = true;
#else
static bool const DEBUG = false;
#endif

#ifdef DEBUG
/* USART DEBUG MODULE */

struct string {
    char const *ptr;
    size_t len;
};

/* buffers */
#define SND_BUFF_CAP 128

struct send_buff {
    size_t beg, end, size;
    struct string data[SND_BUFF_CAP];
};

// this 0-initializes send buffer configuration
struct send_buff snd_buff;

#define can_send() (snd_buff.size > 0 && \
                   (DMA1_Stream6->CR & DMA_SxCR_EN) == 0 && \
                   (DMA1->HISR & DMA_HISR_TCIF6) == 0)

void enqueue(char const* str, size_t const len) {
    snd_buff.data[snd_buff.end] = (struct string){.ptr = str, .len = len};
    snd_buff.end = (snd_buff.end + 1) % SND_BUFF_CAP;
    if (snd_buff.size < SND_BUFF_CAP) {
        ++snd_buff.size;
    } else {
        snd_buff.beg = (snd_buff.beg + 1) % SND_BUFF_CAP;
    }
}

void try_send() {
    if (!can_send()) {
        return;
    }

    register struct string str = snd_buff.data[snd_buff.beg];

    // inicjacja wysyłania
    DMA1_Stream6->M0AR = (uint32_t)(str.ptr);
    DMA1_Stream6->NDTR = str.len;
    DMA1_Stream6->CR |= DMA_SxCR_EN;

    snd_buff.beg = (snd_buff.beg + 1) % SND_BUFF_CAP;
    --snd_buff.size;
}

#define debug(string) \
    do { \
        enqueue(string "\r\n", sizeof(string "\r\n") - 1); \
        try_send(); \
    } while(false)
#else
#define debug(string)
#endif

/* PLAYBACK ROUTINES */

/* Configures PWM timer to constantly output given sample. */
static void emit_sample(uint8_t sample) {

    // Temporarily disable PWM timer in order to reconfigure it for the next sample
    TIM_PWM->CR1 &= ~TIM_CR1_CEN;

    // setup PWM timer
    TIM_PWM->CNT = 0;
    TIM_PWM->CCR1 = sample * volume_factor / 10;
    TIM_PWM->EGR = TIM_EGR_UG;

    // Włączamy licznik w trybie zliczania w górę.
    TIM_PWM->CR1 = TIM_CR1_CEN;
}

/* With each call, plays next sample of the current song. Does so in a cyclic manner. */
static void playback_loop() {
    size_t const num_samples = PCM->data_len / PCM->bytes_per_sample;

    sample_idx %= num_samples;
    emit_sample(PCM->data[sample_idx]);
    ++sample_idx;
}

/* Reconfigures sampling timer to fire its interrupt according to the given sample rate. */
static void reconfigure_sampling_timer(size_t sample_rate) {
    // This results in the best approximation of the given sampling rate (in Hz)
    TIM3->CR1 |= TIM_CR1_UDIS;
    TIM_SAMPLE->ARR = STM_CLOCKING_HZ / sample_rate;
    TIM_SAMPLE->EGR = TIM_EGR_UG;
    TIM3->CR1 &= ~TIM_CR1_UDIS;
}

volatile bool playback_is_on = false;

static void playback_on() {
    playback_is_on = true;
    TIM_PWM->CR1 |= TIM_CR1_CEN;
    TIM_SAMPLE->CR1 |= TIM_CR1_CEN;
}

static void playback_off() {
    playback_is_on = false;
    TIM_SAMPLE->CR1 &= ~TIM_CR1_CEN;
    TIM_PWM->CR1 &= ~TIM_CR1_CEN;
}

static void toggle_playback() {
    if (playback_is_on)
        playback_off();
    else
        playback_on();
}

static void volume_up() {
    if (volume_factor < VOLUME_DIVISOR) {
        ++volume_factor;
    } else {
        debug("Volume has already reached MAX.");
    }
}

static void volume_down() {
    if (volume_factor > 1) {
        --volume_factor;
    } else {
        debug("Volume has already reached MIN.");
    }
}

static void next_song() {
    change_PCM(1);
    reconfigure_sampling_timer(PCM->sample_rate);
    sample_idx = 0;
}

static void prev_song() {
    change_PCM(-1);
    reconfigure_sampling_timer(PCM->sample_rate);
    sample_idx = 0;
}


/* USER INPUT HANDLERS */

typedef enum {NONE, ACTION, LEFT, RIGHT, UP, DOWN} pressed_button_t;

static bool need_repetitions(pressed_button_t button) {
    return button == UP || button == DOWN;
}

static pressed_button_t get_pressed() {
    if (JOYSTICK_ACTION_is_pressed())
        return ACTION;
    else if (JOYSTICK_LEFT_is_pressed())
        return LEFT;
    else if (JOYSTICK_RIGHT_is_pressed())
        return RIGHT;
    else if (JOYSTICK_UP_is_pressed())
        return UP;
    else if (JOYSTICK_DOWN_is_pressed())
        return DOWN;
    else
        return NONE;
}

static void(*get_action(pressed_button_t button))(void) {
    switch (button) {
        case ACTION:
            return toggle_playback;
        case LEFT:
            return prev_song;
        case RIGHT:
            return next_song;
        case UP:
            return volume_up;
        case DOWN:
            return volume_down;
        default:
            return 0; // should never happen
    }
}

volatile irq_level_t level;

static void schedule_delay() {
    debug("Delay scheduled.");
    level = IRQprotect(LOW_IRQ_PRIO);
    TIM_BOUNCE->CNT = 0;
    TIM_BOUNCE->CR1 = TIM_CR1_CEN;
    // We shall mask every button interrupt - this will simply make things simpler.
    // So we mask before scheduling Delay, and unmask in Delay interrupt handler.
}

struct input_state {
    enum {IDLE, BEFORE_ACTION, AFTER_ACTION} state;
    pressed_button_t button;
    bool with_repetitions;
    size_t counter;
};

/* Responds to the event of any joystick button being pushed.
 * It is assumed that only one joystick button may be pushed at a time. */
static void joystick_operation() {
    debug("\r\nJoystick operation.");
    EXTI->PR = 0xFFFFFFFF;
    static size_t const timeout = REPEAT_DELAY_MS / BOUNCING_DELAY_MS;
    static struct input_state config = {.button = NONE, .state = IDLE};

    pressed_button_t pressed_button = get_pressed();
    if (pressed_button == NONE) {
        debug("NONE button pressed");
        config.button = NONE;
        config.state = IDLE;
    } else { // some button is pressed
        if (pressed_button == config.button) { // advance to the next state
            switch (config.state) {
                case IDLE:
                    // should never happen!
                    break;
                case BEFORE_ACTION:
                    debug("Action undertaken! (BEFORE ACTION wait completed)");
                    get_action(pressed_button)();
                    config.state = AFTER_ACTION;
                    config.counter = 0;
                    break;
                case AFTER_ACTION:
                    debug("AFTER ACTION");
                    if (config.with_repetitions) {
                        ++config.counter;
                        if (config.counter >= timeout) { // another repetition takes place
                            config.state = BEFORE_ACTION;
                        }
                    } else {
                        // stay here in order to avoid repetitions
                    }
                    break;
            }
        } else { // abandon previous state, regarding another button. Valid based on the aforementioned assumption.
            debug("Different button pressed, resetting");
            config.button = pressed_button;
            config.state = BEFORE_ACTION;
            config.with_repetitions = need_repetitions(pressed_button);
        }

        schedule_delay();
    }
}

/* INTERRUPTS CONFIGURATION */

/* After specified sample play time, moves on to the next sample. */
void TIM2_IRQHandler(void) {
    uint32_t it_status = TIM_SAMPLE->SR & TIM_SAMPLE->DIER;
    if (it_status & TIM_SR_UIF) {
        TIM_SAMPLE->SR = ~TIM_SR_UIF;
        playback_loop();
    }
}

void TIM5_IRQHandler(void) {
    debug("TIM_BOUNCE interrupt fired.");
    // stop delay timer
    TIM_BOUNCE->CR1 &= ~TIM_CR1_CEN;
    // unmask button interrupts
    IRQunprotect(level);

    uint32_t it_status = TIM_BOUNCE->SR & TIM_BOUNCE->DIER;
    if (it_status & TIM_SR_UIF) {
        TIM_BOUNCE->SR = ~TIM_SR_UIF;
        joystick_operation();
    }
}

/* Joystick interrupts handlers */

// joystick action
void EXTI15_10_IRQHandler(void) {
    joystick_operation();
}

// joystick up/down
void EXTI9_5_IRQHandler(void) {
    joystick_operation();
}

// joystick right
void EXTI4_IRQHandler(void) {
    joystick_operation();
}

// joystick left
void EXTI3_IRQHandler(void) {
    joystick_operation();
}

#define configure_button(button, button_group) \
    GPIOinConfigure(button_group ## _GPIO, \
                    button ## _PIN, \
                    GPIO_PuPd_NOPULL, \
                    EXTI_Mode_Interrupt, \
                    EXTI_Trigger_Falling); \
    EXTI->PR = (1 << button ## _PIN)

int main() {
    // CRUCIAL for proper operation
    init_PCM_arr();

    // GPIO clocking turn-on
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;

    // SYSCFG clocking turn-on
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    /* TIMERS */
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN | RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM5EN;

    /* PWM timer (TIM3) */
    // Configures PC6 as output of TIM3.
    GPIOafConfigure(GPIOC, 6, GPIO_OType_PP,
                    GPIO_Low_Speed,
                    GPIO_PuPd_NOPULL,
                    GPIO_AF_TIM3);

    // Konfigurujemy linię wyjściową OC1REF w trybie PWM 1;
    // rejestr TIM_PWM->CCR1 jest buforowany.
    TIM_PWM->CCMR1 = TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE;

    // Podłączamy linie wyjściowe do wyprowadzeń, stan aktywny to stan wysoki.
    TIM_PWM->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E;

    TIM_PWM->PSC = 0; // Prescaler won't be needed.
    TIM_PWM->ARR = UINT8_MAX - 1; // Adjusted for 8-bit sampling.


    /* Sampling timer (TIM2) */
    TIM_SAMPLE->PSC = 0; // Prescaler won't be needed.

    // Ustawiamy przerwanie uaktualnienia
    TIM_SAMPLE->SR = ~TIM_SR_UIF;
    TIM_SAMPLE->DIER = TIM_DIER_UIE;
    NVIC_EnableIRQ(TIM2_IRQn);

    reconfigure_sampling_timer(PCM->sample_rate);


    /* Bouncing-mitigation timer (TIM5) */
    TIM_BOUNCE->PSC = 0; // Prescaler won't be needed.
    TIM_BOUNCE->ARR = BOUNCING_DELAY_MS * STM_CLOCKING_MHZ * 1000;
    TIM_BOUNCE->EGR = TIM_EGR_UG;

    // Ustawiamy przerwanie uaktualnienia
    TIM_BOUNCE->SR = ~TIM_SR_UIF;
    TIM_BOUNCE->DIER = TIM_DIER_UIE;
    NVIC_EnableIRQ(TIM5_IRQn);


    /* BUTTONS */

    configure_button(JOYSTICK_ACTION, JOYSTICK);
    configure_button(JOYSTICK_DOWN, JOYSTICK);
    configure_button(JOYSTICK_UP, JOYSTICK);
    configure_button(JOYSTICK_RIGHT, JOYSTICK);
    configure_button(JOYSTICK_LEFT, JOYSTICK);

    IRQsetPriority(EXTI3_IRQn, LOW_IRQ_PRIO, LOW_IRQ_SUBPRIO);
    IRQsetPriority(EXTI4_IRQn, LOW_IRQ_PRIO, LOW_IRQ_SUBPRIO);
    IRQsetPriority(EXTI9_5_IRQn, LOW_IRQ_PRIO, LOW_IRQ_SUBPRIO);
    IRQsetPriority(EXTI15_10_IRQn, LOW_IRQ_PRIO, LOW_IRQ_SUBPRIO);

    NVIC_EnableIRQ(EXTI3_IRQn);
    NVIC_EnableIRQ(EXTI4_IRQn);
    NVIC_EnableIRQ(EXTI9_5_IRQn);
    NVIC_EnableIRQ(EXTI15_10_IRQn);

    if (DEBUG) {
        /* USART config */
        RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

        GPIOafConfigure(GPIOA,
                        2,
                        GPIO_OType_PP,
                        GPIO_Fast_Speed,
                        GPIO_PuPd_NOPULL,
                        GPIO_AF_USART2);

        USART2->CR1 = USART_Mode_Tx | USART_WordLength_8b | USART_Parity_No;
        USART2->CR2 = USART_StopBits_1;
        USART2->CR3 = USART_CR3_DMAT;
        USART2->BRR = (PCLK1_HZ + (BAUD_RATE / 2U)) / BAUD_RATE;
        USART2->CR1 |= USART_Enable;


        /* DMA config */
        RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

        DMA1_Stream6->CR = 4U << 25
                           | DMA_SxCR_PL_1
                           | DMA_SxCR_MINC
                           | DMA_SxCR_DIR_0
                           | DMA_SxCR_TCIE;

        DMA1_Stream6->PAR = (uint32_t) &USART2->DR;

        DMA1->HIFCR = DMA_HIFCR_CTCIF6; // interrupt markers cleanup
        NVIC_EnableIRQ(DMA1_Stream6_IRQn); // enable DMA interrupt

        debug("Initialization finished.");
    }
}
