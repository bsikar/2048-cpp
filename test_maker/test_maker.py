import numpy as np


class TestMaker:
    def __init__(self, image, numbers):
        self.image = image
        self.numbers = numbers
    def print_list(numbers):
        # format this like a c++ array when printing
        # by using '{' and '}' instead of '[' and ']'
        # and by adding a comma after each element
        string_array = np.array2string(numbers, separator=", ").replace("[", "{").replace("]", "}")
        print(f"{{{string_array}}}")
