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



def run():
    while True:
        rows = input("Rows: ")
        cols = input("Cols: ")
        file_index = input("File index: ")
        filename = ""+rows+"x"+cols+"_"+file_index+".txt"
        save_to_file(filename, generate(int(rows), int(cols)))

run()

