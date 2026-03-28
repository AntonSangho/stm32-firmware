#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

void gpio_setup(){
    rcc_periph_clock_enable(RCC_GPIOA);
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);
}

int main(void) {
    gpio_setup();
    while (1) {
        gpio_toggle(GPIOA, GPIO5);
        for (volatile int i = 0; i < 1000000; i++);
    }

}




