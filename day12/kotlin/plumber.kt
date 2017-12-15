typealias AdjacencyList = ArrayList<Pair<List<Int>, Int?>>

fun emptyAdjacencyList(): AdjacencyList { return arrayListOf() }

// mark all nodes reachable from node with value mark
fun markReachable(adj: AdjacencyList, node: Int, mark: Int) {
    assert(adj[node].second == mark || adj[node].second == null)
    if (adj[node].second == mark) return
    adj[node] = Pair(adj[node].first, mark)
    for (neighbour in adj[node].first) markReachable(adj, neighbour, mark)
}

fun main(args: Array<String>) {
    // adjacency list, with int for each node to mark as visited
    val adj: AdjacencyList = emptyAdjacencyList()
    while (true) {
        val line = readLine() ?: break
        val s = line.replace(',', ' ').split("<->")
        val destinations = s[1].split("  ").map{x -> x.trim().toInt()}

        // input is guaranteed to have all necessary bi-directional links
        // eg. if 0 -> 2, then 2 -> 0 later on in the input
        // then we don't need to do any special logic here to have undirected edges
        adj.add(Pair(destinations, null))
    }
    markReachable(adj, 0, 0)
    println(adj.fold(0, {acc, node -> if (node.second == 0) acc + 1 else acc}))
    var i = 1
    while (true) {
        // find an unmarked node and start searching from it
        // repeat until no unmarked node
        val next = adj.indexOfFirst{node -> node.second == null}
        if (next == -1) break;
        markReachable(adj, next, i++)
    }
    println(i)
}