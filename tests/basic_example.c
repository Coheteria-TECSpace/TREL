#include <stdio.h>
#include <TREL.h>

int main(int argc, char *argv[])
{
	// Create a rocket structure
	trel_grains_t *engine_grains = trel_grains_init(
		4,
		0.01,
		0.0304,
		0.1,
		0.001
	);
	trel_fuel_t *engine_fuel = trel_fuel_init(
		0.005,
		0.688,
		1859
	);
	trel_screws_t *engine_screws = trel_screws_init(
		"Acero",
		6,
		0.007466,
		0.01
	);
    trel_tubing_t *engine_tube = trel_tubing_init(
        "Aluminio 6061-T6",
        0.073,
        0.0052,
        68900000000.0,
        275000000.0,
        -1,
        310000000,
        205000000,
		0.85
    );
	trel_engine_t *engine = trel_engine_init(
        800,
        1710,
		1.5,
		&engine_grains,
		&engine_fuel,
		&engine_tube,
		&engine_screws
    );
	trel_rocket_t* rocket = trel_rocket_init(
		&engine,   // engine
		0.3,       // telemetry_mass
		0.05,      // parachute_mass
		5.0,       // fuselage_mass
		1.5,       // payload_mass
		1207.0,    // initial_height
		9.936111,  // sim_latitude
		0.13,      // body_diameter
		0.4        // drag_coefficient
	);

	// Visualize the created objects
	// trel_print_grains(engine_grains); // We don't have such nice features yet
	// trel_print_fuel(engine_fuel);
	// trel_print_screws(engine_screws);
	// trel_print_tubing(engine_tubing);
	// trel_print_engine(engine);
	// trel_print_rocket(rocket);

	// Manually visualizing rocket values 
	printf("Rocket\n");
	printf("telemetry_mass %lf\n", rocket->telemetry_mass);
	printf("parachute_mass %lf\n", rocket->parachute_mass);
	printf("fuselage_mass %lf\n", rocket->fuselage_mass);
	printf("payload_mass %lf\n", rocket->payload_mass);
	printf("initial_height %lf\n", rocket->initial_height);
	printf("sim_latitude %lf\n", rocket->sim_latitude);
	printf("body_diameter %lf\n", rocket->body_diameter);
	printf("drag_coefficient %lf\n", rocket->drag_coefficient);

	// Manually visualizing a few values from the rocket time behavior
	printf("\nTotal Delta V: %lf\n", rocket->delta_v);
	printf("Maximum Thrust: %lf\n", rocket->max_thrust);
	printf("Average Thrust: %lf\n", rocket->avg_thrust);
	printf("Maximum Pressure: %lf\n\n", rocket->max_pressure);

	// Access area behavior data
	printf("Average Longitudinal Area: %lf\n", engine->comp_area_values->avg_long_area);
	printf("Average Burn Area: %lf\n", engine->comp_area_values->avg_burn_area);
	printf("Average Transversal Area: %lf\n", engine->comp_area_values->avg_trans_area);
	printf("Burn Standard Deviation: %lf\n", engine->comp_area_values->burn_std_deviation);
	printf("Burn Sum Differential: %lf\n", engine->comp_area_values->burn_sum_diff);
	
	// Access height simulation data
    printf("Max Rocket Height %lf\n", rocket->sim_values->max_rocket_height);
    printf("Max Rocket Position %lf\n", rocket->sim_values->max_rocket_position);
    printf("Max Rocket Speed %lf\n", rocket->sim_values->max_rocket_speed);
    printf("Max Rocket Acceleration %lf\n", rocket->sim_values->max_rocket_acceleration);
    printf("Max Rocket Force Balance %lf\n", rocket->sim_values->max_rocket_force_balance);
    printf("Max Rocket Drag %lf\n", rocket->sim_values->max_rocket_drag);

	// String memory test
	printf("\nScrews' material name: %s\n", engine_screws->material);

	// Freeing allocated memory
	trel_grains_free(&engine_grains);
	trel_fuel_free(&engine_fuel);
	trel_tubing_free(&engine_tube);
	trel_screws_free(&engine_screws);
	trel_engine_free(&engine);
	trel_rocket_free(&rocket);

	return(0);
}
