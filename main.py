import matplotlib.pyplot as plt

def get_data_array_from_file(filename):
    with open(filename, 'r') as file:
        data = [float(line.split()[1]) for line in file]
    return data

data1 = get_data_array_from_file('dataForGraphA.txt')
data2 = get_data_array_from_file('dataForGraphL.txt')

x = list(range(len(data1)))

plt.plot(x, data1, label='Стек с массивом')
plt.plot(x, data2, label='Стек с односвязным списком')

plt.legend()

plt.title('График стека с массивом и c односвязным списком')
plt.grid(True)
plt.xlabel('Количество итераций (1000n)')
plt.ylabel('Время (мс)')

plt.show()
