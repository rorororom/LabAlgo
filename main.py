import matplotlib.pyplot as plt

with open('dataForGraphA.txt', 'r') as file1:
    data1 = [float(line.split()[1]) for line in file1]

with open('dataForGraphL.txt', 'r') as file2:
    data2 = [float(line.split()[1]) for line in file2]

x = list(range(len(data1)))

plt.plot(x, data1, label='Стек с массивом')
plt.plot(x, data2, label='Стек с односвязным списком')

plt.legend()

plt.title('График стека с массивом и c односвязным списком')
plt.grid(True)
plt.xlabel('Количество итераций (1000n)')
plt.ylabel('Время (мс)')

plt.show()
