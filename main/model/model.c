#include <assert.h>
#include "model.h"

void model_init(model_t *pmodel, uint32_t pulse_duration) {
    assert(pmodel != NULL);
    pmodel->pulse_duration = pulse_duration;
}