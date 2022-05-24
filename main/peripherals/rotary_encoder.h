#ifndef ROTARY_ENCODER_H_INCLUDED
#define ROTARY_ENCODER_H_INCLUDED


#include <stdint.h>


void    rotary_encoder_init(void);
uint8_t rotary_encoder_read(void);
uint8_t rotary_encoder_stable_read(void);


#endif