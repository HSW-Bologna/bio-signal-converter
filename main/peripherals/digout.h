#ifndef DIGOUT_H_INCLUDED
#define DIGOUT_H_INCLUDED

#include "hal/gpio_types.h"
#include <string.h>
#include <stdint.h>


typedef enum {
    DIGOUT_RELE1 = 0,
    DIGOUT_RELE2,
    DIGOUT_RELE3,
    DIGOUT_RELE4,
    NUM_DIGOUTS,
} digout_t;


void    digout_init(void);
void    digout_rele_update(digout_t rele, int val);
void    digout_rele_clear_all(void);
uint8_t digout_get(void);

// #define toggle_digout_port(rele_t rele)  update_digout_port(out, !get_digout_port(out))
#define set_digout(rele)   rele_update(rele, 1)
#define clear_digout(rele) rele_update(rele, 0)

#endif