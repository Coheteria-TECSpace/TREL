from TREL import *
from TREL import _TREL_GRAINS_T

created_grains = _TREL_GRAINS_T.from_address(trel_grains_init(
        4,
        0.01,
        0.0304,
        0.1,
        0.001
        ))
p_created_grains = ctypes.pointer(created_grains)
p_p_created_grains = ctypes.pointer(p_created_grains)

created_fuel = TREL_FUEL.from_address(trel_fuel_init(
	0.005,
	0.688,
	1859))
p_created_fuel = ctypes.pointer(created_fuel)
p_p_created_fuel = ctypes.pointer(p_created_fuel)

created_screw = TREL_SCREWS.from_address(trel_screws_init(
        b"Acero",
	6,
	0.007466,
	0.01))
p_created_screw = ctypes.pointer(created_screw)
p_p_created_screw = ctypes.pointer(p_created_screw)

created_tube = TREL_TUBING.from_address(trel_tubing_init(
        b"Aluminio 6061-T6",
        0.073,
        0.0052,
        68900000000.0,
        275000000.0,
        -1,
        310000000,
        205000000,
        0.85))
p_created_tube = ctypes.pointer(created_tube)
p_p_created_tube = ctypes.pointer(p_created_tube)

created_engine = TREL_ENGINE.from_address(trel_engine_init(
        800.0,
        1710.0,
        1.5,
        p_p_created_grains,
        p_p_created_fuel,
        p_p_created_tube,
        p_p_created_screw))
p_created_engine = ctypes.pointer(created_engine)
p_p_created_engine = ctypes.pointer(p_created_engine)

created_rocket = TREL_ROCKET.from_address(trel_rocket_init(
        p_p_created_engine,
        0.3,
        0.05,
        5.0,
        1.5,
        1207.0,
        9.936111,
        0.13,
        0.4))
p_created_rocket = ctypes.pointer(created_rocket)
p_p_created_rocket = ctypes.pointer(p_created_rocket)

#trel_print_rocket(created_rocket)

trel_run_area_comp_iterations(p_p_created_engine)
trel_run_time_comp_iterations(p_p_created_rocket)
trel_run_height_sim_iterations(p_p_created_rocket)

#trel_grains_free(p_p_created_grains)
#trel_fuel_free(p_p_created_fuel)
#trel_tubing_free(p_p_created_tube)
#trel_screws_free(p_p_created_screw)
#trel_engine_free(p_p_created_engine)
#trel_rocket_free(p_p_created_rocket)

trel_print_rocket(created_rocket)
