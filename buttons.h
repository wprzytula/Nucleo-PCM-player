#ifndef BUTTONS_H
#define BUTTONS_H

#include <stm32.h>
#include <gpio.h>

#define AT_BUTTON_GPIO GPIOA // active state: high (1)
#define USER_BUTTON_GPIO GPIOC // active state: low (0)
#define JOYSTICK_GPIO GPIOB // active state: low (0)

#define AT_BUTTON_PIN 0
#define USER_BUTTON_PIN 13
#define JOYSTICK_UP_PIN 5
#define JOYSTICK_RIGHT_PIN 4
#define JOYSTICK_DOWN_PIN 6
#define JOYSTICK_LEFT_PIN 3
#define JOYSTICK_ACTION_PIN 10

#define AT_BUTTON_SYSCFG_IDX 0
#define USER_BUTTON_SYSCFG_IDX 3
#define JOYSTICK_UP_SYSCFG_IDX 1
#define JOYSTICK_RIGHT_SYSCFG_IDX 1
#define JOYSTICK_DOWN_SYSCFG_IDX 1
#define JOYSTICK_LEFT_SYSCFG_IDX 0
#define JOYSTICK_ACTION_SYSCFG_IDX 2

#define AT_BUTTON_SYSCFG_EXTICR SYSCFG_EXTICR1_EXTI0_PA
#define USER_BUTTON_SYSCFG_EXTICR SYSCFG_EXTICR4_EXTI13_PC
#define JOYSTICK_UP_SYSCFG_EXTICR SYSCFG_EXTICR2_EXTI5_PB
#define JOYSTICK_RIGHT_SYSCFG_EXTICR SYSCFG_EXTICR2_EXTI4_PB
#define JOYSTICK_DOWN_SYSCFG_EXTICR SYSCFG_EXTICR2_EXTI6_PB
#define JOYSTICK_LEFT_SYSCFG_EXTICR SYSCFG_EXTICR1_EXTI3_PB
#define JOYSTICK_ACTION_SYSCFG_EXTICR SYSCFG_EXTICR3_EXTI10_PB

#define AT_BUTTON_is_pressed() \
    ((AT_BUTTON_GPIO->IDR >> AT_BUTTON_PIN) & 1)
#define USER_BUTTON_is_pressed() \
    (!((USER_BUTTON_GPIO->IDR >> USER_BUTTON_PIN) & 1))
#define JOYSTICK_UP_is_pressed() \
    (!((JOYSTICK_GPIO->IDR >> JOYSTICK_UP_PIN) & 1))
#define JOYSTICK_DOWN_is_pressed() \
    (!((JOYSTICK_GPIO->IDR >> JOYSTICK_DOWN_PIN) & 1))
#define JOYSTICK_LEFT_is_pressed() \
    (!((JOYSTICK_GPIO->IDR >> JOYSTICK_LEFT_PIN) & 1))
#define JOYSTICK_RIGHT_is_pressed() \
    (!((JOYSTICK_GPIO->IDR >> JOYSTICK_RIGHT_PIN) & 1))
#define JOYSTICK_ACTION_is_pressed() \
    (!((JOYSTICK_GPIO->IDR >> JOYSTICK_ACTION_PIN) & 1))

#endif
