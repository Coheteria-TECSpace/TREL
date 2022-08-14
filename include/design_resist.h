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
// add TREL_EXPORT to any function needed from the dynamic library
void tsel_mean_tubing_diameter(engine_t *engine);
void tsel_width_condition(engine_t *engine);
void tsel_engine_max_pressure(engine_t *engine);
void tsel_tangencial_stress(engine_t *engine);
void tsel_logitudinal_stress(engine_t *engine);
void tsel_radial_stress(engine_t *engine);
void tsel_max_stress(engine_t *engine);
void tsel_margin_of_safety(engine_t *engine);
void tsel_transversal_area_tube(engine_t *engine);
void tsel_ang_circular_sector(engine_t *engine);
void tsel_area_per_screw(engine_t *engine);
void tsel_screw_occupied_area(engine_t *engine);
void tsel_tube_mateial_area(engine_t *engine);
void tsel_width_cutting_segment(engine_t *engine);

#endif //DESIGN_RESISTENCIA_H
