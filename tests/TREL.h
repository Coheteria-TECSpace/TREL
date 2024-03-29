#ifndef TREL_H
#define TREL_H

/* Types */
/* Comp area calculations */
typedef struct trel_comp_area {
    double avg_long_area, avg_trans_area, avg_burn_area, burn_std_deviation, burn_sum_diff;
} trel_comp_area_t;

/* Propellent grains structure */
typedef struct trel_grains {
    unsigned int amount;
    double init_inter_radius, extern_radius, longitude, grain_separation;
} trel_grains_t;

/* Fuel structure */
typedef struct trel_fuel {
    double const_burn_rate, pressure_exponent, density, burn_rate;
} trel_fuel_t;

/* Estructura para tuberia */
typedef struct trel_tubing
{
    char   material[100];
    double diameter_ext, wall_thickness, internal_radius;
    double young_module, sector_angle, mean_tubing_diameter;
    double shear_stress_tension, shear_stress_pressure;
    double ult_stress_tension, ult_stress_pressure;
    double transversal_area, material_area;
} trel_tubing_t;

/* Estructura para tornillos */
typedef struct trel_screws
{
    double diameter, dist_center_wall;
    unsigned int amount;
    double area_per_screw, screw_occupied_area;
    char  material[100];
    double width_cutting_segment;
} trel_screws_t;

/* Estructura del engine */
typedef struct trel_engine
{
    double engine_mass;
    double pressure;                /* chamber pressure in psi */
	double escape_vel, temperature;
    double width_condition, margin_of_safety, max_stress, radial_stress;
    double tangencial_stress, longitudinal_stress, max_pressure;
    double nozzle_efficiency;
    trel_grains_t **grains;              /* ptr to intialized struct */
    trel_fuel_t **fuel;
    trel_tubing_t **tube;                /* ptr to intialized struct */
    trel_screws_t **screws;              /* ptr to initialized struct */
    trel_comp_area_t *comp_area_values; /* ptr to initialized struct */
} trel_engine_t;

/* Struct for height simulation results */
typedef struct trel_height_sim_values
{
    double rocket_position[1000];
    double rocket_speed[1000]; /* m/s */
    double rocket_acceleration[1000];
    double rocket_force_balance[1000];
    double rocket_drag[1000];
    double rocket_weight[1000];
    double rocket_mass[1000];
    double rocket_force[1000];
    double time[1000];
    double max_rocket_height;
    double max_rocket_position;
    double max_rocket_speed; /* m/s */
    double max_rocket_acceleration;
    double max_rocket_force_balance;
    double max_rocket_drag;
} trel_height_sim_t;

/* Struct for the rocket */
typedef struct trel_rocket
{
    trel_engine_t **engine;              /* ptr to initialized struct */
    double telemetry_mass, parachute_mass, fuselage_mass, payload_mass, initial_height;
    double avg_thrust, max_thrust, delta_v, max_pressure; /* Comportamiento en el Tiempo!AD3511 */
    double sim_latitude, body_diameter, drag_coefficient;
    trel_height_sim_t* sim_values;
} trel_rocket_t;

/* Function prototypes */
trel_grains_t *trel_grains_init(
    unsigned int amount,    /* E29 */
    double internal_radius,  /* E30 */
    double external_radius,  /* E31 */
    double longitude,        /* E32 */
    double grain_separation  /* E33 */
);
trel_fuel_t *trel_fuel_init(
    double const_burn_rate,  /* E41 */
    double pressure_exponent,/* E42 */
    double density           /* E44 */
);
trel_tubing_t *trel_tubing_init(
    char* material,         /* E16 & E17 */
    double diameter,         /* E13 */
    double thickness,        /* E14 */
    double young_module,     /* E18 */
    double shear_tension,    /* E20 */
    double shear_pressure,   /* E19 */
    double ult_tension,      /* E22 */
    double ult_pressure,     /* E21 */
    double nozzle_efficiency
);
trel_screws_t *trel_screws_init(
    char* material,
    unsigned int amount,
    double diameter,
    double dist_center_wall
);
trel_engine_t *trel_engine_init(
    double pressure,         /* E24 */
    double temperature,      /* E26 */
    double engine_mass,
    trel_grains_t **grains,
    trel_fuel_t **fuel,
    trel_tubing_t **tube,
    trel_screws_t **screws
);
trel_rocket_t *trel_rocket_init(
    trel_engine_t **engine,
    double telemetry_mass,
    double parachute_mass,
    double fuselage_mass,
    double payload_mass,
    double initial_height,
    double sim_latitude,
    double body_diameter,
    double drag_coefficient
);
double trel_psi_to_pa(double psi);
void trel_set_pressure(trel_engine_t* engine, double pressure);
void trel_set_escape_vel(trel_engine_t* engine, double vel);
double trel_get_escape_vel(trel_engine_t* engine);
double trel_get_pressure(trel_engine_t* engine);
double trel_temper_garganta(trel_engine_t *engine);
int trel_run_area_comp_iterations(trel_engine_t **engine);
int trel_run_time_comp_iterations(trel_rocket_t **rocket);
int trel_run_height_sim_iterations(trel_rocket_t **rocket);

void trel_grains_free(trel_grains_t** grains);
void trel_fuel_free(trel_fuel_t** fuel);
void trel_tubing_free(trel_tubing_t** tubing);
void trel_screws_free(trel_screws_t** screws);
void trel_engine_free(trel_engine_t** engine);
void trel_rocket_free(trel_rocket_t **rocket);

#endif /*TREL_H */
