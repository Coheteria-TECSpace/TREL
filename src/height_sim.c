#include "height_sim.h"
#include "stdio.h"

// TODO: CHECK ANYTHING THAT USES pressure_abs, it might be pressure instead

#define TRANSVERSAL_AREA(DIAMETER) (TREL_PI * DIAMETER * DIAMETER / 4)

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
    return(inst_radius > 0.0 && (inst_radius + burn_rate * step) < extern_radius ? inst_radius + burn_rate * step : 0.0);
}

double calc_burn_rate(double const_burn_rate, double pressure_exponent, double pressure)
{
    return(const_burn_rate * pow(pressure * 0.000145038, pressure_exponent) * 0.0254);
}

double calc_inst_long(double inst_radius, double inst_long, double burn_rate, double step)
{
    return(inst_radius > 0.0 ? inst_long - burn_rate * step * 2.0 : 0.0);
}

int trel_run_height_sim_iterations(trel_rocket_t** rocket)
{    
    engine_t *engine = (*rocket)->engine;
    trel_height_sim_t *res = (*rocket)->sim_values;

    // iterate over given iterations and step size
    const double max_iterations = 1000.0f;
    const double burn_time = Tiempo_quemado_combustion((*rocket)->engine);
    const double step = burn_time / max_iterations;

    // burn rate value from propellant
    const double burn_rate = br_combustion((*rocket)->engine);

    // variables for iteration
    double rocket_height = 0.0;
    //double rocket_total_thrust = 0.0;
    double fuel_volume = 0.0;
    double gravitational_accel = 0.0;
    double pressure_abs = 0.0;
    double virtual_escape_pressure = 0.0;
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

    const double total_volume = TREL_PI * (*rocket)->engine->tube->internal_radius * (*rocket)->engine->tube->internal_radius * ((*rocket)->engine->grains->grain_separation * ((*rocket)->engine->grains->amount - 1) + (*rocket)->engine->grains->longitude * (*rocket)->engine->grains->amount);
    
    inst_long = engine->grains->longitude;
    inst_radius = (*rocket)->engine->grains->init_inter_radius * (*rocket)->engine->grains->init_inter_radius;
    rocket_height = (*rocket)->initial_height;
    gravitational_accel = TREL_ECUATOR_GRAV_ACCEL * (1 + (TREL_GRAV_CRUSH * (sin((*rocket)->sim_latitude * TREL_PI / 180)) * (sin((*rocket)->sim_latitude * TREL_PI / 180))) - (TREL_GRAV_CRUSH_4 * (sin((2 * (*rocket)->sim_latitude) * TREL_PI / 180)) * (sin((2 * (*rocket)->sim_latitude) * TREL_PI / 180)))) - (TREL_GRAV_A * rocket_height);
    atmospheric_pressure = TREL_ATMOSPHERIC_PRESSURE * pow(1.0 - TREL_ADIABATIC_GRADIENT * rocket_height / TREL_STANDARD_TEMP, gravitational_accel * TREL_DRY_AIR_MOLAR_MASS / (TREL_IDEAL_GAS_CONST * TREL_ADIABATIC_GRADIENT));
    pressure = atmospheric_pressure;
    atmospheric_temp = TREL_STANDARD_TEMP - (TREL_ADIABATIC_GRADIENT * rocket_height);
    atmospheric_density = atmospheric_pressure * TREL_DRY_AIR_MOLAR_MASS / (TREL_IDEAL_GAS_CONST * atmospheric_temp);
    fuel_volume = (*rocket)->engine->grains->amount * TREL_PI * (((*rocket)->engine->grains->extern_radius * (*rocket)->engine->grains->extern_radius) - (inst_radius * inst_radius)) * (*rocket)->engine->grains->longitude;
    fuel_mass = fuel_volume * (*rocket)->engine->fuel->density;
    free_volume = total_volume - fuel_volume;
    intern_gas_mass = pressure * free_volume / (TREL_GAS_CONST * (*rocket)->engine->temperature);
    res->rocket_mass[0] = (*rocket)->telemetry_mass + (*rocket)->parachute_mass + (*rocket)->fuselage_mass + (*rocket)->payload_mass + (*rocket)->engine->engine_mass + (*rocket)->engine->fuel->density * fuel_volume;
    res->rocket_weight[0] = res->rocket_mass[0] * gravitational_accel;
    pressure_abs = TREL_ATMOSPHERIC_PRESSURE * pow(1.0 - ((TREL_ADIABATIC_GRADIENT * rocket_height) / (TREL_STANDARD_TEMP)),((gravitational_accel * TREL_DRY_AIR_MOLAR_MASS) / TREL_IDEAL_GAS_CONST * TREL_ADIABATIC_GRADIENT));
    virtual_escape_pressure = pressure / pow((1.0 + ((TREL_HEAT_CAP_RATIO - 1.0) / 2.0) * volumen_unitario((*rocket)->engine) * volumen_unitario((*rocket)->engine)), (TREL_HEAT_CAP_RATIO / (TREL_HEAT_CAP_RATIO - 1.0)));
    force_coeff = pow((((2.0 * TREL_HEAT_CAP_RATIO * TREL_HEAT_CAP_RATIO) / (TREL_HEAT_CAP_RATIO - 1.0)) * pow((2.0 / (TREL_HEAT_CAP_RATIO + 1.0)), ((TREL_HEAT_CAP_RATIO + 1.0) / (TREL_HEAT_CAP_RATIO - 1.0))) * ((1.0 - pow((virtual_escape_pressure / pressure), ((TREL_HEAT_CAP_RATIO-1.0)/TREL_HEAT_CAP_RATIO))))),0.5) + (((virtual_escape_pressure - pressure_abs) / (pressure)) * ((*rocket)->engine->grains->grain_separation / (*rocket)->engine->grains->longitude));
    adjusted_cf = force_coeff * (*rocket)->engine->tube->nozzle_efficiency;
    res->rocket_force[0] = adjusted_cf * pressure * throat_area((*rocket)->engine) > 0 ? adjusted_cf * pressure * throat_area((*rocket)->engine) : 0;
    res->rocket_force_balance[0] = calc_force_balance(res->rocket_force[0], res->rocket_position[0], res->rocket_speed[0], res->rocket_drag[0], res->rocket_weight[0]);

    // iteration loop
    for (int it = 1; it < max_iterations; it++)
    {
        // step time value
        if (res->time[it - 1] + step < burn_time)
            res->time[it] = res->time[it - 1] + step;
        else
            res->time[it] = 0;

        gravitational_accel = TREL_ECUATOR_GRAV_ACCEL * (1 + (TREL_GRAV_CRUSH * (sin((*rocket)->sim_latitude * TREL_PI / 180)) * (sin((*rocket)->sim_latitude * TREL_PI / 180))) - (TREL_GRAV_CRUSH_4 * (sin((2 * (*rocket)->sim_latitude) * TREL_PI / 180)) * (sin((2 * (*rocket)->sim_latitude) * TREL_PI / 180)))) - (TREL_GRAV_A * rocket_height);
        atmospheric_pressure = TREL_ATMOSPHERIC_PRESSURE * pow(1.0 - TREL_ADIABATIC_GRADIENT * rocket_height / TREL_STANDARD_TEMP, gravitational_accel * TREL_DRY_AIR_MOLAR_MASS / (TREL_IDEAL_GAS_CONST * TREL_ADIABATIC_GRADIENT));
        pressure = TREL_GAS_CONST * (*rocket)->engine->temperature * intern_gas_mass / free_volume > atmospheric_pressure ? TREL_GAS_CONST * (*rocket)->engine->temperature * intern_gas_mass / free_volume : atmospheric_pressure;
        inst_radius = calc_inst_radius(inst_radius, calc_burn_rate(burn_rate, (*rocket)->engine->fuel->pressure_exponent, pressure), step, (*rocket)->engine->grains->extern_radius);
        inst_long = calc_inst_long(inst_radius, inst_long, calc_burn_rate(burn_rate, (*rocket)->engine->fuel->pressure_exponent, pressure), step);
        atmospheric_temp = TREL_STANDARD_TEMP - (TREL_ADIABATIC_GRADIENT * rocket_height);
        atmospheric_density = atmospheric_pressure * TREL_DRY_AIR_MOLAR_MASS / (TREL_IDEAL_GAS_CONST * atmospheric_temp);
        fuel_volume = (*rocket)->engine->grains->amount * TREL_PI * (((*rocket)->engine->grains->extern_radius * (*rocket)->engine->grains->extern_radius) - inst_radius * inst_radius) * inst_long;
        produced_mass = - fuel_mass;
        escape_massic_flux = pressure > atmospheric_pressure ? engine->grains->longitude * pressure * TREL_HEAT_CAP_RATIO * (sqrt(pow((2.0 / (TREL_HEAT_CAP_RATIO + 1.0)), ((TREL_HEAT_CAP_RATIO + 1.0) / (TREL_HEAT_CAP_RATIO - 1.0))))) / pow((TREL_HEAT_CAP_RATIO * engine->fuel->const_burn_rate * long_secc_combus(engine)), 0.5f) : 0.0f;
        intern_gas_mass = produced_mass + intern_gas_mass - escape_massic_flux * step > 0 ? produced_mass + intern_gas_mass - escape_massic_flux * step : 0.0;
        fuel_mass = fuel_volume * (*rocket)->engine->fuel->density;
        produced_mass += fuel_mass;
        free_volume = total_volume - fuel_volume;
        res->rocket_mass[it] = (*rocket)->telemetry_mass + (*rocket)->parachute_mass + (*rocket)->fuselage_mass + (*rocket)->payload_mass + (*rocket)->engine->engine_mass + (*rocket)->engine->fuel->density * fuel_volume;
        res->rocket_weight[it] = res->rocket_mass[it] * gravitational_accel;
        res->rocket_drag[it] = 0.5 * atmospheric_density * (*rocket)->drag_coefficient * TRANSVERSAL_AREA((*rocket)->body_diameter) * res->rocket_speed[it - 1] * res->rocket_speed[it - 1];
        res->rocket_force_balance[it] = calc_force_balance(res->rocket_force[it], res->rocket_position[it - 1], res->rocket_speed[it - 1], res->rocket_drag[it], res->rocket_weight[it]);
        res->rocket_acceleration[it] = res->rocket_force_balance[it] / res->rocket_mass[it];
        res->rocket_speed[it] = res->rocket_acceleration[it] * step + res->rocket_speed[it - 1];
        res->rocket_position[it] = (res->rocket_speed[it] * step + res->rocket_position[it - 1]) * (res->rocket_speed[it] * step + res->rocket_position[it - 1] > 0.0);
        rocket_height = (*rocket)->initial_height + res->rocket_position[it];

        // Check for new max values
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

    return(0); // everything went well
}
