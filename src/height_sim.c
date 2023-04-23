#include "height_sim.h"
#include "stdio.h"

#define TRANSVERSAL_AREA(DIAMETER) (TREL_PI * DIAMETER * DIAMETER / 4)
#define POW2(VAR) (VAR * VAR)

double calc_force_balance(double rocket_force, double rocket_position, double rocket_speed, 
                          double rocket_drag, double rocket_weight)
{
    double result = 0.0;
    if (rocket_force < 0.01)
    {
        if (rocket_position > 0.0001)
        {
            result = rocket_speed > 0.0 ? rocket_drag + rocket_weight : rocket_weight - rocket_drag;
        }
    }
    else
    {
        result = rocket_force - rocket_weight - rocket_drag;
    }
    return(result);
}

double calc_inst_radius(double inst_radius, double burn_rate, double step, double extern_radius)
{
    double val = 0.0;
    if (inst_radius > 0.0)
    {
        if ((inst_radius + burn_rate * step) < extern_radius)
        {
            val = inst_radius + burn_rate * step;
        }
        else
        {
            val = 0;
        }
    }
    else
    {
        val = 0;
    }
    return(val);
}

double calc_burn_rate(engine_t *engine, double pressure)
{
    return((*engine->fuel)->const_burn_rate * pow(pressure * 0.000145038, (*engine->fuel)->pressure_exponent) * 0.0254);
}

double calc_inst_long(double inst_radius, double inst_long, double burn_rate, double step)
{
    return(inst_radius > 0.0 ? inst_long - burn_rate * step * 2.0 : 0.0);
}

double calc_iter_pressure(engine_t *engine, double intern_gas_mass, double free_volume, 
                          double atmospheric_pressure)
{
    double val = 0.0;
    if (TREL_GAS_CONST * engine->temperature * intern_gas_mass / free_volume > atmospheric_pressure)
    {
        val = TREL_GAS_CONST * engine->temperature * intern_gas_mass / free_volume;
    }
    else
    {
        val = atmospheric_pressure;
    }
    return(val);
}

double calc_iter_grav_accel(trel_rocket_t **rocket, double rocket_height)
{
    double val = 0.0;
    val = TREL_ECUATOR_GRAV_ACCEL;
    val *= (1 + (TREL_GRAV_CRUSH * (sin((*rocket)->sim_latitude * TREL_PI / 180)) * 
           (sin((*rocket)->sim_latitude * TREL_PI / 180))) - (TREL_GRAV_CRUSH_4 * 
           (sin((2 * (*rocket)->sim_latitude) * TREL_PI / 180)) * (sin((2 * 
           (*rocket)->sim_latitude) * TREL_PI / 180))));
    val -= (TREL_GRAV_A * rocket_height);
    return(val);
}

double calc_iter_force_coeff(double virt_escape_pressure, double pressure, double atmospheric_pressure, engine_t *engine)
{
    double val = pow((2.0 * TREL_HEAT_CAP_RATIO * TREL_HEAT_CAP_RATIO / 
                 (TREL_HEAT_CAP_RATIO - 1.0) * pow((2.0 / (TREL_HEAT_CAP_RATIO + 1.0)), 
                 ((TREL_HEAT_CAP_RATIO + 1) / (TREL_HEAT_CAP_RATIO - 1))) * 
                 ((1 - pow((virt_escape_pressure / pressure), ((TREL_HEAT_CAP_RATIO - 1.0) / 
                 TREL_HEAT_CAP_RATIO))))), 0.5);
    val += (virt_escape_pressure - atmospheric_pressure) / pressure * escape_area(engine) / 
           throat_area(engine);
    return(val);
}

double calc_iter_virt_escape_pressure(double pressure, engine_t *engine)
{
    double val = pressure / pow(1.0 + ((TREL_HEAT_CAP_RATIO - 1.0) / 2.0) * 
                 vel_numero_mach_m2(engine) * vel_numero_mach_m2(engine), TREL_HEAT_CAP_RATIO / 
                 (TREL_HEAT_CAP_RATIO - 1.0));
    return(val);
}

double calc_iter_escape_massic_flux(double pressure, double atmospheric_pressure, engine_t *engine)
{
    double val = 0.0;
    if (pressure > atmospheric_pressure)
    {
        val = throat_area(engine) * pressure * TREL_HEAT_CAP_RATIO * (sqrt(pow((2.0 / 
              (TREL_HEAT_CAP_RATIO + 1.0)) , ((TREL_HEAT_CAP_RATIO + 1.0) / 
              (TREL_HEAT_CAP_RATIO - 1.0))))) / pow((TREL_HEAT_CAP_RATIO * TREL_GAS_CONST * 
              engine->temperature) , 0.5);
    }
    return(val);
}

int trel_run_height_sim_iterations(trel_rocket_t** rocket)
{    
    engine_t *engine = (*rocket)->engine;
    trel_height_sim_t *res = (*rocket)->sim_values;

    /* iterate over given iterations and step size */
    const unsigned int max_iterations = TREL_MAX_ITERATIONS;
    const double burn_time = Tiempo_quemado_combustion((*rocket)->engine);
    const double step = burn_time / TREL_MAX_ITERATIONS;

    unsigned int it = 0;

    /* variables for iteration */
    double rocket_height = 0.0;
    /*double rocket_total_thrust = 0.0; */
    double fuel_volume = 0.0;
    double gravitational_accel = 0.0;
    double force_coeff = 0.0;
    double adjusted_cf = 0.0;
    double atmospheric_density = 0.0;
    double atmospheric_pressure = 0.0;
    double atmospheric_temp = 0.0;
    double inst_radius = 0.0;
    double pressure = 0.0;
    double free_volume = 0.0;
    double intern_gas_mass = 0.0;
    double fuel_mass = 0.0;
    double produced_mass = 0.0;
    double escape_massic_flux = 0.0;
    double inst_long = 0.0;
    double prev_fuel_mass = 0.0;
    double burn_rate = 0.0;
    double virt_escape_pressure = 0.0;
    double delta_m = 0.0;
    const double total_volume = TREL_PI * POW2((*engine->tube)->internal_radius) * 
                                ((*engine->grains)->grain_separation * ((*engine->grains)->amount - 1) + (*engine->grains)->longitude * (*engine->grains)->amount);
    
    inst_long = (*engine->grains)->longitude;
    inst_radius = (*engine->grains)->init_inter_radius;
    fuel_volume = (*engine->grains)->amount * TREL_PI * (POW2((*engine->grains)->extern_radius) - POW2(inst_radius)) * inst_long;
    fuel_mass = fuel_volume * (*engine->fuel)->density;
    prev_fuel_mass = fuel_mass;
    free_volume = total_volume - fuel_volume;
    rocket_height = (*rocket)->initial_height;
    gravitational_accel = TREL_ECUATOR_GRAV_ACCEL * (1.0 + (TREL_GRAV_CRUSH * (sin((*rocket)->sim_latitude * TREL_PI / 180.0)) * (sin((*rocket)->sim_latitude * TREL_PI / 180.0))) - (TREL_GRAV_CRUSH_4 * (sin((2.0 * (*rocket)->sim_latitude) * TREL_PI / 180.0)) * (sin((2.0 * (*rocket)->sim_latitude) * TREL_PI / 180.0)))) - (TREL_GRAV_A * rocket_height);
    atmospheric_pressure = TREL_ATMOSPHERIC_PRESSURE * pow(1.0 - TREL_ADIABATIC_GRADIENT * rocket_height / TREL_STANDARD_TEMP, gravitational_accel * TREL_DRY_AIR_MOLAR_MASS / (TREL_IDEAL_GAS_CONST * TREL_ADIABATIC_GRADIENT));
    pressure = atmospheric_pressure;
    intern_gas_mass = pressure * free_volume / (TREL_GAS_CONST * (*rocket)->engine->temperature);
    burn_rate = calc_burn_rate(engine, pressure);
    atmospheric_temp = TREL_STANDARD_TEMP - (TREL_ADIABATIC_GRADIENT * rocket_height);
    atmospheric_density = atmospheric_pressure * TREL_DRY_AIR_MOLAR_MASS / (TREL_IDEAL_GAS_CONST * atmospheric_temp);
    res->rocket_mass[0] = (*rocket)->telemetry_mass + (*rocket)->parachute_mass + (*rocket)->fuselage_mass + (*rocket)->payload_mass + (*rocket)->engine->engine_mass + (*(*rocket)->engine->fuel)->density * fuel_volume;
    res->rocket_weight[0] = res->rocket_mass[0] * gravitational_accel;
    virt_escape_pressure = calc_iter_virt_escape_pressure(pressure, engine);
    force_coeff = calc_iter_force_coeff(virt_escape_pressure, pressure, atmospheric_pressure, engine);
    adjusted_cf = force_coeff * (*(*rocket)->engine->tube)->nozzle_efficiency;
    res->rocket_force[0] = adjusted_cf * pressure * throat_area((*rocket)->engine) > 0 ? adjusted_cf * pressure * throat_area((*rocket)->engine) : 0;
    res->rocket_force_balance[0] = calc_force_balance(res->rocket_force[0], res->rocket_position[0], res->rocket_speed[0], res->rocket_drag[0], res->rocket_weight[0]);

    /* iteration loop */
    for (it = 1; it < max_iterations; it++)
    {
        res->time[it] = res->time[it - 1] + step;

        gravitational_accel = calc_iter_grav_accel(rocket, rocket_height);
        atmospheric_pressure = TREL_ATMOSPHERIC_PRESSURE * pow(1.0 - TREL_ADIABATIC_GRADIENT * rocket_height / TREL_STANDARD_TEMP, gravitational_accel * TREL_DRY_AIR_MOLAR_MASS / (TREL_IDEAL_GAS_CONST * TREL_ADIABATIC_GRADIENT));  /* ACA SE COLAPSA EL TITANIC */
        pressure = calc_iter_pressure(engine, intern_gas_mass, free_volume, atmospheric_pressure);
        inst_radius = calc_inst_radius(inst_radius, burn_rate, step, (*(*rocket)->engine->grains)->extern_radius);
        inst_long = calc_inst_long(inst_radius, inst_long, burn_rate, step);
        burn_rate = calc_burn_rate(engine, pressure);
        atmospheric_temp = TREL_STANDARD_TEMP - (TREL_ADIABATIC_GRADIENT * rocket_height);
        atmospheric_density = atmospheric_pressure * TREL_DRY_AIR_MOLAR_MASS / (TREL_IDEAL_GAS_CONST * atmospheric_temp);
        fuel_volume = (*(*rocket)->engine->grains)->amount * TREL_PI * (((*(*rocket)->engine->grains)->extern_radius * (*(*rocket)->engine->grains)->extern_radius) - inst_radius * inst_radius) * inst_long;
        escape_massic_flux = calc_iter_escape_massic_flux(pressure, atmospheric_pressure, engine);
        fuel_mass = fuel_volume * (*(*rocket)->engine->fuel)->density;
        produced_mass = prev_fuel_mass - fuel_mass;
        prev_fuel_mass = fuel_mass;
        delta_m = escape_massic_flux * step;
        intern_gas_mass = (produced_mass + intern_gas_mass - delta_m) > 0.0 ? produced_mass + intern_gas_mass - delta_m : 0.0;
        free_volume = total_volume - fuel_volume;
        virt_escape_pressure = calc_iter_virt_escape_pressure(pressure, engine);
        force_coeff = calc_iter_force_coeff(virt_escape_pressure, pressure, atmospheric_pressure, engine);
        adjusted_cf = force_coeff * (*(*rocket)->engine->tube)->nozzle_efficiency;
        res->rocket_mass[it] = (*rocket)->telemetry_mass + (*rocket)->parachute_mass + (*rocket)->fuselage_mass + (*rocket)->payload_mass + (*rocket)->engine->engine_mass + fuel_mass;
        res->rocket_weight[it] = res->rocket_mass[it] * gravitational_accel;
        res->rocket_drag[it] = 0.5 * atmospheric_density * (*rocket)->drag_coefficient * TRANSVERSAL_AREA((*rocket)->body_diameter) * res->rocket_speed[it - 1] * res->rocket_speed[it - 1];
        res->rocket_force[it] = adjusted_cf * pressure * throat_area((*rocket)->engine) > 0 ? adjusted_cf * pressure * throat_area((*rocket)->engine) : 0;
        res->rocket_force_balance[it] = calc_force_balance(res->rocket_force[it], res->rocket_position[it - 1], res->rocket_speed[it - 1], res->rocket_drag[it], res->rocket_weight[it]);
        res->rocket_acceleration[it] = res->rocket_force_balance[it] / res->rocket_mass[it];
        res->rocket_speed[it] = res->rocket_acceleration[it] * step + res->rocket_speed[it - 1];
        res->rocket_position[it] = (res->rocket_speed[it] * step + res->rocket_position[it - 1]) * (res->rocket_speed[it] * step + res->rocket_position[it - 1] > 0.0);
        rocket_height = (*rocket)->initial_height + res->rocket_position[it];

        /* Check for new max values */
        if (rocket_height > res->max_rocket_height)
            res->max_rocket_height = rocket_height;
        if (res->rocket_position[it] > res->max_rocket_position)
            res->max_rocket_position = res->rocket_position[it];
        if (res->rocket_speed[it] > res->max_rocket_speed)
            res->max_rocket_speed = res->rocket_speed[it];
        if (res->rocket_acceleration[it] > res->max_rocket_acceleration)
            res->max_rocket_acceleration = res->rocket_acceleration[it];
        if (res->rocket_force_balance[it] > res->max_rocket_force_balance)
            res->max_rocket_force_balance = res->rocket_force_balance[it];
        if (res->rocket_drag[it] > res->max_rocket_drag)
            res->max_rocket_drag = res->rocket_drag[it];
    }

    return(0); /* everything went well */
}
