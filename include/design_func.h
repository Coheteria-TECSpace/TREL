#ifndef DESIGN_FUNC_H
#define DESIGN_FUNC_H

#include <math.h>

#include "design_constants.h"
#include "rendimientos.h"
#include "val_termod.h"
#include "structs.h"
#include "engine.h"
#include "DLLDefines.h"

// Function prototypes
double trel_get_pressure_pa(engine_t* engine);
double volumen_camara(engine_t* engine);
double calc_escape_vel(engine_t *engine);
double area_interna(engine_t* engine);
double fuerza_maxima(engine_t* engine);
double fuerza_tornillo(engine_t* engine);
double tension(engine_t* engine);
double margen_de_seguridad(engine_t* engine);
double area_de_cortante(engine_t* engine);
double cortante_promedio(engine_t* engine);
double margen_de_seguridad_cortante(engine_t* engine);
double aplastamiento(engine_t* engine);
double margen_de_seguridad_aplaztamiento(engine_t* engine);
double port_area(engine_t* engine);
double long_secc_combus(engine_t* engine);
double volumen_unitario(engine_t* engine);
double desv_est_grains(engine_t* engine);
double throat_area(engine_t* engine);

#endif //DESIGN_FUNC_H
