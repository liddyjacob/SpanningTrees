// Graph utilities.
#pragma once

#include "graph.hpp"

using std::string;
using std::pair;
using std::vector;

// Eliminate repeated edges and sort by parameter
vector<pair<string, Edge> > 
sort_edges(vector< pair<string, Edge> > edges, Type sortby);

Graph find_MST(Graph g){
  //First list edges in order of greatest to least size:
  vector< pair<string, Edge> > undir_edges; 
    undir_edges = sort_edges(g.edges(), DISTANCE);

  Graph mst;

  for (auto pair : undir_edges){

    Graph next_mst = mst;
    string city = pair.first;
    Edge e = pair.second;

    next_mst.add(city);
    next_mst.add(e.city);
    next_mst.edge(city, e);

    string temp = city;
    city = e.city;
    e.city = temp;

    next_mst.edge(city, e);

    if (!next_mst.isCyclic()){

      mst = next_mst;
      
    }
    //Edge capacity reached:
    if (mst.size() == g.size() - 1){
      return mst;
    }
  }

  std::cerr << "No spanning tree could be constructed from graph!\n";
  Graph err_g;
  return err_g;
}


vector<pair<string, Edge> > 
sort_edges(vector< pair<string, Edge> > edges, Type sortby){

  return edges;
}
