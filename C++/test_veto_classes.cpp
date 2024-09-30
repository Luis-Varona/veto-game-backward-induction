#include <cstdio>
#include <string>
#include "veto_game.hpp"

int main() {
    char *outcomes = new char[3];
    outcomes[0] = 'A';
    outcomes[1] = 'B';
    outcomes[2] = 'C';
    
    char *preferences[3] = {outcomes, outcomes + 1, outcomes + 2};
    
    std::vector<char> state_root;
    state_root.push_back('A');
    state_root.push_back('B');
    state_root.push_back('C');
    // char *state_root = new char[3];
    // state_root[0] = 'A';
    // state_root[1] = 'B';
    // state_root[2] = 'C';
    
    std::vector<char> state_child_1;
    state_child_1.push_back('A');
    state_child_1.push_back('B');
    // char *state_child_1 = new char[2];
    // state_child_1[0] = 'A';
    // state_child_1[1] = 'B';
    
    std::vector<char> state_child_2;
    state_child_2.push_back('A');
    state_child_2.push_back('C');
    // char *state_child_2 = new char[2];
    // state_child_2[0] = 'A';
    // state_child_2[1] = 'C';
    
    std::vector<char> state_child_3;
    state_child_3.push_back('B');
    state_child_3.push_back('C');
    // char *state_child_3 = new char[2];
    // state_child_3[0] = 'B';
    // state_child_3[1] = 'C';
    
    VetoGameState root(
        state_root,
        nullptr,
        std::vector<VetoGameState>(),
        nullptr,
        0,
        3,
        2
    );
    
    VetoGameState child_1(
        state_child_1,
        &root,
        std::vector<VetoGameState>(),
        outcomes + 1,
        1,
        0,
        2
    );
    
    VetoGameState child_2(
        state_child_2,
        &root,
        std::vector<VetoGameState>(),
        outcomes,
        1,
        0,
        2
    );
    
    VetoGameState child_3(
        state_child_3,
        &root,
        std::vector<VetoGameState>(),
        outcomes + 1,
        1,
        0,
        2
    );
    
    root.children.push_back(child_1);
    root.children.push_back(child_2);
    root.children.push_back(child_3);
    root.set_outcome(preferences);
    
    char *solution = new char[2];
    solution[0] = 'B';
    solution[1] = 'C';
    
    VetoGameResult result(solution, *root.outcome, 2);
    printf("%s", result.to_string());
};