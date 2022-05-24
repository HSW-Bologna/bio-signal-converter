#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include <stdint.h>

typedef struct {
    uint32_t pulse_duration;
} model_t;

void model_init(model_t *model, uint32_t pulse_duration);

#endif