// Graph utilities.
#pragma once

#include <map>
#include <algorithm>

#include "graph.hpp"

using std::string;
using std::pair;
using std::vector;

Graph find_MST(Graph g, Type t){
  //First list edges in order of greatest to least size:
  vector< pair<string, Edge> > undir_edges; 
    undir_edges = sort_edges(g.edges(), t);

  Graph mst;

  for (auto pair : undir_edges){

    Graph next_mst = mst;
    string city1 = pair.first;
    Edge e = pair.second;

    next_mst.add(city1);
    next_mst.add(e.city);
    next_mst.edge(city1, e);

    string city2 = e.city;
    e.city = city1;

    next_mst.edge(city2, e);

    if (!next_mst.isCyclic(city1, city2)){
      mst = next_mst;
    }

    //Edge capacity reached:
    if (mst.size() == g.size()){
      return mst;
    }
  }

  //std::cerr << "No spanning tree could be constructed from graph!\n";
  //Graph err_g;
  //return err_g;

  return mst;

}

Graph find_shortest(Graph& g, string source, string dest, Type t){

  std::cout << "source: " << source << std::endl;
  std::cout << "dest: " << dest << std::endl;

  Graph g2;

  return g2;
}

Graph BFS(Graph g, string source, string dest){
  std::cout << "source: " << source << std::endl;
  std::cout << "dest: " << dest << std::endl;

  Graph g2;

  return g2;


}
