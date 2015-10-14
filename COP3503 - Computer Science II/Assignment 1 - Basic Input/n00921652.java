import java.util.Scanner;
import java.util.Locale;
import java.text.NumberFormat;

public class n00921652 {
    public static void main(String[] args) {
        double distance;
        double milesPerGallon;
        double pricePerGallon;
        double totalCost;
        Scanner keyboard = new Scanner(System.in);

        //Locale and NumberFormat needed to format final cost
        Locale locale = new Locale("en", "US");
        NumberFormat numberFormat = NumberFormat.getCurrencyInstance(locale);

        //Grab inputs
        System.out.print("Enter the driving distance (miles): ");
        distance = keyboard.nextDouble();

        System.out.print("Enter the miles per gallon: ");
        milesPerGallon = keyboard.nextDouble();

        System.out.print("Enter the price per gallon: ");
        pricePerGallon = keyboard.nextDouble();

        //Perform highly sophisicated computation to figure out final cost and print result
        totalCost = (distance / milesPerGallon) * pricePerGallon;
        System.out.println("The total cost of your trip will be: " + numberFormat.format(totalCost));
    }
}
