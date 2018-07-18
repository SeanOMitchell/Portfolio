public class Main {

    //Main method to run the program
    //Includes the variables for changing and passing to the algorithm
    public static void main(String[] args) {
        int weightMax = 3;
        int itemValue[] = new int[]{4, 5, 3};
        int itemWeight[] = new int[]{1, 2, 3};
        int itemNo = itemWeight.length;
        System.out.print(knapsack(itemNo, weightMax, itemWeight, itemValue));
    }

    //Dynamic programming implementation of the 0-1 knapsack algorithm
    public static int knapsack(int itemNo, int weightMax, int itemWeight[], int itemValue[]){

        //Array to store the results
        int results[][] = new int[itemNo+1][weightMax+1];

        //Populate the array from the bottom up
        for(int i = 0; i <= itemNo; i++){
            for(int j = 0; j <= weightMax; j++){
                if (i == 0 || j == 0){
                    results[i][j] = 0;
                } else if (itemWeight[i-1] > j){
                    results[i][j] = results[i-1][j];
                } else {
                    results[i][j] = max(results[i-1][j], results[i-1][j - itemWeight[i-1]] + itemValue[i-1]);
                }
            }
        }
        //Returns the results
        return results[itemNo][weightMax];
    }

    //Function to return the max of two values
    static int max(int a, int b){
        return (a > b)? a : b;
    }
}
