#include <stm32.h>
#include <gpio.h>

int main() {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    GPIOafConfigure(GPIOA, 6, GPIO_OType_PP,
                    GPIO_Low_Speed,
                    GPIO_PuPd_NOPULL, GPIO_AF_TIM3);
    GPIOafConfigure(GPIOA, 7, GPIO_OType_PP,
                    GPIO_Low_Speed,
                    GPIO_PuPd_NOPULL, GPIO_AF_TIM3);
    TIM3->PSC = 63999;
    TIM3->ARR = 749;
    TIM3->EGR = TIM_EGR_UG;
    TIM3->CCR1 = 249;
    TIM3->CCR2 = 499;

// Licznik będzie zliczał w górę; konfigurujemy linię wyjściową
// OC1REF w trybie PWM 1, a linię OC2REF – w trybie PWM 2;
// rejestry TIM3->CCR1 i TIM3->CCR2 są buforowane
    TIM3->CCMR1 =
            TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 |
            TIM_CCMR1_OC1PE |
            TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 |
            TIM_CCMR1_OC2M_0 | TIM_CCMR1_OC2PE;
// Podłączamy linie wyjściowe do wyprowadzeń, stan aktywny to
// stan niski, bo diodę włączamy stanem niskim
    TIM3->CCER = TIM_CCER_CC1E | TIM_CCER_CC1P |
                 TIM_CCER_CC2E | TIM_CCER_CC2P;
// Włączamy licznik w trybie zliczania w górę z buforowaniem rejestru TIM3->ARR
    TIM3->CR1 = TIM_CR1_ARPE | TIM_CR1_CEN;
}