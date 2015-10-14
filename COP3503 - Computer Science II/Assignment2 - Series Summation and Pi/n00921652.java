/* Travis Gibson
 * n00921652
 * COP3503 Assignment 2
 */

import java.util.Scanner;

public class n00921652 {
    public static void main(String[] args) {
        int input = 0;
        double seriesSum = 0;
        double piSum = 1;
        Scanner keyboard = new Scanner(System.in);

        // Needed for Pi estimation to determine whether to add or subtract next term
        boolean isNegative = true;

        System.out.print("Input an odd integer: ");
        input = keyboard.nextInt();

        for (int i = 3; i <= input; i += 2) {
            seriesSum += (double)(i - 2)/(double)i;

            if (isNegative) {
                piSum -= 1.0/(double)i;
                isNegative = false;
            }
            else {
                piSum += 1.0/(double)i;
                isNegative = true;
            }
            
        }

        // Pi estimation needs to be multiplied by 4 to finalize calculation
        piSum *= 4;

        System.out.println("\nSeries summation to the " + input + " denominator is:\t" + String.format("%.8f", seriesSum));
        System.out.println("Pi estimation to the " + input + " denominator is:\t" + String.format("%.8f", piSum));
    }
}
