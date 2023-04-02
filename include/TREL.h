#ifndef TREL_H
#define TREL_H

// Types
// Comp area calculations
typedef struct {
    double avg_long_area, avg_trans_area, avg_burn_area, burn_std_deviation, burn_sum_diff;
} comp_area_t;

// Propellent grains structure
typedef struct {
    unsigned int amount;
    double init_inter_radius, extern_radius, longitude, grain_separation;
} grains_t;

/* Fuel structure */
typedef struct {
    double const_burn_rate, pressure_exponent, density, burn_rate;
} fuel_t;

// Estructura para tuberia
typedef struct tubing
{
    //char* material;
    double diameter_ext, wall_thickness, internal_radius;
    double young_module, sector_angle, mean_tubing_diameter;
    double shear_stress_tension, shear_stress_pressure;
    double ult_stress_tension, ult_stress_pressure;
    double transversal_area, material_area;
} tubing_t;

// Estructura para tornillos
typedef struct screws
{
    double diameter, dist_center_wall;
    unsigned int amount;
    double area_per_screw, screw_occupied_area;
    char* material;
    double width_cutting_segment;
} screws_t;

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
} engine_t;

// Estructura del cohete
typedef struct trel_rocket
{
    engine_t* engine;              // ptr to initialized struct
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
} trel_rocket_t;

// Function prototypes
grains_t *trel_grains_init(
    unsigned int amount,    /* E29 */
    double internal_radius,  /* E30 */
    double external_radius,  /* E31 */
    double longitude,        /* E32 */
    double grain_separation  /* E33 */
);
fuel_t *trel_fuel_init(
    double const_burn_rate,  /* E41 */
    double pressure_exponent,/* E42 */
    double density           /* E44 */
);
tubing_t *trel_tubing_init(
    //char* material,         /* E16 & E17 */
    double diameter,         /* E13 */
    double thickness,        /* E14 */
    double young_module,     /* E18 */
    double shear_tension,    /* E20 */
    double shear_pressure,   /* E19 */
    double ult_tension,      /* E22 */
    double ult_pressure,     /* E21 */
    double nozzle_efficiency
);
screws_t *trel_screws_init(
//    char* material,
    unsigned int amount,
    double diameter,
    double dist_center_wall
);
engine_t *trel_engine_init(
    double pressure,         /* E24 */
    double temperature,      /* E26 */
    double engine_mass,
    grains_t* grains,
    fuel_t* fuel,
    tubing_t* tube,
    screws_t* screws
);
trel_rocket_t *trel_rocket_init(
    engine_t* engine,
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
void trel_set_pressure(engine_t* engine, double pressure);
void trel_set_escape_vel(engine_t* engine, double vel);
double trel_get_escape_vel(engine_t* engine);
double trel_get_pressure(engine_t* engine);
double trel_temper_garganta(engine_t *engine);
double br_combustion(engine_t *engine);
int trel_run_area_comp_iterations(engine_t **engine);
int trel_run_time_comp_iterations(trel_rocket_t* rocket);
int trel_run_height_sim_iterations(trel_rocket_t** rocket);

#endif //TREL_H
