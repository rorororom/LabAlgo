import matplotlib.pyplot as plt

def get_data_array_from_file(filename):
    with open(filename, 'r') as file:
        data = [float(line.split()[1]) for line in file]
    return data

data1 = get_data_array_from_file('heapSort5.txt')
data2 = get_data_array_from_file('MergeIterative.txt')
data3 = get_data_array_from_file('hoare1.txt')
data4 = get_data_array_from_file('median3.txt')
data5 = get_data_array_from_file('new_LSD.txt')
data6 = get_data_array_from_file('new_intresp.txt')
data7 = get_data_array_from_file('qsort!.txt')

x = [10000*i for i in range(len(data2))]

plt.plot(x, data1, label='Heap_sort, k = 5')
plt.plot(x, data2, label='Merge_Iterative_sort')
plt.plot(x, data3, label='Quick_sort_Hoare')
plt.plot(x, data4, label='Mediana 3')
plt.plot(x, data5, label='LSD')
plt.plot(x, data6, label='introspective')
plt.plot(x, data7, label='qsort')

plt.legend()

plt.title('Сравнение самых быстрых сортировок')
plt.grid(True)
plt.xlabel('Размер (n)')
plt.ylabel('Время (с)')

plt.show()
