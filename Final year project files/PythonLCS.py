#Dynamic programming implementation of the longest common subsequence algorithm
def lcs(string1, string2, stringlength1, stringlength2):

    #Array to store the results
    results = [[0 for _ in range(stringlength2+1)] for _ in range(stringlength1+1)]

    #Populate the array from the bottom up
    for i in range(0, stringlength1 + 1):
        for j in range(0, stringlength2 + 1):
            if i == 0 or j == 0:
                results[i][j] = 0
            elif string1[i-1] == string2[j-1]:
                results[i][j] = results[i-1][j-1] + 1
            else:
                results[i][j] = max(results[i-1][j], results[i][j-1])

    #Returns the results
    return results[stringlength1][stringlength2]


#Main program to run the algorithm
#Includes the variables for changing and passing to the algorithm
string1 = "AGGTAB"
string2 = "GXTXAYB"
stringlength1 = len(string1)
stringlength2 = len(string2)
print(lcs(string1, string2, stringlength1, stringlength2))