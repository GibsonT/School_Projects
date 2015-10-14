import java.util.Scanner;
import java.util.Comparator;
import java.util.Arrays;
import java.io.FileNotFoundException;
import java.io.File;

public class n00921652 {
    public static void main(String args[]) throws FileNotFoundException {
        Vehicle[] vehicles;
        Scanner inputFile = new Scanner(new File(args[0]));
        //inputFile.useDelimiter("\n");
        //System.out.println(inputFile.delimiter());

        //Set size of array to number of entries in input file
        for (int i = 0; ;) {
            if (!inputFile.hasNextLine()) {
                vehicles = new Vehicle[++i]; //Assuming there isn't a new line at EOF, number of entries is number of blank lines + 1
                System.out.print(vehicles.length);
                break;
            }

            if (inputFile.nextLine().isEmpty())
                i++;
        }

        inputFile.close();
        inputFile = new Scanner(new File(args[0]));

        for (int i = 0; i < vehicles.length; i++) {
            String vehicleType = inputFile.nextLine().toLowerCase();
            String name = inputFile.nextLine();
            String address = inputFile.nextLine();
            String phone = inputFile.nextLine();
            String email = inputFile.nextLine();
            boolean convertible;
            String color;
            boolean madeInDetroit;
            boolean madeInUnionShop;
            String countryOfManufacture;
            float importDuty;
            int numberOfSpeeds;
            float weightInTons;
            float cost;
            String datePurchased;

            switch (vehicleType) {
                case "vehicle":
                    vehicles[i] = new Vehicle(name, address, phone, email);
                    if (inputFile.hasNextLine())
                        inputFile.nextLine();
                    break;
                case "car":
                    convertible = inputFile.nextBoolean();
                    inputFile.nextLine();
                    color = inputFile.nextLine();
                    vehicles[i] = new Car(name, address, phone, email, convertible, color);
                    if (inputFile.hasNextLine())
                        inputFile.nextLine();
                    break;
                case "american car":
                    convertible = inputFile.nextBoolean();
                    inputFile.nextLine();
                    color = inputFile.nextLine();
                    madeInDetroit = inputFile.nextBoolean();
                    inputFile.nextLine();
                    madeInUnionShop = inputFile.nextBoolean();
                    if (inputFile.hasNextLine())
                        inputFile.nextLine();
                    vehicles[i] = new AmericanCar(name, address, phone, email, convertible, color, madeInDetroit, madeInUnionShop);
                    if (inputFile.hasNextLine())
                        inputFile.nextLine();
                    break;
                case "foreign car":
                    convertible = inputFile.nextBoolean();
                    inputFile.nextLine();
                    color = inputFile.nextLine();
                    countryOfManufacture = inputFile.nextLine();
                    importDuty = inputFile.nextFloat();
                    if (inputFile.hasNextLine())
                        inputFile.nextLine();
                    vehicles[i] = new ForeignCar(name, address, phone, email, convertible, color, countryOfManufacture, importDuty);
                    if (inputFile.hasNextLine())
                        inputFile.nextLine();
                    break;
                case "bicycle":
                    numberOfSpeeds = inputFile.nextInt();
                    if (inputFile.hasNextLine())
                        inputFile.nextLine();
                    vehicles[i] = new Bicycle(name, address, phone, email, numberOfSpeeds);
                    if (inputFile.hasNextLine())
                        inputFile.nextLine();
                    break;
                    //Not quite sure why this needs 3 nextLine() calls at the end, but "it works" (TM)
                case "truck":
                    weightInTons = inputFile.nextFloat();
                    inputFile.nextLine();
                    cost = inputFile.nextFloat();
                    inputFile.nextLine();
                    datePurchased = inputFile.nextLine();
                    vehicles[i] = new Truck(name, address, phone, email, weightInTons, cost, datePurchased);
                    if (inputFile.hasNextLine())
                        inputFile.nextLine();
                    break;
                default:
                    System.out.println("In default case (shouldn't happen)");
                    break;
            }
        }

        System.out.println("***Printing inputted records***");
        printAll(vehicles); 
        System.out.println("\n\n***Printing records sorted by email***");
        sortByEmail(vehicles);
        System.out.print("\n\nNumber of total records: ");
        printNumberOfRecords(vehicles);
        System.out.println("\n\n***Printing truck and bicycle records***");
        printTrucksAndBicycles(vehicles);
        System.out.println("\n\n***Printing records from area code 987***");
        printFromAreaCode(vehicles, "(987)");
    }

    public static void printAll(Vehicle[] vehicles) {
        for (int i = 0; i < vehicles.length; i++) {
            System.out.println(vehicles[i].toString());
        }
    }

    public static void sortByEmail(Vehicle[] vehicles) {
    
        //Defines how the array should be sorted.
        Comparator<Vehicle> emailComparator = new Comparator<Vehicle>() {
            public int compare(Vehicle s1, Vehicle s2) {
                return s1.getEmail().compareTo(s2.getEmail());
            }
        };
        
        Arrays.sort(vehicles, emailComparator);
        printAll(vehicles);
    }
    
    public static void printTrucksAndBicycles(Vehicle[] vehicles) {
      for (int i = 0; i < vehicles.length; i++) {
         if (vehicles[i].getVehicleType().equals("Truck") || vehicles[i].getVehicleType().equals("Bicycle"))
            System.out.println(vehicles[i].toString());
      }
    }
    
    public static void printFromAreaCode(Vehicle[] vehicles, String areaCode) {
      for (int i = 0; i < vehicles.length; i++) {
         if (vehicles[i].getPhone().startsWith(areaCode))
            System.out.println(vehicles[i].toString());
      }
    }
    
    public static void printNumberOfRecords(Vehicle[] vehicles) {
      System.out.println(vehicles.length);
    }
}

class Vehicle {
    private String name;
    private String address;
    private String phone;
    private String email;
    protected String vehicleType;

    public Vehicle (String name, String address, String phone, String email) {
        this.name = name;
        this.address = address;
        this.phone = phone;
        this.email = email;
        this.vehicleType = "Vehicle";
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public void setPhone(String phone) {
        this.phone = phone;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public void setVehicleType(String vehicleType) {
        this.vehicleType = vehicleType;
    }

    public String getName() {
        return this.name;
    }

    public String getAddress() {
        return this.address;
    }

    public String getPhone() {
        return this.phone;
    }

    public String getEmail() {
        return this.email;
    }

    public String getVehicleType() {
        return this.vehicleType;
    }

    public String toString() {
        return ("Vehicle Type: \t\t" + vehicleType + "\n" +
                "Owner Name: \t\t" + name + "\n" +
                "Address: \t\t" + address + "\n" +
                "Phone: \t\t\t" + phone + "\n" +
                "Email: \t\t\t" + email + "\n");
    }


}

class Car extends Vehicle {
    private boolean convertible;
    private String color;

    public Car(String name, String address, String phone, String email, 
            boolean convertible, String color) {
        super(name, address, phone, email);
        this.vehicleType = "Car";
        this.convertible = convertible;
        this.color = color;
    }

    public void setConvertible(boolean convertible) {
        this.convertible = convertible;
    }

    public void setColor(String color) {
        this.color = color;
    }

    public boolean isConvertible() {
        return this.convertible;
    }

    public String getColor() {
        return this.color;
    }

    public String toString() {
        return (super.toString() + 
                "Color: \t\t\t" + color + "\n" +
                "Is Convertible: \t" + convertible + "\n");
    }
}

class AmericanCar extends Car {
    private boolean madeInDetroit;
    private boolean madeInUnionShop;

    public AmericanCar(String name, String address, String phone, String email, 
            boolean convertible, String color, boolean madeInDetroit, boolean madeInUnionShop) {
        super(name, address, phone, email, convertible, color);
        this.madeInDetroit = madeInDetroit;
        this.madeInUnionShop = madeInUnionShop;
        this.vehicleType = "American Car";
    }

    public void setMadeInDetroit(boolean madeInDetroit) {
        this.madeInDetroit = madeInDetroit;
    }

    public void setMadeInUnionShop(boolean madeInUnionShop) {
        this.madeInUnionShop = madeInUnionShop;
    }

    public boolean isMadeInDetroit() {
        return this.madeInDetroit;
    }

    public boolean isMadeInUnionShop() {
        return this.madeInUnionShop;
    }

    public String toString() {
        return (super.toString() +
                "Made In Detroit: \t" + madeInDetroit + "\n" +
                "Made In A Union Shop: \t" + madeInUnionShop + "\n");
    }
}

class ForeignCar extends Car {
    private String countryOfOrigin;
    private float importDuty;

    public ForeignCar(String name, String address, String phone, String email, 
            boolean convertible, String color, String countryOfOrigin, float importDuty) {
        super(name, address, phone, email, convertible, color);
        this.countryOfOrigin = countryOfOrigin;
        this.importDuty = importDuty;
        this.vehicleType = "Foreign Car";                
    }

    public void setCountryOfOrigin(String countryOfOrigin) {
        this.countryOfOrigin = countryOfOrigin;
    }

    public void setImportDuty(float setImportDuty) {
        this.importDuty = importDuty;
    }

    public String getCountryOfOrigin() {
        return this.countryOfOrigin;
    }

    public float getImportDuty() {
        return this.importDuty;
    }

    public String toString() {
        return (super.toString() +
                "Country Of Origin: \t" + countryOfOrigin + "\n" +
                "Import Duty: \t\t$" + importDuty + "\n");
    }
}

class Bicycle extends Vehicle {
    private int numberOfSpeeds;

    public Bicycle (String name, String address, String phone, String email, int numberOfSpeeds) {
        super(name, address, phone, email);
        this.numberOfSpeeds = numberOfSpeeds;
        this.vehicleType = "Bicycle";
    }

    public void setNumberOfSpeeds(int numberOfSpeeds) {
        this.numberOfSpeeds = numberOfSpeeds;
    }

    public int getNumberOfSpeeds() {
        return this.numberOfSpeeds;
    }

    public String toString() {
        return (super.toString() +
                "Number Of Speeds: \t" + numberOfSpeeds + "\n");
    }
}

class Truck extends Vehicle {
    private float weightInTons;
    private float cost;
    private String datePurchased;

    public Truck (String name, String address, String phone, String email, float weightInTons, float cost, String datePurchased) {
        super(name, address, phone, email);
        this.weightInTons = weightInTons;
        this.cost = cost;
        this.datePurchased = datePurchased;
        this.vehicleType = "Truck";
    }

    public void setWeightInTons(float weightInTons) {
        this.weightInTons = weightInTons;
    }

    public void setCost(float cost) {
        this.cost = cost;
    }

    public String toString() {
        return (super.toString() +
                "Weight (In Tons): \t" + weightInTons + "\n" +
                "Cost: \t\t\t$" + cost + "\n" +
                "Date Purchased: \t" + datePurchased + "\n");
    }

}
