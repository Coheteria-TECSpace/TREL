from TREL import *

engine_grains = TREL_GRAINS(
    4,
    0.01,
    0.0304,
    0.1,
    0.001
)
engine_fuel = TREL_FUEL(
	0.005,
	0.688,
	1859
)
engine_screws = TREL_SCREWS(
    'Acero',
	6,
	0.007466,
	0.01
)
engine_tubing = TREL_TUBING(
    'Aluminio 6061-T6',
    0.073,
    0.0052,
    68900000000.0,
    275000000.0,
    -1,
    310000000,
    205000000,
    0.85
)
engine = TREL_ENGINE(
    800.0,
    1710.0,
    1.5,
    engine_grains,
    engine_fuel,
    engine_tubing,
    engine_screws
)
rocket = TREL_ROCKET(
    engine,
    0.3,
    0.05,
    5.0,
    1.5,
    1207.0,
    9.936111,
    0.13,
    0.4
)

print(f'Grains\n{engine_grains}')
print(f'Fuel\n{engine_fuel}')
print(f'Screws\n{engine_screws}')
print(f'Tubing\n{engine_tubing}')
print(f'Engine\n{engine}')
print(f'Rocket\n{rocket}')
print(list(rocket.get_sim_values().position))

engine_grains.free()
engine_fuel.free()
engine_screws.free()
engine_tubing.free()
engine.free()
rocket.free()
