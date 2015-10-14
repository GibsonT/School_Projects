import javax.swing.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

/**
 * Travis Gibson
 * Assignment 4
 * COP 3530 - Data Structures
 */
public class n00921652 {
    public static void main(String[] args) {
        String input;
        int numberOfWeights;
        Integer[] weights;          //Storing as Integer instead of int to take advantage of sorting in descending order
        String[] weightOptions;
        int targetWeight;
        String[] weightStrings;
        String[] acceptedWeights;
        ArrayList<ArrayList<Integer>> calculatedWeights;

        input= (String) JOptionPane.showInputDialog(
                null,
                "Enter the target weight followed by the weight values for the knapsack.\n"
                + "Type \"stop\" to quit.",
                "Assignment 4 - Knapsack Problem",
                JOptionPane.PLAIN_MESSAGE,
                null,
                null,
                "");

        if (input == null) {
            input = "stop";
        }

        while (!input.equals("stop")) {
            calculatedWeights = new ArrayList<ArrayList<Integer>>();

            //Splitting input string to separate targetWeight and list of given weights
            weightOptions = input.trim().split(" +", 2);
            targetWeight = Integer.parseInt(weightOptions[0]);

            //Count number of given weights, set size of weights array
            numberOfWeights = 0;
            for (int i = 0; i < weightOptions[1].length(); i++) {
                if (weightOptions[1].charAt(i) == ' ') {
                    numberOfWeights++;
                }
            }
            if (numberOfWeights > 0) {
                numberOfWeights++;
            }

            weights = new Integer[numberOfWeights];

            //Parse given weights and place into array
            for (int i = 0; i < numberOfWeights; i++) {
                String[] nextWeight = weightOptions[1].split(" +", 2);
                weights[i] = Integer.parseInt(nextWeight[0]);
                if (nextWeight.length > 1) {
                    weightOptions[1] = nextWeight[1];
                }
            }

            Arrays.sort(weights, Collections.reverseOrder());
            Knapsack(targetWeight, numberOfWeights, weights, calculatedWeights);

            //Format results
            if (calculatedWeights.isEmpty()) {
                JOptionPane.showMessageDialog(
                        null,
                        "No combination of the weights that match the target found!"
                );
            }
            else {
                String finalInput = "";
                for (int i = 0; i < calculatedWeights.size(); i++) {
                    for (int j = 0; j < calculatedWeights.get(i).size(); j++){
                       finalInput += calculatedWeights.get(i).get(j) + " ";
                    }

                    finalInput += "\n";
                }

                JOptionPane.showMessageDialog(
                        null,
                        "The following combinations were found:\n" + finalInput
                );
            }

            input= (String) JOptionPane.showInputDialog(
                    null,
                    "Enter the target weight followed by the weight values for the knapsack.\n"
                    + "Type \"stop\" to quit.",
                    "Assignment 4 - Knapsack Problem",
                    JOptionPane.PLAIN_MESSAGE,
                    null,
                    null,
                    "");

            if (input == null) {
                input = "stop";
            }
        }
    }

    // This thing is UGLY, but it gets the job done with recursion.
    static int Knapsack(int targetWeight, int numberOfWeights, Integer[] weightsToSort, ArrayList<ArrayList<Integer>> acceptedWeights) {
        for (int i = 0; i < weightsToSort.length; i++) {
            //Weight is less than target, lets take it and try it out
            //If it's the last weight to test, no reason to take
            if (weightsToSort[i] < targetWeight && i != weightsToSort.length - 1) {
                //Create a new array from sub-array
                Integer[] newArray = new Integer[weightsToSort.length - (i + 1)];
                int newTarget = targetWeight - weightsToSort[i];
                System.arraycopy(weightsToSort, i + 1, newArray, 0, newArray.length);

                if (Knapsack(newTarget, numberOfWeights, newArray, acceptedWeights) != -1) {
                    if (acceptedWeights.size() == 0 || acceptedWeights.get(acceptedWeights.size() - 1).get(acceptedWeights.get(acceptedWeights.size() - 1).size() - 1) >= weightsToSort[i]) {
                        acceptedWeights.add(new ArrayList<Integer>());
                    }

                    acceptedWeights.get(acceptedWeights.size() - 1).add(weightsToSort[i]);

                    //Don't return if we're back at the original input array
                    if (numberOfWeights != weightsToSort.length) {
                        return weightsToSort[i];
                    }
                }
            }

            else if (weightsToSort[i] == targetWeight) {
                if (acceptedWeights.size() == 0 || acceptedWeights.get(acceptedWeights.size() - 1).get(acceptedWeights.get(acceptedWeights.size() - 1).size() - 1) >= weightsToSort[i]) {
                    acceptedWeights.add(new ArrayList<Integer>());
                }

                acceptedWeights.get(acceptedWeights.size() - 1).add(weightsToSort[i]);

                if (numberOfWeights != weightsToSort.length) {
                    return weightsToSort[i];
                }
            }
        }

        return -1;
    }
}
