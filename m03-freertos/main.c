#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <FreeRTOS.h>
#include <task.h>

#define LED_PORT  GPIOA
#define LED_PIN   GPIO5

static void gpio_setup(void)
{
    rcc_periph_clock_enable(RCC_GPIOA);
    gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);
}

/* TODO: LED를 500ms 주기로 토글하는 태스크 함수 작성 */
/* 힌트: 태스크 함수 시그니처는 void task_name(void *pvParameters) */
void led_task(void *pvParameters){
    while (1)
    {
        /* code */
        gpio_toggle(LED_PORT, LED_PIN);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
/* 힌트: vTaskDelay(pdMS_TO_TICKS(500)) 으로 딜레이 */

int main(void)
{
    gpio_setup();

    /* TODO: xTaskCreate()로 LED 태스크 생성 */
    xTaskCreate(led_task, "LED", 128, NULL, 1, NULL);
    /* 힌트: 스택 크기 128, 우선순위 1 */

    /* TODO: vTaskStartScheduler()로 스케줄러 시작 */
    vTaskStartScheduler();


    while (1);
    return 0;
}


