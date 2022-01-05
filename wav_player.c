#include <stm32.h>
#include <gpio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "delay.h"
#include "buttons.h"
#include "pcm.h"

bool at_button_state, user_button_state, joystick_left_state, joystick_right_state,
    joystick_up_state, joystick_down_state, joystick_action_state;

#define TIM_SAMPLE TIM2
#define TIM_PWM TIM3
#define STM_CLOCKING_MHZ 16
#define STM_CLOCKING (1000000 * STM_CLOCKING_MHZ)
#define BOUNCING_DELAY_MS 5 // 5 ms should suffice
#define BOUNCING_T (250 * BOUNCING_DELAY_MS * STM_CLOCKING_MHZ)

size_t sample_idx; // Index of the currently played sample.


/* PLAYBACK ROUTINES */

static void emit_sample(uint8_t sample) {

    // temporarily disable PWM timer in order to reconfigure it for the next sample
    TIM_PWM->CR1 &= ~TIM_CR1_CEN;

    // setup PWM timer

    TIM_PWM->PSC = 0;
    TIM_PWM->ARR = 254; // Rezultat: Proporcjonalne oddanie amplitudy fali.
    TIM_PWM->CCR1 = sample;
    TIM_PWM->EGR = TIM_EGR_UG;

    // Włączamy licznik w trybie zliczania w górę z buforowaniem rejestru TIM_PWM->ARR
    TIM_PWM->CR1 = TIM_CR1_ARPE | TIM_CR1_CEN;
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
    TIM_SAMPLE->ARR = STM_CLOCKING / sample_rate;
    TIM_SAMPLE->EGR = TIM_EGR_UG;
    TIM3->CR1 &= ~TIM_CR1_UDIS;
}

bool playback_is_on = false;

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

#define action_on_pressed(button, action) \
    do { \
        if (button ## _is_pressed()) { \
            Delay(BOUNCING_T); \
            if (button ## _is_pressed()) { \
                action(); \
                while (button ## _is_pressed()) \
                    Delay(BOUNCING_T); \
            } \
        } \
    } while(false)

/* Responds to the event of any joystick button being pushed. */
static void joystick_operation() {
    EXTI->PR = 0xFFFFFFFF;

    action_on_pressed(JOYSTICK_ACTION, toggle_playback);
    action_on_pressed(JOYSTICK_LEFT, prev_song);
    action_on_pressed(JOYSTICK_RIGHT, next_song);
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

/* Joystick interrupts handlers */
void EXTI15_10_IRQHandler(void) {
    joystick_operation();
}

void EXTI9_5_IRQHandler(void) {
    joystick_operation();
}

void EXTI4_IRQHandler(void) {
    joystick_operation();
}

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
    
    // Configure buttons
    configure_button(JOYSTICK_ACTION, JOYSTICK);
    configure_button(JOYSTICK_DOWN, JOYSTICK);
    configure_button(JOYSTICK_UP, JOYSTICK);
    configure_button(JOYSTICK_RIGHT, JOYSTICK);
    configure_button(JOYSTICK_LEFT, JOYSTICK);
    
    // Enable button interrupts
    NVIC_EnableIRQ(EXTI3_IRQn);
    NVIC_EnableIRQ(EXTI4_IRQn);
    NVIC_EnableIRQ(EXTI9_5_IRQn);
    NVIC_EnableIRQ(EXTI15_10_IRQn);


    /* TIMERS */
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN | RCC_APB1ENR_TIM2EN;

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


    /* Sampling timer (TIM2) */
    TIM_SAMPLE->PSC = 0; // Prescaler won't be needed.

    // Ustawiamy przerwanie uaktualnienia
    TIM_SAMPLE->SR = ~TIM_SR_UIF;
    TIM_SAMPLE->DIER = TIM_DIER_UIE;
    NVIC_EnableIRQ(TIM2_IRQn);

    reconfigure_sampling_timer(PCM->sample_rate);

    // OFF by default, since playback still needs to be turned on by pushing joystick action.
    // TIM_SAMPLE->CR1 = TIM_CR1_CEN; 
}
