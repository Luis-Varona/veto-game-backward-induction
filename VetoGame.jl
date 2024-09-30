module VetoGame
    # EXPORTS AND IMPORTS
    export VetoGameResult, solve_veto_game
    using Combinatorics: combinations
    using DataStructures: Queue, dequeue!, enqueue!
    
    # STRUCT: `VetoGameResult`
    struct VetoGameResult{T}
        solution::Vector{T}
        outcome::T
    end
    
    function Base.getproperty(result::VetoGameResult, prop::Symbol)
        if prop in fieldnames(VetoGameResult)
            out = getfield(result, prop)
        elseif prop == :to_string
            rounds = Vector{String}(undef, length(result.solution) + 1)
            rounds[1:(end - 1)] .= [
                "Player $i vetoes $option\n" for (i, option) in enumerate(result.solution)
            ]
            rounds[end] = "\nOutcome: $(result.outcome)"
            out = join(rounds)
        else
            throw(ArgumentError("type VetoGameResult has no field $prop"))
        end
        
        return out
    end
    
    function Base.propertynames(::VetoGameResult)
        return (:solution, :outcome, :to_string)
    end
    
    # MUTABLE STRUCT: `VetoGameState`
    mutable struct VetoGameState{T}
        state::Vector{T}
        parent::Union{Nothing, VetoGameState{T}}
        children::Vector{VetoGameState{T}}
        outcome::Union{Missing, T}
        depth::Int64
    end
    
    # FUNCTION: `solve_veto_game`
    function solve_veto_game(preferences::Matrix{T}) where T
        (m, n) = size(preferences)
        
        if m != n + 1
            throw(ArgumentError(
                "`preferences` must have `n` columns (players) and `n + 1` rows (options)."
            ))
        end
        
        root = VetoGameState{T}(unique(preferences), nothing, VetoGameState{T}[], missing, 0)
        Q = Queue{VetoGameState{T}}()
        enqueue!(Q, root)
        
        while first(Q).depth < n
            node = dequeue!(Q)
            depth = node.depth
            
            for comb in combinations(node.state, n - depth)
                child = VetoGameState{T}(comb, node, VetoGameState{T}[], missing, depth + 1)
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
        solution = Vector{T}(undef, n)
        node = root
        
        while node.depth < n
            child = node.children[1]
            solution[node.depth + 1] = setdiff(node.state, child.state)[1]
            node = child
        end
        
        return VetoGameResult{T}(solution, node.outcome)
    end
    
    # FUNCTION: `set_outcome!`
    function set_outcome!(node::VetoGameState{T}, preferences::Matrix{T}) where T
        player_prefs = @view preferences[:, node.depth + 1]
        sort!(node.children, by = x -> findfirst(player_prefs .== x.outcome))
        
        child = node.children[1]
        node.children = [child]
        node.outcome = child.outcome
        return node
    end
end