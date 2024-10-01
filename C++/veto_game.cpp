#include <cstdio> ///
#include <iostream> ///
#include <cstdlib>
#include <algorithm>
#include <queue>
#include "veto_game.hpp"

VetoGameResult solve_veto_game(char **preferences, int n) {
    char *options = preferences[0];
    // std::vector<char> options;
    // options.assign(preferences[0], preferences[0] + n + 1);
    // for (char c : options) { ///
    //     std::cout << c << ','; ///
    // } ///
    // std::cout << std::endl; ///
    
    VetoGameState root = VetoGameState(
        options,
        nullptr,
        std::vector<VetoGameState>(),
        nullptr,
        0,
        0,
        n
    );
    for (int i = 0; i < n + 1; i ++) {
        std::cout << root.state[i] << ','; ///
    }
    printf("Meow\n"); ///
    
    std::queue<VetoGameState*> Q;
    Q.push(&root);
    VetoGameState *node = &root;
    int depth = 0;
    
    while (depth < n) {
        Q.pop();
        // if (node.depth == 1) { ///
        //     printf("%d | ", node.depth); ///
        //     printf("%d\n", node.parent->depth); ///
        // } ///
        
        for (int i = 0; i < n - depth + 1; i++) {
            // char state_child[n - depth];
            char *state_child = new char[n - depth];
            
            for (int j = 0; j < i; j++) {
                state_child[j] = node->state[j];
            }
            
            for (int j = i; j < n - depth; j++) {
                state_child[j] = node->state[j + 1];
            }
            
            // std::vector<char> state_child;
            
            // for (int j = 0; j < i; j++) {
            //     state_child.push_back(node->state[j]);
            // }
            
            // for (int j = i + 1; j < n - depth + 1; j++) {
            //     state_child.push_back(node->state[j]);
            // }
            
            VetoGameState child = VetoGameState(
                // std::vector<char>(),
                // &state_child[0],
                state_child,
                node,
                std::vector<VetoGameState>(),
                nullptr,
                depth + 1,
                0,
                n
            );
            
            // for (int j = 0; j < i; j++) {
            //     child.state.push_back(node->state[j]);
            // }
            
            // for (int j = i + 1; j < n - depth + 1; j++) {
            //     child.state.push_back(node->state[j]);
            // }
            
            node->children.push_back(child); /// Not working here?
            node->num_children++;
            printf("%ul\n", node->children.size()); /// Error here...
            printf("%d\n", node->num_children); /// Error here...
            Q.push(&child);
            // Q.push(&node->children.back());
            if (child.depth < 4) {
                for (int i = 0; i < n - depth; i++) {
                    std::cout << child.state[i] << ','; ///
                }
                printf("\n"); ///
                printf("%d\n", &state_child); ///
                printf("%d\n", &child); ///
            }
            // if (child.depth < 4) { ///
            //     for (char c : child.state) { ///
            //         std::cout << c << ','; ///
            //     }
            //     std::cout << '|'; ///
            //     for (char c : child.parent->state) { ///
            //         std::cout << c << ','; ///
            //     }
            //     std::cout << '|'; ///
            //     for (char c : Q.back()->state) { ///
            //         std::cout << c << ','; ///
            //     }
            //     std::cout << std::endl; ///
            // } ///
        }
        
        // for (char c : node->children[8].state) { ///
        //     std::cout << c << ','; ///
        // }
        // std::cout << '|'; ///
        // for (char c : Q.front()->state) { ///
        //     std::cout << c << ','; ///
        // }
        // std::cout << std::endl; ///
        // printf("%d,|", &Q.front()); ///
        // printf("%d\n", &node->children[8]); ///
        
        // std::cout << std::endl; ///
        printf("%d\n", node->num_children); ///
        node = Q.front();
        depth = node->depth;
        printf("%d\n", &node); ///
        printf("%d | ", depth); ///
        for (int i = 0; i < n - depth; i++) {
            std::cout << node->state[i] << ','; ///
        }
        printf("\n"); ///
        // for (char c : node->state) { ///
        //     std::cout << c << ','; ///
        // }
        // std::cout << std::endl; ///
    }
    
    // for (char c : node.state) { ///
    //     std::cout << c << ','; ///
    // }
    // std::cout << std::endl; ///
    // for (char c : node.parent->state) { ///
    //     std::cout << c << ','; ///
    // }
    // VetoGameState m = root.children[0];
    printf("%d\n", root.children.size()); ///
    for (int i = 0; i < n; i ++) {
        std::cout << root.children[0].state[i] << ','; ///
    }
    printf("\n"); ///
    for (int i = 0; i < n; i ++) {
        std::cout << root.children[1].state[i] << ','; ///
    }
    printf("\n"); ///
    for (int i = 0; i < n; i ++) {
        std::cout << root.children[8].state[i] << ','; ///
    }
    printf("\n"); ///
    
    for (int i = 0; i < n; i ++) {
        std::cout << node->state[i] << ','; ///
    }
    printf("Meow\n"); ///
    while (depth == n) {
        Q.pop();
        node->outcome = node->state;
        // node->outcome = node->state.data();
        node->num_children = 1;
        Q.push(node->parent);
        
        node = Q.front();
        depth = node->depth;
        // for (char c : node.state) { ///
        //     std::cout << c << ','; ///
        // }
        // std::cout << std::endl; ///
        // for (char c : node.parent->state) { ///
        //     std::cout << c << ','; ///
        // }
        // std::cout << std::endl; ///
    }
    
    printf("C\n"); ///
    while (depth > 0) {
        Q.pop();
        VetoGameState *parent = node->parent;
        
        while (!Q.empty() && node->parent == parent) {
            Q.pop();
            node->set_outcome(preferences);
            node = Q.front();
        }
        
        depth = node->depth;
        Q.push(node->parent);
    }
    
    root.set_outcome(preferences);
    char *solution = new char[n];
    node = &root;
    depth = 0;
    
    printf("D\n"); ///
    while (depth < n) {
        VetoGameState *child = &node->children[0];
        
        solution[node->depth] = *std::set_difference(
            node->state,
            node->state + n + 1,
            child->state,
            child->state + n + 1,
            new char[1]
        );
        // solution[node->depth] = *std::set_difference(
        //     node->state.begin(),
        //     node->state.end(),
        //     child->state.begin(),
        //     child->state.end(),
        //     new char[1]
        // );
        
        node = child;
        depth = node->depth;
    }
    
    return VetoGameResult(solution, node->outcome[0], n);
}