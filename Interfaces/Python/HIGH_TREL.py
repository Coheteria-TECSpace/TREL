import ctypes
from TREL import _trel_grains_init, _TREL_GRAINS_T, _trel_grains_free
from TREL import _trel_fuel_init, _TREL_FUEL_T, _trel_fuel_free
from TREL import _trel_screws_init, _TREL_SCREWS_T, _trel_screws_free
from TREL import _trel_tubing_init, _TREL_TUBING_T, _trel_tubing_free
from TREL import _trel_engine_init, _TREL_ENGINE_T, _trel_engine_free

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
        self.values.material, self.values.amount, self.values.diameter, self.values.dist_center_wall, self.values.area_per_screw, self.values.screw_occupied_area, self.values.width_cutting_segment))
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
        self.values.material, self.values.diameter_ext, self.values.wall_thickness, self.values.internal_radius, self.values.young_module, self.values.sector_angle, self.values.mean_tubing_diameter, self.values.shear_stress_tension, self.values.shear_stress_pressure, self.values.ult_stress_tension, self.values.ult_stress_pressure, self.values.transversal_area, self.values.material_area, self.values.nozzle_efficiency))
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
        self.values.engine_mass, self.values.pressure, self.values.escape_vel, self.values.temperature, self.values.width_condition, self.values.margin_of_safety, self.values.max_stress, self.values.radial_stress, self.values.tangencial_stress, self.values.longitudinal_stress, self.values.max_pressue, self.values.nozzle_efficiency))
    def __str__(self):
        return(self.__repr__() if self.allocated else 'NULL')
