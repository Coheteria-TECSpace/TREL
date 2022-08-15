#ifndef DESIGN_RESISTENCIA_H
#define DESIGN_RESISTENCIA_H

/*****
Implementacion original por Kevin, en Python
Inicio de traduccion a C por lross2k
******/

#include <math.h>

#include "design_constants.h"
#include "engine.h"
#include "DLLDefines.h"
#include "structs.h"

// TODO: remove temp_

// Function prototypes
// add APPLIB_EXPORT to any function needed from the dynamic library
void trel_mean_tubing_diameter(engine_t *engine);
void trel_width_condition(engine_t *engine);
void trel_engine_max_pressure(engine_t *engine);
void trel_tangencial_stress(engine_t *engine);
void trel_logitudinal_stress(engine_t *engine);
void trel_radial_stress(engine_t *engine);
void trel_max_stress(engine_t *engine);
void trel_margin_of_safety(engine_t *engine);
void trel_transversal_area_tube(engine_t *engine);
void trel_ang_circular_sector(engine_t *engine);
void trel_area_per_screw(engine_t *engine);
void trel_screw_occupied_area(engine_t *engine);
void trel_tube_mateial_area(engine_t *engine);
void trel_width_cutting_segment(engine_t *engine);

#endif //DESIGN_RESISTENCIA_H
