#include "rocket.h"

/* Initializes all the variables in the rocket struct */
trel_rocket_t* trel_rocket_init(
    engine_t* engine,
    double telemetry_mass,
    double parachute_mass,
    double fuselage_mass,
    double payload_mass)
{
    trel_rocket_t* rocket = (trel_rocket_t*)malloc(sizeof(trel_rocket_t));
    if (!rocket) {
        printf("Rocket initialization failed\n");
        exit(1);
    }
    rocket->telemetry_mass = telemetry_mass;
    rocket->parachute_mass = parachute_mass;
    rocket->fuselage_mass = fuselage_mass;
    rocket->payload_mass = payload_mass;
    rocket->engine = engine;
    if (trel_run_time_comp_iterations(rocket)) // 1 means there was an error
    {
        return(NULL); // NULL means the engine couldn't be properly generated
    }
    return(rocket);
}
