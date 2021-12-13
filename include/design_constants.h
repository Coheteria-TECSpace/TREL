#ifndef TSEL_CONSTANTS
#define TSEL_CONSTANTS

//Constantes matemáticas
#define TSEL_PI 3.141592f					// PI

//Recamara 
#define press_Pa (800.0f*6894.757f)			//E25 float input

//Constantes Físicas
#define GRAVITY 9.81f					// g

#define PRESION_ATMOSFERICA 101325.0f   /* E9   */
#define HEAT_CAPACITY_RATIO 1.043f		/* E46  */
#define CONSTANTE_GASES 196.14f			/* E47  */

//Constantes - rendimientos - 
//#define cant_granos 4.0f				// E29
//#define ri 0.01f 						// E30
//#define re 0.0304f						// E31
//#define Lg 0.1f							// E32
//#define const_a_br 0.005f				// E41
//#define const_n_br 0.688f				// E42
//#define dens_comb 1859.0f				// E44
#define FACT_CONV_BR 0.000145038f		// factor de conversion para la tasa de quemado
#define FACT_CONV_M_TO_I 0.0254f		//factor de conversion de metros a pulgadas

//Comportamiento en el tiempo//
// TODO: revisar esto
//#define I_T
//#define I_sp

//Valores termodinámicos//
#define escape 0						// E62 float var

#endif // TSEL_CONSTANTS
