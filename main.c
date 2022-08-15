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
		0.01f,
		0.0304f,
		0.1f,
		0.001f
	);
	fuel_t* created_fuel = trel_fuel_init(
		0.005f,
		0.688f,
		1859
	);
	screws_t* created_screw = trel_screws_init(
		"Acero",
		6,
		0.007466f,
		0.01f
	);
	// Se inicializa la tuberia
    tubing_t* created_tube = trel_tubing_init(
        "Aluminio 6061-T6",
        0.073f,
        0.0052f,
        68900000000.0f,
        275000000.0f,
        -1,
        310000000,
        205000000
    );
	// Se inicializa el motor usando los tornillos y tuberia creados
	engine_t* testing_engine = trel_engine_init(
        800,
        1710,
		created_grains,
		created_fuel,
        created_tube,
        created_screw
    );

	// Acceder a memoria inicializada
	printf("La presion del motor dada es %f psi\n",trel_get_pressure(testing_engine));
	printf("\nLa velocidad de escape automaticamente inicializada es %f\n", trel_get_escape_vel(testing_engine));

	// Modificar valores de memoria con funciones
	trel_set_escape_vel(testing_engine, 666.420f);
	printf("\nLa velocidad de escape modificada con tsel_set_escape_vel() es %f\n", trel_get_escape_vel(testing_engine));

	// Usando una funcion de rendimientos.c
	printf("\nEl valor de combuistion es %f\n", br_combustion(testing_engine));

	// Usando una funcion de val_termod.c
	printf("\nLa temperatura en garganta es de %f\n", trel_temper_garganta(testing_engine));

	// Probando valores generados por comp_area.c
	printf("\nArea longitudinal promedio: %f\n", testing_engine->comp_area_values->avg_long_area);
	printf("Area quemado promedio: %f\n", testing_engine->comp_area_values->avg_burn_area);
	printf("Area transversal promedio: %f\n", testing_engine->comp_area_values->avg_trans_area);
	printf("Suma de diferencia quemado: %f\n", testing_engine->comp_area_values->burn_sum_diff);
	printf("Desviacion estandar area de quemado: %f\n", testing_engine->comp_area_values->burn_std_deviation);
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
