#ifndef TREL_H
#define TREL_H

//#include "design_func.h"

// Types
// Propellent grains structure
typedef struct {
    unsigned int amount;
    float init_inter_radius, extern_radius, longitude, grain_separation;
} grains_t;

/* Fuel structure */
typedef struct {
    float const_burn_rate, pressure_exponent, density, burn_rate;
} fuel_t;

// Estructura para tuberia
typedef struct tubing
{
    char* material;
    float diameter_ext, wall_thickness, internal_radius;
    float young_module, sector_angle, mean_tubing_diameter;
    float shear_stress_tension, shear_stress_pressure;
    float ult_stress_tension, ult_stress_pressure;
    float transversal_area, material_area;
} tubing_t;

// Estructura para tornillos
typedef struct screws
{
    float diameter, dist_center_wall;
    unsigned int amount;
    float area_per_screw, screw_occupied_area;
    char* material;
    float width_cutting_segment;
} screws_t;

// Estructura del engine
typedef struct engine
{
    float pressure;         // chamber pressure in psi
    float escape_vel, temperature;
    float width_condition, margin_of_safety, max_stress, radial_stress;
    float tangencial_stress, longitudinal_stress, max_pressure;
    grains_t* grains;       // ptr to intialized struct
    fuel_t* fuel;
    tubing_t* tube;         // ptr to intialized struct
    screws_t* screws;       // ptr to initialized struct
} engine_t;

// Function prototypes
grains_t *trel_grains_init(
    unsigned int amount,    /* E29 */
    float internal_radius,  /* E30 */
    float external_radius,  /* E31 */
    float longitude,        /* E32 */
    float grain_separation  /* E33 */
);
fuel_t *trel_fuel_init(
    float const_burn_rate,  /* E41 */
    float pressure_exponent,/* E42 */
    float density           /* E44 */
);
tubing_t *trel_tubing_init(
    char* material,         /* E16 & E17 */
    float diameter,         /* E13 */
    float thickness,        /* E14 */
    float young_module,     /* E18 */
    float shear_tension,    /* E20 */
    float shear_pressure,   /* E19 */
    float ult_tension,      /* E22 */
    float ult_pressure      /* E21 */
);
screws_t *trel_screws_init(
    char* material,
    unsigned int amount,
    float diameter,
    float dist_center_wall
);
engine_t *trel_engine_init(
    float pressure,         /* E24 */
    float temperature,      /* E26 */
    grains_t* grains,
    fuel_t* fuel,
    tubing_t* tube,
    screws_t* screws
);
float trel_psi_to_pa(float psi);
void trel_set_pressure(engine_t* engine, float pressure);
void trel_set_escape_vel(engine_t* engine, float vel);
float trel_get_escape_vel(engine_t* engine);
float trel_get_pressure(engine_t* engine);
float trel_temper_garganta(engine_t *engine);
float br_combustion(engine_t *engine);

#endif //TREL_H
