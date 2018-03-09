// graph.hpp
// Represent a graph with an adjacency list

#pragma once

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "edge.hpp"

enum Type {DISTANCE, PRICE};


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
    std::vector<std::pair<std::string, Edge> > edges(){return list.pairs();}

    bool contains(std::string city)
    { return list.map.find(city) != list.map.end(); }
    
    bool isCyclic() {return false;} //TODO FIXME


    void add(std::string node){list.add(node);}

    void edge(std::string city, Edge e){list.edge(city, e);}

    int size(){ return list.size(); }


  private:

    AdjacencyList list;
    
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
