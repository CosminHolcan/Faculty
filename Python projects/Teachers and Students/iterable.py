import unittest

class Iterable_Data :

    def __init__(self):
        self.__list = []
        self.__index = 0

    def __setitem__(self, key, value):
        self.__list[key] = value

    def __getitem__(self, item):
        return self.__list[item]

    def __delitem__(self, key):
        del self.__list[key]

    def __next__(self):
        if self.__index > len(self.__list) - 1:
            raise StopIteration
        else:
            self.__index += 1
        return self.__list[self.__index]

    def __iter__(self):
        return iter(self.__list)

    def __len__(self):
        return len(self.__list)

    def append(self, item):
        self.__list.append(item)

    def return_list(self):
        return self.__list[:]

def filter(List, condition) :
    aux_list = list()
    for i in range(len(List)) :
        if condition(List[i]) :
            aux_list.append(List[i])
    return aux_list


def shellSort(arr, function):
    n = len(arr)
    gap = n // 2
    while gap > 0:
        for i in range(gap, n):
            temp = arr[i]
            j = i
            while j >= gap and function(arr[j - gap], temp) :
                arr[j] = arr[j - gap]
                j -= gap
            arr[j] = temp
        gap //= 2

    return arr

def sort_function(first_number, second_number):
        return first_number >= second_number

def filter_function(number) :
    if number > 10 :
        return number

class Tests(unittest.TestCase) :

    def test_adding_elements(self) :
        data = Iterable_Data()
        data.append(5)
        self.assertTrue(data[0] == 5)

    def test_get_elements(self):
        data = Iterable_Data()
        data.append(5)
        data.append(8)
        data.append(25)
        self.assertTrue(data.return_list() == [5, 8, 25])

    def test_delete_element(self):
        data = Iterable_Data()
        data.append(5)
        data.append(8)
        data.append(25)
        data.__delitem__(2)
        self.assertTrue( data.return_list() == [5, 8])

    def test_length(self):
        data = Iterable_Data()
        data.append(5)
        data.append(8)
        data.append(25)
        self.assertTrue(data.__len__() == 3)

    def test_set_item(self):
        data = Iterable_Data()
        data.append(5)
        data.append(8)
        data.append(25)
        data.__setitem__(2, 100)
        self.assertTrue(data[2] == 100)

    def test_shell_sort(self):
        vector = [ 25, 45, 86, 7, 17, 36]
        new_vector = shellSort(vector, sort_function)
        self.assertTrue(new_vector == [7, 17, 25, 36, 45, 86])

    def test_filter(self):
        vector = [4, 8 , 15 , 29, 2, 64]
        filter_vector = filter(vector, filter_function)
        self.assertTrue( filter_vector == [15, 29, 64])



