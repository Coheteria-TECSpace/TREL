#ifndef TREL_CONSTANTS
#define TREL_CONSTANTS

#define TREL_MAX_STR_LEN 100
#define TREL_MAX_ITERATIONS 1000

//Constantes matemáticas
#define TREL_PI 3.1415926535898			// PI

//Recamara 
#define press_Pa (800.0*6894.757)		//E25 double input

// Gravitational constants
#define TREL_GRAV_CONST 9.81	 // m/s^2
#define TREL_ECUATOR_GRAV_ACCEL 9.78032 // m/s^2
#define TREL_GRAV_CRUSH 0.0053024
#define TREL_GRAV_CRUSH_4 0.0000058
#define TREL_GRAV_A 0.000003086 // s^-2

// Atmospheric constants
#define TREL_ATMOSPHERIC_PRESSURE 101325.0   /* E9   */
#define TREL_ADIABATIC_GRADIENT 0.0065
#define TREL_STANDARD_TEMP 288.15
#define TREL_DRY_AIR_MOLAR_MASS 0.02896
#define TREL_IDEAL_GAS_CONST 8.31447 // J/mol*K

// Thermodinamic constants
#define TREL_HEAT_CAP_RATIO 1.043		/* E46  */
#define TREL_GAS_CONST 196.14	 // J/kg*K		/* E47  */

#define FACT_CONV_BR 0.000145038		// factor de conversion para la tasa de quemado
#define FACT_CONV_M_TO_I 0.0254		//factor de conversion de metros a pulgadas

#endif // TREL_CONSTANTS
