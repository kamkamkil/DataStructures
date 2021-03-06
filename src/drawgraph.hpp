#pragma once
#include "graph.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <functional>
#include <utility>
using namespace std;
template <typename E>
void drawGraph(Graph<std::pair<float, float>, E> &graph, std::string filename)
{
    auto getX = [&](double id) -> double { return graph.vertexData(id).first * 10; };
    auto getY = [&](double id) -> double { return graph.vertexData(id).second * 10; };
    ofstream data;
    string dataFile = "data_" + filename;
    data.open("graph_out/" + dataFile);
    double n = 0;
    for (auto &&value : graph)
    {
        data << getX(n) << "    " << getY(n);
        data << "    \"[" << value.first << ","<<value.second << "] ( " << n << " ) "
             << "\"" << endl;
        n++;
    }
    data << endl;
    data << endl;

    for (size_t node = 0; node < graph.nrOfVertices(); node++)
    {
        for (auto &&value : graph.neighbours(node))
        {
            data << getX(node) << "    " << getY(node) << "    " << getX(value) << "    " << getY(value) << endl;
        }
    }
    data << endl;
    data << endl;

    for (size_t node = 0; node < graph.nrOfVertices(); node++)
    {
        for (auto &&value : graph.neighbours(node))
        {
            data << (getX(node) + 4 * getX(value)) / 5 << "   " << (getY(node) + 4 * getY(value)) / 5 << "     \" " << graph.edgeLabel(node, value) << "\"" << endl;
        }
    }
    data.close();

    data.open("graph_out/script_" + filename);
    data << "set key off" << endl;
    data << "plot \"" << dataFile << "\"  index 0 with labels point  pt 7 offset char 0,1,\\" << endl;
    data << "\"" << dataFile << "\" index 1  using 1:2:($3-$1):($4-$2)  with vectors head filled,\\" << endl;
    // data << "\"" << dataFile << "\" index 2 using 1:2:3 with labels boxed tc lt 1 " << endl;
    data.close();
}

template <typename V, typename E>
void drawGraph(Graph<V, E> &graph, double radius, std::string filename)
{
    auto getX = [&](double id) -> double { return radius * cos(id * (6.28 / (double)graph.nrOfVertices())); };
    auto getY = [&](double id) -> double { return radius * sin(id * (6.28 / (double)graph.nrOfVertices())); };
    ofstream data;
    string dataFile = "data_" + filename;
    data.open("graph_out/" + dataFile);
    double n = 0;
    for (auto &&value : graph)
    {
        data << getX(n) << "    " << getY(n);
        data << "    \"" << value << " ( " << n << " ) "
             << "\"" << endl;
        n++;
    }
    data << endl;
    data << endl;

    for (size_t node = 0; node < graph.nrOfVertices(); node++)
    {
        for (auto &&value : graph.neighbours(node))
        {
            data << getX(node) << "    " << getY(node) << "    " << getX(value) << "    " << getY(value) << endl;
        }
    }
    data << endl;
    data << endl;

    for (size_t node = 0; node < graph.nrOfVertices(); node++)
    {
        for (auto &&value : graph.neighbours(node))
        {
            data << (getX(node) + 4 * getX(value)) / 5 << "   " << (getY(node) + 4 * getY(value)) / 5 << "     \" " << graph.edgeLabel(node, value) << "\"" << endl;
        }
    }
    data.close();

    data.open("graph_out/script_" + filename);
    data << "set key off" << endl;
    data << "plot \"" << dataFile << "\"  index 0 with labels point  pt 7 offset char 0,1,\\" << endl;
    data << "\"" << dataFile << "\" index 1  using 1:2:($3-$1):($4-$2)  with vectors head filled,\\" << endl;
    data << "\"" << dataFile << "\" index 2 using 1:2:3 with labels boxed tc lt 1 " << endl;
    data.close();
}
template <typename V, typename E>
void animatePath(Graph<V, E> &graph, double radius, std::string filename, size_t vertex)
{
    auto getX = [&](double id) -> double { return radius * cos(id * (6.28 / (double)graph.nrOfVertices())); };
    auto getY = [&](double id) -> double { return radius * sin(id * (6.28 / (double)graph.nrOfVertices())); };
    ofstream data;
    string baseGraph = "graph_" + filename;
    string animationData = "data_" + filename;
    drawGraph(graph, 20, baseGraph);
    vector<size_t> result = BFS(graph, vertex);
    data.open("graph_out/" + animationData);
    for (size_t i = 0; i < result.size(); i++)
    {
        for (size_t k = 0; k < i; k++)
        {
            data << getX(result[k]) << "    " << getY(result[k]) << endl;
        }
        data << endl
             << endl;
    }
    data.close();
    data.open("graph_out/stript" + filename);
    data << "set term gif animate delay 25" << endl;
    data << "set xrange[-25 : 25]" << endl;
    data << "set yrange[-25 : 25]" << endl;
    data << "set key off" << endl;
    data << "set samples 800" << endl;
    data << "set output \"" << filename << ".gif\"" << endl;
    data << "plot "
         << "\"data_" + baseGraph << "\" index 0 with labels point  pt 7 offset char 0,1,\\" << endl;
    data << "\"data_" + baseGraph << "\" index 1  using 1:2:($3-$1):($4-$2)  with vector,\\" << endl;
    data << "\"data_" + baseGraph << "\" index 2 using 1:2:3 with labels boxed tc lt 1" << endl;
    for (size_t i = 0; i < result.size(); i++)
    {
        data << "plot\""
             << "data_" + baseGraph << "\" index 0 with labels point  pt 7 offset char 0,1,\\" << endl;
        data << "\"data_" + baseGraph << "\" index 1  using 1:2:($3-$1):($4-$2)  with vector,\\" << endl;
        data << "\"data_" + baseGraph << "\" index 2 using 1:2:3 with labels boxed tc lt 1,\\" << endl;
        data << "\"data_" + filename << "\" index " << i << " using 1:2:(1) with circles" << endl;
    }
    data << "set term wxt";
    data.close();
}
