// highArray.java
// demonstrates array class with high-level interface
// to run this program: C>java HighArrayApp
////////////////////////////////////////////////////////////////
class HighArray
   {
   private long[] a;                 // ref to array a
   private int nElems;               // number of data items
   //-----------------------------------------------------------
   public HighArray(int max)         // constructor
      {
      a = new long[max];                 // create the array
      nElems = 0;                        // no items yet
      }
   //-----------------------------------------------------------
   public boolean find(long searchKey)
      {                              // find specified value
      int j;
      for(j=0; j<nElems; j++)            // for each element,
         if(a[j] == searchKey)           // found item?
            break;                       // exit loop before end
      if(j == nElems)                    // gone to end?
         return false;                   // yes, can't find it
      else
         return true;                    // no, found it
      }  // end find()
   //-----------------------------------------------------------
   public void insert(long value)    // put element into array
      {
      a[nElems] = value;             // insert it
      nElems++;                      // increment size
      }
   //-----------------------------------------------------------
   public boolean delete(long value)
      {
      int j;
      for(j=0; j<nElems; j++)        // look for it
         if( value == a[j] )
            break;
      if(j==nElems)                  // can't find it
         return false;
      else                           // found it
         {
         for(int k=j; k<nElems; k++) // move higher ones down
            a[k] = a[k+1];
         nElems--;                   // decrement size
         return true;
         }
      }  // end delete()
   //-----------------------------------------------------------
   public void display()             // displays array contents
      {
      for(int j=0; j<nElems; j++)       // for each element,
         System.out.print(a[j] + " ");  // display it
      System.out.println("");
      }
   //-----------------------------------------------------------
   public long getMax() {           // gets max value currently stored in array
      long maxValue = 0;

      if (nElems <= 0) {            // if no values stored in array
         maxValue = -1;
      }

      else {
         for (int i = 0; i < nElems; i++) { // now loop through array and find highest value
            if (a[i] > maxValue) {
               maxValue = a[i];
            }
         }
      }

      return maxValue;
   }
   //-----------------------------------------------------------
   public long getMin() {           // get min value currently stored in array
      long minValue = 0;

      if (nElems <= 0) {            // if no values in array
         minValue = -1;
      }

      else {
         minValue = a[0];           //set minValue to first item to start comparisons

         for (int i = 0; i < nElems; i++) {  // now loop through array and find lowest value
            if (a[i] < minValue) {
               minValue = a[i];
            }
         }
      }

      return minValue;
   }
   }  // end class HighArray
////////////////////////////////////////////////////////////////
class n00921652
   {
   public static void main(String[] args)
      {
      int maxSize = 100;            // array size
      long y;                       // will be set to max value of array
      long z;                       // will be set to min value of array
      HighArray arr;                // reference to array
      arr = new HighArray(maxSize); // create the array

      arr.insert(77);               // insert 10 items
      arr.insert(99);
      arr.insert(44);
      arr.insert(55);
      arr.insert(22);
      arr.insert(88);
      arr.insert(11);
      arr.insert(00);
      arr.insert(66);
      arr.insert(33);

      arr.display();                // display items

      int searchKey = 35;           // search for item
      if( arr.find(searchKey) )
         System.out.println("Found " + searchKey);
      else
         System.out.println("Can't find " + searchKey);

      arr.delete(00);               // delete 3 items
      arr.delete(55);
      arr.delete(99);

      arr.display();                // display items again

      y = arr.getMax();             // get max value of array
      System.out.println(y);        // display max value
      z = arr.getMin();             // get min value of array
      System.out.println(z);        // display min value
      }  // end main()
   }  // end class HighArrayApp
