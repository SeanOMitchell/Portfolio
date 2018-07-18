public class Main {

    //Main method to run the program
    //Includes the variables for changing and passing to the algorithm
    public static void main(String args[]) {
        int dimensionValues[] = {1, 1, 1, 1};
        int dimensionNo = dimensionValues.length;
        System.out.println(MatrixChainOrder(dimensionValues, dimensionNo));
    }

    //Dynamic programming implementation of the matrix chain algorithm
    private static int MatrixChainOrder(int dimensionValues[], int dimensionNo) {

        //Array to store the results
        int results[][] = new int[dimensionNo-1][dimensionNo-1];

        //Populate the array from the bottom up
        //l = chain length
        for (int l = 1; l < dimensionNo-1; l++) {
            for (int i = 0; i < dimensionNo-l; i++) {
                results[i][i] = 0;
                int j = i + l;
                //Escape clause for j values that are too big
                if(j == dimensionNo-1) continue;
                results[i][j] = Integer.MAX_VALUE;
                for (int k = i; k <= j-1; k++) {
                    int tempAnswer = results[i][k] + results[k+1][j] + dimensionValues[i] * dimensionValues[k+1] * dimensionValues[j+1];
                    if (tempAnswer < results[i][j]) {
                        results[i][j] = tempAnswer;
                    }
                }
            }
        }
        //Returns the results
        return results[0][dimensionNo-2];
    }
}
