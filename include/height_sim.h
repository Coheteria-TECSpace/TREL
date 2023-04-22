#ifndef HEIGHT_SIM_H
#define HEIGHT_SIM_H

#include "design_func.h"

/* Function prototypes */
int TREL_EXPORT trel_run_height_sim_iterations(trel_rocket_t** rocket);
double calc_iter_virt_escape_pressure(double pressure, engine_t *engine);
double calc_iter_force_coeff(double virt_escape_pressure, double pressure, double atmospheric_pressure, engine_t *engine);
double calc_iter_escape_massic_flux(double pressure, double atmospheric_pressure, engine_t *engine);

#endif /*HEIGHT_SIM_H */
