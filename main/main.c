#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_task_wdt.h"

#include "model/model.h"
#include "controller/controller.h"
#include "peripherals/digin.h"
#include "peripherals/digout.h"
#include "peripherals/hardwareprofile.h"
#include "peripherals/serial.h"
#include "peripherals/heartbit.h"
#include "peripherals/rotary_encoder.h"


static const char *TAG = "Main";


void app_main(void) {
    const uint32_t pulses[] = {10, 50, 80, 100, 300, 400, 500, 700, 800, 900};

    model_t model;

    heartbit_init(2000UL);
    rotary_encoder_init();

    uint8_t configuration = rotary_encoder_stable_read();
    ESP_LOGI(TAG, "Encoder: 0x%02X", configuration);

    model_init(&model, pulses[configuration]);
    controller_init(&model);
    digout_init();
    digin_init();

    ESP_LOGI(TAG, "Begin main loop");
    esp_task_wdt_add(NULL);
    for (;;) {
        esp_task_wdt_reset();

        unsigned int map = digin_take_reading();
        for (digin_t in = DIGIN_1; in < NUM_DIGIN; in++) {
            if (((map & (1 << in)) > 0) && digin_get(in)) {
                // Send the configured pulse
                controller_start_pulse(&model, in);
            }
        }

        vTaskDelay(pdMS_TO_TICKS(5));
    }
}
