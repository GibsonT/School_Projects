import javax.swing.*;

/**
 * Travis Gibson n00921652
 * Data Structures - COP3530
 * Assignment 3
 */

public class n00921652 {
    public static void main(String[] args) {
        String input= (String)JOptionPane.showInputDialog(
                null,
                "Pick three values, spaced out with spaces.\n"
                    + "1st Value: Number of values in the list.\n"
                    + "2nd Value: The starting number to start cycling through the list.\n"
                    + "3rd Value: How many numbers to skip for each iteration.\n\n"
                    + "You may also type \"stop\" to end the program.",
                "Assignment 3 - Cycling / Deleting Through a Linked List",
                JOptionPane.PLAIN_MESSAGE,
                null,
                null,
                "");

        // In case user hits "Cancel"
        if (input == null) {
            input = "stop";
        }

        // In case user enters something like "Stop"
        input = input.toLowerCase();

        while (!input.equals("stop")) {
            CircularLinkedList linkedList = new CircularLinkedList();

            //Strip leading and trailing whitespace, then split into 3 ints
            //separated by spaces
            String[] listOptions = input.trim().split(" +", 3);

            int listSize = Integer.parseInt(listOptions[0]);
            int startPos = Integer.parseInt(listOptions[1]);
            int passingBy = Integer.parseInt(listOptions[2]);

            // Populate the list with 1 through listSize
            for (int i = 1; i <= listSize; i++) {
                linkedList.Insert(new Link(i));
            }

            // Create the iterator and increment it until at the chosen start point
            ListIterator iterator = new ListIterator(linkedList);
            if (startPos != 1) {
                for (int i = 2; i <= startPos; i++) {
                    iterator.Increment();
                }
            }

            // Start incrementing the iterator by the chosen skip amount and deleting
            // whichever one the iterator lands on
            while (linkedList.MoreThanOne()) {
                for (int i = 0; i < passingBy; i++) {
                    iterator.Increment();
                }

                iterator.DeleteCurrentLink();
            }

            // We're done, show the result
            JOptionPane.showMessageDialog(
                    null,
                    "The final value in this list is: " + linkedList.FirstLink().GetData()
            );

            // Go through another list?
            input= (String)JOptionPane.showInputDialog(
                    null,
                    "Pick three values, spaced out with spaces.\n"
                            + "1st Value: Number of values in the list.\n"
                            + "2nd Value: The starting number to start cycling through the list.\n"
                            + "3rd Value: How many numbers to skip for each iteration.\n\n"
                            + "You may also type \"stop\" to end the program.",
                    "Assignment 3 - Cycling / Deleting Through a Linked List",
                    JOptionPane.PLAIN_MESSAGE,
                    null,
                    null,
                    "");

            // In case user hits "Cancel"
            if (input == null) {
                input = "stop";
            }

            // In case user enters something like "Stop"
            input = input.toLowerCase();
        }
    }
}

class CircularLinkedList {
    private Link first;
    private Link last;

    public CircularLinkedList() {
        this.first = null;
        this.last = null;
    }

    // Adds a Link to the end of the list
    public void Insert(Link link) {
        if (IsEmpty()) {
            this.first = link;
            this.last = link;
            link.SetNext(link);
        }
        else {
            this.last.SetNext(link);
            this.last = link;
            link.SetNext(this.first);
        }
    }

    // Simply checks if the list contains more than one Link
    //
    // Works a lot faster than a full-blown Size() function, and
    // fit perfectly for this assignment.
    public boolean MoreThanOne() {
        boolean moreThanOne = false;
        if (!IsEmpty() && this.first.GetNext() != this.last) {
            moreThanOne = true;
        }

        return moreThanOne;
    }

    // Checks if the list is empty
    public boolean IsEmpty() {
        boolean empty;

        if (this.first == null) {
            empty = true;
        }
        else {
            empty = false;
        }

        return empty;
    }

    public Link FirstLink() {
        return this.first;
    }

    public Link LastLink() {
        return this.last;
    }

    public void SetFirst(Link link) {
        this.first = link;
    }

    public void SetLast(Link link) {
        this.last = link;
    }
}

class Link {
    private int data;
    private Link next;

    public Link(int data) {
        this.data = data;
        this.next = null;
    }

    public int GetData() {
        return this.data;
    }

    public Link GetNext() {
        return this.next;
    }

    public void SetNext(Link next) {
        this.next = next;
    }
}

class ListIterator {
    private CircularLinkedList linkedList;
    private Link currentLink;
    private Link previousLink;
    private Link nextLink;

    public ListIterator(CircularLinkedList linkedList) {
        this.linkedList = linkedList;
        this.currentLink = linkedList.FirstLink();
        this.previousLink = linkedList.LastLink();
        this.nextLink = currentLink.GetNext();
    }

    // Deletes the link in currentLink, and moves the current link up one link in the list
    public void DeleteCurrentLink() {
        if (this.currentLink == linkedList.FirstLink()) {
            linkedList.SetFirst(nextLink);
        }
        if (this.currentLink == linkedList.LastLink()) {
            linkedList.SetLast(previousLink);
        }

        previousLink.SetNext(nextLink);
        currentLink = nextLink;
    }

    // Moves the currentLink pointer up one link in the linked list
    public void Increment() {
        previousLink = currentLink;
        currentLink = currentLink.GetNext();
        nextLink = currentLink.GetNext();
    }
}
