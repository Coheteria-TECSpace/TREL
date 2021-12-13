#include <design_resist.h>

/*****
Implementacion original por Kevin, en Python
Inicio de traduccion a C por lross2k
******/

// Variables necesarias de partes anteriores
//float temp_E13 = 0.0730f;
//float temp_E14 = 0.0052f;
//float temp_E15 = 0.0314f;

// Resistencia de materiales E115
void tsel_mean_tubing_diameter(engine_t *engine)
{
    engine->tube->mean_tubing_diameter = engine->tube->diameter_ext-engine->tube->wall_thickness;
}
// condición de espesor del tubo E116
void tsel_width_condition(engine_t *engine)
{
    engine->width_condition = engine->tube->mean_tubing_diameter/engine->tube->wall_thickness;
}
// Presión maxima E118
void tsel_engine_max_pressure(engine_t *engine)
{
    // TODO: max_pressure = get_max(float *sim_data, int n_sim_data)
    engine->max_pressure = 5.95f*powf(10,6); // Pascal
    //engine.max_pressure = 5.95*e**6 # Pascales (Obtenido de simulación)
    //engine.pmax = 863.01 #PSI
}

/* Esfuerzo por presión */
// Esfuezo Tangencial E121
void tsel_tangencial_stress(engine_t *engine)
{
    // TODO: implement into engine
    // could be done branchless
    if (engine->width_condition> 20.0f)
    {
        engine->tangencial_stress = engine->max_pressure*engine->tube->internal_radius/engine->tube->wall_thickness;
    }
    else
    {
        engine->tangencial_stress = engine->max_pressure*(powf((engine->tube->diameter_ext/2.0f),2.0f)+powf(engine->tube->internal_radius,2.0f))/(powf(engine->tube->diameter_ext/2.0f,2.0f)-powf(engine->tube->internal_radius,2.0f));
    }
}
// Esfuerzo Longitudinal E122
void tsel_logitudinal_stress(engine_t *engine)
{
    if (engine->width_condition > 20.0f)
    {
        engine->longitudinal_stress = engine->max_pressure*engine->tube->internal_radius/2.0f*engine->tube->wall_thickness;
    }
    else
    {
        engine->longitudinal_stress = engine->max_pressure*powf(engine->tube->internal_radius,2.0f)/(powf(engine->tube->diameter_ext,2.0f)-powf(engine->tube->internal_radius,2.0f));
    }
}
// Esfuerzo Radial E123
void tsel_radial_stress(engine_t *engine)
{
    if (engine->width_condition > 20.0f)
    {
        engine->radial_stress = 0.0f;
    }
    else
    {            
        engine->radial_stress = -engine->max_pressure;
    }
}
// Esfuerzo Maximo E125
void tsel_max_stress(engine_t *engine)
{
    if (engine->tangencial_stress > engine->radial_stress)
    {
        engine->max_stress = engine->tangencial_stress;
    }
    else
    {
        engine->max_stress = engine->radial_stress;
    }
}
// Margen de Seguridad E127
void tsel_margin_of_safety(engine_t *engine)
{
    engine->margin_of_safety = engine->tube->shear_stress_tension/engine->max_stress;
}

/* Determinación de Areas afectadas por tornillos */

// engine_t has screws_t *screws to initialize at allocation
//engine->screws->n_screws = 6;
//engine->screws->diameter = 0.009f;
//engine->screws->dist_center_wall = 0.01f;

// Area_Transversal_tubo E133
// engine_t has tubing_t *tube
void tsel_transversal_area_tube(engine_t *engine)
{
    engine->tube->transversal_area = (float)TSEL_PI*(powf(engine->tube->diameter_ext/2.0f,2.0f)-powf(engine->tube->internal_radius,2.0f));
}
// Angulo de sector circular E134
void tsel_ang_circular_sector(engine_t *engine)
{
    engine->tube->sector_angle = (180.0f/TSEL_PI)*asinf((engine->screws->diameter/2)/engine->tube->internal_radius);
}
// Area transversal de 1 tornillo E135
void tsel_area_per_screw(engine_t *engine)
{
    engine->screws->area_per_screw = (float)(engine->tube->sector_angle/2.0f)*(powf(engine->tube->diameter_ext/2.0f,2.0f)-powf(engine->tube->internal_radius,2.0f)-powf(engine->tube->wall_thickness,2.0f));
}
// Area transversal ocupada por los tornillos E136
void tsel_screw_occupied_area(engine_t *engine)
{
    engine->screws->screw_occupied_area = engine->screws->area_per_screw*engine->screws->amount;
}
// Area de material E137
void tsel_tube_mateial_area(engine_t *engine)
{
    engine->tube->material_area = engine->tube->transversal_area-engine->screws->screw_occupied_area;
}
// Espesor del segmento cortante E138
void tsel_width_cutting_segment(engine_t *engine)
{
    engine->screws->width_cutting_segment = engine->screws->dist_center_wall-(engine->screws->diameter/2.0f);
}
