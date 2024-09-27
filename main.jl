include("VetoGame.jl")
using .VetoGame: solve_veto_game

function main()
    # Each column represents the preferences of a player in descending order
    preferences = ['A'  'B'  'F'  'H'  'C'  'I'  'D'  'E';
                   'B'  'A'  'B'  'D'  'H'  'F'  'G'  'I';
                   'C'  'D'  'G'  'E'  'I'  'B'  'C'  'A';
                   'D'  'H'  'I'  'A'  'A'  'E'  'A'  'D';
                   'E'  'G'  'C'  'G'  'D'  'C'  'F'  'G';
                   'F'  'I'  'E'  'C'  'B'  'D'  'H'  'F';
                   'G'  'F'  'H'  'F'  'G'  'A'  'B'  'H';
                   'H'  'C'  'A'  'I'  'E'  'H'  'E'  'B';
                   'I'  'E'  'D'  'B'  'F'  'G'  'I'  'C']
    
    result = solve_veto_game(preferences)
    println(result.to_string)
end

main()