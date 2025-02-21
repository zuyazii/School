import java.util.ArrayList;
import java.util.List;

// Abstract base class for all products
abstract class Product {
    protected String name;
    protected double basePrice;
    protected boolean refundable;

    public Product(String name, double basePrice, boolean refundable) {
        this.name = name;
        this.basePrice = basePrice;
        this.refundable = refundable;
    }

    // Polymorphic method to get the price (may be overridden)
    public abstract double getPrice();

    public boolean isRefundable() {
        return refundable;
    }
}

// Regular products with fixed pricing (e.g., books, packaged food)
class RegularProduct extends Product {
    public RegularProduct(String name, double basePrice, boolean refundable) {
        super(name, basePrice, refundable);
    }

    @Override
    public double getPrice() {
        return basePrice;
    }
}

// Perishable products whose price may vary with freshness (e.g., fresh milk)
class PerishableProduct extends Product {
    // freshnessFactor: 1.0 means full price, 0.5 means half price, etc.
    private double freshnessFactor;

    public PerishableProduct(String name, double basePrice, boolean refundable, double freshnessFactor) {
        super(name, basePrice, refundable);
        this.freshnessFactor = freshnessFactor;
    }

    @Override
    public double getPrice() {
        return basePrice * freshnessFactor;
    }
}

// Order class that aggregates multiple products
class Order {
    private List<Product> products = new ArrayList<>();

    public void addProduct(Product p) {
        products.add(p);
    }

    // Calculates total order amount regardless of refund policies
    public double calculateTotal() {
        double total = 0;
        for (Product p : products) {
            total += p.getPrice();
        }
        return total;
    }

    // Calculates refund amount (only refundable items)
    public double calculateRefund() {
        double refundTotal = 0;
        for (Product p : products) {
            if (p.isRefundable()) {
                refundTotal += p.getPrice();
            } else {
                // Print rejection info for non-refundable items
                System.out.println("Sorry, this item is not refoundable");
            }
        }
        return refundTotal;
    }
}

public class SupermarketCashierSystem {
    public static void main(String[] args) {
        Order order = new Order();

        // Scenario: A customer makes a purchase that includes:
        // 1. 2 tins of cola (regular product, assume refundable)
        Product cola = new RegularProduct("Cola", 8, true);
        // Add two tins of cola
        order.addProduct(cola);
        order.addProduct(cola);

        // 2. A book titled "The Little Prince" (regular product, refundable)
        Product book = new RegularProduct("The Little Prince", 100, true);
        order.addProduct(book);

        // 3. A pair of socks (non-refundable)
        Product socks = new RegularProduct("Socks", 30, false);
        order.addProduct(socks);

        // 4. A bottle of fresh milk (perishable, non-refundable, half-price due to freshness)
        // Original price is 24, half-price means a freshness factor of 0.5.
        Product milk = new PerishableProduct("Fresh Milk", 24, false, 0.5);
        order.addProduct(milk);

        // Calculate and output total amount for the order.
        double totalAmount = order.calculateTotal();
        System.out.println("Total amount for the order: " + totalAmount + " HKD");

        // Simulate refund: only refundable items should be refunded.
        double refundAmount = order.calculateRefund();
        System.out.println("Total refund amount: " + refundAmount + " HKD");
    }
}