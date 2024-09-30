#include <cstdio> ///
#include <iostream> ///
#include <cstdlib>
#include <algorithm>
#include <queue>
#include "veto_game.hpp"

VetoGameResult solve_veto_game(char **preferences, int n) {
    // char *options = preferences[0];
    std::vector<char> options;
    options.assign(preferences[0], preferences[0] + n + 1);
    for (char c : options) { ///
        std::cout << c << ','; ///
    } ///
    std::cout << std::endl; ///
    
    VetoGameState root = VetoGameState(
        options,
        nullptr,
        std::vector<VetoGameState>(),
        nullptr,
        0,
        0,
        n
    );
    
    std::queue<VetoGameState*> Q;
    Q.push(&root);
    VetoGameState *node = Q.front();
    int depth = 0;
    
    while (depth < n) {
        Q.pop();
        // if (node.depth == 1) { ///
        //     printf("%d | ", node.depth); ///
        //     printf("%d\n", node.parent->depth); ///
        // } ///
        
        for (int i = 0; i < n - depth + 1; i++) {
            // std::vector<char> state_child;
            
            // for (int j = 0; j < i; j++) {
            //     state_child.push_back(node->state[j]);
            // }
            
            // for (int j = i + 1; j < n - depth + 1; j++) {
            //     state_child.push_back(node->state[j]);
            // }
            
            VetoGameState child = VetoGameState(
                std::vector<char>(),
                // state_child,
                node,
                std::vector<VetoGameState>(),
                nullptr,
                depth + 1,
                0,
                n
            );
            
            for (int j = 0; j < i; j++) {
                child.state.push_back(node->state[j]);
            }
            
            for (int j = i + 1; j < n - depth + 1; j++) {
                child.state.push_back(node->state[j]);
            }
            
            node->children.push_back(child);
            Q.push(&child);
            // if (child.depth < 4) { ///
            //     printf("%d | ", child.depth); ///
            //     printf("%d | ", child.parent->depth); ///
            //     printf("%d\n", node->depth); ///
            // } ///
            if (child.depth < 4) { ///
                for (char c : child.state) { ///
                    std::cout << c << ','; ///
                }
                std::cout << '|'; ///
                for (char c : child.parent->state) { ///
                    std::cout << c << ','; ///
                }
                std::cout << '|'; ///
                for (char c : Q.back()->state) { ///
                    std::cout << c << ','; ///
                }
                std::cout << std::endl; ///
            } ///
        }
        
        for (char c : node->children[8].state) { ///
            std::cout << c << ','; ///
        }
        std::cout << '|'; ///
        for (char c : Q.front()->state) { ///
            std::cout << c << ','; ///
        }
        std::cout << std::endl; ///
        printf("%d,|", &Q.front()); ///
        printf("%d\n", &node->children[8]); ///
        
        std::cout << std::endl; ///
        node = Q.front();
        depth = node->depth;
        printf("%d | ", depth); ///
        for (char c : node->state) { ///
            std::cout << c << ','; ///
        }
        std::cout << std::endl; ///
    }
    
    // for (char c : node.state) { ///
    //     std::cout << c << ','; ///
    // }
    // std::cout << std::endl; ///
    // for (char c : node.parent->state) { ///
    //     std::cout << c << ','; ///
    // }
    printf("Meow\n"); ///
    while (depth == n) {
        Q.pop();
        // node.outcome = node.state;
        node->outcome = node->state.data();
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
            node->state.begin(),
            node->state.end(),
            child->state.begin(),
            child->state.end(),
            new char[1]
        );
        
        node = child;
        depth = node->depth;
    }
    
    return VetoGameResult(solution, node->outcome[0], n);
}