public class Main {

    public static void main(String[] args) throws Exception {
        Transpartation_problem TP=new Transpartation_problem();
        String in="in1.txt";
        TP.init(in);
        TP.northWestCornerRule();
        TP.steppingStone();
        TP.printPath("out.txt");

    }
}
