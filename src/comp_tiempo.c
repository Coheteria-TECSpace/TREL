//Proms_Comportamiento_Tiempo//
#include "rendimientos.h"

//Lista definida desde AB32:AB1149
float empuje_prom_tiempo(float list[])
{
    float prom_final = 0;
    int cont = 0;
    for (long unsigned int n = 0; n < sizeof(*list); n++)
    {
        if (list[n] > 0)
        {
            prom_final = prom_final + list[n];
            cont += 1;
        }
    }
    prom_final = prom_final / cont;
    return prom_final;
}

//E25
float impulso_tot(float list[])
{
    float IT = 0;
    for (long unsigned int n = 0; n < sizeof(*list); n++)
    {
        IT = IT + list[n];
    }
    return IT;
}

//E26
float impulso_esp(float list[], engine_t *engine)
{
    return impulso_tot(list) / (masa_combustible(engine) * 9.81f);
}

//AD3511
float delta_V(float list[])
{
    float DeltaV = 0;
    for (long unsigned int n = 0; n < sizeof(*list); n++)
    {
        DeltaV = DeltaV + list[n];
    }

    return DeltaV;
}
