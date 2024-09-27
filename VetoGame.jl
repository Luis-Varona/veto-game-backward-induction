module VetoGame
    # EXPORTS AND IMPORTS
    export solve_veto_game, solve_veto_game_letters
    using Combinatorics: combinations
    using DataStructures: Queue, dequeue!, enqueue!
    
    # MUTABLE STRUCT: `StateNode`
    mutable struct StateNode
        state::Vector{Int64}
        parent::Union{Nothing, StateNode}
        children::Vector{StateNode}
        outcome::Int64
        depth::Int64
    end
    
    # FUNCTION: `solve_veto_game`
    function solve_veto_game(preferences::Matrix{Int64})
        (m, n) = size(preferences)
        
        if m != n + 1
            throw(ArgumentError(
                "`preferences` must have `n` columns (players) and `n + 1` rows (options)."
            ))
        end
        
        root = StateNode(1:m, nothing, StateNode[], 0, 0)
        Q = Queue{StateNode}()
        enqueue!(Q, root)
        
        while first(Q).depth < n
            node = dequeue!(Q)
            depth = node.depth
            
            for comb in combinations(node.state, m - depth - 1)
                child = StateNode(comb, node, StateNode[], 0, depth + 1)
                push!(node.children, child)
                enqueue!(Q, child)
            end
        end
        
        while first(Q).depth == n
            node = dequeue!(Q)
            node.outcome = node.state[1]
            enqueue!(Q, node.parent)
        end
        
        while first(Q).depth > 0
            parent = first(Q).parent
            
            while !isempty(Q) && first(Q).parent == parent
                node = dequeue!(Q)
                set_outcome!(node, preferences)
            end
            
            enqueue!(Q, node.parent)
        end
        
        set_outcome!(root, preferences)
        solution = Vector{Int64}(undef, n)
        node = root
        
        while node.depth < n
            child = node.children[1]
            solution[node.depth + 1] = setdiff(node.state, child.state)[1]
            node = child
        end
        
        return solution
    end
    
    # FUNCTION: `solve_veto_game_letters`
    # function solve_veto_game_letters(preferences::Matrix{Char}, hash::Dict{Char, Int64})
    #     hash_rev = Dict(values(hash) .=> keys(hash))
        
    #     for (i, k) in enumerate(solve_veto_game([hash[k] for k in preferences]))
    #         println("Player $i vetoes $(hash_rev[k])")
    #     end
    # end
    function solve_veto_game_letters(preferences::Matrix)
        options = unique(preferences)
        hash = Dict(option => i for (i, option) in enumerate(options))
        hash_rev = Dict(values(hash) .=> keys(hash))
        solution = solve_veto_game([hash[k] for k in preferences])
        
        for (i, k) in enumerate(solution)
            println("Player $i vetoes $(hash_rev[k])")
        end
        
        println("\nEnd result: $(setdiff(options, solution)[1])")
    end
    
    # FUNCTION: `set_outcome!`
    function set_outcome!(node::StateNode, preferences::Matrix{Int64})
        player_prefs = @view preferences[:, node.depth + 1]
        sort!(node.children, by = x -> findfirst(player_prefs .== x.outcome))
        
        child = node.children[1]
        node.children = [child]
        node.outcome = child.outcome
        return node
    end
end