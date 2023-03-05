import ctypes
import os
#TREL = ctypes.CDLL(os.getcwd()+"/libTREL.so")
TREL = ctypes.CDLL("../build/libTREL.so")

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
                ("area_per_screw", ctypes.c_double),
                ("screw_occupied_area", ctypes.c_double),
                ("width_cutting_segment", ctypes.c_double),
                ("amount", ctypes.c_uint)]

trel_screws_init = TREL.trel_screws_init
trel_screws_init.argtypes = [ctypes.c_uint,
                             ctypes.c_double,
                             ctypes.c_double]
trel_screws_init.restype = ctypes.c_void_p

# Struct and constructor for tubing
class TREL_TUBING(ctypes.Structure):
    _fields_ = [("diameter_ext", ctypes.c_double),
                ("wall_thickness", ctypes.c_double),
                ("internal_radius", ctypes.c_double),
                ("young_module", ctypes.c_double),
                ("sector_angle", ctypes.c_double),
                ("mean_tubing_diameter", ctypes.c_double),
                ("shear_stress_tension", ctypes.c_double),
                ("shear_stress_pressure", ctypes.c_double),
                ("transversal_area", ctypes.c_double),
                ("material_area", ctypes.c_double)]

trel_tubing_init = TREL.trel_tubing_init
trel_tubing_init.argtypes = [ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double]
trel_tubing_init.restype = ctypes.c_void_p

