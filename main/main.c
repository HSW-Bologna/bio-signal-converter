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


static const char *TAG = "Main";


void app_main(void) {
    model_t model;

    model_init(&model);
    controller_init(&model);
    digout_init();
    digin_init();
    serial_init();

    ESP_LOGI(TAG, "Begin main loop");
    esp_task_wdt_add(NULL);
    for (;;) {
        esp_task_wdt_reset();
        controller_manage_packet(&model);
    }
}
