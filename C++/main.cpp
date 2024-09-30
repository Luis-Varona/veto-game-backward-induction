#include <cstdio>
#include "veto_game.hpp"

int main() {
    char **preferences = new char*[8];
    
    for (int i = 0; i < 8; i++) {
        preferences[i] = new char[9];
    }
    
    preferences[0][0] = 'A';
    preferences[0][1] = 'B';
    preferences[0][2] = 'C';
    preferences[0][3] = 'D';
    preferences[0][4] = 'E';
    preferences[0][5] = 'F';
    preferences[0][6] = 'G';
    preferences[0][7] = 'H';
    preferences[0][8] = 'I';
    
    preferences[1][0] = 'B';
    preferences[1][1] = 'A';
    preferences[1][2] = 'D';
    preferences[1][3] = 'H';
    preferences[1][4] = 'G';
    preferences[1][5] = 'I';
    preferences[1][6] = 'F';
    preferences[1][7] = 'C';
    preferences[1][8] = 'E';
    
    preferences[2][0] = 'F';
    preferences[2][1] = 'B';
    preferences[2][2] = 'G';
    preferences[2][3] = 'I';
    preferences[2][4] = 'C';
    preferences[2][5] = 'E';
    preferences[2][6] = 'H';
    preferences[2][7] = 'A';
    preferences[2][8] = 'D';
    
    preferences[3][0] = 'H';
    preferences[3][1] = 'D';
    preferences[3][2] = 'E';
    preferences[3][3] = 'A';
    preferences[3][4] = 'G';
    preferences[3][5] = 'C';
    preferences[3][6] = 'F';
    preferences[3][7] = 'I';
    preferences[3][8] = 'B';
    
    preferences[4][0] = 'C';
    preferences[4][1] = 'H';
    preferences[4][2] = 'I';
    preferences[4][3] = 'A';
    preferences[4][4] = 'D';
    preferences[4][5] = 'B';
    preferences[4][6] = 'G';
    preferences[4][7] = 'E';
    preferences[4][8] = 'F';
    
    preferences[5][0] = 'I';
    preferences[5][1] = 'F';
    preferences[5][2] = 'B';
    preferences[5][3] = 'E';
    preferences[5][4] = 'C';
    preferences[5][5] = 'D';
    preferences[5][6] = 'A';
    preferences[5][7] = 'H';
    preferences[5][8] = 'G';
    
    preferences[6][0] = 'D';
    preferences[6][1] = 'G';
    preferences[6][2] = 'C';
    preferences[6][3] = 'A';
    preferences[6][4] = 'F';
    preferences[6][5] = 'H';
    preferences[6][6] = 'B';
    preferences[6][7] = 'E';
    preferences[6][8] = 'I';
    
    preferences[7][0] = 'E';
    preferences[7][1] = 'I';
    preferences[7][2] = 'A';
    preferences[7][3] = 'D';
    preferences[7][4] = 'G';
    preferences[7][5] = 'F';
    preferences[7][6] = 'H';
    preferences[7][7] = 'B';
    preferences[7][8] = 'C';
    
    VetoGameResult result = solve_veto_game(preferences, 8);
    printf("%s", result.to_string());
};