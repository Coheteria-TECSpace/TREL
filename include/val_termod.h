#ifndef VAL_TERMOD_FUNC_H
#define VAL_TERMOD_FUNC_H 

#include <math.h>

#include "DLLDefines.h"
#include "design_constants.h"
#include "design_func.h"
#include "structs.h"

// Prototipos de funciones
float APPLIB_EXPORT vol_esp_cam_combustion(engine_t* engine);
float APPLIB_EXPORT vol_esp_garganta(engine_t* engine);
float APPLIB_EXPORT vol_esp_escape(engine_t* engine);
float APPLIB_EXPORT presion_garganta(engine_t* engine);
//float APPLIB_EXPORT presion_escape(engine_t* engine);	// TODO
float APPLIB_EXPORT trel_temper_garganta(engine_t *engine);
//float APPLIB_EXPORT temper_escape(engine_t* engine);
float APPLIB_EXPORT velocidad_garganta(engine_t* engine);
float APPLIB_EXPORT vel_sonica_local_at(engine_t* engine);
float APPLIB_EXPORT vel_numero_mach_mt(engine_t* engine);
float APPLIB_EXPORT velocidad_escape(engine_t* engine);
float APPLIB_EXPORT vel_sonica_local_a2(engine_t* engine);
float APPLIB_EXPORT vel_numero_mach_m2(engine_t* engine);
float APPLIB_EXPORT vel_escape_caract(engine_t* engine);

#endif // VAL_TERMOD_FUNC_H

