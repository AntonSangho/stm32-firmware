#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>

extern void xPortSysTickHandler(void);
extern void xPortPendSVHandler(void);
extern void vPortSVCHandler(void);

/* libopencm3 ↔ FreeRTOS 핸들러 브릿지 */
void sys_tick_handler(void) { xPortSysTickHandler(); }
void __attribute__((naked)) pend_sv_handler(void)  { __asm volatile("b xPortPendSVHandler"); }
void __attribute__((naked)) sv_call_handler(void)  { __asm volatile("b vPortSVCHandler");    }

int _write(int fd, char *buf, int len)
{
    for (int i = 0; i < len; i++) {
        usart_send_blocking(USART2, buf[i]);
    }
    return len;
}

static void usart_setup(void)
{
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_USART2);

    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);
    gpio_set_af(GPIOA, GPIO_AF7, GPIO2);

    usart_set_baudrate(USART2, 115200);
    usart_set_databits(USART2, 8);
    usart_set_stopbits(USART2, USART_STOPBITS_1);
    usart_set_parity(USART2, USART_PARITY_NONE);
    usart_set_mode(USART2, USART_MODE_TX);
    usart_enable(USART2);
}

static void uart_task(void *pvParameters)
{
    (void)pvParameters;
    while (1) {
        printf("hello world\r\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main(void)
{
    usart_setup();

    xTaskCreate(uart_task, "UART", 256, NULL, 1, NULL);
    vTaskStartScheduler();

    while (1);
}
