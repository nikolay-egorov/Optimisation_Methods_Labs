public class Shipment {

    final double costPerUnit;
    final int r, c;
    double quantity;

    public Shipment(double quantity, double cpu, int r, int c) {
        this.quantity = quantity;
        costPerUnit = cpu;
        this.r = r;
        this.c = c;
    }
}
