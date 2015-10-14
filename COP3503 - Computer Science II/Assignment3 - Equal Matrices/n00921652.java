/*************************
/* COP3503 Assignment 3
/* Travis Gibson, n00921652
*************************/


import java.util.Scanner;

public class n00921652 {
   public static void main(String[] args) {
      int[][] matrix1 = new int[3][3];
      int[][] matrix2 = new int[3][3];
      Scanner keyboard = new Scanner(System.in);
      
      System.out.print("Enter list 1: ");
      for (int i = 0; i < matrix1.length; i++) {
         for (int j = 0; j < matrix1[i].length; j++) {
            matrix1[i][j] = keyboard.nextInt();
         }
      }
      
      System.out.print("Enter list 2: ");
      for (int i = 0; i < matrix2.length; i++) {
         for (int j = 0; j < matrix2[i].length; j++) {
            matrix2[i][j] = keyboard.nextInt();
         }
      }
      
      if (Strict.equals(matrix1, matrix2))
         System.out.println("\nMatrices are equal.\n");
      else
         System.out.println("\nMatrices are not equal.\n");
         
      System.out.println("There are " + Strict.howmany(matrix1, matrix2) + " matching cells.\n");
      System.out.println("There are " + Strict.diagonal(matrix1, matrix2) + " matching diagonal cells.\n");
      
      System.out.print("The average of all of the values in both matrices is ");
      System.out.format("%.2f", Strict.average(matrix1, matrix2));
      System.out.println(".\n");
      
      Strict.display(matrix1, matrix2);
      if (Strict.silly(matrix1, matrix2))
         System.out.println("\nThe matrices are silly.\n");
      else
         System.out.println("\nThe matrices are not silly.\n");
   }
}

class Strict {
   public static boolean equals(int[][] m1, int[][] m2) {
      boolean matricesAreEqual = true;
      
      // If the matrices are different lengths, they aren't equal
      if (m1.length == m2.length) {
         
         // I never actually tried using two conditions in a for loop. It apparantly works!
         // Loop will stop if it finds a pair that aren't equal.
         for (int i = 0; (i < m1.length && matricesAreEqual); i++) {
            
            if (m1[i].length == m2[i].length) {
               
               for (int j = 0; j < m1[i].length; j++) {
                  
                  if (m1[i][j] != m2[i][j]) {
                     matricesAreEqual = false;
                     break;
                  }
               }
            }
         }
      }
      
      else
         matricesAreEqual = false;
      
      return matricesAreEqual;
   }
   
   public static int howmany(int[][] m1, int[][] m2) {
      int matchingCount = 0;
      
      for (int i = 0; i < m1.length; i++) {
         for (int j = 0; j < m1[i].length; j++) {
            if (m1[i][j] == m2[i][j])
               matchingCount++;
         }
      }
      
      return matchingCount;
   }
   
   public static int diagonal(int[][] m1, int[][] m2) {
      int matchingCount = 0;
      
      for (int i = 0; (i < m1.length && i < m1[i].length); i++) {
         if (m1[i][i] == m2[i][i])
            matchingCount++;
      }
      
      return matchingCount;
   }
   
   public static double average(int[][] m1, int[][] m2) {
      int valueCount = m1.length + m2.length;
      int valueTotal = 0;
      
      for (int i = 0; i < m1.length; i++) {
         for (int j = 0; j < m1.length; j++) {
            valueTotal += m1[i][j];
            valueTotal += m2[i][j];
         }
      }
      
      return ((double)valueTotal / (double)valueCount);
   }
   
   public static void display(int[][] m1, int[][] m2) {
      
      // Begin special formatting voodoo
      System.out.println("Matrix 1 odds:");
      System.out.print("[ [");
      for (int i = 0; i < m1.length; i++) {
         for (int j = 0; j < m1[i].length; j++) {
            if (m1[i][j] % 2 != 0)
               System.out.format("%02d", m1[i][j]);
            else
               System.out.print("--");
            
            if (j != m1[i].length - 1)
               System.out.print("  ");
         }
         
         if (i == m1.length - 1) {
            System.out.println("] ]");
         }
         else {
            System.out.println("]");
            System.out.print("  [");
         }
            
      }
      
      System.out.println("\nMatrix 2 odds:");
      System.out.print("[ [");
      for (int i = 0; i < m2.length; i++) {
         for (int j = 0; j < m2[i].length; j++) {
            if (m2[i][j] % 2 != 0)
               System.out.format("%02d", m2[i][j]);
            else
               System.out.print("--");
            
            if (j != m2[i].length - 1)
               System.out.print("  ");
         }
         
         if (i == m2.length - 1) {
            System.out.println("] ]");
         }
         else {
            System.out.println("]");
            System.out.print("  [");
         }
            
      }
   }
   
   public static boolean silly(int[][] m1, int[][] m2) {
      boolean areArraysSilly = true;
      
      for (int i = 0; i < m1.length; i++) {
         for (int j = 0; j < m1[i].length; j++) {
            if (m1[i][j] <= 1 || m1[i][j] > 10 || m2[i][j] <= 1 || m2[i][j] > 10)
               areArraysSilly = false; 
         }
      }
      
      return areArraysSilly;
   }
}