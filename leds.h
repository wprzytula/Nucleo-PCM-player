#include <stm32.h>
#include <gpio.h>

#define RED_LED_GPIO GPIOA
#define GREEN_LED_GPIO GPIOA
#define BLUE_LED_GPIO GPIOB
#define GREEN2_LED_GPIO GPIOA

#define RED_LED_PIN 6
#define GREEN_LED_PIN 7
#define BLUE_LED_PIN 0
#define GREEN2_LED_PIN 5

#define RedLEDon() \
    RED_LED_GPIO->BSRR = 1 << (RED_LED_PIN + 16)
#define RedLEDoff() \
    RED_LED_GPIO->BSRR = 1 << RED_LED_PIN
#define RedLEDtoggle() \
    do { \
        if ((RED_LED_GPIO->ODR >> RED_LED_PIN) & 1) RedLEDon(); else RedLEDoff(); \
    } while(0)
#define GreenLEDon() \
    GREEN_LED_GPIO->BSRR = 1 << (GREEN_LED_PIN + 16)
#define GreenLEDoff() \
    GREEN_LED_GPIO->BSRR = 1 << GREEN_LED_PIN
#define GreenLEDtoggle() \
    do { \
        if ((GREEN_LED_GPIO->ODR >> GREEN_LED_PIN) & 1) GreenLEDon(); else GreenLEDoff(); \
    } while(0)
#define BlueLEDon() \
    BLUE_LED_GPIO->BSRR = 1 << (BLUE_LED_PIN + 16)
#define BlueLEDoff() \
    BLUE_LED_GPIO->BSRR = 1 << BLUE_LED_PIN
#define BlueLEDtoggle() \
    do { \
        if ((BLUE_LED_GPIO->ODR >> BLUE_LED_PIN) & 1) BlueLEDon(); else BlueLEDoff(); \
    } while(0)
#define Green2LEDon() \
    GREEN2_LED_GPIO->BSRR = 1 << GREEN2_LED_PIN
#define Green2LEDoff() \
    GREEN2_LED_GPIO->BSRR = 1 << (GREEN2_LED_PIN + 16)
#define Green2LEDtoggle() \
    do { \
        if (!((GREEN2_LED_GPIO->ODR >> GREEN2_LED_PIN) & 1)) Green2LEDon(); else Green2LEDoff(); \
    } while(0)
