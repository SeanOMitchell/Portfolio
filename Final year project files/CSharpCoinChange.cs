using System;

namespace CSharpCoinChange
{
    class Program
    {
        //Main method to run the program
        //Includes the variables for changing and passing to the algorithm
        public static void Main()
        {
            int[] denominations = { 1, 2, 3 };
            int coinNo = denominations.Length;
            int goal = 4;
            Console.Write(CoinChange(denominations, coinNo, goal));
            Console.ReadKey();
        }

        //Dynamic programming implementation of the coin change algorithm
        static long CoinChange(int[] denominations, int coinNo, int goal)
        {
            //Array to store the results
            int[] results = new int[goal + 1];

            //Initialise the array to 0
            for (int i = 0; i < results.Length; i++)
            {
                results[i] = 0;
            }

            results[0] = 1;

            //Populate the array from the bottom up
            for (int i = 0; i < coinNo; i++)
            {
                for (int j = denominations[i]; j <= goal; j++)
                {
                    results[j] += results[j - denominations[i]];
                }
            }

            //Returns the results
            return results[goal];
        }
    }
}
