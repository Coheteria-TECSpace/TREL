#include "rocket.h"

/* Initializes all the variables in the rocket struct */
trel_rocket_t* trel_rocket_init(
    engine_t* engine,
    double telemtry_mass,
    double parachute_mass,
    double fuselage_mass)
{
    trel_rocket_t* rocket = (trel_rocket_t*)malloc(sizeof(trel_rocket_t));
    if (!rocket) {
        printf("Rocket initialization failed\n");
        exit(1);
    }
    rocket->telemtry_mass = telemtry_mass;
    rocket->parachute_mass = parachute_mass;
    rocket->fuselage_mass = fuselage_mass;
    rocket->engine = engine;
    return(rocket);
}
