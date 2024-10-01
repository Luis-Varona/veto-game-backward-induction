import java.util.LinkedList;
import java.util.Queue;

public class VetoGame {
    //
    private final String[] preferences;
    
    public VetoGame(String[] preferences) {
        this.preferences = preferences;
    }
    
    public String[] getPreferences() {
        return preferences;
    }
    
    //
    private VetoGameState searchFromRoot() {
        int n = preferences.length;
        
        if (preferences[0].length() != n + 1) {
            throw new IllegalArgumentException(
                "`preferences` must have `n` columns (players) and `n + 1` rows (options)."
            );
        }
        
        VetoGameState root = new VetoGameState(preferences[0], '\0', 0, null);
        Queue<VetoGameState> nodeQueue = new LinkedList<>();
        nodeQueue.add(root);
        
        while (nodeQueue.peek().getDepth() < n) {
            VetoGameState node = nodeQueue.remove();
            
            for (int i = 0; i < node.getState().length() - 1; i++) {
                String stateChild = node.getState().substring(0, i);
                stateChild += node.getState().substring(i + 1);
                
                VetoGameState child = new VetoGameState(
                    stateChild,
                    node.getState().charAt(i),
                    node.getDepth() + 1,
                    node
                );
                
                node.addChild(child);
                nodeQueue.add(child);
            }
            
            VetoGameState child = new VetoGameState(
                node.getState().substring(0, node.getState().length() - 1),
                node.getState().charAt(node.getState().length() - 1),
                node.getDepth() + 1,
                node
            );
            
            node.addChild(child);
            nodeQueue.add(child);
        }
        
        while (nodeQueue.peek().getDepth() == n) {
            VetoGameState node = nodeQueue.remove();
            node.setOutcome(node.getState().charAt(0));
            nodeQueue.add(node.getParent());
        }
        
        while (nodeQueue.peek().getDepth() > 0) {
            VetoGameState parent = nodeQueue.peek().getParent();
            VetoGameState node = nodeQueue.peek();
            
            while (!nodeQueue.isEmpty() && nodeQueue.peek().getParent() == parent) {
                node = nodeQueue.remove();
                node.findOutcome(preferences);
            }
            
            nodeQueue.add(node.getParent());
        }
        
        root.findOutcome(preferences);
        return root;
    }
    
    public VetoGameResult findSolution() {
        VetoGameState node = searchFromRoot();
        String solution = "";
        
        while (node.getDepth() < preferences.length) {
            VetoGameState child = node.getChildren().get(0);
            solution += child.getDeletion();
            node = child;
        }
        
        return new VetoGameResult(solution, node.getOutcome());
    }
}
