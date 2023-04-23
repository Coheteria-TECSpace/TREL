from TREL import *

created_grains = TREL_GRAINS.from_address(trel_grains_init(
        4,
        0.01,
        0.0304,
        0.1,
        0.001
        ))

created_fuel = TREL_FUEL.from_address(trel_fuel_init(
		0.005,
		0.688,
		1859))

created_screw = TREL_SCREWS.from_address(trel_screws_init(
		6,
		0.007466,
		0.01))

created_tube = TREL_TUBING.from_address(trel_tubing_init(
        0.073,
        0.0052,
        68900000000.0,
        275000000.0,
        -1,
        310000000,
        205000000))

print(created_tube.wall_thickness)
