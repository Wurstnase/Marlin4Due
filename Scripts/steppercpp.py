# This is something to test the stepper.cpp from Marlin
# - The main-routine should work like the original one
# - uint-stuff is not 100% correct at the moment
#
# There are a lot of globals. I don't like them but my experience is not big enough to change it now.
# The planner needs some more work. It goes only one-way.

from sam3x_helper import uint32_t, uint64_t
import plannercpp
from config import *
import matplotlib.pyplot as plt

debugging_1 = True
debugging_2 = True


def pre_run():
    global current_block
    global step_events_completed, HAL_timer_complete, acc_step_rate
    global first_in_quad, first_in_double

    entry_factor = JERK / SPEED_MM_S
    plannercpp.calculate_trapezoid_for_current_block(entry_factor, 0)  # calculate current_block
    current_block = plannercpp.current_block

    # reset some counter
    step_events_completed = 0
    HAL_timer_complete = 0
    acc_step_rate = 0

    first_in_quad = True
    first_in_double = True


def MultiU24X24toH16(longIn1, longIn2):
    return (uint64_t(longIn1) * uint32_t(longIn2)) >> 24


def calc_timer(step_rate):
    global step_loops
    global first_in_quad, first_in_double

    step_rate = step_rate if step_rate < MAX_STEP_FREQUENCY else MAX_STEP_FREQUENCY
    step_rate = uint32_t(step_rate)

    if step_rate > (2 * DOUBLE_FREQUENCY):
        if first_in_quad & debugging_1:
            print("quadstepping: {} steps\nstep_events: {}".format(step_rate, step_events_completed))
            first_in_quad = False
            first_in_double = True
        step_rate >>= 2
        step_loops = 4
    elif step_rate > DOUBLE_FREQUENCY:
        if first_in_double & debugging_1:
            print("doublestepping: {} steps\nstep_events: {}".format(step_rate, step_events_completed))
            first_in_quad = True
            first_in_double = False
        step_rate >>= 1
        step_loops = 2
    else:
        step_loops = 1
        
    step_rate = uint32_t(step_rate) if step_rate > 210 else 210
    timer = HAL_TIMER_RATE / step_rate
    timer = uint32_t(timer)
    return timer

    step_rate = uint32_t(step_rate) if step_rate > 210 else 210
    timer = HAL_TIMER_RATE / step_rate
    timer = uint32_t(timer)
    return timer


def trapezoid_generator_reset():
    global deceleration_time
    global OCR1A_nominal, step_loops_nominal, acceleration_time, HAL_timer_set_count, acc_step_rate
    global actual_step_rate

    deceleration_time = 0
    OCR1A_nominal = calc_timer(current_block.nominal_rate)
    OCR1A_nominal = uint32_t(OCR1A_nominal)

    step_loops_nominal = step_loops
    acc_step_rate = current_block.initial_rate
    acc_step_rate = uint32_t(acc_step_rate)

    acceleration_time = calc_timer(acc_step_rate)

    HAL_timer_set_count = acceleration_time
    actual_step_rate = acc_step_rate

# Debugging stuff
first_acc_until = True
first_dec_after = True
dec_after = 0
first_else = True


def ISR_workhorse():
    global step_events_completed, HAL_timer_set_count, step_loops, deceleration_time, acceleration_time, acc_step_rate
    global first_acc_until, first_dec_after, first_else
    global dec_after
    global HAL_timer_complete
    global actual_step_rate
    # check current_block != 0
    # stepper control

    # calculation of the new timer
    # this is what we want to see
    # first you need to set the step_events_completed to 0!
    #
    # calculate current_block (done with import/run this file)
    #
    # now you can run the workhorse with run_it(steps)
    # steps is ~ TRAVEL_IN_MM * STEP_PER_MM (take a look in config.py)

    if step_events_completed <= current_block.accelerate_until:
        if first_acc_until & debugging_2:
            print("first_acc_until: {0}\nspeed: {1}".format(step_events_completed, acc_step_rate))
            first_acc_until = False
            first_dec_after = True

        acc_step_rate = MultiU24X24toH16(acceleration_time, current_block.acceleration_rate)

        if acc_step_rate > current_block.nominal_rate:
            acc_step_rate = current_block.nominal_rate

        timer = calc_timer(acc_step_rate)
        HAL_timer_set_count = timer
        actual_step_rate = acc_step_rate

        acceleration_time += timer

    elif step_events_completed > current_block.decelerate_after:
        if first_dec_after & debugging_2:
            print("first_dec_after: {0}\nspeed: {1}".format(step_events_completed, acc_step_rate))
            first_dec_after = False
            first_acc_until = True
            dec_after = HAL_timer_complete
        step_rate = MultiU24X24toH16(deceleration_time, current_block.acceleration_rate)

        if step_rate > acc_step_rate:
            step_rate = current_block.final_rate
            # print('xTruex')
        else:
            step_rate = acc_step_rate - step_rate
            # print(step_rate)

        timer = calc_timer(step_rate)
        HAL_timer_set_count = timer
        actual_step_rate = step_rate

        deceleration_time += timer

    else:
        if first_else & debugging_2:
            print('first_else: {0}\nspeed: {1}'.format(step_events_completed, acc_step_rate))
            first_else = False
        HAL_timer_set_count = OCR1A_nominal
        actual_step_rate = current_block.nominal_rate

        step_loops = step_loops_nominal

    HAL_timer_complete += HAL_timer_set_count


list_of_acc_step_rate = []
list_of_timer_complete = []


def run_it(steps):
    global step_events_completed
    global list_of_acc_step_rate
    global list_of_timer_complete
    last_acc = 0
    pre_run()

    list_of_acc_step_rate.clear()
    list_of_timer_complete.clear()
    trapezoid_generator_reset()
    list_of_acc_step_rate.append(actual_step_rate)
    list_of_timer_complete.append(HAL_timer_complete)
    for step_events_completed in range(0, steps-1):
        ISR_workhorse()
        list_of_acc_step_rate.append(actual_step_rate)
        list_of_timer_complete.append(HAL_timer_complete)
        step_events_completed += 1
        if last_acc == actual_step_rate & actual_step_rate < 150:
            print("break: {}\ntime: {}".format(step_events_completed, HAL_timer_complete))
            break

        last_acc = actual_step_rate

    print('last: {0}\nspeed: {1}\nsteps: {2}'.format(HAL_timer_complete, actual_step_rate, step_events_completed))


def show_plot():
    x, acc_plt = plt.subplots(2)
    acc_plt[0].step(list_of_timer_complete, list_of_acc_step_rate, 'k', label='HAL_timer')
    steps = range(0, len(list_of_acc_step_rate))
    acc_plt[1].plot(steps, list_of_acc_step_rate)

    for i in range(0, 2):
        acc_plt[i].set_xlim(acc_plt[i].get_xlim()[1] * (-0.1))
        acc_plt[i].set_ylim(-100, current_block.nominal_rate*1.1)

    plt.show()


def auto_mode(steps):
    run_it(steps)
    show_plot()