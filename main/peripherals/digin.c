#include "peripherals/hardwareprofile.h"
#include "peripherals/digin.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "gel/debounce/debounce.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "freertos/timers.h"

static const char *TAG = "Digin";


static debounce_filter_t filter = {0};


void digin_init(void) {
#define GPIO_INPUT_PIN_SEL ((1ULL << IN1) | (1ULL << IN2) | (1ULL << IN3) | (1ULL << IN4))
    (void)TAG;

    gpio_config_t io_conf = {0};
    io_conf.intr_type     = GPIO_INTR_DISABLE;
    io_conf.pin_bit_mask  = GPIO_INPUT_PIN_SEL;
    io_conf.mode          = GPIO_MODE_INPUT;
    io_conf.pull_down_en  = 0;
    io_conf.pull_up_en    = 0;
    gpio_config(&io_conf);

    debounce_filter_init(&filter);
}


int digin_get(digin_t digin) {
    return debounce_read(&filter, digin);
}


int digin_take_reading(void) {
    unsigned int input = 0;
    input |= !gpio_get_level(IN1);
    input |= (!gpio_get_level(IN2)) << 1;
    input |= (!gpio_get_level(IN3)) << 2;
    input |= (!gpio_get_level(IN4)) << 3;
    return debounce_filter(&filter, input, 5);
}


unsigned int digin_get_inputs(void) {
    return debounce_value(&filter);
}
