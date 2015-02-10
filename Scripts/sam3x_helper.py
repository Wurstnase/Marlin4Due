from math import copysign, fabs


def sign(number):
    return copysign(1, number)


def uint(number, bit):
    maxbit = 2**bit - 1
    number = maxbit if number > maxbit else number
    return int(number)


def int_(number, bit):
    halfbit = 2**bit / 2 - 1
    number_sign = sign(number)
    number = fabs(number)
    number = number if number < halfbit else number
    number *= number_sign
    return int(number)


def int32_t(number):
    return int_(number, 32)


def uint8_t(number):
    return uint(number, 8)


def uint16_t(number):
    return uint(number, 16)


def uint32_t(number):
    return uint(number, 32)


def uint64_t(number):
    return uint(number, 64)