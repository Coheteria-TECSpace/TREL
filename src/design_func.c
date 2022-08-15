#include "design_func.h"
/*Hoja de Excel: Diseño*/

/*Constants*/
// E9 PRESION_ATMOSFERICA
// E46 'Heat Capacity ratio' HEAT_CAPACITY_RATIO
// E47 CONSTANTE_GASES
// E54 PRESION_ATMOSFERICA
// E162 DIAMETRO_NUCLEO

/*Functions*/
// E25 returns chamber pressure in pascals
float trel_get_pressure_pa(engine_t* engine)
{
	return(trel_psi_to_pa(engine->pressure));
}
// E49 Volumen especifico camara
float volumen_camara(engine_t *engine)
{
	return(engine->temperature*CONSTANTE_GASES/trel_get_pressure_pa(engine));
}
// E62 Velocidad de escape
float calc_escape_vel(engine_t* engine)
{	
	float calc_pow = powf((PRESION_ATMOSFERICA / trel_get_pressure_pa(engine)), ((HEAT_CAPACITY_RATIO - 1.0f) / HEAT_CAPACITY_RATIO));
	return(sqrtf(2.0f * HEAT_CAPACITY_RATIO /(HEAT_CAPACITY_RATIO -1.0f) * CONSTANTE_GASES * engine->temperature * (1.0f - calc_pow)));
}
/* Determinacion de fuerza sobre tapas*/
// E140 Area interna
float area_interna(engine_t *engine)
{
	return(TREL_PI*powf(engine->tube->internal_radius,2));
}
// E141 Fuerza maxima
float fuerza_maxima(engine_t *engine)
{
	return(engine->max_pressure*area_interna(engine)); 
}
// E142 Fuerza por tornillo
float fuerza_tornillo(engine_t *engine)
{
	return(fuerza_maxima(engine)/engine->screws->amount);
}
/*Esfuerzo circunferencial*/
// E144 Tension
float tension(engine_t *engine)
{
	return(fuerza_maxima(engine)/engine->tube->material_area);
}
// E145 Margen de seguridad
float margen_de_seguridad(engine_t *engine)
{
	return(engine->tube->shear_stress_tension/tension(engine));
}
/*Esfuerzo longitudinal*/
// E146 Area de cortante
float area_de_cortante(engine_t *engine)
{
	return(engine->screws->width_cutting_segment*engine->tube->wall_thickness);
}
// E147 Cortante promedio
float cortante_promedio(engine_t *engine)
{
	return(fuerza_tornillo(engine)/area_de_cortante(engine));
}
// E148 Margen de seguridad cortante
float margen_de_seguridad_cortante(engine_t *engine)
{
	return(engine->tube->ult_stress_pressure/cortante_promedio(engine));
}
/*Esfuerzo de aplastamiento*/
// E149 Aplastamiento
float aplastamiento(engine_t *engine)
{
	return(fuerza_tornillo(engine)/engine->screws->area_per_screw);
}
// E150 Margen de seguridad aplaztamiento
float margen_de_seguridad_aplaztamiento(engine_t *engine)
{
	return(engine->tube->shear_stress_tension/aplastamiento(engine));
}
/*Deformacion circunferencial*/
// E152 Deformacion unitaria
float deformacion_unitaria(engine_t *engine)
{
	return(engine->tangencial_stress/engine->tube->young_module);
}
// E153 Circunferencia interna total
float circunferencia_interna_total(engine_t *engine)
{
	return(2*TREL_PI*engine->tube->internal_radius);
}
// E154 Deformacion de la circunferencia interna
float deformacion_circunferencia_interna(engine_t *engine)
{
	return(deformacion_unitaria(engine)*circunferencia_interna_total(engine)*1000.0f);
}
// E155 Circunferencia externa inicial
float circunferencia_externa_inicial(engine_t *engine)
{
	return(TREL_PI*engine->tube->diameter_ext);
}
// E156 Deformacion de circunferencia externa
float deformacion_circunferencia_externa(engine_t *engine)
{
	return(circunferencia_externa_inicial(engine)*deformacion_unitaria(engine)*1000);
}
// E157 Radio interno final
// radio_final(circunferencia_interna_total(),deformacion_circunferencia_interna());
float radio_final(float circ_total,float deform_circ)
{
	return(circ_total*(deform_circ/1000.0f)/(2.0f*TREL_PI));
}
// E158 Diferencia de radio interno
//float engine->tube->internal_radius = 1;	// Dependencia E15
float diferencia_radio_interno(engine_t *engine)
{
	return(radio_final(circunferencia_interna_total(engine),deformacion_circunferencia_interna(engine))-engine->tube->internal_radius*1000.0f);
}
// E159 es la misma ecuacion de E157
// radio_final(circunferencia_interna_inicial(),deformacion_circunferencia_externa());
// E160 Diferencia radio externo
float diferencia_radio_externo(engine_t *engine)
{
	return((radio_final(circunferencia_externa_inicial(engine),deformacion_circunferencia_externa(engine))-(engine->tube->diameter_ext/2.0f))*1000.0f);
}
/*Resistencia de tornillos*/

/*Ecuacion de Barlow*/

/*Longitud maxima de Tornillo*/

/*O-ring's*/

/*Informacion*/

