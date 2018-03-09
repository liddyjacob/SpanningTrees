// graph.hpp
// Represent a graph with an adjacency list

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "edge.hpp"


struct AdjacencyList{

  std::map<std::string, std::vector<Edge> > map;

  AdjacencyList(){}

  void add(std::string city){

    if (map.find(city) == map.end()){
      //New city
      map[city] = std::vector<Edge>();
    }

  }

  void edge(std::string city1, Edge e){
    
    if (map.find(city1) == map.end() | map.find(e.city) == map.end()){
      std::cerr << city1 << " or " << e.city << "are not currently stored\n";
      return;
    }

  }

  int size(){ return map.size(); }
};


class Graph{
  public:

    Graph()
      : list()
    {}

    Graph(std::vector<std::string> cities);

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
