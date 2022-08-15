#include "comp_area.h"

// TODO: Evaluate if we need dynamic allocation for this iteration

int trel_run_area_comp_iterations(engine_t* engine)
{
    // iterate over given iterations and step size
    const float max_iterations = 1000.0f;
    const float burn_time = Tiempo_quemado_combustion(engine);
    const float step = burn_time/max_iterations;
    float time = 0.0f; // time in seconds

    // burn rate value from propellant
    const float burn_rate = br_combustion(engine);

    // variables for iteration
    float inst_radius = 0.0f;
    float inst_long = 0.0f;

    // sums for eventual average value
    float transversal_area = 0.0f;
    float sum_transversal_area = 0.0f;
    float longitudinal_area = 0.0f;
    float sum_longitudinal_area = 0.0f;
    float burn_area = 0.0f;
    float sum_burn_area = 0.0f;

    // array for final values calculation
    float burn_area_array[1000];
    // initialize array
    for (int i = 0; i < 1000; i++)
        burn_area_array[i] = 0.0f;

    // iteration loop
    for (int it = 0; it < max_iterations; it++)
    {
        // instantaneous grain radius step
        inst_radius = engine->grains->init_inter_radius + burn_rate * time;

        // instantaneous grain longitude step
        inst_long = engine->grains->longitude - 2.0f * burn_rate * time;

        // add to transversal area sum
        transversal_area = TREL_PI * (engine->grains->extern_radius*engine->grains->extern_radius - 
                                      inst_radius * inst_radius);
        sum_transversal_area += transversal_area;
        
        // add to longitudinal area sum
        if (!transversal_area)
            longitudinal_area = 0.0f;
        else
            longitudinal_area = 2 * TREL_PI * inst_radius * inst_long;
        sum_longitudinal_area += longitudinal_area;

        // add to burn area sum
        burn_area_array[it] = transversal_area * 2 + longitudinal_area;
        sum_burn_area += burn_area_array[it];

        // step time value
        if (time + step < burn_time)
            time += step;
        else
            time = 0;
    }

    // calculate average transversal area
    transversal_area = sum_transversal_area / max_iterations;
    engine->comp_area_values->avg_trans_area = transversal_area;

    // calculate average longitudinal area
    longitudinal_area = sum_longitudinal_area / max_iterations;
    engine->comp_area_values->avg_long_area = longitudinal_area;

    // calculate average burn area
    burn_area = sum_burn_area / max_iterations;
    engine->comp_area_values->avg_burn_area = burn_area;

    // calculate the difference of each iteration's burn area and the average burn area
    for (int i = 0; i < max_iterations; i++)
        burn_area_array[i] = burn_area_array[i] - burn_area;

    // calculate standard deviation
    double burn_std_deviation = 0.0;
    // sum the squared burn area differences
    for (int i = 0; i < max_iterations; i++) burn_std_deviation += burn_area_array[i] * burn_area_array[i];
    // calculate the average of the squared differences
    burn_std_deviation /= 1000.0;
    // get the square root of the avg
    burn_std_deviation = sqrt(burn_std_deviation);
    // store the value in the engine
    engine->comp_area_values->burn_std_deviation = burn_std_deviation;

    // then sum all the greater than zero differences, store them to a variable, and 
    // sum all the lower than zero differences, store them to another variable
    float lt_differences = 0.0f; // lower
    float gt_differences = 0.0f; // greater

    for (int i = 0; i < max_iterations; i++)
        if (burn_area_array[i] > 0)
            gt_differences += burn_area_array[i];
        else
            lt_differences += burn_area_array[i];

    // calculate the difference of burn area by adding the two sums
    engine->comp_area_values->burn_sum_diff = gt_differences + lt_differences;
    
    return(0); // everything went well
}
