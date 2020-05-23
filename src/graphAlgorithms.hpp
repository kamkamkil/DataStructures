template <typename V, typename E>
void DFS(const Graph<V, E> graph, size_t vertex, std::function<void(const V &)> fun)
{
    if (graph.neighbours(vertex).empty())
    {
        fun(graph.vertexData(vertex));
        return;
    }
    std::vector<bool> visited(graph.nrOfVertices());
    for (size_t i = 0; i < graph.nrOfVertices(); i++)
        visited[i] = false;
    visited[vertex] = true;
    std::stack<size_t> stack;
    stack.push(vertex);
    fun(graph.vertexData(vertex));
    size_t current = graph.neighbours(vertex).back();
    auto test = [&](size_t vertex_) -> bool {
        for (auto &&n : graph.neighbours(vertex_))
        {
            if (!visited[n])
                return true;
        }
        return false;
    };
    while (current != vertex || test(vertex)) //TODO ten kod bardzo mocno poczebuje refraktoringu
    {
        stack.push(current);
        if (!visited[current])
        {
            fun(graph.vertexData(current));
            visited[current] = true;
        }
        bool finish = true;
        for (auto &&value : visited)
        {
            if (!value)
            {
                finish = false;
                break;
            }
        }
        if (finish)
            return;
        if (test(current))
        {
            for (auto &&ver : graph.neighbours(current))
                if (!visited[ver])
                {
                    current = ver;
                    break;
                }
        }
        else
        {
            while (!stack.empty() && !test(current))
            {
                current = stack.top();
                stack.pop();
            }
        }
    };
}
template <typename V, typename E>
void BFS(const Graph<V, E> graph, size_t vertex, std::function<void(const V &)> fun) //const
{
    if (graph.neighbours(vertex).empty())
    {
        fun(graph.vertexData(vertex));
        return;
    }
    std::vector<bool> visited(graph.nrOfVertices());
    for (size_t i = 0; i < graph.nrOfVertices(); i++)
        visited[i] = false;
    visited[vertex] = true;
    std::queue<size_t> queue;
    size_t current;
    queue.push(vertex);
    while (!queue.empty())
    {
        current = queue.front();
        queue.pop();
        visited[current] = true;
        fun(graph.vertexData(current));
        if (!graph.neighbours(current).empty())
        {
            for (auto &&node : graph.neighbours(current))
            {
                if (!visited[node])
                {
                    queue.push(node);
                    visited[node] = true;
                }
            }
        }
    }
}

template <typename V, typename E>
std::vector<size_t> BFS(const Graph<V, E> graph, size_t vertex) //const
{
    std::vector<size_t> result;
    if (graph.neighbours(vertex).empty())
    {
        result.push_back(vertex);
        return result;
    }
    std::vector<bool> visited(graph.nrOfVertices());
    for (size_t i = 0; i < graph.nrOfVertices(); i++)
        visited[i] = false;
    visited[vertex] = true;
    std::queue<size_t> queue;
    size_t current;
    queue.push(vertex);
    while (!queue.empty())
    {
        current = queue.front();
        queue.pop();
        visited[current] = true;
        result.push_back(current);
        if (!graph.neighbours(current).empty())
        {
            for (auto &&node : graph.neighbours(current))
            {
                if (!visited[node])
                {
                    queue.push(node);
                    visited[node] = true;
                }
            }
        }
    }
    return result;
}

template <typename V, typename E>
std::pair<double, std::vector<std::size_t>> dijkstra(
    Graph<V, E> &graph, std::size_t start_idx, std::size_t end_idx, std::function<double(const E &)> getEdgeLength = [](const E &edge) -> E { return edge; })
{
    std::set<std::pair<double,size_t>> unvisited;
    for (size_t i = 0; i < graph.nrOfVertices(); i++)
        if (i != start_idx)
            unvisited.insert({std::numeric_limits<double>::max(),i});
        else
            unvisited.insert({0,i});
    std::vector<size_t> predecesor(graph.nrOfVertices());

    auto current_node = unvisited.find({0 , start_idx});
    while ((*current_node).second != end_idx)
    {
        auto neighbours = graph.neighbours((*current_node).second);
        auto it = std::remove_if(neighbours.begin(), neighbours.end(), [&](size_t n) -> bool { return std::none_of(unvisited.begin(), unvisited.end(), [&](const std::pair<double,size_t> a) -> bool { return a.second == n; }); });
        neighbours.erase(it,neighbours.end());
        // it = remove_if(neighbours.begin(), neighbours.end(),[&](size_t n) -> bool {})
        for (auto &&neighbour : neighbours)
        {
            auto temp = std::find_if(unvisited.begin(), unvisited.end(), [&](const std::pair<double,size_t> a) -> bool { return a.second == neighbour; }); //TODO zmiana nazwy
            if (getEdgeLength(graph.edgeLabel((*current_node).second, neighbour)) + (*current_node).first < (*temp).first)
            {
                unvisited.erase(temp);
                unvisited.insert({graph.edgeLabel((*current_node).second, neighbour) + (*current_node).first,neighbour});
                predecesor[neighbour] = (*current_node).second;
            }
        }
        unvisited.erase(current_node);
        if(unvisited.empty())
            throw "now parh exeption";
        current_node = std::min_element(unvisited.begin(), unvisited.end());
    }
    size_t node = end_idx;
    std::vector<size_t> result;
    while (node != start_idx)
    {
        result.push_back(node);
        node = predecesor[node];
    }
    result.push_back(start_idx);
    auto result_distance = std::find_if(unvisited.begin(), unvisited.end(), [&](const std::pair<double,size_t> a) -> bool { return a.second == end_idx; });
    std::reverse(result.begin(), result.end());
    return {(*result_distance).second, result};
}