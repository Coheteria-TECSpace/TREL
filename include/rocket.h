#ifndef ROCKET_H
#define ROCKET_H

#include <stdlib.h>
#include <stdio.h>

#include "DLLDefines.h"
#include "design_func.h"
#include "structs.h"

/* TODO: free library structs function */

/* Function prototypes */
trel_rocket_t TREL_EXPORT* trel_rocket_init(
    engine_t **engine,
    double telemetry_mass,
    double parachute_mass,
    double fuselage_mass,
    double payload_mass,
    double initial_height,
    double sim_latitude,
    double body_diameter,
    double drag_coefficient
);

void TREL_EXPORT trel_rocket_free(trel_rocket_t **rocket);

#endif/*ROCKET_H */
