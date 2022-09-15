#include "val_termod.h"

// Volumenes

// E49 Volumen Especifico Camara de Combustible
float vol_esp_cam_combustion(engine_t *engine)
{
    return (engine->temperature * CONSTANTE_GASES) / trel_get_pressure_pa(engine);

}

// E50 Volumen Especifico de Garganta
float vol_esp_garganta(engine_t *engine)
{
    return vol_esp_cam_combustion(engine) * (powf((HEAT_CAPACITY_RATIO + 1),(1 / HEAT_CAPACITY_RATIO - 1)));
}

// E51 Volumen Especifico Escape
float vol_esp_escape(engine_t *engine)
{
    return vol_esp_cam_combustion(engine) * powf((trel_get_pressure_pa(engine) / PRESION_ATMOSFERICA), (1 / HEAT_CAPACITY_RATIO));
}

// Presiones

// E53 presion de garganta
float presion_garganta(engine_t *engine)
{
    return trel_get_pressure_pa(engine) * powf((vol_esp_cam_combustion(engine) / vol_esp_garganta(engine)), (HEAT_CAPACITY_RATIO));
}

// Temperaturas

// E56 temperatura de garganta
float trel_temper_garganta(engine_t *engine)
{
    return engine->temperature * powf((vol_esp_cam_combustion(engine) / vol_esp_garganta(engine)),(HEAT_CAPACITY_RATIO - 1));
}


// E57 temperatura de escape
float presion_escape(engine_t *engine)
{
    return engine->temperature * (powf((PRESION_ATMOSFERICA / trel_get_pressure_pa(engine)),((HEAT_CAPACITY_RATIO - 1) / HEAT_CAPACITY_RATIO)));
}


// Velocidades

// E59 velocidad garganta
float velocidad_garganta(engine_t *engine)
{
    return powf(((2.0f * HEAT_CAPACITY_RATIO) / (HEAT_CAPACITY_RATIO + 1.0f) * CONSTANTE_GASES * engine->temperature),(0.5f));
}

// E60 Velocidad Sonica Local at
float vel_sonica_local_at(engine_t *engine)
{
    return powf((HEAT_CAPACITY_RATIO * CONSTANTE_GASES * presion_garganta(engine)),(0.5));
}

// E61 Numero Mach Mt
float vel_numero_mach_mt(engine_t *engine)
{
    return velocidad_garganta(engine) / vel_sonica_local_at(engine);
}

// E62 Velocidad de Escape
float velocidad_escape(engine_t *engine)
{
    return powf(powf(((2.0f * HEAT_CAPACITY_RATIO) / (HEAT_CAPACITY_RATIO - 1.0f) * CONSTANTE_GASES * engine->temperature* (1.0f - (PRESION_ATMOSFERICA /trel_get_pressure_pa(engine) ))),
    ((HEAT_CAPACITY_RATIO - 1.0f) / HEAT_CAPACITY_RATIO)), (0.5f));
}

// E63 Velocidad Sonica Local a2
float vel_sonica_local_a2(engine_t *engine)
{
    return powf((HEAT_CAPACITY_RATIO * CONSTANTE_GASES * presion_escape(engine)),(0.5)); 
}

// E64 Numero Mach M2
float vel_numero_mach_m2(engine_t *engine)

{
    return velocidad_escape(engine) / vel_sonica_local_a2(engine);
}

// E65 Velocidad de escape caracteristica
float vel_escape_caract(engine_t *engine)
{
    return powf(powf((CONSTANTE_GASES * engine->temperature) / (HEAT_CAPACITY_RATIO *(2 / (HEAT_CAPACITY_RATIO + 1))),((HEAT_CAPACITY_RATIO + 1) / (HEAT_CAPACITY_RATIO - 1))), (0.5));
}

