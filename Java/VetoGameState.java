import java.util.ArrayList;

public class VetoGameState {
    //
    private final String state;
    private final char deletion;
    private final int depth;
    private final VetoGameState parent;
    private final ArrayList<VetoGameState> children;
    private char outcome;
    
    public VetoGameState(String state, char deletion, int depth, VetoGameState parent) {
        this.state = state;
        this.deletion = deletion;
        this.depth = depth;
        this.parent = parent;
        this.children = new ArrayList<>();
        this.outcome = '\0';
    }
    
    //
    public String getState() {
        return state;
    }
    
    public char getDeletion() {
        return deletion;
    }
    
    public int getDepth() {
        return depth;
    }
    
    public VetoGameState getParent() {
        return parent;
    }
    
    public ArrayList<VetoGameState> getChildren() {
        return children;
    }
    
    public char getOutcome() {
        return outcome;
    }
    
    //
    public void addChild(VetoGameState child) {
        children.add(child);
    }
    
    public void setOutcome(char outcome) {
        this.outcome = outcome;
    }
    
    public void findOutcome(String[] preferences) {
        String playerPreferences = preferences[depth];
        int rankMin = playerPreferences.length() - 1;
        int idxChild = 0;
        
        for (int i = 0; i < children.size(); i++) {
            int rank = playerPreferences.indexOf(children.get(i).getOutcome());
            
            if (rank < rankMin) {
                rankMin = rank;
                idxChild = i;
            }
            
            if (rank == 0) break;
        }
        
        VetoGameState child = children.get(idxChild);
        setOutcome(child.getOutcome());
        children.clear();
        children.add(child);
    }
}