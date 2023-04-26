import ctypes
from TREL import _trel_grains_init, _TREL_GRAINS_T, _trel_grains_free
from TREL import _trel_fuel_init, _TREL_FUEL_T, _trel_fuel_free
from TREL import _trel_screws_init, _TREL_SCREWS_T, _trel_screws_free
from TREL import _trel_tubing_init, _TREL_TUBING_T, _trel_tubing_free

class TREL_GRAINS():
    def __init__(self, amount, internal_radius, external_radius, longitude, separation):
        self.values = _TREL_GRAINS_T.from_address(_trel_grains_init(
            amount, internal_radius, external_radius, longitude, separation))
        self._p_grains_instance = ctypes.pointer(self.values)
        self._p_p_grains_instance = ctypes.pointer(self._p_grains_instance)
        self.allocated = True
    def free(self):
        _trel_grains_free(self._p_p_grains_instance)
        self.allocated = False
    def __repr__(self):
        return('Amount: %f\nInternal radius: %f\nExternal radius: %f\nLongitude: %f\nSeparation: %f' % (
            self.values.amount, self.values.internal_radius, self.values.external_radius, self.values.longitude, self.values.separation))
    def __str__(self):
        return(self.__repr__() if self.allocated else 'NULL')

class TREL_FUEL():
    def __init__(self, c_burn_rate, pressure_exponent, density):
        self.values = _TREL_FUEL_T.from_address(_trel_fuel_init(
            c_burn_rate, pressure_exponent, density))
        self._p_fuel_instance = ctypes.pointer(self.values)
        self._p_p_fuel_instance = ctypes.pointer(self._p_fuel_instance)
        self.allocated = True
    def free(self):
        _trel_fuel_free(self._p_p_fuel_instance)
        self.allocated = False
    def __repr__(self):
        return('Const Burn Rate: %f\nPressure Exponent: %f\nDensity: %f\nBurn Rate: %f' % (
            self.values.c_burn_rate, self.values.pressure_exponent, self.values.density, self.values.burn_rate))
    def __str__(self):
        return(self.__repr__() if self.allocated else 'NULL')

class TREL_SCREWS():
    def __init__(self, material_name, amount, diameter, dist_center_wall):
        if len(material_name) > 99:
            print("ERROR: TREL's materials can't take more than 99 characters")
            return(None)
        self.values = _TREL_SCREWS_T.from_address(_trel_screws_init(
            bytes(material_name, 'utf8'), amount, diameter, dist_center_wall))
        self._p_screws_instance = ctypes.pointer(self.values)
        self._p_p_screws_instance = ctypes.pointer(self._p_screws_instance)
        self.allocated = True
    def free(self):
        _trel_screws_free(self._p_p_screws_instance)
        self.allocated = False
    def __repr__(self):
        return('Material: %s\nAmount: %f\nDiameter: %f\nWall Center Distance: %f\nArea Per Screw:%f\nScrew Occupied Area: %f\nWidth Cutting Segment %f' % (
        self.values.material_name, self.values.amount, self.values.diameter, self.values.dist_center_wall, self.values.area_per_screw, self.values.screw_occupied_area, self.values.width_cutting_segment))
    def __str__(self):
        return(self.__repr__() if self.allocated else 'NULL')

class TREL_TUBING():
    def __init__(self, material_name, external_diameter, thickness, young_module, shear_tension, ult_tension, ult_pressure, nozzle_efficiency):
        if len(material_name) > 99:
            print("ERROR: TREL's materials can't take more than 99 characters")
            return(None)
        self.valores = _TREL_TUBING_T.from_address(_trel_tubing_init(
            bytes(material_name, 'utf8'), external_diameter, thickness, young_module, shear_tension, ult_tension, ult_pressure, nozzle_efficiency))
        self._p_tubing_instance = ctypes.pointer(self.valores)
        self._p_p_tubing_instance = ctypes.pointer(self._p_tubing_instance)
        self.allocated = True
    def free(self):
        _trel_tubing_free(self._p_p_tubing_instance)
        self.allocated = False
    def __repr__(self):
        return('Material: %s\nExternal Diameter: %f\nWall Thickness: %f\nInternal Radius: %f\n' % (
        self.material, ))
    def __str__(self):
        return(self.__repr__() if self.allocated else 'NULL')
