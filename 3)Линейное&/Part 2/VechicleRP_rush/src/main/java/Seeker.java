import java.util.ArrayList;

public class Seeker {

    int NumOfVehicles;
    int NumOfCustomers;
    Vehicle[] Vehicles;
    double Cost;

    //Tabu Variables
    public Vehicle[] VehiclesForBestSolution;
    double BestSolutionCost;

    public ArrayList<Double> PastSolutions;


    public Seeker(int numOfVehicles, int numOfCustomers,int VehCapacity) {
        NumOfVehicles = numOfVehicles;
        NumOfCustomers = numOfCustomers;
        this.Cost=0;

        Vehicles = new Vehicle[NumOfVehicles];
        VehiclesForBestSolution = new Vehicle[numOfVehicles];
        PastSolutions = new ArrayList<Double>();


        for (int i = 0; i < numOfVehicles; i++) {
            Vehicles[i] = new Vehicle(i+1,VehCapacity);
            VehiclesForBestSolution[i] = new Vehicle(i+1,VehCapacity);
        }

    }


    public boolean leftCustomerExists(Node[] Nodes)
    {
        for (int i = 1; i < Nodes.length; i++)
        {
            if (!Nodes[i].IsRouted)
                return true;
        }
        return false;
    }


    public void GreedyWay(Node[] Nodes , double[][] CostMatrix){
        double CandCost,EndCost;
        int VehIndex = 0;

        while (leftCustomerExists(Nodes)) {
            int CustIndex = 0;
            Node Candidate = null;
            double minCost = (float) Double.MAX_VALUE;

            if (Vehicles[VehIndex].Route.isEmpty())
            {
                Vehicles[VehIndex].AddNode(Nodes[0]);
            }


            for (int i = 1; i < NumOfCustomers; i++) {
                if(Nodes[i].IsRouted == false){
                    if(Vehicles[VehIndex].CheckIfFits(Nodes[i].demand)){
                        CandCost = CostMatrix[Vehicles[VehIndex].curLocation][i];
                        if(minCost > CandCost){
                            minCost = CandCost;
                            CustIndex = i;
                            Candidate = Nodes[i];

                        }
                    }
                }
            }

            if (Candidate==null){
                //Not a single Customer Fits
                if ( VehIndex+1 < Vehicles.length ) //We have more vehicles to assign
                {
                    if (Vehicles[VehIndex].curLocation != 0) {//End this route
                        EndCost = CostMatrix[Vehicles[VehIndex].curLocation][0];
                        Vehicles[VehIndex].AddNode(Nodes[0]);
                        this.Cost +=  EndCost;
                    }
                    VehIndex = VehIndex+1; //Go to next Vehicle
                }
                else //We DO NOT have any more vehicle to assign. The problem is unsolved under these parameters
                {
                    System.out.println("\nThe rest customers do not fit in any Vehicle\n" +
                            "The problem cannot be resolved under these constrains");
                    System.exit(0);
                }
            }
            else
            {
                Vehicles[VehIndex].AddNode(Candidate);//If a fitting Customer is Found
                Nodes[CustIndex].IsRouted = true;
                this.Cost += minCost;
            }
        }


        EndCost = CostMatrix[Vehicles[VehIndex].curLocation][0];
        Vehicles[VehIndex].AddNode(Nodes[0]);
        this.Cost +=  EndCost;


    }



    public void PathPrint(String Sol_Label)//Print Solution In console
    {
        System.out.println("=========================================================");
        System.out.println(Sol_Label+"\n");

        for (int j=0 ; j < NumOfVehicles ; j++)
        {
            if (! Vehicles[j].Route.isEmpty())
            {   System.out.print("Vehicle " + j + ":");
                int RoutSize = Vehicles[j].Route.size();
                for (int k = 0; k < RoutSize ; k++) {
                    if (k == RoutSize-1)
                    { System.out.print(Vehicles[j].Route.get(k).NodeId );  }
                    else
                    { System.out.print(Vehicles[j].Route.get(k).NodeId+ "->"); }
                }
                System.out.println();
            }
        }
        System.out.println("\nSolution Costs "+this.Cost+"\n");
    }



 }




