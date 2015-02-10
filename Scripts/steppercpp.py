from sam3x_helper import uint32_t, uint64_t
import plannercpp
from config import HAL_TIMER_RATE, MAX_STEP_FREQUENCY, DOUBLE_FREQUENCY
import matplotlib.pyplot as plt


plannercpp.calculate_trapezoid_for_current_block(0, 0)  # calculate current_block
current_block = plannercpp.current_block

# reset some counter
step_events_completed = 0
HAL_timer_complete = 0
acc_step_rate = 0

curblock_nominal_rate =         current_block.nominal_rate
curblock_initial_rate =         current_block.initial_rate
curblock_accelerate_until =   current_block.accelerate_until
curblock_acceleration_rate =    current_block.acceleration_rate
curblock_decelerate_after =   current_block.decelerate_after
curblock_final_rate =           current_block.final_rate


def MultiU24X24toH16(longIn1, longIn2):
    return (uint64_t(longIn1) * uint32_t(longIn2)) >> 24

# This is a simulation, so I don't need quadstepping for now
first_in_quad = True
first_in_double = True


def calc_timer(step_rate):
    global step_loops
    global first_in_quad, first_in_double

    step_rate = step_rate if step_rate < MAX_STEP_FREQUENCY else MAX_STEP_FREQUENCY
    step_rate = uint32_t(step_rate)

    if step_rate > (2 * DOUBLE_FREQUENCY):
        if first_in_quad:
            print("quadstepping at {} steps".format(step_rate))
            first_in_quad = False
            first_in_double = True
        step_rate >>= 2
        step_loops = 4
    elif step_rate > DOUBLE_FREQUENCY:
        if first_in_double:
            print("doublestepping at {} steps".format(step_rate))
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


def trapezoid_generator_reset():
    global deceleration_time
    global OCR1A_nominal, step_loops_nominal, acceleration_time, HAL_timer_set_count, acc_step_rate
    global actual_step_rate

    deceleration_time = 0
    OCR1A_nominal = calc_timer(curblock_nominal_rate)
    OCR1A_nominal = uint32_t(OCR1A_nominal)

    step_loops_nominal = step_loops
    acc_step_rate = curblock_initial_rate
    acc_step_rate = uint32_t(acc_step_rate)

    acceleration_time = calc_timer(acc_step_rate)

    HAL_timer_set_count = acceleration_time
    actual_step_rate = acc_step_rate

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

    if step_events_completed <= curblock_accelerate_until:
        if first_acc_until:
            # print("first_acc_until: {0}\nspeed: {1}".format(step_events_completed, acc_step_rate))
            first_acc_until = False
            first_dec_after = True

        acc_step_rate = MultiU24X24toH16(acceleration_time, curblock_acceleration_rate)

        if acc_step_rate > curblock_nominal_rate:
            acc_step_rate = curblock_nominal_rate

        timer = calc_timer(acc_step_rate)
        HAL_timer_set_count = timer
        actual_step_rate = acc_step_rate

        acceleration_time += timer

    elif step_events_completed > curblock_decelerate_after:
        if first_dec_after:
            # print("first_dec_after: {0}\nspeed: {1}".format(step_events_completed, acc_step_rate))
            first_dec_after = False
            first_acc_until = True
            dec_after = HAL_timer_complete
        step_rate = MultiU24X24toH16(deceleration_time, curblock_acceleration_rate)

        if step_rate > acc_step_rate:
            step_rate = curblock_final_rate
            # print('xTruex')
        else:
            step_rate = acc_step_rate - step_rate
            # print(step_rate)

        timer = calc_timer(step_rate)
        HAL_timer_set_count = timer
        actual_step_rate = step_rate

        deceleration_time += timer

    else:
        if first_else:
            # print('first_else: {0}\nspeed: {1}'.format(step_events_completed, acc_step_rate))
            first_else = False
        HAL_timer_set_count = OCR1A_nominal
        actual_step_rate = curblock_nominal_rate

        step_loops = step_loops_nominal

    HAL_timer_complete += HAL_timer_set_count


list_of_acc_step_rate = []
list_of_timer_complete = []


def run_it(steps):
    global step_events_completed
    global list_of_acc_step_rate
    global list_of_timer_complete
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
    print('last: {0}\nspeed: {1}'.format(HAL_timer_complete, actual_step_rate))


def show_plot():
    plt.step(list_of_timer_complete, list_of_acc_step_rate, 'k', label='HAL_timer')
    plt.ylim(0, curblock_nominal_rate*1.05)

    plt.show()


def auto_mode(steps):
    run_it(steps)
    show_plot()
