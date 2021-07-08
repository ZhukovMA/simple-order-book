import matplotlib.pyplot as plt

PATH = "logs.log"

modes = {}

with open(PATH, 'r') as fin:
    for x in range(2):
        title = fin.readline()
        print('title', title)
        for x in range(3):
            size = fin.readline()
            if not size:
                break
            print('size', size)
            el_time = float(fin.readline())
            print('el_time', el_time)
            if title not in modes:
                modes[title] = ([], [])
            modes[title][0].append(size)
            modes[title][1].append(el_time)

fig = plt.figure(figsize=(8, 15))


plt.title("Реализованные сделки со вставкой новых значений")
for key in modes.keys():
    pair = modes[key]
    plt.plot(pair[0], pair[1], label=key)


plt.grid()
plt.xlabel("Сумма заявков")
plt.ylabel("Время, мкс.")

plt.legend()
plt.show()

fig.savefig('temp.png', dpi=fig.dpi)

