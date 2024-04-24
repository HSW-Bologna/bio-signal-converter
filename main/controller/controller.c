#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "controller.h"
#include "model/model.h"
#include "peripherals/storage.h"
#include "peripherals/serial.h"
#include "peripherals/digin.h"
#include "peripherals/digout.h"
#include "peripherals/hardwareprofile.h"
#include "esp_log.h"


static void pulse_end_timer(TimerHandle_t timer);


static const char   *TAG = "Controller";
static TimerHandle_t timers[NUM_DIGOUTS];
static const int     inverted[NUM_DIGOUTS] = {0, 0, 0, 0};


void controller_init(model_t *pmodel) {
    (void)TAG;

    static StaticTimer_t static_timers[NUM_DIGOUTS];
    for (digout_t out = DIGOUT_RELE1; out < NUM_DIGOUTS; out++) {
        timers[out] =
            xTimerCreateStatic("Rele timer", 1, pdFALSE, (void *)(uintptr_t)out, pulse_end_timer, &static_timers[out]);

        if (inverted[out]) {
            digout_rele_update(out, 1);
        } else {
            digout_rele_update(out, 0);
        }
    }
}


void controller_start_pulse(model_t *pmodel, digin_t in) {
    const digout_t outputs[] = {DIGOUT_RELE1, DIGOUT_RELE2, DIGOUT_RELE3, DIGOUT_RELE4};
    digout_t       out       = outputs[in];

    if (pmodel->pulse_duration == 0) {
        return;
    }

    xTimerChangePeriod(timers[out], pmodel->pulse_duration, portMAX_DELAY);
    if (inverted[in]) {
        digout_rele_update(out, 0);
    } else {
        digout_rele_update(out, 1);
    }
    xTimerStart(timers[out], portMAX_DELAY);
}


static void pulse_end_timer(TimerHandle_t timer) {
    digout_t out = (digout_t)(uintptr_t)pvTimerGetTimerID(timer);
    if (inverted[out]) {
        digout_rele_update(out, 1);
    } else {
        digout_rele_update(out, 0);
    }
}
