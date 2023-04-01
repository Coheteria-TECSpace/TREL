#include "design_func.h"
/*Hoja de Excel: Diseño*/

/*Functions*/
// E25 returns chamber pressure in pascals
double trel_get_pressure_pa(engine_t* engine)
{
	return(trel_psi_to_pa(engine->pressure));
}

//E34 returns the grain standard deviation
double desv_est_grains(engine_t *engine)
{
	return((double)(engine->comp_area_values->burn_std_deviation)*10000.0f);
}

//E35 Volumen unitario granos
double volumen_unitario(engine_t *engine)
{
	return(TREL_PI*(0.1)*((engine->grains->extern_radius)*(engine->grains->extern_radius)-(0.01)*(0.01)));
}

// E36 Masa unitaria grano
double masa_unitaria(engine_t* engine)
{
	return(volumen_unitario(engine)*1000.0f*(engine->fuel->density));
}

// E37 Longitud total con combustible
double longitudt_ccombustible(engine_t *engine)
{
	return((engine->grains->amount)*(engine->grains->longitude));
}

// E38 Port Area
double port_area(engine_t* engine)
{
	return(TREL_PI*(engine->grains->init_inter_radius)*(engine->grains->init_inter_radius));
}

// E39
double long_secc_combus(engine_t* engine)
{
	return((engine->grains->grain_separation)*((engine->grains->amount)-1.0)+((engine->grains->longitude)*(engine->grains->amount)));
}

// E49 Volumen especifico camara
double volumen_camara(engine_t *engine)
{
	return(engine->temperature*TREL_GAS_CONST/trel_get_pressure_pa(engine));
}
// E62 Velocidad de 

double calc_escape_vel(engine_t* engine)
{	
	double calc_pow = pow((TREL_ATMOSPHERIC_PRESSURE / trel_get_pressure_pa(engine)), ((TREL_HEAT_CAP_RATIO - 1.0) / TREL_HEAT_CAP_RATIO));
	return(sqrt(2.0 * TREL_HEAT_CAP_RATIO /(TREL_HEAT_CAP_RATIO -1.0) * TREL_GAS_CONST * engine->temperature * (1.0 - calc_pow)));
}

/* Determinacion de fuerza sobre tapas*/
// E140 Area interna
double area_interna(engine_t *engine)
{
	return(TREL_PI*pow(engine->tube->internal_radius,2));
}
// E141 Fuerza maxima
double fuerza_maxima(engine_t *engine)
{
	return(engine->max_pressure*area_interna(engine)); 
}
// E142 Fuerza por tornillo
double fuerza_tornillo(engine_t *engine)
{
	return(fuerza_maxima(engine)/engine->screws->amount);
}
/*Esfuerzo circunferencial*/
// E144 Tension
double tension(engine_t *engine)
{
	return(fuerza_maxima(engine)/engine->tube->material_area);
}
// E145 Margen de seguridad
double margen_de_seguridad(engine_t *engine)
{
	return(engine->tube->shear_stress_tension/tension(engine));
}
/*Esfuerzo longitudinal*/
// E146 Area de cortante
double area_de_cortante(engine_t *engine)
{
	return(engine->screws->width_cutting_segment*engine->tube->wall_thickness);
}
// E147 Cortante promedio
double cortante_promedio(engine_t *engine)
{
	return(fuerza_tornillo(engine)/area_de_cortante(engine));
}
// E148 Margen de seguridad cortante
double margen_de_seguridad_cortante(engine_t *engine)
{
	return(engine->tube->ult_stress_pressure/cortante_promedio(engine));
}
/*Esfuerzo de aplastamiento*/
// E149 Aplastamiento
double aplastamiento(engine_t *engine)
{
	return(fuerza_tornillo(engine)/engine->screws->area_per_screw);
}
// E150 Margen de seguridad aplaztamiento
double margen_de_seguridad_aplaztamiento(engine_t *engine)
{
	return(engine->tube->shear_stress_tension/aplastamiento(engine));
}
/*Deformacion circunferencial*/
// E152 Deformacion unitaria
double deformacion_unitaria(engine_t *engine)
{
	return(engine->tangencial_stress/engine->tube->young_module);
}
// E153 Circunferencia interna total
double circunferencia_interna_total(engine_t *engine)
{
	return(2*TREL_PI*engine->tube->internal_radius);
}
// E154 Deformacion de la circunferencia interna
double deformacion_circunferencia_interna(engine_t *engine)
{
	return(deformacion_unitaria(engine)*circunferencia_interna_total(engine)*1000.0f);
}
// E155 Circunferencia externa inicial
double circunferencia_externa_inicial(engine_t *engine)
{
	return(TREL_PI*engine->tube->diameter_ext);
}
// E156 Deformacion de circunferencia externa
double deformacion_circunferencia_externa(engine_t *engine)
{
	return(circunferencia_externa_inicial(engine)*deformacion_unitaria(engine)*1000);
}
// E157 Radio interno final
// radio_final(circunferencia_interna_total(),deformacion_circunferencia_interna());
double radio_final(double circ_total,double deform_circ)
{
	return(circ_total*(deform_circ/1000.0f)/(2.0f*TREL_PI));
}
// E158 Diferencia de radio interno
//double engine->tube->internal_radius = 1;	// Dependencia E15
double diferencia_radio_interno(engine_t *engine)
{
	return(radio_final(circunferencia_interna_total(engine),deformacion_circunferencia_interna(engine))-engine->tube->internal_radius*1000.0f);
}
// E159 es la misma ecuacion de E157
// radio_final(circunferencia_interna_inicial(),deformacion_circunferencia_externa());
// E160 Diferencia radio externo
double diferencia_radio_externo(engine_t *engine)
{
	return((radio_final(circunferencia_externa_inicial(engine),deformacion_circunferencia_externa(engine))-(engine->tube->diameter_ext/2.0f))*1000.0f);
}
/*Escape*/
// E88
double throat_area(engine_t *engine)
{
	return((double)mg_combustion(engine) * vol_esp_garganta(engine) / velocidad_garganta(engine));
}

// E89
double escape_area(engine_t* engine)
{
	return((double)mg_combustion(engine) * vol_esp_escape(engine) / calc_escape_vel(engine));
}

// E101 engine->nozzle_efficiency
void set_nozzle_efficiency(engine_t* engine, double value)
{
	engine->nozzle_efficiency = value;
}
