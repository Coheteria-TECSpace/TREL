#include "rocket.h"

/* Initializes all the variables in the rocket struct */
trel_rocket_t *trel_rocket_init(
    engine_t **engine,
    double telemetry_mass,
    double parachute_mass,
    double fuselage_mass,
    double payload_mass,
    double initial_height,
    double sim_latitude,
    double body_diameter,
    double drag_coefficient)
{
    trel_rocket_t* rocket = (trel_rocket_t*)malloc(sizeof(trel_rocket_t));
    trel_height_sim_t* sim_values = (trel_height_sim_t*)malloc(sizeof(trel_height_sim_t));
    unsigned int i = 0;
    if (!rocket) {
        printf("Rocket initialization failed\n");
        exit(1);
    }

    if (!sim_values) {
        printf("Engine initialization failed due to sim_values\n");
        exit(1);
    }
    sim_values->max_rocket_acceleration = 0.0;
    sim_values->max_rocket_drag = 0.0;
    sim_values->max_rocket_force_balance = 0.0;
    sim_values->max_rocket_height = 0.0;
    sim_values->max_rocket_position = 0.0;
    sim_values->max_rocket_speed = 0.0;

    for (i = 0; i < TREL_MAX_ITERATIONS; i++)
    {
        sim_values->rocket_position[i] = 0.0;
        sim_values->rocket_speed[i] = 0.0;
        sim_values->rocket_acceleration[i] = 0.0;
        sim_values->rocket_force_balance[i] = 0.0;
        sim_values->rocket_drag[i] = 0.0;
        sim_values->rocket_weight[i] = 0.0;
        sim_values->rocket_mass[i] = 0.0;
        sim_values->rocket_force[i] = 0.0;
        sim_values->time[i] = 0.0;
    }

    rocket->telemetry_mass = telemetry_mass;
    rocket->parachute_mass = parachute_mass;
    rocket->fuselage_mass = fuselage_mass;
    rocket->payload_mass = payload_mass;
    rocket->engine = engine;
    rocket->initial_height = initial_height;
    rocket->sim_latitude = sim_latitude;
    rocket->body_diameter = body_diameter;
    rocket->drag_coefficient = drag_coefficient;
    rocket->sim_values = sim_values;
    if (trel_run_time_comp_iterations(&rocket)) /* 1 means there was an error */
    {
        return(NULL); /* NULL means the engine couldn't be properly generated */
    }
    if (trel_run_height_sim_iterations(&rocket)) /* 1 means there was an error */
    {
        return(NULL); /* NULL means the engine couldn't be properly generated */
    }
    return(rocket);
}

void trel_height_sim_free(trel_height_sim_t **values)
{
    free(*values);
    *values = NULL;
}

void trel_rocket_free(trel_rocket_t **rocket)
{
    if (*rocket != NULL)
    {
        if ((*rocket)->sim_values != NULL)
        {
            free((*rocket)->sim_values);
            (*rocket)->sim_values = NULL;
        }
        trel_engine_free((*rocket)->engine);
        {
            free(*rocket);
            *rocket = NULL;
        }
    }
}
