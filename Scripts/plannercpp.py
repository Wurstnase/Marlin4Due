from math import ceil, floor
from sam3x_helper import uint32_t, int32_t
import config


class Block():
    pass

current_block = Block()
current_block.nominal_rate = config.SPEED_MM_S * config.STEPS_PER_MM  # mm/s * steps/mm
current_block.initial_rate = 0  # changes in planner (jerk etc.)
current_block.acceleration_st = config.ACCELERATION * config.STEPS_PER_MM

current_block.millimeters = config.TRAVEL_IN_MM  # mm to travel
current_block.step_event_count = current_block.millimeters * config.STEPS_PER_MM

current_block.acceleration_rate = current_block.acceleration_st * (2**24) / config.HAL_TIMER_RATE


def estimate_acceleration_distance(initial_rate, target_rate, acceleration):
    if acceleration != 0:
        return ((target_rate ** 2 - initial_rate ** 2)
                / (2.0 * acceleration))
    else:
        return 0.0


def intersection_distance(initial_rate, final_rate, acceleration, distance):
    if acceleration != 0:
        return ((2.0 * acceleration * distance - initial_rate ** 2 + final_rate ** 2)
                / (4.0 * acceleration))
    else:
        return 0.0


def calculate_trapezoid_for_current_block(entry_factor, exit_factor):
    global current_block
    # current_block = block[myblock]

    initial_rate = uint32_t(ceil(current_block.nominal_rate * entry_factor))
    final_rate = uint32_t(ceil(current_block.nominal_rate * exit_factor))

    LIMIT = 120
    if initial_rate < LIMIT:
        initial_rate = LIMIT
    if final_rate < LIMIT:
        final_rate = LIMIT

    acceleration = current_block.acceleration_st
    acceleration_steps = uint32_t(ceil(estimate_acceleration_distance(
        initial_rate,
        current_block.nominal_rate,
        acceleration)))
    decelerate_steps = uint32_t(floor(estimate_acceleration_distance(
        current_block.nominal_rate,
        final_rate,
        -acceleration)))

    plateau_steps = int32_t(current_block.step_event_count - acceleration_steps - decelerate_steps)

    if plateau_steps < 0:
        acceleration_steps = ceil(intersection_distance(
            initial_rate,
            final_rate,
            acceleration,
            current_block.step_event_count))
        acceleration_steps = max(acceleration_steps, 0)
        acceleration_steps = min(uint32_t(acceleration_steps),
                                 current_block.step_event_count)
        plateau_steps = 0

    current_block.accelerate_until = acceleration_steps
    current_block.decelerate_after = acceleration_steps + plateau_steps
    current_block.initial_rate = initial_rate
    current_block.final_rate = final_rate
