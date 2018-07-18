#Dynamic programming implementation of the coin change algorithm
def coinchange(denominations, coinno, goal):
    #Array to store the results
    results = [0 for _ in range(goal + 1)]

    #initialise the array to 0
    for i in range(coinno):
        results[0] = 1

    #Populate the array from the bottom up
    for i in range(0, coinno):
        for j in range(denominations[i], goal+1):
            results[j] = results[j] + results[j - denominations[i]]
    #Returns the results
    return results[goal]


#Main program to run the algorithm
#Includes the variables for changing and passing to the algorithm
denominations = [1, 2, 5]
coinno = len(denominations)
goal = 5
print(coinchange(denominations, coinno, goal))