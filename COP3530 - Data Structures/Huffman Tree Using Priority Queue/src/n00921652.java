import java.io.*;
import java.util.*;               // for Stack class

/**
 * Created by tgibson on 3/12/2015.
 */
public class n00921652 {
    public static void main(String[] args) throws FileNotFoundException {

        //Allocate nodes for each letter
        Node aNode = new Node();
        Node bNode = new Node();
        Node cNode = new Node();
        Node dNode = new Node();
        Node eNode = new Node();
        Node fNode = new Node();
        Node gNode = new Node();
        Tree huffmanTree = new Tree();
        int maxQueueSize = 7;
        PriorityQueue nodeQueue = new PriorityQueue(maxQueueSize);
        String testFile = new Scanner(new File(args[0])).useDelimiter("\\A").next();
        String encodedMessage = "\t";

        //Assign letters to nodes
        aNode.letter = 'A';
        bNode.letter = 'B';
        cNode.letter = 'C';
        dNode.letter = 'D';
        eNode.letter = 'E';
        fNode.letter = 'F';
        gNode.letter = 'G';

        //Process string and get frequencies
        for (int i = 0; i < testFile.length(); i++) {
            char letter = testFile.charAt(i);

            switch (letter) {
                case 'A':
                    aNode.frequency++;
                    break;
                case 'B':
                    bNode.frequency++;
                    break;
                case 'C':
                    cNode.frequency++;
                    break;
                case 'D':
                    dNode.frequency++;
                    break;
                case 'E':
                    eNode.frequency++;
                    break;
                case 'F':
                    fNode.frequency++;
                    break;
                case 'G':
                    gNode.frequency++;
                    break;
                default:
                    break;
            }
        }

        //Insert each into priority queue
        nodeQueue.Insert(aNode);
        nodeQueue.Insert(bNode);
        nodeQueue.Insert(cNode);
        nodeQueue.Insert(dNode);
        nodeQueue.Insert(eNode);
        nodeQueue.Insert(fNode);
        nodeQueue.Insert(gNode);

        //Prep the nodes to insert into Huffman tree
        //This will leave us with one main node, with the rest as children
        while (nodeQueue.GetSize() > 1) {
            Node newNode = new Node();
            newNode.leftChild = nodeQueue.Remove();
            newNode.rightChild = nodeQueue.Remove();
            newNode.frequency = newNode.leftChild.frequency + newNode.rightChild.frequency;

            nodeQueue.Insert(newNode);
        }

        //Insert the meganode into Huffman tree
        huffmanTree.insert(nodeQueue.Remove());

        //Get the codes for each letter
        huffmanTree.findCodes(huffmanTree.GetRoot(), new String());

        //Generate the encoded string
        int byteCount = 0;
        int bitCount = 0;
        for (int i = 0; i < testFile.length(); i++) {
            String code = "";
            switch (testFile.charAt(i)) {
                case 'A':
                    code = aNode.code;
                    break;
                case 'B':
                    code = bNode.code;
                    break;
                case 'C':
                    code = cNode.code;
                    break;
                case 'D':
                    code = dNode.code;
                    break;
                case 'E':
                    code = eNode.code;
                    break;
                case 'F':
                    code = fNode.code;
                    break;
                case 'G':
                    code = gNode.code;
                    break;
                default:
                    break;
            }
            if (code.equals("")) {
                continue;
            }

            for (int j = 0; j < code.length(); j++) {
                if (bitCount == 8) {
                    encodedMessage = encodedMessage + " ";
                    bitCount = 0;
                    if (++byteCount == 3) {
                        encodedMessage = encodedMessage + "\n\t";
                        byteCount = 0;
                    }
                }

                encodedMessage = encodedMessage + code.charAt(j);
                bitCount++;
            }
        }

        System.out.println("-------------------HUFFMAN TREE-------------------");
        huffmanTree.displayTree();
        System.out.println("--------------------------------------------------\n\n");

        System.out.println("--------------------CODE TABLE--------------------");
        if (aNode.frequency != 0) System.out.println("\tA:\t\t" + aNode.code);
        if (bNode.frequency != 0) System.out.println("\tB:\t\t" + bNode.code);
        if (cNode.frequency != 0) System.out.println("\tC:\t\t" + cNode.code);
        if (dNode.frequency != 0) System.out.println("\tD:\t\t" + dNode.code);
        if (eNode.frequency != 0) System.out.println("\tE:\t\t" + eNode.code);
        if (fNode.frequency != 0) System.out.println("\tF:\t\t" + fNode.code);
        if (gNode.frequency != 0) System.out.println("\tG:\t\t" + gNode.code);
        System.out.println("--------------------------------------------------\n\n");

        System.out.println("--------------------ENCODED FILE------------------");
        System.out.println(encodedMessage);
        System.out.println("--------------------------------------------------\n\n");

        System.out.println("------------------DECODED STRING------------------");
        System.out.println(huffmanTree.decode(encodedMessage));
        System.out.println("--------------------------------------------------\n\n");
    }
}

class Node {
    public int frequency = 0;
    public char letter = '!';       // I'm using '!' to denote that this isn't a leaf
    public String code;
    public Node leftChild;         // this node's left child
    public Node rightChild;        // this node's right child
}

class Tree
{
    private Node root;             // first node of tree

    public Tree()                  // constructor
    { root = null; }            // no nodes in tree yet

    public Node GetRoot() {
        return root;
    }

    //Due to how I designed this program, the insert function is very basic in this case
    public void insert(Node node)
    {
        root = node;
    }

    //Recursively search the tree and assign the proper coding to each letter
    public void findCodes(Node localRoot, String code) {
        if (localRoot.letter != '!') {
            localRoot.code = code;
        }

        else {
            findCodes(localRoot.leftChild, code + "0");
            findCodes(localRoot.rightChild, code + "1");
        }
    }

    //Traverse the tree and decode the encoded string
    public String decode(String encodedString) {
        Node node = root;
        String decodedString = "";

        for (int i = 0; i < encodedString.length(); i++) {
            if (encodedString.charAt(i) == '0') {
                node = node.leftChild;
            }
            else if (encodedString.charAt(i) == '1') {
                node = node.rightChild;
            }

            if (node.letter != '!') {
                decodedString = decodedString + node.letter;
                node = root;
            }
        }

        return decodedString;
    }

    public void displayTree()
    {
        Stack globalStack = new Stack();
        globalStack.push(root);
        int nBlanks = 32;
        boolean isRowEmpty = false;
        System.out.println(
                "......................................................");
        while(isRowEmpty==false)
        {
            Stack localStack = new Stack();
            isRowEmpty = true;

            for(int j=0; j<nBlanks; j++)
                System.out.print(' ');

            while(globalStack.isEmpty()==false)
            {
                Node temp = (Node)globalStack.pop();
                if(temp != null)
                {
                    if (temp.letter != '!') {
                        System.out.print(temp.letter);
                    }
                    else {
                        System.out.print(temp.frequency);
                    }

                    localStack.push(temp.leftChild);
                    localStack.push(temp.rightChild);

                    if(temp.leftChild != null ||
                            temp.rightChild != null)
                        isRowEmpty = false;
                }
                else
                {
                    System.out.print("--");
                    localStack.push(null);
                    localStack.push(null);
                }
                for(int j=0; j<nBlanks*2-2; j++)
                    System.out.print(' ');
            }  // end while globalStack not empty
            System.out.println();
            nBlanks /= 2;
            while(localStack.isEmpty()==false)
                globalStack.push( localStack.pop() );
        }  // end while isRowEmpty is false
        System.out.println(
                "......................................................");
    }  // end displayTree()
}  // end class Tree

class PriorityQueue {
    private int maxSize;
    private Node[] nodeArray;
    private int numberOfItems;

    public PriorityQueue(int maxSize) {
        this.maxSize = maxSize;
        this.nodeArray = new Node[maxSize];
        this.numberOfItems = 0;
    }

    //Insert node into queue, with highest frequency characters in the front
    public void Insert(Node node) {
        int arrayIndex;

        if (node.frequency != 0) {
            if (numberOfItems == 0) {
                nodeArray[numberOfItems++] = node;
            }
            else {
                for (arrayIndex = numberOfItems - 1; arrayIndex >= 0; arrayIndex--) {
                    if (node.frequency >= nodeArray[arrayIndex].frequency) {
                        nodeArray[arrayIndex + 1] = nodeArray[arrayIndex];
                    } else {
                        break;
                    }
                }

                nodeArray[arrayIndex + 1] = node;
                numberOfItems++;
            }
        }
    }

    public Node Remove() {
        return nodeArray[--numberOfItems];
    }

    //Returns current number of nodes in queue
    public int GetSize() {
        return numberOfItems;
    }
}
