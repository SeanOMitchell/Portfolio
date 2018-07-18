import sys


#Dynamic programming implementation of the matrix chain algorithm
def matrixchainorder(dimensionvalues, dimensionno):
    #Array to store the results
    results = [[0 for _ in range(dimensionno-1)] for _ in range(dimensionno-1)]

    #Populate the array from the bottom up
    #l = chain length
    for l in range(1, dimensionno-1):
        for i in range(0, dimensionno-l):
            results[i][i] = 0
            j = i + l
            #Escape clause for j values that are too big
            if j == dimensionno-1:
                continue
            results[i][j] = sys.maxsize
            for k in range(i, j):
                tempAnswer = results[i][k] + results[k+1][j] + dimensionvalues[i] * dimensionvalues[k+1] * dimensionvalues[j+1]
                if tempAnswer < results[i][j]:
                    results[i][j] = tempAnswer

    #Returns the results
    return results[0][dimensionno-2]


#Main program to run the algorithm
#Includes the variables for changing and passing to the algorithm
dimensionvalues = [10, 5, 20, 15, 8]
dimensionno = len(dimensionvalues)
print(matrixchainorder(dimensionvalues, dimensionno))
# This Code is contributed by Bhavya Jain