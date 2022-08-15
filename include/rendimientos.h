#ifndef RENDIMIENTOS_H
#define RENDIMIENTOS_H

#include <math.h>

#include "DLLDefines.h"
#include "structs.h"
#include "design_constants.h"
#include "design_func.h"
#include "comp_area.h"
#include "comp_tiempo.h"

// TODO: cambiar list[] por nombres mas descriptivos

// Function prototypes
float TREL_EXPORT volumen_combustible(engine_t *engine);
float TREL_EXPORT masa_combustible(engine_t* engine);
float TREL_EXPORT Tiempo_quemado_combustion(engine_t* engine);
double TREL_EXPORT Ab_combustion(engine_t* engine);
float TREL_EXPORT br_combustion(engine_t* engine);
double TREL_EXPORT mg_combustion(engine_t* engine);
double TREL_EXPORT emp_teo(engine_t* engine);
float TREL_EXPORT emp_prom(float list[]);
float TREL_EXPORT emp_max(float list[]);
float TREL_EXPORT I_sp_teo(engine_t* engine);
float TREL_EXPORT I_sp_esperado(float list[], engine_t *engine);
double TREL_EXPORT I_tot_teo(engine_t* engine);
float TREL_EXPORT I_tot_esp(float list[]);
float TREL_EXPORT Delta_V_Esp(float list[]);

#endif //RENDIMIENTOS_H
