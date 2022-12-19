#include "hal/gpio_types.h"
#include "peripherals/hardwareprofile.h"
#include "peripherals/digout.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "driver/gpio.h"
#include "digout.h"


void digout_init(void) {
#define GPIO_OUTPUT_PIN_SEL ((1ULL << RELE1) | (1ULL << RELE2) | (1ULL << RELE3) | (1ULL << RELE4))

    gpio_config_t io_conf = {0};
    io_conf.intr_type     = GPIO_INTR_DISABLE;
    io_conf.mode          = GPIO_MODE_INPUT_OUTPUT;
    io_conf.pin_bit_mask  = GPIO_OUTPUT_PIN_SEL;
    io_conf.pull_down_en  = 0;
    io_conf.pull_up_en    = 0;
    gpio_config(&io_conf);
}


void digout_rele_update(digout_t rele, int val) {
    const gpio_num_t gpios[] = {RELE1, RELE2, RELE3, RELE4};
    val                      = val > 0;
    gpio_set_level(gpios[rele], val);
}


void digout_rele_clear_all(void) {
    gpio_set_level(RELE1, 0);
    gpio_set_level(RELE2, 0);
    gpio_set_level(RELE3, 0);
    gpio_set_level(RELE4, 0);
}


uint8_t digout_get(void) {
    uint8_t res = 0;
    res |= gpio_get_level(RELE1);
    res |= (gpio_get_level(RELE2)) << 1;
    res |= (gpio_get_level(RELE3)) << 2;
    res |= (gpio_get_level(RELE4)) << 3;
    return res;
}
