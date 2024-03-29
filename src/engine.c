#include <string.h>
#include "engine.h"

/* Initializes all variables in the grains struct */
grains_t *trel_grains_init(
    unsigned int amount,
    double internal_radius,
    double external_radius,
    double longitude,
    double grain_separation)
{
    grains_t *grains = (grains_t *) malloc(sizeof(grains_t));
    if (!grains) {
        printf("Grains initialization failed\n");
        exit(1);
    }
    grains->amount = amount;
    grains->init_inter_radius = internal_radius;
    grains->extern_radius = external_radius;
    grains->longitude = longitude;
    grains->grain_separation = grain_separation;
    return(grains);
}

/* Initializes all the variables in the fuel strcut */
fuel_t* trel_fuel_init(
    double const_burn_rate,
    double pressure_exponent,
    double density)
{
    fuel_t *fuel = (fuel_t *) malloc(sizeof(fuel_t));
    if (!fuel) {
        printf("Fuel initialization failed\n");
        exit(1);
    }
    fuel->const_burn_rate = const_burn_rate;
    fuel->pressure_exponent = pressure_exponent;
    fuel->density = density;
    fuel->burn_rate = 0.0f;
    return(fuel);
}

/* Initializes all the variables in the tube struct */
tubing_t* trel_tubing_init(
    char  *material,
    double diameter,
    double thickness,
    double young_module,
    double shear_tension,
    double shear_pressure,
    double ult_tension,
    double ult_pressure,
    double nozzle_efficiency)
{
    tubing_t *tube = (tubing_t *) malloc(sizeof(tubing_t));
    if (!tube) {
        printf("Tubing initialization failed\n");
        exit(1);
    }
#if defined (_WIN32) /* Take advantage of TR 24731-1 from MSVC */
    strcpy_s(tube->material, sizeof(char) * TREL_MAX_STR_LEN - 1, material);
#else /* Take the most portable approach for NIX */
    strncpy(tube->material, material, TREL_MAX_STR_LEN - 1);
#endif
    tube->diameter_ext              = diameter;
    tube->wall_thickness            = thickness;
    tube->young_module              = young_module;
    tube->shear_stress_tension      = shear_tension;
    tube->shear_stress_pressure     = shear_pressure;
    tube->ult_stress_tension        = ult_tension;
    tube->ult_stress_pressure       = ult_pressure;
    tube->mean_tubing_diameter      = 0.0;
    tube->transversal_area          = 0.0;
    tube->internal_radius           = (tube->diameter_ext-(2.0*tube->wall_thickness))/2.0; /* E15 */
    tube->sector_angle              = 0.0;    /* degrees */
    tube->material_area             = 0.0;
    tube->nozzle_efficiency         = nozzle_efficiency;
    return(tube);
}

/* Initializes all the variables in the screws struct */
screws_t* trel_screws_init(
    char *material,
    unsigned int amount,
    double diameter,
    double dist_center_wall)
{
    screws_t *screws = (screws_t *) malloc(sizeof(screws_t));
    if (!screws) {
        printf("Screws initialization failed\n");
        exit(1);
    }
#if defined (_WIN32) /* Take advantage of TR 24731-1 from MSVC */
    strcpy_s(screws->material, sizeof(char) * TREL_MAX_STR_LEN - 1, material);
#else /* Take the most portable approach for NIX */
    strncpy(screws->material, material, TREL_MAX_STR_LEN - 1);
#endif
    screws->diameter = diameter;
    screws->amount = amount;
    screws->dist_center_wall = dist_center_wall;
    screws->area_per_screw = 0.0f;
    screws->screw_occupied_area = 0.0f;
    screws->width_cutting_segment = 0.0f;
    return(screws);
}

/* Initializes all the variables in the engine struct */
engine_t* trel_engine_init(
    double pressure,
    double temperature,
    double engine_mass,
    grains_t **grains,
    fuel_t **fuel,
    tubing_t **tube,
    screws_t **screws)
{
    comp_area_t *comp_area_values = (comp_area_t*) malloc(sizeof(comp_area_t));
    engine_t *engine = (engine_t *) malloc(sizeof(engine_t));

    if (!comp_area_values) {
        printf("Engine initialization failed due to comp_area_values\n");
        exit(1);
    }
    comp_area_values->avg_burn_area = 0.0f;
    comp_area_values->avg_long_area = 0.0f;
    comp_area_values->avg_trans_area = 0.0f;
    comp_area_values->burn_std_deviation = 0.0f;
    comp_area_values->burn_sum_diff = 0.0f;

    if (!engine) {
        printf("Engine initialization failed\n");
        exit(1);
    }
    engine->width_condition = 0.0f;
    engine->margin_of_safety = 0.0f;
    engine->max_stress = 0.0f;
    engine->radial_stress = 0.0f;
    engine->tangencial_stress = 0.0f;
    engine->longitudinal_stress = 0.0f;
    engine->max_pressure = 0.0f;
    engine->pressure = pressure;
    engine->temperature = temperature;
    engine->grains = grains;
    engine->fuel = fuel;
    engine->tube = tube;
    engine->screws = screws;
    engine->escape_vel = calc_escape_vel(engine);
    engine->comp_area_values = comp_area_values;
    engine->engine_mass = engine_mass;
    engine->nozzle_efficiency = 0.0f;
    trel_engine_max_pressure(engine);
    trel_transversal_area_tube(engine);
    trel_tube_mateial_area(engine);
    trel_width_cutting_segment(engine);
    trel_area_per_screw(engine);
    trel_tangencial_stress(engine);
    if (trel_run_area_comp_iterations(&engine)) /* 1 means there was an error */
    {
        return(NULL); /* NULL means the engine couldn't be properly generated */
    }
	return(engine);
}

/* returns given psi value in pascals */
double trel_psi_to_pa(double psi)
{
	return(6894.757f*psi);
}

/* returns the chamber pressure of given engine in psi */
double trel_get_pressure(engine_t *engine)
{
    return(engine->pressure);
}

/* sets the chamber pressure in psi as given to the engine */
void trel_set_pressure(engine_t *engine, double pressure)
{
	engine->pressure = pressure;
}

void trel_set_escape_vel(engine_t *engine, double vel)
{
     engine->escape_vel = vel;
}

double trel_get_escape_vel(engine_t *engine)
{
    return engine->escape_vel;
}

int trel_set_engine_mass(engine_t* engine, double mass)
{
    if (!engine) return(1);
    engine->engine_mass = mass;
    return(0);
}

void trel_grains_free(grains_t** grains)
{
    free(*grains);
    *grains = NULL;
}

void trel_fuel_free(fuel_t** fuel)
{
    free(*fuel);
    *fuel = NULL;
}

void trel_tubing_free(tubing_t** tubing)
{
    free(*tubing);
    *tubing = NULL;
}

void trel_screws_free(screws_t** screws)
{
    free(*screws);
    *screws = NULL;
}

void trel_comp_area_free(comp_area_t** values)
{
    free(*values);
    *values = NULL;
}

void trel_engine_free(engine_t** engine)
{
    if (*engine != NULL)
    {
    if ((*engine)->comp_area_values != NULL)
    {
        free((*engine)->comp_area_values);
        (*engine)->comp_area_values = NULL;
    }
    if ((*(*engine)->screws) != NULL)
    {
        free((*(*engine)->screws));
        (*(*engine)->screws) = NULL;
    }
    if ((*(*engine)->tube) != NULL)
    {
        free((*(*engine)->tube));
        (*(*engine)->tube) = NULL;
    }
    if ((*(*engine)->fuel) != NULL)
    {
        free((*(*engine)->fuel));
        (*(*engine)->fuel) = NULL;
    }
    if ((*(*engine)->grains) != NULL)
    {
        free((*(*engine)->grains));
        (*(*engine)->grains) = NULL;
    }
    free(*engine);
    *engine = NULL;
    }
}
