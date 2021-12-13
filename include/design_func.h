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
float APPLIB_EXPORT tsel_get_pressure_pa(engine_t* engine);
float APPLIB_EXPORT volumen_camara(engine_t* engine);
float APPLIB_EXPORT calc_escape_vel(engine_t *engine);
float APPLIB_EXPORT area_interna(engine_t* engine);
float APPLIB_EXPORT fuerza_maxima(engine_t* engine);
float APPLIB_EXPORT fuerza_tornillo(engine_t* engine);
float APPLIB_EXPORT tension(engine_t* engine);
float APPLIB_EXPORT margen_de_seguridad(engine_t* engine);
float APPLIB_EXPORT area_de_cortante(engine_t* engine);
float APPLIB_EXPORT cortante_promedio(engine_t* engine);
float APPLIB_EXPORT margen_de_seguridad_cortante(engine_t* engine);
float APPLIB_EXPORT aplastamiento(engine_t* engine);
float APPLIB_EXPORT margen_de_seguridad_aplaztamiento(engine_t* engine);

#endif //DESIGN_FUNC_H
