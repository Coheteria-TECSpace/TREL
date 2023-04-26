from TREL import *

# Create a rocket structure
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

# Visualize the created objetcs
print(f'Grains\n{engine_grains}\n')
print(f'Fuel\n{engine_fuel}\n')
print(f'Screws\n{engine_screws}\n')
print(f'Tubing\n{engine_tubing}\n')
print(f'Engine\n{engine}\n')
print(f'Rocket\n{rocket}\n')

# Access area behavior data
print('Area behavior data')
print(f'Average Longitudinal Area: {engine.get_area_behavior().avg_long_area}')
print(f'Average Transversal Area: {engine.get_area_behavior().avg_trans_area}')
print(f'Average Burn Area: {engine.get_area_behavior().avg_burn_area}')
print(f'Burn Standard Deviation: {engine.get_area_behavior().burn_std_deviation}')
print(f'Brun Sum Differential: {engine.get_area_behavior().burn_sum_diff}')

# Access height simulation data
print('\nHeight simulation data')
print(f'Position {len(list(rocket.get_sim_values().position))} items')
print(f'Speed {len(list(rocket.get_sim_values().speed))} items')
print(f'Acceleration {len(list(rocket.get_sim_values().acceleration))} items')
print(f'Force Balance {len(list(rocket.get_sim_values().force_balance))} items')
print(f'Drag {len(list(rocket.get_sim_values().drag))} items')
print(f'Weight {len(list(rocket.get_sim_values().weight))} items')
print(f'Mass {len(list(rocket.get_sim_values().mass))} items')
print(f'Force {len(list(rocket.get_sim_values().force))} items')
print(f'Time {len(list(rocket.get_sim_values().time))} items')
print(f'Maximum Height: {rocket.get_sim_values().max_height}')
print(f'Maximum Position: {rocket.get_sim_values().max_position}')
print(f'Maximum Speed: {rocket.get_sim_values().max_speed}')
print(f'Maximum Acceleration: {rocket.get_sim_values().max_acceleration}')
print(f'Maximum Force Balance: {rocket.get_sim_values().max_force_balance}')
print(f'Maximum Position: {rocket.get_sim_values().max_position}')
print(f'Maximum Drag: {rocket.get_sim_values().max_drag}')

# Delete the objects created **ALWAYS DO AFTER YOU DON'T NEED THEM**
engine_grains.free()
engine_fuel.free()
engine_screws.free()
engine_tubing.free()
engine.free()
rocket.free()
