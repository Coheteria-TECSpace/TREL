#include "val_termod.h"

// Volumenes

// E49 Volumen Especifico Camara de Combustible
double vol_esp_cam_combustion(engine_t *engine)
{
    return (engine->temperature * CONSTANTE_GASES) / trel_get_pressure_pa(engine);

}

// E50 Volumen Especifico de Garganta
double vol_esp_garganta(engine_t *engine)
{
    return vol_esp_cam_combustion(engine) * (pow((HEAT_CAPACITY_RATIO + 1),(1 / HEAT_CAPACITY_RATIO - 1)));
}

// E51 Volumen Especifico Escape
double vol_esp_escape(engine_t *engine)
{
    return vol_esp_cam_combustion(engine) * pow((trel_get_pressure_pa(engine) / PRESION_ATMOSFERICA), (1 / HEAT_CAPACITY_RATIO));
}

// Presiones

// E53 presion de garganta
double presion_garganta(engine_t *engine)
{
    return trel_get_pressure_pa(engine) * pow((vol_esp_cam_combustion(engine) / vol_esp_garganta(engine)), (HEAT_CAPACITY_RATIO));
}

// Temperaturas

// E56 temperatura de garganta
double trel_temper_garganta(engine_t *engine)
{
    return engine->temperature * pow((vol_esp_cam_combustion(engine) / vol_esp_garganta(engine)),(HEAT_CAPACITY_RATIO - 1));
}


// E57 temperatura de escape
double presion_escape(engine_t *engine)
{
    return engine->temperature * (pow((PRESION_ATMOSFERICA / trel_get_pressure_pa(engine)),((HEAT_CAPACITY_RATIO - 1) / HEAT_CAPACITY_RATIO)));
}


// Velocidades

// E59 velocidad garganta
double velocidad_garganta(engine_t *engine)
{
    return pow(((2.0f * HEAT_CAPACITY_RATIO) / (HEAT_CAPACITY_RATIO + 1.0f) * CONSTANTE_GASES * engine->temperature),(0.5f));
}

// E60 Velocidad Sonica Local at
double vel_sonica_local_at(engine_t *engine)
{
    return pow((HEAT_CAPACITY_RATIO * CONSTANTE_GASES * presion_garganta(engine)),(0.5));
}

// E61 Numero Mach Mt
double vel_numero_mach_mt(engine_t *engine)
{
    return velocidad_garganta(engine) / vel_sonica_local_at(engine);
}

// E63 Velocidad Sonica Local a2
double vel_sonica_local_a2(engine_t *engine)
{
    return pow((HEAT_CAPACITY_RATIO * CONSTANTE_GASES * presion_escape(engine)),(0.5)); 
}

// E64 Numero Mach M2
double vel_numero_mach_m2(engine_t *engine)

{
    return calc_escape_vel(engine) / vel_sonica_local_a2(engine);
}

// E65 Velocidad de escape caracteristica
double vel_escape_caract(engine_t *engine)
{
    return pow(pow((CONSTANTE_GASES * engine->temperature) / (HEAT_CAPACITY_RATIO *(2 / (HEAT_CAPACITY_RATIO + 1))),((HEAT_CAPACITY_RATIO + 1) / (HEAT_CAPACITY_RATIO - 1))), (0.5));
}
