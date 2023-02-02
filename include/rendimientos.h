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
double TREL_EXPORT volumen_combustible(engine_t *engine);
double TREL_EXPORT masa_combustible(engine_t* engine);
double TREL_EXPORT Tiempo_quemado_combustion(engine_t* engine);
double TREL_EXPORT Ab_combustion(engine_t* engine);
double TREL_EXPORT br_combustion(engine_t* engine);
double TREL_EXPORT mg_combustion(engine_t* engine);
double TREL_EXPORT emp_teo(engine_t* engine);
double TREL_EXPORT emp_prom(trel_rocket_t* rocket);
double TREL_EXPORT emp_max(trel_rocket_t* rocket);
double TREL_EXPORT I_sp_teo(engine_t* engine);
double TREL_EXPORT I_sp_esperado(engine_t* engine);
double TREL_EXPORT I_tot_teo(engine_t* engine);
double TREL_EXPORT I_tot_esp(engine_t* engine);
double TREL_EXPORT Delta_V_Esp(trel_rocket_t* rocket);

#endif //RENDIMIENTOS_H
