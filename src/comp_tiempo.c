#include "comp_tiempo.h"

//Lista definida desde AB32:AB1149
/*
float empuje_prom_tiempo(float list[])
{
    float prom_final = 0;
    int cont = 0;
    for (long unsigned int n = 0; n < sizeof(*list); n++)
    {
        if (list[n] > 0)
        {
            prom_final = prom_final + list[n];
            cont += 1;
        }
    }
    prom_final = prom_final / cont;
    return prom_final;
}*/

//Comportamiento en el Tiempo!AD3511
int trel_run_time_comp_iterations(trel_rocket_t* rocket)
{
    engine_t* engine = rocket->engine;

    // iterate over given iterations and step size
    const float max_iterations = 1000.0f;
    const float burn_time = Tiempo_quemado_combustion(engine);
    const float step = burn_time / max_iterations;
    float time = 0.0f; // time in seconds

    // variables for iteration
    double dead_mass = rocket->fuselage_mass + rocket->parachute_mass + rocket->telemtry_mass + engine->egine_mass;
    const float delta_t = step;
    float pressure_abs = PRESION_ATMOSFERICA;
    float pressure = pressure_abs / 6894.757f;
    float pressure_man = pressure_abs - PRESION_ATMOSFERICA;
    float burn_rate = engine->fuel->const_burn_rate * powf(pressure_abs * 0.000145038f, engine->fuel->pressure_exponent) * 0.0254f;
    float inst_radius = engine->grains->init_inter_radius;
    float inst_long = engine->grains->longitude;
    float trans_area = inst_radius > 0 ? TREL_PI * engine->grains->extern_radius * engine->grains->extern_radius - inst_radius * inst_radius : 0.0f;
    float long_area = trans_area == 0 ? 0.0f : 2 * TREL_PI * inst_radius * inst_long;
    float burn_area = trans_area * 2 + long_area;
    float total_burn_area = burn_area > 0 ? burn_area * engine->grains->extern_radius : 0.0f;
    float fuel_vol = engine->grains->extern_radius * TREL_PI * (engine->grains->extern_radius * engine->grains->extern_radius - inst_radius * inst_radius) * inst_long;
    float fuel_mass = engine->fuel->density * fuel_vol;
    float produced_mass = 0.0f;
    float produced_massic_flux = 0.0f;
    float escape_massic_flux = 0.0f;
    float flux_diff = produced_massic_flux - escape_massic_flux;
    float escape_delta_m = 0.0f;
    float free_vol = port_area(engine) - fuel_vol;
    float internal_mass = (free_vol * pressure_abs) / (long_secc_combus(engine) * engine->fuel->const_burn_rate);
    float areas_ratio = total_burn_area / engine->grains->longitude;
    float virtual_escape_pressure = pressure_abs / powf((1 + ((HEAT_CAPACITY_RATIO - 1) / 2) * volumen_unitario(engine) * volumen_unitario(engine)), (engine->tube->ult_stress_tension / (engine->tube->ult_stress_tension - 1)));
    float real_escape_pressure = pressure_abs / powf((1 + ((HEAT_CAPACITY_RATIO - 1) / 2) * volumen_unitario(engine) * volumen_unitario(engine)), (HEAT_CAPACITY_RATIO / (HEAT_CAPACITY_RATIO - 1))) < PRESION_ATMOSFERICA ? PRESION_ATMOSFERICA : pressure_abs / powf((1 + ((HEAT_CAPACITY_RATIO - 1) / 2) * volumen_unitario(engine) * volumen_unitario(engine)), (HEAT_CAPACITY_RATIO / (HEAT_CAPACITY_RATIO - 1)));
    float force_coeff = powf((((2 * HEAT_CAPACITY_RATIO * HEAT_CAPACITY_RATIO) / (HEAT_CAPACITY_RATIO - 1)) * powf((2 / (HEAT_CAPACITY_RATIO + 1)), ((HEAT_CAPACITY_RATIO + 1) / (HEAT_CAPACITY_RATIO - 1))) * ((1 - powf((virtual_escape_pressure / pressure_abs), ((HEAT_CAPACITY_RATIO - 1) / HEAT_CAPACITY_RATIO))))), 0.5f) + (((virtual_escape_pressure - PRESION_ATMOSFERICA) / (pressure_abs)) * (engine->grains->grain_separation / engine->grains->longitude));
    float adjusted_cr = force_coeff * desv_est_grains(engine);
    float force = adjusted_cr * pressure_abs * engine->grains->longitude > 0 ? adjusted_cr * pressure_abs * engine->grains->longitude : 0.0f;
    float total_thrust = 0.0f;
    float delta_v = total_thrust / (fuel_mass + (float)dead_mass);

    // sums for eventual result values
    double sum_delta_v = delta_v;
    double sum_avg_thrust = force;

    // variable for max thrust
    double max_thrust = force;

    // iteration loop
    for (int it = 0; it < max_iterations; it++)
    {
        pressure_abs = engine->fuel->const_burn_rate * long_secc_combus(engine) * internal_mass / free_vol;
        pressure = pressure_abs / 6894.757f;
        pressure_man = pressure_abs - PRESION_ATMOSFERICA;
        burn_rate = engine->fuel->const_burn_rate * powf(pressure_abs * 0.000145038f, engine->fuel->pressure_exponent) * 0.0254f;
        inst_radius = inst_radius > 0 && (inst_radius + burn_rate * delta_t) < engine->grains->extern_radius ? inst_radius + burn_rate * delta_t : 0;
        inst_long = inst_radius > 0 ? inst_long - burn_rate * delta_t * 2 : 0;
        trans_area = inst_radius > 0 ? TREL_PI * engine->grains->extern_radius * engine->grains->extern_radius - inst_radius * inst_radius : 0.0f;
        long_area = trans_area == 0 ? 0.0f : 2 * TREL_PI * inst_radius * inst_long;
        burn_area = trans_area * 2 + long_area;
        total_burn_area = burn_area > 0 ? burn_area * engine->grains->extern_radius : 0.0f;
        fuel_vol = engine->grains->extern_radius * TREL_PI * (engine->grains->extern_radius * engine->grains->extern_radius - inst_radius * inst_radius) * inst_long;
        produced_mass = fuel_mass - engine->fuel->density * fuel_vol;
        fuel_mass = engine->fuel->density * fuel_vol;
        produced_massic_flux = produced_mass / delta_t;
        escape_massic_flux = pressure_abs > PRESION_ATMOSFERICA ? engine->grains->longitude * pressure_abs * HEAT_CAPACITY_RATIO * (sqrtf(powf((2.0f / (HEAT_CAPACITY_RATIO + 1.0f)), ((HEAT_CAPACITY_RATIO + 1.0f) / (HEAT_CAPACITY_RATIO - 1.0f))))) / powf((HEAT_CAPACITY_RATIO * engine->fuel->const_burn_rate * long_secc_combus(engine)), 0.5f) : 0.0f;
        flux_diff = produced_massic_flux - escape_massic_flux;
        escape_delta_m = escape_massic_flux * delta_t;
        internal_mass = produced_mass + internal_mass - escape_delta_m > 0 ? produced_mass + internal_mass - escape_delta_m : 0.0f;
        areas_ratio = total_burn_area / engine->grains->longitude;
        virtual_escape_pressure = pressure_abs / powf((1 + ((HEAT_CAPACITY_RATIO - 1) / 2) * volumen_unitario(engine) * volumen_unitario(engine)), (engine->tube->ult_stress_tension / (engine->tube->ult_stress_tension - 1)));
        real_escape_pressure = pressure_abs / powf((1 + ((HEAT_CAPACITY_RATIO - 1) / 2) * volumen_unitario(engine) * volumen_unitario(engine)), (HEAT_CAPACITY_RATIO / (HEAT_CAPACITY_RATIO - 1))) < PRESION_ATMOSFERICA ? PRESION_ATMOSFERICA : pressure_abs / powf((1 + ((HEAT_CAPACITY_RATIO - 1) / 2) * volumen_unitario(engine) * volumen_unitario(engine)), (HEAT_CAPACITY_RATIO / (HEAT_CAPACITY_RATIO - 1)));
        force_coeff = powf((((2 * HEAT_CAPACITY_RATIO * HEAT_CAPACITY_RATIO) / (HEAT_CAPACITY_RATIO - 1)) * powf((2 / (HEAT_CAPACITY_RATIO + 1)), ((HEAT_CAPACITY_RATIO + 1) / (HEAT_CAPACITY_RATIO - 1))) * ((1 - powf((virtual_escape_pressure / pressure_abs), ((HEAT_CAPACITY_RATIO - 1) / HEAT_CAPACITY_RATIO))))), 0.5f) + (((virtual_escape_pressure - PRESION_ATMOSFERICA) / (pressure_abs)) * (engine->grains->grain_separation / engine->grains->longitude));
        adjusted_cr = force_coeff * desv_est_grains(engine);
        total_thrust = ((force + adjusted_cr * pressure_abs * engine->grains->longitude > 0 ? adjusted_cr * pressure_abs * engine->grains->longitude : 0.0f) / (2)) * delta_t;
        force = adjusted_cr * pressure_abs * engine->grains->longitude > 0 ? adjusted_cr * pressure_abs * engine->grains->longitude : 0.0f;
        delta_v = total_thrust / (fuel_mass + (float)dead_mass);

        // step time value
        if (time + step < burn_time)
            time += step;
        else
            time = 0;

        // add to delta_v sum and avg thrust
        sum_delta_v += delta_v;
        sum_avg_thrust += force;

        if (force > max_thrust)
            max_thrust = force;
    }

    // storing values
    rocket->delta_v = sum_delta_v;
    rocket->max_thrust = max_thrust;
    // calculate avg thrust
    rocket->avg_thrust = sum_avg_thrust / max_iterations;

    return(0);
}
