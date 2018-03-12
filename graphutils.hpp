// Graph utilities.

/*
IN THIS FILE: mst is an implimentation of Kruskals,
              shortest is an impl. of Dijkstras
*/

#pragma once

#include <map>
#include <algorithm>
//#include <queue>

#include "graph.hpp"

using std::string;
using std::pair;
using std::vector;

struct priority_queue{

  vector<string> storage;

  void insert(string s, std::map<string, double>& dist){

    if (dist[s] == -1){
      storage.push_back(s);
      return;
    }

    if (dist[s] == 0){
      storage.push_back(s);
      return; 
    }

    for (int i = 0; i < storage.size(); ++i){

      if (dist[storage[i]] == -1){
        storage.insert(storage.begin() + i, s);
        return;
      }

      if (dist[storage[i]] > dist[s]){
        storage.insert(storage.begin() + i, s);
        return;
      }
    }

    storage.push_back(s);

  }

  string pop(){
    string s = storage[0];
    storage.erase(storage.begin());

    return s;
  }
};

struct Route{

  Route(const Route& cpy, string add){
    path = cpy.path;
    path.push_back(add);
  }

  Route(){}

  Route(string source){
    path.push_back(source);
  }

  void display(){

    for (int i = 0; i < path.size(); ++i){
      string p = path[i];
      std::cout << p; 
      if (i != path.size() - 1) {std::cout << " -> ";}

    }
  }

  vector<string> path;
};


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

pair<std::map<string, Route>, std::map<string, double> >
find_shortest_routes(Graph& g, string source, Type t, double limit = -1){

  std::map<string, Route> routes;
  std::map<std::string, double> dist;


  if (!g.contains(source)){
    std::cerr << "Graph does not contain " << source << std::endl;
    return std::make_pair(routes, dist);
 }

  
  std::map<std::string, bool> visited;
    visited[source] = false;

  dist[source] = 0.0;
  routes[source] = Route(source);

  priority_queue pq;
    pq.insert(source, dist);

  for (auto pair : g.edges()){
    string city = pair.first;
    if (city != source){
      dist[city] = -1;
      visited[city] = false;
    }
  }

  while (pq.storage.size() != 0){
    string v = pq.pop();

    if (!visited[v]) {

      visited[v] = true;

      for (auto adj : g[v]){

        double weight;
        if (t == DISTANCE) {weight = adj.distance;}
        if (t == PRICE) {weight = adj.price; }
        if (t == HOPS) {weight = 1;}

        if (limit != -1){
          
          if (limit < weight + dist[v]){
            continue;
          }
        }

        if (dist[adj.city] == -1){
          
          dist[adj.city] = weight + dist[v];

          routes[adj.city] = Route(routes[v], adj.city);

        } else if (dist[adj.city] > weight + dist[v]){

          dist[adj.city] = weight + dist[v]; 

          routes[adj.city] = Route(routes[v], adj.city);
        }

        pq.insert(adj.city, dist);

      }
    }
  }

  return std::make_pair(routes, dist);
}

pair<Route, double> find_shortest(Graph& g, string source, string dest, Type t){

  if (!g.contains(dest)){
    std::cerr << "Graph does not contain " << dest << std::endl;
    return std::make_pair(Route(), -1);
  } 

  auto routes_dists = find_shortest_routes(g, source, t);

  Route r = routes_dists.first[dest];
  double d = routes_dists.second[dest];

  return std::make_pair(r,d);
};

pair <vector<Route>, vector<double> > budget_trips(Graph& g, double& budget){
  

  pair<vector<Route>, vector<double> > trips;

  for (string city : g.get_cities()){


    auto routes_dists = find_shortest_routes(g, city, PRICE, budget);

    std::map<string, Route> rts_map = routes_dists.first;
    std::map<string, double> dsts_map = routes_dists.second;

    std::vector<Route> rts;
    std::vector<double> dsts;
    for (auto p_r : rts_map){
      
      string city = p_r.first;
      Route r = p_r.second;
      double dist = dsts_map[city];

      rts.push_back(r);
      dsts.push_back(dist);

    }
   trips.first.insert(trips.first.end(),rts.begin(), rts.end()) ; 
   trips.second.insert(trips.second.end(),dsts.begin(), dsts.end());

  }

  return trips;
}
  
