#include "comp_tiempo.h"

#define POW2(VAR) (VAR * VAR)

double calc_iter_internal_mass(double produced_mass, double internal_mass, double escape_delta_m)
{
    double val = 0.0;
    if (produced_mass + internal_mass - escape_delta_m > 0.0)
    {
        val = produced_mass + internal_mass - escape_delta_m;
    }
    return(val);
}

/*Comportamiento en el Tiempo!AD3511 */
int trel_run_time_comp_iterations(trel_rocket_t* rocket)
{
    engine_t* engine = rocket->engine;
   
    /* iterate over given iterations and step size */
    const double max_iterations = TREL_MAX_ITERATIONS;
    const double burn_time = Tiempo_quemado_combustion(engine);
    const double step = burn_time / 3000.0;
    double time = 0.0; /* time in seconds */
    double last_force = 0.0;
    const double total_volume = TREL_PI * POW2((*engine->tube)->internal_radius) * 
                                ((*engine->grains)->grain_separation * ((*engine->grains)->amount - 1) + (*engine->grains)->longitude * (*engine->grains)->amount);

    /* variables for iteration */
    double dead_mass = rocket->fuselage_mass + rocket->parachute_mass + rocket->telemetry_mass + engine->engine_mass + rocket->payload_mass;
    const double delta_t = step;
    double pressure_abs = TREL_ATMOSPHERIC_PRESSURE;
    /*double pressure = pressure_abs / 6894.757f; */
    /*double pressure_man = pressure_abs - TREL_ATMOSPHERIC_PRESSURE; */
    double burn_rate = (*engine->fuel)->const_burn_rate * pow(pressure_abs * 0.000145038f, (*engine->fuel)->pressure_exponent) * 0.0254f;
    double inst_radius = (*engine->grains)->init_inter_radius;
    double inst_long = (*engine->grains)->longitude;
    /*double trans_area = inst_radius > 0 ? TREL_PI * (*engine->grains)->extern_radius * (*engine->grains)->extern_radius - inst_radius * inst_radius : 0.0f; */
    /*double long_area = trans_area == 0 ? 0.0f : 2 * TREL_PI * inst_radius * inst_long; */
    /*double burn_area = trans_area * 2 + long_area; */
    /*double total_burn_area = burn_area > 0 ? burn_area * (*engine->grains)->extern_radius : 0.0f; */
    double fuel_vol = (*engine->grains)->amount * TREL_PI * (POW2((*engine->grains)->extern_radius) - POW2(inst_radius)) * inst_long;
    double fuel_mass = (*engine->fuel)->density * fuel_vol;
    double produced_mass = 0.0;
    /*double produced_massic_flux = 0.0f; */
    double escape_massic_flux = 0.0;
    /*double flux_diff = produced_massic_flux - escape_massic_flux; */
    double escape_delta_m = 0.0f;
    double free_vol = total_volume - fuel_vol;
    double internal_mass = (free_vol * pressure_abs) / (engine->temperature * TREL_GAS_CONST);
    /*double areas_ratio = total_burn_area / (*engine->grains)->longitude;     */
    double virtual_escape_pressure = calc_iter_virt_escape_pressure(pressure_abs, engine);
    /*double real_escape_pressure = pressure_abs / pow((1 + ((TREL_HEAT_CAP_RATIO - 1) / 2) * volumen_unitario(engine) * volumen_unitario(engine)), (TREL_HEAT_CAP_RATIO / (TREL_HEAT_CAP_RATIO - 1))) < TREL_ATMOSPHERIC_PRESSURE ? TREL_ATMOSPHERIC_PRESSURE : pressure_abs / pow((1 + ((TREL_HEAT_CAP_RATIO - 1) / 2) * volumen_unitario(engine) * volumen_unitario(engine)), (TREL_HEAT_CAP_RATIO / (TREL_HEAT_CAP_RATIO - 1))); */
    double force_coeff = calc_iter_force_coeff(virtual_escape_pressure, pressure_abs, TREL_ATMOSPHERIC_PRESSURE, engine);
    double adjusted_cf = force_coeff * (*engine->tube)->nozzle_efficiency;
    double force = adjusted_cf * pressure_abs * (*engine->grains)->longitude > 0 ? adjusted_cf * pressure_abs * (*engine->grains)->longitude : 0.0;
    double total_thrust = 0.0;
    double delta_v = total_thrust / (fuel_mass + (double)dead_mass);

    /* sums for eventual result values */
    double sum_delta_v = delta_v;
    double sum_avg_thrust = force;

    /* variable for max thrust */
    double max_thrust = force;
    double max_pressure = pressure_abs;

    /* iteration loop */
    int it = 0;
    for (it = 0; it < max_iterations; it++)
    {
        pressure_abs = TREL_GAS_CONST * engine->temperature * internal_mass / free_vol;
        /*pressure = pressure_abs / 6894.757f; */
        /*pressure_man = pressure_abs - TREL_ATMOSPHERIC_PRESSURE; */
        burn_rate = (*engine->fuel)->const_burn_rate * pow(pressure_abs * 0.000145038f, (*engine->fuel)->pressure_exponent) * 0.0254f;
        inst_radius = inst_radius > 0 && (inst_radius + burn_rate * delta_t) < (*engine->grains)->extern_radius ? inst_radius + burn_rate * delta_t : 0;
        inst_long = inst_radius > 0 ? inst_long - burn_rate * delta_t * 2 : 0;
        /*trans_area = inst_radius > 0 ? TREL_PI * (*engine->grains)->extern_radius * (*engine->grains)->extern_radius - inst_radius * inst_radius : 0.0f; */
        /*long_area = trans_area == 0 ? 0.0f : 2 * TREL_PI * inst_radius * inst_long; */
        /*burn_area = trans_area * 2 + long_area; */
        /*total_burn_area = burn_area > 0 ? burn_area * (*engine->grains)->extern_radius : 0.0f; */
        fuel_vol = (*engine->grains)->amount * TREL_PI * (POW2((*engine->grains)->extern_radius) - POW2(inst_radius)) * inst_long;
        free_vol = total_volume - fuel_vol;
        produced_mass = fuel_mass - (*engine->fuel)->density * fuel_vol;
        fuel_mass = (*engine->fuel)->density * fuel_vol;
        /*produced_massic_flux = produced_mass / delta_t; */
        escape_massic_flux = calc_iter_escape_massic_flux(pressure_abs, TREL_ATMOSPHERIC_PRESSURE, engine);
        /*flux_diff = produced_massic_flux - escape_massic_flux; */
        escape_delta_m = escape_massic_flux * delta_t;
        internal_mass = calc_iter_internal_mass(produced_mass, internal_mass, escape_delta_m);
        /*areas_ratio = total_burn_area / (*engine->grains)->longitude; */
        virtual_escape_pressure = calc_iter_virt_escape_pressure(pressure_abs, engine);
        /*real_escape_pressure = pressure_abs / pow((1 + ((TREL_HEAT_CAP_RATIO - 1) / 2) * volumen_unitario(engine) * volumen_unitario(engine)), (TREL_HEAT_CAP_RATIO / (TREL_HEAT_CAP_RATIO - 1))) < TREL_ATMOSPHERIC_PRESSURE ? TREL_ATMOSPHERIC_PRESSURE : pressure_abs / pow((1 + ((TREL_HEAT_CAP_RATIO - 1) / 2) * volumen_unitario(engine) * volumen_unitario(engine)), (TREL_HEAT_CAP_RATIO / (TREL_HEAT_CAP_RATIO - 1))); */
        force_coeff = calc_iter_force_coeff(virtual_escape_pressure, pressure_abs, TREL_ATMOSPHERIC_PRESSURE, engine);
        adjusted_cf = force_coeff * (*engine->tube)->nozzle_efficiency;
        /*total_thrust = ((force + adjusted_cr * pressure_abs * (*engine->grains)->longitude > 0 ? adjusted_cr * pressure_abs * (*engine->grains)->longitude : 0.0f) / (2.0f)) * delta_t; */
        last_force = force;
        force = adjusted_cf * pressure_abs * throat_area(engine) > 0 ? adjusted_cf * pressure_abs * throat_area(engine) : 0.0;
        total_thrust = ((force + last_force) / 2.0) * delta_t;
        delta_v = total_thrust / (fuel_mass + dead_mass);

        /* step time value */
        if (time + step < burn_time)
            time += step;
        else
            time = 0;

        /* add to delta_v sum and avg thrust */
        sum_delta_v += delta_v;
        sum_avg_thrust += total_thrust;

        if (total_thrust > max_thrust)
            max_thrust = total_thrust;

        if (pressure_abs > max_pressure)
            max_pressure = pressure_abs;
    }

    /* storing values */
    rocket->delta_v = sum_delta_v;
    rocket->max_thrust = max_thrust;
    rocket->max_pressure = max_pressure;
    /* calculate avg thrust */
    rocket->avg_thrust = sum_avg_thrust / max_iterations;

    return(0);
}
