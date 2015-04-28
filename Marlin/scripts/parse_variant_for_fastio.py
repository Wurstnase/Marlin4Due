__author__ = 'Nico'

input_file = 'C:/Users/Nico/AppData/Roaming/Arduino15/packages/arduino/hardware/sam/1.6.3/variants/arduino_due_x'
input_file += '/variant.cpp'

at_pins = False


def skip_until_pin_description(line):
    global at_pins
    if line.find('PinDescription g_APinDescription'):
        at_pins = True


def has_pin_line(line):
    has_pin = line.find('PIO_DEFAULT')
    if has_pin > 10:
        if line.find('PIO_NOT_A_PIN') > 10:
            return False
        else:
            return True


def get_wport(line):
    pos = line.find('PIO')
    return line[pos:pos+4]


def get_pin(line):
    pos = line.find('_P') + 3
    my_string = line[pos:pos+4]
    number = ''
    for char in my_string:
        try:
            int(char)
            number += char
        except ValueError:
            break
    return number

with open(input_file, 'r') as file:
    due_pin = 0
    for line in file:
        if not at_pins:
            skip_until_pin_description(line)
        else:
            if has_pin_line(line):
                # print(line[:30])
                print('#define DIO{}_PIN {}'.format(due_pin, get_pin(line)))
                print('#define DIO{}_WPORT {}\n'.format(due_pin, get_wport(line)))
                due_pin += 1
file.close()
