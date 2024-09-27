include("VetoGame.jl")
using .VetoGame: solve_veto_game

function main()
    # Each column represents the preferences of a player in descending order
    preferences = ['A'  'B'  'C';
                   'B'  'A'  'B';
                   'C'  'D'  'A';
                   'D'  'C'  'D']
    
    result = solve_veto_game(preferences)
    println(result.to_string)
end

main()