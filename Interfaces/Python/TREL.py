import ctypes
import os

TREL_MAX_STR_LEN = 100
TREL_MAX_ITERATIONS = 1000

if os.name == 'posix':
    TREL = ctypes.CDLL("../build/libTREL.so")
elif os.name == 'nt':
    TREL = ctypes.CDLL("../../out/build/x64-Release/TREL.dll")

# Struct for comp area simulation
class TREL_COMP_AREA(ctypes.Structure):
    _fields_ = [("avg_long_area", ctypes.c_double),
                ("avg_trans_area", ctypes.c_double),
                ("avg_burn_area", ctypes.c_double),
                ("burn_std_deviation", ctypes.c_double),
                ("burn_sum_diff", ctypes.c_double)]

# Struct and constructor for propellent grains
class TREL_GRAINS(ctypes.Structure):
    _fields_ = [("amount", ctypes.c_uint),
                ("init_inter_radius", ctypes.c_double),
                ("extern_radius", ctypes.c_double),
                ("longitude", ctypes.c_double),
                ("grain_separation", ctypes.c_double)]

trel_grains_init = TREL.trel_grains_init
trel_grains_init.argtypes = [ctypes.c_int,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double]
trel_grains_init.restype = ctypes.c_void_p

# Struct and constructor for fuel
class TREL_FUEL(ctypes.Structure):
    _fields_ = [("const_burn_rate", ctypes.c_double),
                ("pressure_exponent", ctypes.c_double),
                ("density", ctypes.c_double),
                ("burn_rate", ctypes.c_double)]

trel_fuel_init = TREL.trel_fuel_init
trel_fuel_init.argtypes = [ctypes.c_double,
                           ctypes.c_double,
                           ctypes.c_double]
trel_fuel_init.restype = ctypes.c_void_p

# Struct and constructor for screws
class TREL_SCREWS(ctypes.Structure):
    _fields_ = [("diameter", ctypes.c_double),
                ("dist_center_wall", ctypes.c_double),
                ("amount", ctypes.c_uint),
                ("area_per_screw", ctypes.c_double),
                ("screw_occupied_area", ctypes.c_double),
                ("material", TREL_MAX_STR_LEN * ctypes.c_char),
                ("width_cutting_segment", ctypes.c_double)]

trel_screws_init = TREL.trel_screws_init
trel_screws_init.argtypes = [ctypes.c_char_p,
                             ctypes.c_uint,
                             ctypes.c_double,
                             ctypes.c_double]
trel_screws_init.restype = ctypes.c_void_p

# Struct and constructor for tubing
class TREL_TUBING(ctypes.Structure):
    _fields_ = [("material", TREL_MAX_STR_LEN * ctypes.c_char),
                ("diameter_ext", ctypes.c_double),
                ("wall_thickness", ctypes.c_double),
                ("internal_radius", ctypes.c_double),
                ("young_module", ctypes.c_double),
                ("sector_angle", ctypes.c_double),
                ("mean_tubing_diameter", ctypes.c_double),
                ("shear_stress_tension", ctypes.c_double),
                ("shear_stress_pressure", ctypes.c_double),
                ("ult_stress_tension", ctypes.c_double),
                ("ult_stress_pressure", ctypes.c_double),
                ("transversal_area", ctypes.c_double),
                ("material_area", ctypes.c_double),
                ("nozzle_efficiency", ctypes.c_double)]

trel_tubing_init = TREL.trel_tubing_init
trel_tubing_init.argtypes = [ctypes.c_char_p,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double]
trel_tubing_init.restype = ctypes.c_void_p

# Struct and constructor for engine
class TREL_ENGINE(ctypes.Structure):
    _fields_ = [("engine_mass", ctypes.c_double),
                ("pressure", ctypes.c_double),
                ("escape_vel", ctypes.c_double),
                ("temperature", ctypes.c_double),
                ("width_condition", ctypes.c_double),
                ("margin_of_safety", ctypes.c_double),
                ("max_stress", ctypes.c_double),
                ("radial_stress", ctypes.c_double),
                ("tangencial_stress", ctypes.c_double),
                ("longitudinal_stress", ctypes.c_double),
                ("max_pressue", ctypes.c_double),
                ("nozzle_efficiency", ctypes.c_double),
                ("grains", ctypes.POINTER(ctypes.POINTER(TREL_GRAINS))),
                ("fuel", ctypes.POINTER(ctypes.POINTER(TREL_FUEL))),
                ("tube", ctypes.POINTER(ctypes.POINTER(TREL_TUBING))),
                ("screws", ctypes.POINTER(ctypes.POINTER(TREL_SCREWS))),
                ("comp_area_values", ctypes.POINTER(TREL_COMP_AREA))]

trel_engine_init = TREL.trel_engine_init
trel_engine_init.argtypes = [ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.POINTER(ctypes.POINTER(TREL_GRAINS)),
                             ctypes.POINTER(ctypes.POINTER(TREL_FUEL)),
                             ctypes.POINTER(ctypes.POINTER(TREL_TUBING)),
                             ctypes.POINTER(ctypes.POINTER(TREL_SCREWS))]
trel_engine_init.restype = ctypes.c_void_p

# Struct for sim values
class TREL_HEIGHT_SIM(ctypes.Structure):
    _fields_ = [("position", TREL_MAX_ITERATIONS * ctypes.c_double),
                ("speed", TREL_MAX_ITERATIONS * ctypes.c_double),
                ("acceleration", TREL_MAX_ITERATIONS * ctypes.c_double),
                ("force_balance", TREL_MAX_ITERATIONS * ctypes.c_double),
                ("drag", TREL_MAX_ITERATIONS * ctypes.c_double),
                ("weight", TREL_MAX_ITERATIONS * ctypes.c_double),
                ("mass", TREL_MAX_ITERATIONS * ctypes.c_double),
                ("force", TREL_MAX_ITERATIONS * ctypes.c_double),
                ("time", TREL_MAX_ITERATIONS * ctypes.c_double),
                ("max_height", ctypes.c_double),
                ("max_position", ctypes.c_double),
                ("max_speed", ctypes.c_double),
                ("max_acceleration", ctypes.c_double),
                ("max_force_balance", ctypes.c_double),
                ("max_drag", ctypes.c_double)]

# Struct and constructor for rocket
class TREL_ROCKET(ctypes.Structure):
    _fields_ = [("engine", ctypes.POINTER(ctypes.POINTER(TREL_ENGINE))),
                ("telemetry_mass", ctypes.c_double),
                ("parachute_mass", ctypes.c_double),
                ("fuselage_mass", ctypes.c_double),
                ("payload_mass", ctypes.c_double),
                ("initial_height", ctypes.c_double),
                ("avg_thrust", ctypes.c_double),
                ("max_thrust", ctypes.c_double),
                ("delta_v", ctypes.c_double),
                ("max_pressure", ctypes.c_double),
                ("sim_latitude", ctypes.c_double),
                ("body_diameter", ctypes.c_double),
                ("drag_coefficient", ctypes.c_double),
                ("sim_values", ctypes.POINTER(TREL_HEIGHT_SIM))]

trel_rocket_init = TREL.trel_rocket_init
trel_rocket_init.argtypes = [ctypes.POINTER(ctypes.POINTER(TREL_ENGINE)),
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double]
trel_rocket_init.restype = ctypes.c_void_p

trel_run_area_comp_iterations = TREL.trel_run_area_comp_iterations
trel_run_area_comp_iterations.argtypes = [ctypes.POINTER(ctypes.POINTER(TREL_ENGINE))]

trel_run_time_comp_iterations = TREL.trel_run_time_comp_iterations
trel_run_time_comp_iterations.argtypes = [ctypes.POINTER(ctypes.POINTER(TREL_ROCKET))]

trel_run_height_sim_iterations = TREL.trel_run_height_sim_iterations
trel_run_height_sim_iterations.argtypes = [ctypes.POINTER(ctypes.POINTER(TREL_ROCKET))]

trel_grains_free = TREL.trel_grains_free
trel_grains_free.argtypes = [ctypes.POINTER(ctypes.POINTER(TREL_GRAINS))]
trel_grains_free.restype = ctypes.c_void_p

trel_fuel_free = TREL.trel_fuel_free
trel_fuel_free.argtypes = [ctypes.POINTER(ctypes.POINTER(TREL_FUEL))]
trel_fuel_free.restype = ctypes.c_void_p

trel_tubing_free = TREL.trel_tubing_free
trel_tubing_free.argtypes = [ctypes.POINTER(ctypes.POINTER(TREL_TUBING))]
trel_tubing_free.restype = ctypes.c_void_p

trel_screws_free = TREL.trel_screws_free
trel_screws_free.argtypes = [ctypes.POINTER(ctypes.POINTER(TREL_SCREWS))]
trel_screws_free.restype = ctypes.c_void_p

trel_engine_free = TREL.trel_engine_free
trel_engine_free.argtypes = [ctypes.POINTER(ctypes.POINTER(TREL_ENGINE))]
trel_engine_free.restype = ctypes.c_void_p

trel_rocket_free = TREL.trel_rocket_free
trel_rocket_free.argtypes = [ctypes.POINTER(ctypes.POINTER(TREL_ROCKET))]
trel_rocket_free.restype = ctypes.c_void_p

def trel_print_rocket(rocket):
    print("\nGrains data")
    print("amount",                rocket.engine.contents.contents.grains.contents.contents.amount)
    print("init_inter_radius",     rocket.engine.contents.contents.grains.contents.contents.init_inter_radius)
    print("extern_radius",         rocket.engine.contents.contents.grains.contents.contents.extern_radius)
    print("longitude",             rocket.engine.contents.contents.grains.contents.contents.longitude)
    print("grain_separation",      rocket.engine.contents.contents.grains.contents.contents.grain_separation)

    print("\nFuel data")
    print("const_burn_rate",       rocket.engine.contents.contents.fuel.contents.contents.const_burn_rate)
    print("pressure_exponent",     rocket.engine.contents.contents.fuel.contents.contents.pressure_exponent)
    print("density",               rocket.engine.contents.contents.fuel.contents.contents.density)
    print("burn_rate",             rocket.engine.contents.contents.fuel.contents.contents.burn_rate)

    print("\nScrews data")
    print("diameter",              rocket.engine.contents.contents.screws.contents.contents.diameter)
    print("dist_center_wall",      rocket.engine.contents.contents.screws.contents.contents.dist_center_wall)
    print("area_per_screw",        rocket.engine.contents.contents.screws.contents.contents.area_per_screw)
    print("screw_occupied_area",   rocket.engine.contents.contents.screws.contents.contents.screw_occupied_area)
    print("width_cutting_segment", rocket.engine.contents.contents.screws.contents.contents.width_cutting_segment)
    print("material",              rocket.engine.contents.contents.screws.contents.contents.material.decode('ASCII'))
    print("amount",                rocket.engine.contents.contents.screws.contents.contents.amount)

    print("\nTubing data")
    print("material",              rocket.engine.contents.contents.tube.contents.contents.material.decode('ASCII'))
    print("diameter_ext",          rocket.engine.contents.contents.tube.contents.contents.diameter_ext)
    print("wall_thickness",        rocket.engine.contents.contents.tube.contents.contents.wall_thickness)
    print("internal_radius",       rocket.engine.contents.contents.tube.contents.contents.internal_radius)
    print("young_module",          rocket.engine.contents.contents.tube.contents.contents.young_module)
    print("sector_angle",          rocket.engine.contents.contents.tube.contents.contents.sector_angle)
    print("mean_tubing_diameter",  rocket.engine.contents.contents.tube.contents.contents.mean_tubing_diameter)
    print("shear_stress_tension",  rocket.engine.contents.contents.tube.contents.contents.shear_stress_tension)
    print("shear_stress_pressure", rocket.engine.contents.contents.tube.contents.contents.shear_stress_pressure)
    print("ult_stress_tension",    rocket.engine.contents.contents.tube.contents.contents.ult_stress_tension)
    print("ult_stress_pressure",   rocket.engine.contents.contents.tube.contents.contents.ult_stress_pressure)
    print("transversal_area",      rocket.engine.contents.contents.tube.contents.contents.transversal_area)
    print("material_area",         rocket.engine.contents.contents.tube.contents.contents.material_area)
    print("nozzle_efficiency",     rocket.engine.contents.contents.tube.contents.contents.nozzle_efficiency)

    print("\nEngine data")
    print("engine_mass",           rocket.engine.contents.contents.engine_mass)
    print("pressure",              rocket.engine.contents.contents.pressure)
    print("escape_vel",            rocket.engine.contents.contents.escape_vel)
    print("temperature",           rocket.engine.contents.contents.temperature)
    print("width_condition",       rocket.engine.contents.contents.width_condition)
    print("margin_of_safety",      rocket.engine.contents.contents.margin_of_safety)
    print("max_stress",            rocket.engine.contents.contents.max_stress)
    print("radial_stress",         rocket.engine.contents.contents.radial_stress)
    print("tangencial_stress",     rocket.engine.contents.contents.tangencial_stress)
    print("longitudinal_stress",   rocket.engine.contents.contents.longitudinal_stress)
    print("max_pressue",           rocket.engine.contents.contents.max_pressue)
    print("nozzle_efficiency",     rocket.engine.contents.contents.nozzle_efficiency)

    print("\nComp area data")
    print("avg_long_area",         rocket.engine.contents.contents.comp_area_values.contents.avg_long_area)
    print("avg_trans_area",        rocket.engine.contents.contents.comp_area_values.contents.avg_trans_area)
    print("avg_burn_area",         rocket.engine.contents.contents.comp_area_values.contents.avg_burn_area)
    print("burn_std_deviation",    rocket.engine.contents.contents.comp_area_values.contents.burn_std_deviation)
    print("burn_sum_diff",         rocket.engine.contents.contents.comp_area_values.contents.burn_sum_diff)

    print("\nRocket data")
    print("telemetry_mass",        rocket.telemetry_mass)
    print("parachute_mass",        rocket.parachute_mass)
    print("fuselage_mass",         rocket.fuselage_mass)
    print("payload_mass",          rocket.payload_mass)
    print("initial_height",        rocket.initial_height)
    print("avg_thrust",            rocket.avg_thrust)
    print("max_thrust",            rocket.max_thrust)
    print("delta_v",               rocket.delta_v)
    print("max_pressure",          rocket.max_pressure)
    print("sim_latitude",          rocket.sim_latitude)
    print("body_diameter",         rocket.body_diameter)
    print("drag_coefficient",      rocket.drag_coefficient)

    print("\nHeight sim data")
    print("rocket_position list with %i items" %      (len(list(rocket.sim_values.contents.position))))
    print("rocket_speed list with %i items" %         (len(list(rocket.sim_values.contents.speed))))
    print("rocket_acceleration list with %i items" %  (len(list(rocket.sim_values.contents.acceleration))))
    print("rocket_force_balance list with %i items" % (len(list(rocket.sim_values.contents.force_balance))))
    print("rocket_drag list with %i items" %          (len(list(rocket.sim_values.contents.drag))))
    print("rocket_weight list with %i items" %        (len(list(rocket.sim_values.contents.weight))))
    print("rocket_mass list with %i items" %          (len(list(rocket.sim_values.contents.mass))))
    print("rocket_force list with %i items" %         (len(list(rocket.sim_values.contents.force))))
    print("time list with %i items" %                 (len(list(rocket.sim_values.contents.time))))
    print("max_height",            rocket.sim_values.contents.max_height)
    print("max_position",          rocket.sim_values.contents.max_position)
    print("max_speed",             rocket.sim_values.contents.max_speed)
    print("max_acceleration",      rocket.sim_values.contents.max_acceleration)
    print("max_force_balance",     rocket.sim_values.contents.max_force_balance)
    print("max_drag",              rocket.sim_values.contents.max_drag)
