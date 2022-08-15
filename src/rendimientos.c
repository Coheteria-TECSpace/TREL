#include "rendimientos.h"

/*Otras variables adyacentes */
/*E43 */
float br_combustion(engine_t *engine)
{
    return (engine->fuel->const_burn_rate* powf(trel_get_pressure_pa(engine) * FACT_CONV_BR, engine->fuel->pressure_exponent) * FACT_CONV_M_TO_I);
}

/*Combustible */

/*E67 Volumen_Combustible */
float volumen_combustible(engine_t *engine)
{
    return(float)(TREL_PI*engine->grains->longitude*engine->grains->amount*(powf(engine->grains->extern_radius,2.0f)-powf(engine->grains->init_inter_radius,2.0f)));
}

/*E68 Masa_Combustible */
float masa_combustible(engine_t *engine)
{
    return (volumen_combustible(engine) *engine->fuel->density);
}

/*Combustión*/

/*E70 Tiempo de quemado total_Combustible*/
float Tiempo_quemado_combustion(engine_t *engine)
{
    return (engine->grains->extern_radius-engine->grains->init_inter_radius)/br_combustion(engine);
}

/*E71 Área de quemado */
float Ab_combustion(engine_t *engine)
{
    return (prom_A_Quemado()*engine->grains->amount);
}

/*E72 Flujo másico*/
float mg_combustion(engine_t *engine)
{
    return Ab_combustion(engine)*engine->fuel->density*br_combustion(engine);
}

/*Fuerzas*/

/*E74 Empuje teórico*/
float emp_teo(engine_t *engine)
{
    return mg_combustion(engine)*velocidad_escape(engine);
}

/*E76 Empuje promedio esperado*/
float emp_prom(float list[])
{
    return empuje_prom_tiempo(list);
}

/*E78 Empuje máximo esperado*/
float emp_max(float list[])
{
    float max = 0;
    long unsigned int n;
    for (n = 0; n < sizeof(*list); n++)
    {
        if (list[n] > max)
        {
            max = list[n];
        }
    }
    return max;
}

/*Impulsos*/

/*E81 Impulso específico teórico*/
float I_sp_teo(engine_t *engine)
{
    return velocidad_escape(engine)/GRAVITY;
}

/*E82 Impulso específico esperado*/
float I_sp_esperado(float list[], engine_t *engine)
{
    return (float)(impulso_esp(list, engine)/(masa_combustible(engine)*GRAVITY));
}

/*E83 Impulso total teórico*/
float I_tot_teo(engine_t *engine)
{
    return emp_teo(engine)* Tiempo_quemado_combustion(engine);
}

/*E84 Impulso total esperado*/
float I_tot_esp(float list[])
{
    return impulso_tot(list);
}

/*E85 Delta V esperado*/
float Delta_V_Esp(float list[])
{
    return delta_V(list);
}
