#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#define LED_PORT   GPIOA
#define LED_PIN    GPIO5
#define BTN_PORT   GPIOC
#define BTN_PIN    GPIO13


static void gpio_setup(void)
{
    /* TODO: GPIOA 클럭 활성화 */
    rcc_periph_clock_enable(RCC_GPIOA);   
    /* TODO: GPIOC 클럭 활성화 */
    rcc_periph_clock_enable(RCC_GPIOC);
    /* TODO: PA5를 출력으로 설정 */
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);
    /* TODO: PC13을 입력으로 설정, Pull-up 적용 */
    gpio_mode_setup(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO13);
}

int main(void)
{
    gpio_setup();

    while (1) {
        /* TODO: 버튼이 눌리면(LOW) LED ON, 아니면 LED OFF */
        /* 힌트: gpio_get() 반환값이 0이면 버튼 눌림 */
        if (gpio_get(BTN_PORT, BTN_PIN) == 0){
            gpio_set(LED_PORT, LED_PIN);
        }
        else {
            gpio_clear(LED_PORT, LED_PIN);
        }
    }

    return 0;
}

