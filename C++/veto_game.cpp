#include <cstdio> ///
#include <cstdlib>
#include <algorithm>
#include <queue>
#include "veto_game.hpp"

VetoGameResult solve_veto_game(char **preferences, int n) {
    char *options = preferences[0];
    // char *options = std::unique(preferences[0], preferences[0] + n);
    
    VetoGameState root = VetoGameState(
        options,
        nullptr,
        std::vector<VetoGameState>(),
        nullptr,
        0,
        0,
        n
    );
    
    std::queue<VetoGameState> Q;
    Q.push(root);
    VetoGameState node = Q.front();
    int depth = 0;
    
    while (depth < n) {
        Q.pop();
        
        for (int i = 0; i < n - depth + 1; i++) {
            char *state_child = new char[n - depth];
            
            for (int j = 0; j < i; j++) {
                state_child[j] = node.state[j];
            }
            
            for (int j = i; j < n - depth; j++) {
                state_child[j] = node.state[j + 1]; /// Error is here?
            }
            
            VetoGameState child = VetoGameState(
                state_child,
                &node,
                std::vector<VetoGameState>(),
                nullptr,
                depth + 1,
                0,
                n
            );
            
            node.children.push_back(child);
            Q.push(child);
        }
        
        node = Q.front();
        depth = node.depth;
    }
    
    printf("Meow\n"); ///
    for (int i = 0; i < n; i++) { ///
        printf("%c,", node.state[i]); ///
    } ///
    printf("\n"); ///
    for (int i = 0; i < n; i++) { ///
        printf("%c,", node.parent[0].state[i]); ///
    } ///
    printf("\n"); ///
    while (depth == n) {
        Q.pop();
        node.outcome = node.state;
        node.num_children = 1;
        Q.push(*node.parent);
        // printf("%s\n", node.parent->state); ///
        // printf("%d\n", node.depth); ///
        // printf("%d\n", node.parent->depth); ///
        
        node = Q.front();
        depth = node.depth;
        // printf("%s\n", node.state); ///
        // printf("%s\n", Q.back().state); ///
    }
    
    printf("C\n"); ///
    while (depth > 0) {
        Q.pop();
        VetoGameState *parent = node.parent;
        
        while (!Q.empty() && node.parent == parent) {
            Q.pop();
            node.set_outcome(preferences);
            node = Q.front();
        }
        
        depth = node.depth;
        Q.push(*node.parent);
    }
    
    root.set_outcome(preferences);
    char *solution = new char[n];
    node = root;
    depth = 0;
    
    printf("D\n"); ///
    while (depth < n) {
        VetoGameState *child = &node.children[0];
        solution[node.depth] = *std::set_difference(
            node.state,
            node.state + n - depth + 1,
            child->state,
            child->state + n - depth,
            new char[1]
        );
        node = *child;
        depth = node.depth;
    }
    
    return VetoGameResult(solution, *node.outcome, n);
}