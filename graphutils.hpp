// Graph utilities.
#pragma once

#include <map>
#include <algorithm>

#include "graph.hpp"

using std::string;
using std::pair;
using std::vector;

// Eliminate repeated edges and sort by parameter
vector<pair<string, Edge> > 
sort_edges(vector< pair<string, Edge> > pairs, Type sortby);
bool comp_dist(pair<string, Edge> p1, pair<string, Edge> p2);
bool comp_price(pair<string, Edge> p1, pair<string, Edge> p2);

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

    //string temp = city;
    //city = e.city;
    //e.city = temp;

    //next_mst.edge(city, e);

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

//Eliminate repeated edge.
vector<pair<string, Edge> > 
sort_edges(vector< pair<string, Edge> > pairs, Type sortby){

  vector<pair<string, Edge> > sorted_edges; // Must use insertion sort

  std::map<pair<string, string>, bool> connections;

  for (auto p : pairs){

    string city1 = p.first;
    string city2 = p.second.city;

    pair<string, string> new_connection = std::minmax(city1, city2);

    if (connections.find(new_connection) != connections.end() ){
      continue; // We already have this connection.
    } 

    connections[new_connection] = true;

    sorted_edges.push_back(p);

    if (sortby == DISTANCE) {  // TODO: FIX THIS HACK
     std::sort(sorted_edges.begin(), sorted_edges.end(), comp_dist);     
    }

    if (sortby == PRICE) {  // TODO: FIX THIS HACK
     std::sort(sorted_edges.begin(), sorted_edges.end(), comp_price);     
    }
  
  }

  return sorted_edges;
}

bool comp_dist(pair<string, Edge> p1, pair<string, Edge> p2){
  return p1.second.distance < p2.second.distance;
}

bool comp_price(pair<string, Edge> p1, pair<string, Edge> p2){
  return p1.second.price < p2.second.price;
}

