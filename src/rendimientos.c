#include "rendimientos.h"

/*Otras variables adyacentes */
/*E43 */
double br_combustion(engine_t *engine)
{
    return ((*engine->fuel)->const_burn_rate* pow(trel_get_pressure_pa(engine) * 
            FACT_CONV_BR, (*engine->fuel)->pressure_exponent) * FACT_CONV_M_TO_I);
}

/*Combustible */

/*E67 Volumen_Combustible */
double volumen_combustible(engine_t *engine)
{
    return(double)(TREL_PI*(*engine->grains)->longitude*(*engine->grains)->amount*(pow(
                  (*engine->grains)->extern_radius,2.0f)-pow((*engine->grains)->init_inter_radius,2.0f)));
}

/*E68 Masa_Combustible */
double masa_combustible(engine_t *engine)
{
    return (volumen_combustible(engine) *(*engine->fuel)->density);
}

/*Combustión*/

/*E70 Tiempo de quemado total_Combustible*/
double Tiempo_quemado_combustion(engine_t *engine)
{
    return ((*engine->grains)->extern_radius-(*engine->grains)->init_inter_radius)/br_combustion(engine);
}

/*E71 Área de quemado */
double Ab_combustion(engine_t *engine)
{
    return (engine->comp_area_values->avg_burn_area*(*engine->grains)->amount);
}

/*E72 Flujo másico*/
double mg_combustion(engine_t *engine)
{
    return Ab_combustion(engine)*(*engine->fuel)->density*br_combustion(engine);
}

/*Fuerzas*/

/*E74 Empuje teórico*/
double emp_teo(engine_t *engine)
{
    return mg_combustion(engine)*calc_escape_vel(engine);
}

/*E76 Empuje promedio esperado*/
double emp_prom(trel_rocket_t* rocket)
{
    if (!rocket->avg_thrust)
        trel_run_time_comp_iterations(&rocket);
    return(rocket->avg_thrust);
}

/*E78 Empuje máximo esperado*/
double emp_max(trel_rocket_t* rocket)
{
    return(rocket->max_thrust);
}

/*Impulsos*/

/*E81 Impulso específico teórico*/
double I_sp_teo(engine_t *engine)
{
    return calc_escape_vel(engine)/TREL_GRAV_CONST;
}

/*E82 Impulso específico esperado*/
double I_sp_esperado(engine_t* engine)
{
    return((*engine->fuel)->density);
}

/*E83 Impulso total teórico*/
double I_tot_teo(engine_t *engine)
{
    return emp_teo(engine)* Tiempo_quemado_combustion(engine);
}

/*E84 Impulso total esperado*/
double I_tot_esp(engine_t* engine)
{
    return(br_combustion(engine));
}

/*E85 Delta V esperado*/
double Delta_V_Esp(trel_rocket_t* rocket)
{
    return(rocket->delta_v);
}
