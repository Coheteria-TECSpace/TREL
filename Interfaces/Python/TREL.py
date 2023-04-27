import ctypes
import os

TREL_MAX_STR_LEN = 100
TREL_MAX_ITERATIONS = 1000

if os.name == 'posix':
    TREL = ctypes.CDLL("./libTREL.so")
elif os.name == 'nt':
    TREL = ctypes.CDLL("./TREL.dll")

# Struct for comp area simulation
class TREL_COMP_AREA(ctypes.Structure):
    _fields_ = [("avg_long_area", ctypes.c_double),
                ("avg_trans_area", ctypes.c_double),
                ("avg_burn_area", ctypes.c_double),
                ("burn_std_deviation", ctypes.c_double),
                ("burn_sum_diff", ctypes.c_double)]

# Struct and constructor for propellent grains
class _TREL_GRAINS_T(ctypes.Structure):
    _fields_ = [("amount", ctypes.c_uint),
                ("init_inter_radius", ctypes.c_double),
                ("extern_radius", ctypes.c_double),
                ("longitude", ctypes.c_double),
                ("grain_separation", ctypes.c_double)]

_trel_grains_init = TREL.trel_grains_init
_trel_grains_init.argtypes = [ctypes.c_int,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double]
_trel_grains_init.restype = ctypes.c_void_p

# Struct and constructor for fuel
class _TREL_FUEL_T(ctypes.Structure):
    _fields_ = [("const_burn_rate", ctypes.c_double),
                ("pressure_exponent", ctypes.c_double),
                ("density", ctypes.c_double),
                ("burn_rate", ctypes.c_double)]

_trel_fuel_init = TREL.trel_fuel_init
_trel_fuel_init.argtypes = [ctypes.c_double,
                           ctypes.c_double,
                           ctypes.c_double]
_trel_fuel_init.restype = ctypes.c_void_p

# Struct and constructor for screws
class _TREL_SCREWS_T(ctypes.Structure):
    _fields_ = [("diameter", ctypes.c_double),
                ("dist_center_wall", ctypes.c_double),
                ("amount", ctypes.c_uint),
                ("area_per_screw", ctypes.c_double),
                ("screw_occupied_area", ctypes.c_double),
                ("material", TREL_MAX_STR_LEN * ctypes.c_char),
                ("width_cutting_segment", ctypes.c_double)]

_trel_screws_init = TREL.trel_screws_init
_trel_screws_init.argtypes = [ctypes.c_char_p,
                             ctypes.c_uint,
                             ctypes.c_double,
                             ctypes.c_double]
_trel_screws_init.restype = ctypes.c_void_p

# Struct and constructor for tubing
class _TREL_TUBING_T(ctypes.Structure):
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

_trel_tubing_init = TREL.trel_tubing_init
_trel_tubing_init.argtypes = [ctypes.c_char_p,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double]
_trel_tubing_init.restype = ctypes.c_void_p

# Struct and constructor for engine
class _TREL_ENGINE_T(ctypes.Structure):
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
                ("max_pressure", ctypes.c_double),
                ("nozzle_efficiency", ctypes.c_double),
                ("grains", ctypes.POINTER(ctypes.POINTER(_TREL_GRAINS_T))),
                ("fuel", ctypes.POINTER(ctypes.POINTER(_TREL_FUEL_T))),
                ("tube", ctypes.POINTER(ctypes.POINTER(_TREL_TUBING_T))),
                ("screws", ctypes.POINTER(ctypes.POINTER(_TREL_SCREWS_T))),
                ("comp_area_values", ctypes.POINTER(TREL_COMP_AREA))]

_trel_engine_init = TREL.trel_engine_init
_trel_engine_init.argtypes = [ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.POINTER(ctypes.POINTER(_TREL_GRAINS_T)),
                             ctypes.POINTER(ctypes.POINTER(_TREL_FUEL_T)),
                             ctypes.POINTER(ctypes.POINTER(_TREL_TUBING_T)),
                             ctypes.POINTER(ctypes.POINTER(_TREL_SCREWS_T))]
_trel_engine_init.restype = ctypes.c_void_p

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
class _TREL_ROCKET_T(ctypes.Structure):
    _fields_ = [("engine", ctypes.POINTER(ctypes.POINTER((_TREL_ENGINE_T)))),
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

_trel_rocket_init = TREL.trel_rocket_init
_trel_rocket_init.argtypes = [ctypes.POINTER(ctypes.POINTER((_TREL_ENGINE_T))),
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double,
                             ctypes.c_double]
_trel_rocket_init.restype = ctypes.c_void_p

trel_run_area_comp_iterations = TREL.trel_run_area_comp_iterations
trel_run_area_comp_iterations.argtypes = [ctypes.POINTER(ctypes.POINTER((_TREL_ENGINE_T)))]

trel_run_time_comp_iterations = TREL.trel_run_time_comp_iterations
trel_run_time_comp_iterations.argtypes = [ctypes.POINTER(ctypes.POINTER(_TREL_ROCKET_T))]

trel_run_height_sim_iterations = TREL.trel_run_height_sim_iterations
trel_run_height_sim_iterations.argtypes = [ctypes.POINTER(ctypes.POINTER(_TREL_ROCKET_T))]

_trel_grains_free = TREL.trel_grains_free
_trel_grains_free.argtypes = [ctypes.POINTER(ctypes.POINTER(_TREL_GRAINS_T))]
_trel_grains_free.restype = ctypes.c_void_p

_trel_fuel_free = TREL.trel_fuel_free
_trel_fuel_free.argtypes = [ctypes.POINTER(ctypes.POINTER(_TREL_FUEL_T))]
_trel_fuel_free.restype = ctypes.c_void_p

_trel_tubing_free = TREL.trel_tubing_free
_trel_tubing_free.argtypes = [ctypes.POINTER(ctypes.POINTER(_TREL_TUBING_T))]
_trel_tubing_free.restype = ctypes.c_void_p

_trel_screws_free = TREL.trel_screws_free
_trel_screws_free.argtypes = [ctypes.POINTER(ctypes.POINTER(_TREL_SCREWS_T))]
_trel_screws_free.restype = ctypes.c_void_p

_trel_engine_free = TREL.trel_engine_free
_trel_engine_free.argtypes = [ctypes.POINTER(ctypes.POINTER((_TREL_ENGINE_T)))]
_trel_engine_free.restype = ctypes.c_void_p

_trel_rocket_free = TREL.trel_rocket_free
_trel_rocket_free.argtypes = [ctypes.POINTER(ctypes.POINTER(_TREL_ROCKET_T))]
_trel_rocket_free.restype = ctypes.c_void_p

class TREL_GRAINS():
    def __init__(self, amount, internal_radius, external_radius, longitude, separation):
        self.values = _TREL_GRAINS_T.from_address(_trel_grains_init(
            amount, internal_radius, external_radius, longitude, separation))
        self._p = ctypes.pointer(self.values)
        self._p_p = ctypes.pointer(self._p)
        self.allocated = True
    def free(self):
        _trel_grains_free(self._p_p)
        self.allocated = False
    def __repr__(self):
        return('Amount: %f\nInternal radius: %f\nExternal radius: %f\nLongitude: %f\nSeparation: %f' % (
            self.values.amount, self.values.init_inter_radius, self.values.extern_radius, self.values.longitude, self.values.grain_separation))
    def __str__(self):
        return(self.__repr__() if self.allocated else 'NULL')

class TREL_FUEL():
    def __init__(self, c_burn_rate, pressure_exponent, density):
        self.values = _TREL_FUEL_T.from_address(_trel_fuel_init(
            c_burn_rate, pressure_exponent, density))
        self._p = ctypes.pointer(self.values)
        self._p_p = ctypes.pointer(self._p)
        self.allocated = True
    def free(self):
        _trel_fuel_free(self._p_p)
        self.allocated = False
    def __repr__(self):
        return('Const Burn Rate: %f\nPressure Exponent: %f\nDensity: %f\nBurn Rate: %f' % (
            self.values.const_burn_rate, self.values.pressure_exponent, self.values.density, self.values.burn_rate))
    def __str__(self):
        return(self.__repr__() if self.allocated else 'NULL')

class TREL_SCREWS():
    def __init__(self, material_name, amount, diameter, dist_center_wall):
        if len(material_name) > 99:
            print("ERROR: TREL's materials can't take more than 99 characters")
            return(None)
        self.values = _TREL_SCREWS_T.from_address(_trel_screws_init(
            bytes(material_name, 'utf8'), amount, diameter, dist_center_wall))
        self._p = ctypes.pointer(self.values)
        self._p_p = ctypes.pointer(self._p)
        self.allocated = True
    def free(self):
        _trel_screws_free(self._p_p)
        self.allocated = False
    def __repr__(self):
        return('Material: %s\nAmount: %f\nDiameter: %f\nWall Center Distance: %f\nArea Per Screw:%f\nScrew Occupied Area: %f\nWidth Cutting Segment %f' % (
        self.values.material.decode('utf8'), self.values.amount, self.values.diameter, self.values.dist_center_wall, self.values.area_per_screw, self.values.screw_occupied_area, self.values.width_cutting_segment))
    def __str__(self):
        return(self.__repr__() if self.allocated else 'NULL')

class TREL_TUBING():
    def __init__(self, material_name, external_diameter, thickness, young_module, shear_tension, shear_pressure, ult_tension, ult_pressure, nozzle_efficiency):
        if len(material_name) > 99:
            print("ERROR: TREL's materials can't take more than 99 characters")
            return(None)
        self.values = _TREL_TUBING_T.from_address(_trel_tubing_init(
            bytes(material_name, 'utf8'), external_diameter, thickness, young_module, shear_tension, shear_pressure, ult_tension, ult_pressure, nozzle_efficiency))
        self._p = ctypes.pointer(self.values)
        self._p_p = ctypes.pointer(self._p)
        self.allocated = True
    def free(self):
        _trel_tubing_free(self._p_p)
        self.allocated = False
    def __repr__(self):
        return('Material: %s\nExternal Diameter: %f\nWall Thickness: %f\nInternal Radius: %f\nYoung Module: %f\nSector Angle: %f\nMean Tubing Diameter: %f\nShear Stress Tension: %f\nShear Stress Pressure: %f\nUltimate Stress Tension: %f\nUltimate Stress Pressure: %f\nTransversal Area: %f\nMaterial Area %f\nNozzle Efficiency %f' % (
        self.values.material.decode('utf8'), self.values.diameter_ext, self.values.wall_thickness, self.values.internal_radius, self.values.young_module, self.values.sector_angle, self.values.mean_tubing_diameter, self.values.shear_stress_tension, self.values.shear_stress_pressure, self.values.ult_stress_tension, self.values.ult_stress_pressure, self.values.transversal_area, self.values.material_area, self.values.nozzle_efficiency))
    def __str__(self):
        return(self.__repr__() if self.allocated else 'NULL')

class TREL_ENGINE():
    def __init__(self, pressure, temperature, mass, grains, fuel, tubing, screws):
        self.values = _TREL_ENGINE_T.from_address(_trel_engine_init(
            pressure, temperature, mass, grains._p_p, fuel._p_p, tubing._p_p, screws._p_p))
        self._p = ctypes.pointer(self.values)
        self._p_p = ctypes.pointer(self._p)
        self.allocated = True
    def free(self):
        _trel_engine_free(self._p_p)
        self.allocated = False
    def __repr__(self):
        return('Engine Mass: %f\nPressue: %f\nEscape Velocity: %f\nTemperature %f\nWidth Condition: %f\nMargin of Safety: %f\nMaximum Stress: %f\nRadial Stress: %f\nTangencial Stress: %f\nLongitudinal Stress: %f\nMaximum Pressure: %f\nNozzle Efficiency: %f' % (
        self.values.engine_mass, self.values.pressure, self.values.escape_vel, self.values.temperature, self.values.width_condition, self.values.margin_of_safety, self.values.max_stress, self.values.radial_stress, self.values.tangencial_stress, self.values.longitudinal_stress, self.values.max_pressure, self.values.nozzle_efficiency))
    def get_area_behavior(self):
        return(self.values.comp_area_values.contents)
    def __str__(self):
        return(self.__repr__() if self.allocated else 'NULL')

class TREL_ROCKET():
    def __init__(self, engine, telemetry_mass, parachute_mass, fuselage_mass, payload_mass, initial_height, sim_latitude, body_diameter, drag_coefficient):
        self.values = _TREL_ROCKET_T.from_address(_trel_rocket_init(
            engine._p_p, telemetry_mass, parachute_mass, fuselage_mass, payload_mass, initial_height, sim_latitude, body_diameter, drag_coefficient))
        self._p = ctypes.pointer(self.values)
        self._p_p = ctypes.pointer(self._p)
        self.allocated = True
    def free(self):
        _trel_rocket_free(self._p_p)
        self.allocated = False
    def __repr__(self):
        return('Telemetry Mass: %f\nParachute Mass: %f\nFuselage Mass: %f\nPayload Mass: %f\nInitial Height: %f\nAverage Thrust: %f\nMaximum Thrust: %f\nDelta V: %f\nMaximum Pressure: %f\nSimulation Latitude: %f\nBody Diameter: %f\nDrag Coefficient: %f' % (
        self.values.telemetry_mass, self.values.parachute_mass, self.values.fuselage_mass, self.values.payload_mass, self.values.initial_height, self.values.avg_thrust, self.values.max_thrust, self.values.delta_v, self.values.max_pressure, self.values.sim_latitude, self.values.body_diameter, self.values.drag_coefficient))
    def get_sim_values(self):
        return(self.values.sim_values.contents)
    def __str__(self):
        return(self.__repr__() if self.allocated else 'NULL')
