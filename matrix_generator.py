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


save_to_file('3x2_1.txt', generate(3, 2))

