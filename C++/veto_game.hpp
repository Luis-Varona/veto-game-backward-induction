//
#ifndef VETOGAME
#define VETOGAME

#include <algorithm>
#include <string>
#include <sstream>

//
class VetoGameResult {
    public:
        char *solution;
        char outcome;
        int n;
        
        VetoGameResult(char *solution, char outcome, int n) {
            this->solution = solution;
            this->outcome = outcome;
            this->n = n;
        }
        
        char *to_string() {
            std::stringstream rounds_stream;
            
            for (int i = 0; i < n; i++) {
                rounds_stream << "Player " << i + 1 << " vetoes " << solution[i] << '\n';
            }
            
            rounds_stream << "Outcome: " << outcome << '\n';
            std::string rounds = rounds_stream.str();
            char *out = new char[rounds.size()];
            std::copy(rounds.begin(), rounds.end(), out);
            
            return out;
        }
};

//
class VetoGameState {
    public:
        char *state;
        VetoGameState *parent;
        std::vector<VetoGameState> children;
        char *outcome;
        int depth;
        int num_children;
        int n;
        
        VetoGameState(
            char *state,
            VetoGameState *parent,
            std::vector<VetoGameState> children,
            char *outcome,
            int depth,
            int num_children,
            int n
        ) {
            this->state = state;
            this->parent = parent;
            this->children = children;
            this->outcome = outcome;
            this->depth = depth;
            this->num_children = num_children;
            this->n = n;
        }
        
        void set_outcome(char **preferences) {
            char *player_prefs = preferences[depth];
            int rank_min = n;
            int idx_child = 0;
            
            for (int i = 0; i < num_children; i++) {
                int rank = std::find(
                    player_prefs,
                    player_prefs + n + 1,
                    *children[i].outcome
                ) - player_prefs;
                
                if (rank < rank_min) {
                    rank_min = rank;
                    idx_child = i;
                }
                
                if (rank == 0) {
                    break;
                }
            }
            
            VetoGameState child = children[idx_child];
            children.clear();
            children.push_back(child);
            outcome = child.outcome;
        }
};

//
VetoGameResult solve_veto_game(char **preferences, int n);

//
#endif