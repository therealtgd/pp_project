import numpy as np
def generate(m, n):
    return np.random.randint(0,100,size=(m, n))
def save_to_file(filename, arr):
    with open(filename, 'w') as f:
        s = ""
        s += str(arr.shape[0]) + " " + str(arr.shape[1])
        s += "\n\n"
        for i in range(arr.shape[0]):
            for j in range(arr.shape[1]):
                s+= str(arr[i][j])
                if j != arr.shape[1] -1:
                    s+= " " 
            if i != arr.shape[0] - 1:
                s+="\n"
        f.write(s)


# save_to_file('3x3_1.txt', generate(3, 3))
# save_to_file('3x3_2.txt', generate(3, 3))
save_to_file('20x100_1.txt', generate(20, 100))
save_to_file('100x100_1.txt', generate(100, 100))
save_to_file('3x5_1.txt', generate(3, 5))
save_to_file('5x5_1.txt', generate(5, 5))
