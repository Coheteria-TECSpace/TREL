#include <stdio.h>
#include <string.h>
// Header for all the library functions
#include <TREL.h>

// Example of how to use the library functions
void print_debug_example()
{
	// Se inicializan los tornillos
    printf("Inicializando structs\n");
	grains_t* created_grains = trel_grains_init(
		4,
		0.01,
		0.0304,
		0.1,
		0.001
	);
	fuel_t* created_fuel = trel_fuel_init(
		0.005,
		0.688,
		1859
	);
	screws_t* created_screw = trel_screws_init(
		"Acero",
		6,
		0.007466,
		0.01
	);

    //printf("Probando %i y %s\n", created_screw->amount, created_screw->material);
    printf("Probando %i\n", created_screw->amount);

	// Se inicializa la tuberia
    tubing_t* created_tube = trel_tubing_init(
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
	// Se inicializa el motor usando los tornillos y tuberia creados
	engine_t* testing_engine = trel_engine_init(
        800,
        1710,
		1.5,
		created_grains,
		created_fuel,
        created_tube,
        created_screw
    );
	// Se inicializa el cohete
	trel_rocket_t* testing_rocket = trel_rocket_init(
		testing_engine,  // engine
		0.3,             // telemetry_mass
		0.05,            // parachute_mass
		5.0,             // fuselage_mass
		1.5,             // payload_mass
		1207.0,          // initial_height
		9.936111,        // sim_latitude
		0.13,            // body_diameter
		0.4              // drag_coefficient
	);

	// Acceder a memoria inicializada
	printf("La presion del motor dada es %lf psi\n",trel_get_pressure(testing_engine));
	printf("\nLa velocidad de escape automaticamente inicializada es %lf\n", trel_get_escape_vel(testing_engine));

	// Modificar valores de memoria con funciones
	trel_set_escape_vel(testing_engine, 666.420);
	printf("\nLa velocidad de escape modificada con tsel_set_escape_vel() es %lf\n", trel_get_escape_vel(testing_engine));

	// Usando una funcion de rendimientos.c
	printf("\nEl valor de combuistion es %lf\n", br_combustion(testing_engine));

	// Usando una funcion de val_termod.c
	printf("\nLa temperatura en garganta es de %lf\n", trel_temper_garganta(testing_engine));

	// Probando valores generados por comp_area.c
	printf("\nArea longitudinal promedio: %lf\n", testing_engine->comp_area_values->avg_long_area);
	printf("Area quemado promedio: %lf\n", testing_engine->comp_area_values->avg_burn_area);
	printf("Area transversal promedio: %lf\n", testing_engine->comp_area_values->avg_trans_area);
	printf("Suma de diferencia quemado: %lf\n", testing_engine->comp_area_values->burn_sum_diff);
	printf("Desviacion estandar area de quemado: %lf\n", testing_engine->comp_area_values->burn_std_deviation);

	// Probando valores generados por comp_tiempo.c
	printf("\nDelta V total: %lf\n", testing_rocket->delta_v);
	printf("Maximo impulso: %lf\n", testing_rocket->max_thrust);
	printf("Impulso promedio: %lf\n", testing_rocket->avg_thrust);
	printf("Maxima presion: %lf\n", testing_rocket->max_pressure);

	// Probando valores generados por height_sim.c
	for (int i = 0; i < 50; i += 10)
		printf("Masa de cohete %lf\n", testing_rocket->rocket_mass[i]);
	
	// Printing rocket values
	printf("\nRocket data\n");
	printf("telemetry_mass %lf\n", testing_rocket->telemetry_mass);
	printf("parachute_mass %lf\n", testing_rocket->parachute_mass);
	printf("fuselage_mass %lf\n", testing_rocket->fuselage_mass);
	printf("payload_mass %lf\n", testing_rocket->payload_mass);
	printf("initial_height %lf\n", testing_rocket->initial_height);
	printf("avg_thrust %lf\n", testing_rocket->avg_thrust);
	printf("max_thrust %lf\n", testing_rocket->max_thrust);
	printf("delta_v %lf\n", testing_rocket->delta_v);
	printf("max_pressure %lf\n", testing_rocket->max_pressure);
	printf("sim_latitude %lf\n", testing_rocket->sim_latitude);
	printf("max_sim_height %lf\n", testing_rocket->max_sim_height);
	printf("body_diameter %lf\n", testing_rocket->body_diameter);
	printf("drag_coefficient %lf\n", testing_rocket->drag_coefficient);
	/*
	printf("rocket_position %lf\n", testing_rocket->rocket_position);
	printf("rocket_speed %lf\n", testing_rocket->rocket_speed);
	printf("rocket_acceleration %lf\n", testing_rocket->rocket_acceleration);
	printf("rocket_force_balance %lf\n", testing_rocket->rocket_force_balance);
	printf("rocket_drag %lf\n", testing_rocket->rocket_drag);
	printf("rocket_weight %lf\n", testing_rocket->rocket_weight);
	printf("rocket_mass %lf\n", testing_rocket->rocket_mass);
	printf("rocket_force %lf\n", testing_rocket->rocket_force);
	printf("time %lf\n", testing_rocket->time);
	*/

	printf("Tubing's material name: %s\n", created_tube->material);
	printf("Screws' material name: %s\n", created_screw->material);
}

// Para hacer pruebas de la lib se tiene la aplicacion de CLI basica
int main(int argc, char *argv[])
{
	printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("*         TECSpace Rocket Engine Lib          *\n");
	printf("*                v 0.2d                       *\n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
	if (argc <= 1)
	{
		printf(	"Usage: -f <enginefile> [options]\n"
				"Check help with : --help or -h\n");

		printf("\n* * *\nShowing debug example, gonna remove this for final CLI build\n* * *\n\n");

		print_debug_example();
	}
	else
	{
		int i;
		for (i = 1; i < argc; i++) {
			printf("Parameter %s\n", argv[i]);
			if (strncmp(argv[i],"-f",2) == 0) {
				if (i+1 < argc) {
					//-f toma el siguiente argumento
					if (strncmp(argv[i+1],"debug",6) == 0) {
						printf("\'-f debug\' showing the debugging example\n");
						print_debug_example();
					}
					else {
						printf("%s is not a valid file for -f\nRead --help\n", argv[i+1]);
					}
					i++;
				}
				else
				{
					printf("Missing arguments\n");
				}
			}
			else if (strncmp(argv[i],"--help",7) == 0 || strncmp(argv[i],"-h",3) == 0) {
				printf("This app hasn't been released yet, expect bugs\n\n");
				printf("--help (-h)\nShows this message\n\n");
				printf("-f <enginefile> [options]\nSelects the engine file to read and searches for options\n"
					"options should be given as [opt1,opt2,opt3] with no spaces\n"
					"there aren\'t avaliable options yet\n");
			}
			else
			{
				printf("Unknown parameter %s\n", argv[i]);
			}
			printf("\n");
		}
	}
	return(0);
}
