#ifndef ENGINE_H
#define ENGINE_H

#include <stdlib.h>
#include <stdio.h>

#include "DLLDefines.h"
#include "design_func.h"
#include "design_resist.h"
#include "structs.h"

/* Function prototypes */
grains_t TREL_EXPORT *trel_grains_init(
    unsigned int amount,    /* E29 */
    double internal_radius,  /* E30 */
    double external_radius,  /* E31 */
    double longitude,        /* E32 */
    double grain_separation  /* E33 */
);
fuel_t TREL_EXPORT *trel_fuel_init(
    double const_burn_rate,  /* E41 */
    double pressure_exponent,/* E42 */
    double density           /* E44 */
);
tubing_t TREL_EXPORT *trel_tubing_init(
    char  *material,         /* E16 & E17 */
    double diameter,         /* E13 */
    double thickness,        /* E14 */
    double young_module,     /* E18 */
    double shear_tension,    /* E20 */
    double shear_pressure,   /* E19 */
    double ult_tension,      /* E22 */
    double ult_pressure,     /* E21 */
    double nozzle_efficiency
);
screws_t TREL_EXPORT* trel_screws_init(
    char* material,
    unsigned int amount,
    double diameter,
    double dist_center_wall
);
engine_t TREL_EXPORT* trel_engine_init(
    double pressure,         /* E24 */
    double temperature,      /* E26 */
    double engine_mass,
    grains_t **grains,
    fuel_t **fuel,
    tubing_t **tube,
    screws_t **screws
);
double TREL_EXPORT trel_psi_to_pa(double psi);
void TREL_EXPORT trel_set_pressure(engine_t *engine, double pressure);
void TREL_EXPORT trel_set_escape_vel(engine_t *engine, double vel);
double TREL_EXPORT trel_get_escape_vel(engine_t *engine);
double TREL_EXPORT trel_get_pressure(engine_t *engine);
void TREL_EXPORT trel_grains_free(grains_t** grains);
void TREL_EXPORT trel_fuel_free(fuel_t** fuel);
void TREL_EXPORT trel_tubing_free(tubing_t** tubing);
void TREL_EXPORT trel_screws_free(screws_t** screws);
void TREL_EXPORT trel_engine_free(engine_t** engine);

#endif /* ENGINE_H */
