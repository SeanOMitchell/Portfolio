#Dynamic programming implementation of the 0-1 knapsack problem
def knapsack(itemno, weightmax, itemweight, itemvalue):
    #array to store the results
    results = [[0 for _ in range(weightmax + 1)] for _ in range(itemno + 1)]

    #Populate the array from the bottom up
    for i in range(itemno + 1):
        for j in range(weightmax + 1):
            if i == 0 or j == 0:
                results[i][j] = 0
            elif itemweight[i-1] > j:
                results[i][j] = results[i - 1][j]
            else:
                results[i][j] = max(results[i-1][j], results[i-1][j - itemweight[i-1]] + itemvalue[i-1])

    #Returns the results
    return results[itemno][weightmax]


#Main program to run the algorithm
#Includes the variables for changing and passing to the algorithm
weightmax = 50
itemvalue = [60, 100, 120]
itemweight = [10, 20, 30]
itemno = len(itemvalue)
print(knapsack(itemno, weightmax, itemweight, itemvalue))