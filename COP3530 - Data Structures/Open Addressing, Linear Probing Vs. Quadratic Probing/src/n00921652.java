import java.util.Scanner;

/**
 * Travis Gibson, n00921652
 * Assignment 6 - Open Addressing Experiment
 */
public class n00921652 {
    public static void main(String[] args) {
        final int NUMBER_OF_SAMPLES = 10000;
        final int NUMBER_OF_SEARCHES = 100;
        final int MAX_INT_SIZE;
        final int NUMBER_OF_TESTS = 9;
        int[] randomDataSample = new int[NUMBER_OF_SAMPLES];
        int[] searchValues = new int[NUMBER_OF_SEARCHES];
        Scanner scanner = new Scanner(System.in);

        System.out.println("\nEnter the maximum integer value for the samples: ");
        int testSize = scanner.nextInt();
        while (testSize < 1 || testSize > Math.pow(2, 31) - 1) {
            System.out.println("Value too large or less than 1, please try again: ");
            scanner.nextInt();
        }
        MAX_INT_SIZE = testSize;

        System.out.print("\n");

        System.out.println("Generating sample data to fill tables . . .");
        for (int i = 0; i < NUMBER_OF_SAMPLES; i++) {
            randomDataSample[i] = (int)((Math.random() * MAX_INT_SIZE) + 1);
        }

        System.out.println("\nGenerating sample data to search tables . . .");
        for (int i = 0; i < NUMBER_OF_SEARCHES; i++) {
            searchValues[i] = (int)((Math.random() * MAX_INT_SIZE) + 1);
        }

        System.out.println("\nPerforming tests, please wait. This will take a few minutes . . .");
        System.out.println("\n(For each load: Top Row - Linear, Bottom Row - Quadratic)");
        System.out.println("Load\tES\tDS\tTS\tEF\tDF\tTF");
        System.out.println("========================================================");
        for (int i = 0; i < NUMBER_OF_TESTS; i++) {
            double loadFactor = (double)(NUMBER_OF_TESTS - i) / 10;
            int hashTableSize = FindNextPrime((int)(Math.ceil(NUMBER_OF_SAMPLES / loadFactor)));
            loadFactor = (double)NUMBER_OF_SAMPLES/(double)hashTableSize;
            int linearFindSuccess = 0;
            int linearFindFail = 0;
            int quadraticFindSuccess = 0;
            int quadraticFindFail = 0;
            int linearSuccessProbeLength = 0;
            int linearFailProbeLength = 0;
            int quadraticSuccessProbeLength = 0;
            int quadraticFailProbeLength = 0;
            HashTable linearHashTable = new HashTable(hashTableSize);
            HashTable quadraticHashTable = new HashTable(hashTableSize);
            System.gc();

            for (int j = 0; j < NUMBER_OF_SAMPLES; j++) {
                linearHashTable.LinearInsert(randomDataSample[j]);
                quadraticHashTable.QuadraticInsert(randomDataSample[j]);
                System.gc();    // Will run out of memory for VM otherwise
            }

            for (int j = 0; j < NUMBER_OF_SEARCHES; j++) {
                if (linearHashTable.LinearFind(searchValues[j])) {
                    linearFindSuccess++;
                    linearSuccessProbeLength += linearHashTable.GetLatestProbeLength();
                }
                else {
                    linearFindFail++;
                    linearFailProbeLength += linearHashTable.GetLatestProbeLength();
                }

                if (quadraticHashTable.QuadraticFind(searchValues[j])) {
                    quadraticFindSuccess++;
                    quadraticSuccessProbeLength += quadraticHashTable.GetLatestProbeLength();
                }
                else {
                    quadraticFindFail++;
                    quadraticFailProbeLength += quadraticHashTable.GetLatestProbeLength();
                }
            }

            double avgLinearSuccessProbeLength = (double)linearSuccessProbeLength/(double)linearFindSuccess;
            double avgLinearFailProbeLength = (double)linearFailProbeLength/(double)linearFindFail;
            double avgQuadraticSuccessProbeLength = (double)quadraticSuccessProbeLength/(double)quadraticFindSuccess;
            double avgQuadraticFailProbeLength = (double)quadraticFailProbeLength/(double)quadraticFindFail;
            double theoLinearFailProbeLength = (1.f + (1.f/((1.f - loadFactor)*(1.f - loadFactor)))) / 2.f;
            double theoLinearSuccessProbeLength = (1.f + (1.f/(1.f - loadFactor))) / 2.f;
            double theoQuadraticFailProbeLength = (1.f / (1.f - loadFactor));
            double theoQuadraticSuccessProbeLength = Math.log((1.f / (1.f - loadFactor))) / loadFactor;

            System.out.printf("%.2f", loadFactor);
            System.out.print("\t");
            System.out.printf("%.2f", avgLinearSuccessProbeLength);
            System.out.print("\t" + linearFindSuccess + "\t");
            System.out.printf("%.2f", theoLinearSuccessProbeLength);
            System.out.printf("\t");
            System.out.printf("%.2f", avgLinearFailProbeLength);
            System.out.print("\t" + linearFindFail + "\t");
            System.out.printf("%.2f", theoLinearFailProbeLength);
            System.out.printf("\n\t");
            System.out.printf("%.2f", avgQuadraticSuccessProbeLength);
            System.out.print("\t" + quadraticFindSuccess + "\t");
            System.out.printf("%.2f", theoQuadraticSuccessProbeLength);
            System.out.print("\t");
            System.out.printf("%.2f", avgQuadraticFailProbeLength);
            System.out.print("\t" + quadraticFindFail + "\t");
            System.out.printf("%.2f", theoQuadraticFailProbeLength);
            System.out.print("\n");
        }
    }

    public static int FindNextPrime(int start) {
        int possiblePrime = start;
        if (possiblePrime % 2 == 0) {
            possiblePrime++;
        }

        int sqrtOfPossiblePrime = (int)Math.ceil(Math.sqrt((double)possiblePrime));

        for (int i = 3; i < sqrtOfPossiblePrime; i += 2) {
            if (possiblePrime % i == 0) {
                possiblePrime = FindNextPrime(possiblePrime + 2);
                break;
            }
        }

        return possiblePrime;
    }
}

class HashTable {
    private final int tableSize;
    private int[] table;
    private int latestProbeLength;

    public HashTable(int tableSize) {
        this.tableSize = tableSize;
        this.table = new int[tableSize];
        for (int i = 0; i < tableSize; i++) {
            table[i] = -1;
        }
    }

    public void LinearInsert(int key) {
        int keyHash = Hash(key);

        for (int i = 0; i < tableSize; i++) {
            int index = (keyHash + i) % tableSize;
            /*if (index >= tableSize) {
                index -= tableSize;
            }*/

            if (table[index] == -1) {
                table[index] = key;
                return;
            }
        }
    }

    public Boolean LinearFind(int key) {
        int keyHash = Hash(key);
        latestProbeLength = 1;

        for (int i = 0; i < tableSize; i++) {
            int index = (keyHash + i) % tableSize;
            /*if (index >= tableSize) {
                index -= tableSize;
            }*/

            if (table[index] == key) {
                return true;
            }
            else if (table[index] == -1) {
                break;
            }

            latestProbeLength++;
        }

        return false;
    }

    public Boolean QuadraticInsert(int key) {
        int keyHash = Hash(key);

        for (int i = 0; i < tableSize / 2; i++) {
            int index = (keyHash + (i * i)) % tableSize;
            /*while (index >= tableSize) {
                index -= tableSize;
            }*/

            if (index > -1 && table[index] == -1) {
                table[index] = key;
                return true;
            }
        }

        return false;
    }

    public Boolean QuadraticFind(int key) {
        int keyHash = Hash(key);
        latestProbeLength = 1;

        for (int i = 0; i < tableSize / 2; i++) {
            int index = (keyHash + (i * i)) % tableSize;
            /*while (index >= tableSize) {
                index -= tableSize;
            }*/
            if (index > -1 && table[index] == key) {
                return true;
            }
            else if (index <= -1 || table[index] == -1) {
                break;
            }

            latestProbeLength++;
        }

        return false;
    }

    public int Hash(Integer value) {
        int hashValue = 0;

        for (int i = 0; i < value.toString().length(); i++) {
            int thisDigit = Integer.parseInt(String.valueOf(value.toString().charAt(value.toString().length() - 1 - i)));

            hashValue = (hashValue * 10 + thisDigit) % tableSize;
        }

        return hashValue;
    }

    public int GetLatestProbeLength() {
        return latestProbeLength;
    }
}

class Element {
    private int key;
    private int hash;

    public Element(int key, int hash) {
        this.key = key;
        this.hash = hash;
    }

    public int getKey() {
        return key;
    }

    public void setKey(int key) {
        this.key = key;
    }

    public int getHash() {
        return hash;
    }

    public void setHash(int hash) {
        this.hash = hash;
    }
}
