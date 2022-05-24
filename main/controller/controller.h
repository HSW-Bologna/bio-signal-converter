#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

#include "model/model.h"
#include "peripherals/digin.h"


void controller_init(model_t *model);
void controller_manage_packet(model_t *pmodel);
void controller_start_pulse(model_t *pmodel, digin_t in);


#endif