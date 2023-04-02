#ifndef TREL_STRUCTS_H
#define TREL_STRUCTS_H

#include "design_constants.h"
#include "DLLDefines.h"

// Comp area calculations
typedef struct {
    double avg_long_area, avg_trans_area, avg_burn_area, burn_std_deviation, burn_sum_diff;
} TREL_EXPORT comp_area_t;

// Propellent grains structure
typedef struct {
    unsigned int amount;
    double init_inter_radius, extern_radius, longitude, grain_separation;
} TREL_EXPORT grains_t;

/* Fuel structure */
typedef struct {
    double const_burn_rate, pressure_exponent, density, burn_rate;
} TREL_EXPORT fuel_t;

// Estructura para tuberia
typedef struct tubing
{
   char   material[TREL_MAX_STR_LEN];
   double diameter_ext, wall_thickness, internal_radius;
   double young_module, sector_angle, mean_tubing_diameter;
   double shear_stress_tension, shear_stress_pressure;
   double ult_stress_tension, ult_stress_pressure;
   double transversal_area, material_area;
   double nozzle_efficiency;
} TREL_EXPORT tubing_t;

// Estructura para tornillos
typedef struct screws
{
	double diameter, dist_center_wall;
	unsigned int amount;
    double area_per_screw, screw_occupied_area;
	char   material[TREL_MAX_STR_LEN];
    double width_cutting_segment;
} TREL_EXPORT screws_t;

// Estructura del engine
typedef struct engine
{
    double engine_mass;
    double pressure;                // chamber pressure in psi
	double escape_vel, temperature;
    double width_condition, margin_of_safety, max_stress, radial_stress;
    double tangencial_stress, longitudinal_stress, max_pressure;
    double nozzle_efficiency;
    grains_t *grains;              // ptr to intialized struct
    fuel_t *fuel;
    tubing_t *tube;                // ptr to intialized struct
	screws_t *screws;              // ptr to initialized struct
    comp_area_t *comp_area_values; // ptr to initialized struct
} TREL_EXPORT engine_t;

// Struct for the whole rocket simulation
typedef struct trel_rocket
{
    engine_t *engine;              // ptr to initialized struct
    double telemetry_mass, parachute_mass, fuselage_mass, payload_mass, initial_height;
    double avg_thrust, max_thrust, delta_v, max_pressure; // Comportamiento en el Tiempo!AD3511
    double sim_latitude, max_sim_height, body_diameter, drag_coefficient;
    double rocket_position[1000];
    double rocket_speed[1000]; // m/s
    double rocket_acceleration[1000];
    double rocket_force_balance[1000];
    double rocket_drag[1000];
    double rocket_weight[1000];
    double rocket_mass[1000];
    double rocket_force[1000];
    double time[1000];
} TREL_EXPORT trel_rocket_t;

#endif //TREL_STRUCTS_H
