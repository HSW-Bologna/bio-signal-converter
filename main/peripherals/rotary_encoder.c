#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <driver/gpio.h>
#include "hardwareprofile.h"
#include "rotary_encoder.h"


void rotary_encoder_init(void) {
    gpio_config_t config = {
        .intr_type    = GPIO_INTR_DISABLE,
        .mode         = GPIO_MODE_INPUT,
        .pin_bit_mask = BIT64(HAP_ROT_1) | BIT64(HAP_ROT_2) | BIT64(HAP_ROT_4) | BIT64(HAP_ROT_8),
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&config));
}


uint8_t rotary_encoder_stable_read(void) {
    uint8_t old_read, new_read;

    do {
        old_read = rotary_encoder_read();
        vTaskDelay(pdMS_TO_TICKS(10));
        new_read = rotary_encoder_read();
        vTaskDelay(pdMS_TO_TICKS(10));
    } while (old_read != new_read);

    return new_read;
}


uint8_t rotary_encoder_read(void) {
    return (!gpio_get_level(HAP_ROT_1) << 1) | (!gpio_get_level(HAP_ROT_2) << 0) | (!gpio_get_level(HAP_ROT_4) << 3) |
           (!gpio_get_level(HAP_ROT_8) << 2);
}