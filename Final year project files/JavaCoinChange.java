public class Main {

    //Main method to run the program
    //Includes the variables for changing and passing to the algorithm
    public static void main(String[] args)
    {
        String string1 = "ABCDE";
        String string2 = "ABCDE";
        char[] stringArray1=string1.toCharArray();
        char[] stringArray2=string2.toCharArray();
        int stringLength1 = stringArray1.length;
        int stringLength2 = stringArray2.length;
        System.out.println(lcs(stringArray1, stringArray2, stringLength1, stringLength2 ));
    }

    //Dynamic programming implementation of the longest common subsequence algorithm
    private static int lcs( char[] stringArray1, char[] stringArray2, int stringLength1, int stringLength2 )
    {
        //Array to store the results
        int results[][] = new int[stringLength1+1][stringLength2+1];

        //Populate the array from the bottom up
        for (int i = 0; i <= stringLength1; i++) {
            for (int j = 0; j <= stringLength2; j++) {
                if (i == 0 || j == 0) {
                    results[i][j] = 0;
                }else if (stringArray1[i-1] == stringArray2[j-1]) {
                    results[i][j] = results[i - 1][j - 1] + 1;
                }else {
                    results[i][j] = max(results[i - 1][j], results[i][j - 1]);
                }
            }
        }
        //Returns the results
        return results[stringLength1][stringLength2];
    }

    //Function to return the max of two values
    static int max(int a, int b){
        return (a > b)? a : b;
    }
}
