include("VetoGame.jl")
using .VetoGame: solve_veto_game_letters

function main()
    # Each column represents the preferences of a player in descending order
    preferences = ['A'  'B'  'C';
                   'B'  'A'  'B';
                   'C'  'D'  'A';
                   'D'  'C'  'D']
    
    solution = solve_veto_game_letters(preferences)
end

main()