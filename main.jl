include("VetoGame.jl")
using .VetoGame: solve_veto_game

function main()
    # Each column represents the preferences of a player in descending order
    preferences = ["A"  "B"  "C";
                   "B"  "A"  "B";
                   "C"  "D"  "A";
                   "D"  "C"  "D"]
    
    hash = Dict("A" => 1, "B" => 2, "C" => 3, "D" => 4)
    preferences = [hash[k] for k in preferences]
    solution = solve_veto_game(preferences)
    
    hash = Dict(v => k for (k, v) in hash)
    solution = ["Player $i" => hash[k] for (i, k) in enumerate(solution)]
    println(solution)
end

main()