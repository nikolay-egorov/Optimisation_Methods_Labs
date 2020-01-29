import java.util.ArrayList;

public class Vehicle {

    public int VehId;
    public int capacity;
    public int load;
    public int curLocation;
    public boolean close;
    public ArrayList<Node> Route = new ArrayList<Node>();

    public Vehicle(int vehId, int capacity) {
        VehId = vehId;
        this.capacity = capacity;
    }

    public void AddNode(Node Client){
        Route.add(Client);
        this.load +=  Client.demand;
        this.curLocation = Client.NodeId;
    }

    public boolean CheckIfFits(int demand){
        return (load + demand <= capacity);
    }
}
