#include <stm32.h>
#include <gpio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <irq.h>

#include "leds.h"
#include "usart.h"
#include "buttons.h"

struct string {
    char const *ptr;
    size_t len;
}; 

/* buffers */
#define SND_BUFF_CAP 128

struct string snd_buff[SND_BUFF_CAP];

struct buff_config {
    size_t beg, end, size;
};

// this 0-initializes send buffer configuration
struct buff_config snd_buff_c;

#define can_send() (snd_buff_c.size > 0 && \
                   (DMA1_Stream6->CR & DMA_SxCR_EN) == 0 && \
                   (DMA1->HISR & DMA_HISR_TCIF6) == 0)

bool at_button_state, user_button_state, joystick_left_state, joystick_right_state,
    joystick_up_state, joystick_down_state, joystick_action_state;

void enqueue(char const* str, size_t const len) {
    snd_buff[snd_buff_c.end] = (struct string){.ptr = str, .len = len};
    snd_buff_c.end = (snd_buff_c.end + 1) % SND_BUFF_CAP;
    if (snd_buff_c.size < SND_BUFF_CAP) {
        ++snd_buff_c.size;
    } else {
        snd_buff_c.beg = (snd_buff_c.beg + 1) % SND_BUFF_CAP;
    }
}

void try_send() {
    if (!can_send()) {
        return;
    }
    
    register struct string str = snd_buff[snd_buff_c.beg];
    
    // inicjacja wysyłania
    DMA1_Stream6->M0AR = (uint32_t)(str.ptr);
    DMA1_Stream6->NDTR = str.len;
    DMA1_Stream6->CR |= DMA_SxCR_EN;
    
    snd_buff_c.beg = (snd_buff_c.beg + 1) % SND_BUFF_CAP;
    --snd_buff_c.size;
}

#define check_button(button_state, button, NAME) \
    do { \
        if ((button_state) != button ## _is_pressed()) { \
            if (!(button_state)) { \
                enqueue(NAME PRESSED, sizeof(NAME PRESSED)); \
            } else { \
                enqueue(NAME RELEASED, sizeof(NAME RELEASED)); \
            } \
            (button_state) = !(button_state); \
            try_send(); \
        } \
    } while(0)

#define PRESSED " PRESSED\r\n"
#define RELEASED " RELEASED\r\n"

void notify_button_state_updates() {
    EXTI->PR = 0xFFFFFFFF;
    check_button(at_button_state, AT_BUTTON, "MODE");
    check_button(user_button_state, USER_BUTTON, "USER");
    check_button(joystick_action_state, JOYSTICK_ACTION, "FIRE");
    check_button(joystick_up_state, JOYSTICK_UP, "UP");
    check_button(joystick_down_state, JOYSTICK_DOWN, "DOWN");
    check_button(joystick_left_state, JOYSTICK_LEFT, "LEFT");
    check_button(joystick_right_state, JOYSTICK_RIGHT, "RIGHT");
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

void DMA1_Stream6_IRQHandler() {
    /* Odczytaj zgłoszone przerwania DMA1. */
    register uint32_t isr = DMA1->HISR;
    if (isr & DMA_HISR_TCIF6) {
        /* Obsłuż zakończenie transferu w strumieniu 6. */
        DMA1->HIFCR = DMA_HIFCR_CTCIF6;
        /* Jeśli jest coś do wysłania, wystartuj kolejną transmisję. */
        try_send();
    }
}

#define configure_button(button, button_group) \
    GPIOinConfigure(button_group ## _GPIO, \
                    button ## _PIN, \
                    GPIO_PuPd_NOPULL, \
                    EXTI_Mode_Interrupt, \
                    EXTI_Trigger_Rising_Falling); \
    EXTI->PR = (1 << button ## _PIN);

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
    
    DMA1_Stream6->PAR = (uint32_t)&USART2->DR;
    
    DMA1->HIFCR = DMA_HIFCR_CTCIF6; // interrupt markers cleanup
    NVIC_EnableIRQ(DMA1_Stream6_IRQn); // enable DMA interrupt
}
