#ifndef RENDIMIENTOS
#define RENDIMIENTOS

#include <math.h>

#include "DLLDefines.h"
#include "structs.h"
#include "design_constants.h"
#include "design_func.h"
#include "comp_area.h"
#include "comp_tiempo.h"

// TODO: cambiar list[] por nombres mas descriptivos

//Constructores
float APPLIB_EXPORT volumen_combustible(engine_t *engine);
float APPLIB_EXPORT masa_combustible(engine_t* engine);
float APPLIB_EXPORT Tiempo_quemado_combustion(engine_t* engine);
float APPLIB_EXPORT Ab_combustion(engine_t* engine);
float APPLIB_EXPORT br_combustion(engine_t* engine);
float APPLIB_EXPORT mg_combustion(engine_t* engine);
float APPLIB_EXPORT emp_teo(engine_t* engine);
float APPLIB_EXPORT emp_prom(float list[]);
float APPLIB_EXPORT emp_max(float list[]);
float APPLIB_EXPORT I_sp_teo(engine_t* engine);
float APPLIB_EXPORT I_sp_esperado(float list[], engine_t *engine);
float APPLIB_EXPORT I_tot_teo(engine_t* engine);
float APPLIB_EXPORT I_tot_esp(float list[]);
float APPLIB_EXPORT Delta_V_Esp(float list[]);

#endif // RENDIMIENTOS
