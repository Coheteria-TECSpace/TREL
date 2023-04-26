from HIGH_TREL import *

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

print(f'Grains\n{engine_grains}')
print(f'Fuel\n{engine_fuel}')
print(f'Screws\n{engine_screws}')

engine_grains.free()
engine_fuel.free()
engine_screws.free()
