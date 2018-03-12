// graph.hpp
// Represent a graph with an adjacency list
#pragma once

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

#include "edge.hpp"

using std::vector;
using std::string;
using std::pair;

enum Type {DISTANCE, PRICE, HOPS,LEXICOGRAPHIC};

// Eliminate repeated edges and sort by parameter 
bool comp_dist(pair<string, Edge> p1, pair<string, Edge> p2);
bool comp_price(pair<string, Edge> p1, pair<string, Edge> p2);
bool comp_lex(pair<string, Edge> p1, pair<string, Edge> p2);



vector<pair<string, Edge> >
sort_edges(vector< pair<string, Edge> > pairs, Type sortby);


struct AdjacencyList{

  std::map<std::string, std::vector<Edge> > map;
  AdjacencyList(){}

  void add(std::string city){

    if (map.find(city) == map.end()){
      //New city
      map[city] = std::vector<Edge>();
    }
  }

  void edge(std::string city, Edge e){
    
    if (map.find(city) == map.end() | map.find(e.city) == map.end()){
      std::cerr << city << " or " << e.city << "are not currently stored\n";
      return;
    }

    map[city].push_back(e);
  }

  std::vector<std::pair<std::string, Edge> > pairs(){

    std::vector<std::pair<std::string, Edge> > pairs;
    for (auto it : map){

      for (auto edge : it.second){ 
        pairs.push_back(std::make_pair(it.first, edge));
      }  
    }
    return pairs;
  }

  int size(){ return map.size(); }

};



class Graph{
  public:

    Graph()
      : list()
    {}

    Graph(std::vector<std::string> cities);

    void show(std::ostream& output);
    void show_edges(std::ostream& output);

    std::vector<std::pair<std::string, Edge> > edges(){return list.pairs();}

    bool contains(std::string city)
    { return list.map.find(city) != list.map.end(); }
    
    bool isCyclic(std::string old_city, std::string new_city);

    void add(std::string node)
    {
      list.add(node);
      cities.push_back(node);
    }

    void edge(std::string city, Edge e){list.edge(city, e);}

    int size(){ return list.size(); }

    std::vector<std::string> get_cities(){return cities;}

    std::vector<Edge> operator[](std::string source){ return list.map[source]; }
  private:

    AdjacencyList list;
    std::vector<std::string> cities;
    bool isCyclicUtil(std::string prev_city, 
                      std::string new_city,
                      std::map<std::string, bool>& visited);  

};

Graph::Graph(std::vector<std::string> cities){
  for (city : cities){
    list.add(city);
  }
}

void Graph::show(std::ostream& output){

  for (auto it : list.map){
    
    std::string city = it.first;
    output << "## " << city << " ##" << std::endl;

    std::vector<Edge> edges = it.second;

    for (Edge edge : edges){

      output << std::setprecision (2) << std::fixed;
      output << '\t' << city << "->" << edge.city;
      output << ": " << edge.distance << " miles;";
      output << " $"  << edge.price << std::endl;

    }

  }
}

void Graph::show_edges(std::ostream& output){ 

  vector<pair<string, Edge> > undir_edges;
    undir_edges = sort_edges(edges(), LEXICOGRAPHIC);

  for (auto pair : undir_edges){

    string city = pair.first;
    Edge edge = pair.second;

    {
      output << std::setprecision(2) << std::fixed;
      output << city << "<--->" << edge.city;
      output << ": " << edge.distance << " miles;";
      output << " $"  << edge.price << std::endl;
    }

  }

  

}

bool Graph::isCyclic(std::string old_city, std::string new_city){

  std::map<std::string, bool> visited;

  for (auto it : list.map){
    visited[it.first] = false;
  }

 isCyclicUtil(old_city, new_city, visited);

  return visited[old_city];
}

bool Graph::isCyclicUtil(std::string prev_city,
                  std::string new_city, 
                  std::map<std::string, bool>& visited){

  visited[new_city] = true;
  
  for (Edge edge : list.map[new_city]){
    
    if (edge.city != prev_city){

        std::string newnew_city = edge.city;

        if (!visited[newnew_city]){
          isCyclicUtil(new_city, newnew_city, visited);
        } else {
          //Return false?
        }
    }
  }

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

    if (sortby == LEXICOGRAPHIC){
      std::sort(sorted_edges.begin(), sorted_edges.end(), comp_lex);
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

bool comp_lex(pair<string, Edge> p1, pair<string, Edge> p2){
  return p1.first < p2.first; 
}
