#ifndef ENGINE_H
#define ENGINE_H

#include <stdlib.h>
#include <stdio.h>

#include "DLLDefines.h"
#include "design_func.h"
#include "design_resist.h"
#include "structs.h"

// TODO: free library structs function



// Function prototypes
grains_t TREL_EXPORT *trel_grains_init(
    unsigned int amount,    /* E29 */
    float internal_radius,  /* E30 */
    float external_radius,  /* E31 */
    float longitude,        /* E32 */
    float grain_separation  /* E33 */
);
fuel_t TREL_EXPORT *trel_fuel_init(
    float const_burn_rate,  /* E41 */
    float pressure_exponent,/* E42 */
    float density           /* E44 */
);
tubing_t TREL_EXPORT *trel_tubing_init(
    char *material,         /* E16 & E17 */
    float diameter,         /* E13 */
    float thickness,        /* E14 */
    float young_module,     /* E18 */
    float shear_tension,    /* E20 */
    float shear_pressure,   /* E19 */
    float ult_tension,      /* E22 */
    float ult_pressure      /* E21 */
);
screws_t TREL_EXPORT* trel_screws_init(
    char* material,
    unsigned int amount,
    float diameter,
    float dist_center_wall
);
engine_t TREL_EXPORT* trel_engine_init(
    float pressure,         /* E24 */
    float temperature,      /* E26 */
    grains_t* grains,
    fuel_t* fuel,
    tubing_t* tube,
    screws_t* screws
);
float TREL_EXPORT trel_psi_to_pa(float psi);
void TREL_EXPORT trel_set_pressure(engine_t *engine, float pressure);
void TREL_EXPORT trel_set_escape_vel(engine_t *engine, float vel);
float TREL_EXPORT trel_get_escape_vel(engine_t *engine);
float TREL_EXPORT trel_get_pressure(engine_t *engine);

#endif // ENGINE_H
