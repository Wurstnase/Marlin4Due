__author__ = 'Nico'

for i in range(0, 87+1):
    print('#define DIO{0}_PIN '.format(i))
    print('#define DIO{0}_WPORT PIO\n'.format(i))