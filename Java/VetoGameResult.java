public class VetoGameResult {
    //
    private final String solution;
    private final char outcome;
    
    public VetoGameResult(String solution, char outcome) {
        this.solution = solution;
        this.outcome = outcome;
    }
    
    //
    public String getSolution() {
        return solution;
    }
    
    public char getOutcome() {
        return outcome;
    }
    
    //
    @Override
    public String toString() {
        String out = "";
        
        for (int i = 0; i < solution.length(); i++) {
            out += String.format("Player %d vetoes %c\n", i + 1, solution.charAt(i));
        }
        
        out += String.format("Outcome: %c\n", outcome);
        return out;
    }
}