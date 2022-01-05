#include <stm32.h>
#include <gpio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "buttons.h"
#include "pcm.h"

bool at_button_state, user_button_state, joystick_left_state, joystick_right_state,
    joystick_up_state, joystick_down_state, joystick_action_state;

#define TIM_SAMPLE TIM2
#define TIM_PWM TIM3
#define STM_CLOCKING 16000000 // 16 MHz

size_t sample_idx;

void playback_on() {
    TIM_PWM->CR1 |= TIM_CR1_CEN;
    TIM_SAMPLE->CR1 |= TIM_CR1_CEN;
}

void playback_off() {
    TIM_SAMPLE->CR1 &= ~TIM_CR1_CEN;
    TIM_PWM->CR1 &= ~TIM_CR1_CEN;
}

void notify_button_state_updates() {
    EXTI->PR = 0xFFFFFFFF;

    if (joystick_action_state != JOYSTICK_ACTION_is_pressed()) {
        if (JOYSTICK_ACTION_is_pressed()) {
            playback_on();
        } else {
            playback_off();
        }
        (joystick_action_state) = !(joystick_action_state);
    }
}

void reconfigure_sampling_timer(size_t sample_rate) {
    // This results in the best approximation of the given sampling rate (in Hz)
    TIM3->CR1 |= TIM_CR1_UDIS;
    TIM_SAMPLE->ARR = STM_CLOCKING / sample_rate;
    TIM_SAMPLE->EGR = TIM_EGR_UG;
    TIM3->CR1 &= ~TIM_CR1_UDIS;
}

void emit_sample(uint8_t sample) {

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

// Z każdym wywołaniem cyklicznie odtwarza kolejną próbkę bieżącego utworu.
void playback_loop() {
    size_t const num_samples = PCM->data_len / PCM->bytes_per_sample;

    sample_idx %= num_samples;
    emit_sample(PCM->data[sample_idx]);
    ++sample_idx;
}

// Przerwanie, którego rolą jest przestawienie odtwarzanej próbki na kolejną.
void TIM2_IRQHandler(void) {
    uint32_t it_status = TIM_SAMPLE->SR & TIM_SAMPLE->DIER;
    if (it_status & TIM_SR_UIF) {
        TIM_SAMPLE->SR = ~TIM_SR_UIF;
        playback_loop();
    }
}

void EXTI15_10_IRQHandler(void) {
    notify_button_state_updates();
}

void EXTI9_5_IRQHandler(void) {
    notify_button_state_updates();
}

void EXTI4_IRQHandler(void) {
    notify_button_state_updates();
}

void EXTI3_IRQHandler(void) {
    notify_button_state_updates();
}

void EXTI0_IRQHandler(void) {
    notify_button_state_updates();
}

#define configure_button(button, button_group) \
    GPIOinConfigure(button_group ## _GPIO, \
                    button ## _PIN, \
                    GPIO_PuPd_NOPULL, \
                    EXTI_Mode_Interrupt, \
                    EXTI_Trigger_Rising_Falling); \
    EXTI->PR = (1 << button ## _PIN)

int main() {
    // GPIO clocking turn-on
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;

    // SYSCFG clocking turn-on
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    
    // configure buttons
    configure_button(AT_BUTTON, AT_BUTTON);
    configure_button(USER_BUTTON, USER_BUTTON);
    configure_button(JOYSTICK_ACTION, JOYSTICK);
    configure_button(JOYSTICK_DOWN, JOYSTICK);
    configure_button(JOYSTICK_UP, JOYSTICK);
    configure_button(JOYSTICK_RIGHT, JOYSTICK);
    configure_button(JOYSTICK_LEFT, JOYSTICK);
    
    // enable button interrupts
    NVIC_EnableIRQ(EXTI15_10_IRQn);
    NVIC_EnableIRQ(EXTI9_5_IRQn);
    NVIC_EnableIRQ(EXTI0_IRQn);
    NVIC_EnableIRQ(EXTI3_IRQn);
    NVIC_EnableIRQ(EXTI4_IRQn);

    /* TIMERS */
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN | RCC_APB1ENR_TIM2EN;

    /* PWM timer (TIM3) */
    // Konfiguracja wyprowadzenia PC6 jako wyjście licznika TIM3.
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

    // Włączamy licznik w trybie zliczania w górę.
    TIM_SAMPLE->CR1 = TIM_CR1_CEN;
}
