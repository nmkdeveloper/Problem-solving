import random

with open("BAI1.INP", "w") as file:
    file.write("1000\n")
    for i in range(1000):
        file.write(f"{random.randint(1, 1000)}\n")