public class VetoGameTester {
    public static void main(String[] args) {
        String[] preferences = {
            "ABCDEFGHI",
            "BADHGIFCE",
            "FBGICEHAD",
            "HDEAGCFIB",
            "CHIADBGEF",
            "IFBECDAHG",
            "DGCAFHBEI",
            "EIADGFHBC"
        };
        
        VetoGame game = new VetoGame(preferences);
        VetoGameResult result = game.findSolution();
        System.out.println(result.toString());
    }
}
