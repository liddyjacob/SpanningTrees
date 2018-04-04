#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "graph.hpp"
#include "graphutils.hpp"
#include "interpret.hpp"
#include "commands.hpp"

const char* LOAD_FILE = ".load_file";

int main(int argc, char** argv){

  Commands commands;

  parse(argc, argv, commands);

  if (commands.type == ERROR){
    std::cerr << "Invalid arguments: ";

    for (int i = 1; i < argc; ++i){
      std::cerr << argv[i] << ' ';
    } 
    std::cerr << std::endl;
    std::cerr << "See ./graph --help for options" << std::endl; 
    return -1;
  }


  if (commands.type == HELP){ 
    std::cerr << "Usage: \n"
              << "To load a graph file: \n"
              << "\t./graph l (graph_file)\n"
              << "To view the routes in the graph\n"
              << "\t./graph v\n"
              << "To find the minimum spanning tree based off distance:\n"
              << "\t./graph mst\n"
              << "To find the shortest paths from source city to dest city:\n"
              << "\t./graph s -s (source) -d (dest)\n"
              << "To find the trips given a specified budget:\n"
              << "\t./graph b (budget)"
              << std::endl;
    return 0;
  }

  if (commands.type == LOAD){
    // Save contents

    std::ifstream newfile;
      newfile.open(commands.args.filename.c_str()); 

    if (!newfile.is_open()) {
      std::cerr << "File failed to open\n";
      return -1;
    }

    std::ofstream loadfile;
      loadfile.open(LOAD_FILE, std::ios::trunc);

    loadfile << newfile.rdbuf();

    newfile.close();
    loadfile.close();

    std::cout << commands.args.filename << ": Successfully loaded\n"; 
    return 0;
  }

  Graph airlines;
  std::ifstream data;
  data.open(LOAD_FILE);

  fill(airlines, data);

  if (commands.type == MST){

    std::cout << "##### MINIMUM SPANNING TREE/FOREST ######" 
              << std::endl << std::endl;

    find_MST(airlines, DISTANCE).show_edges(std::cout);

  }

  if (commands.type == SHORTEST){

    std::string source = commands.args.source_dest.first;
    std::string dest = commands.args.source_dest.second;

    std::cout << "###### SHORTEST PATHS ######\n";
    std::cout << "### BASED ON DISTANCE ###\n";
    
    pair<Route, double> p = find_shortest(airlines, source, dest, DISTANCE);
    if (p.first.path.size() == 0){
      std::cout << "There are no routes between the specified cities\n";
      return 0;
    }
    std::cout << "Route: ";
    p.first.display();
    std::cout << "\n\tTotal cost: " << p.second << " Miles.\n";
    
    std::cout << "\n### BASED ON PRICE ###\n";

    p = find_shortest(airlines, source, dest, PRICE);
    std::cout << "Route: ";
    p.first.display();
    std::cout << "\n\tTotal cost: $" << p.second << "\n";

    std::cout << "\n### BASED ON HOPS ###\n";
 
    p = find_shortest(airlines, source, dest, HOPS);
    std::cout << "Route: ";
    p.first.display();
    std::cout << "\n\tTotal hops: " << p.second << "\n";

 }

  if (commands.type == BUDGET){

    double budget = commands.args.budget;

    auto rvect_pvect = budget_trips(airlines, budget);

    vector<Route> rvect = rvect_pvect.first; // Route vector
    vector<double> pvect = rvect_pvect.second; // Price vector

    if (rvect.size() != pvect.size()){
      std::cerr << "Error! Price vector and route vector have different size!" 
                << std::endl;

      std::cerr << "\t rvect has size " << rvect.size()
                << "\n\t pvect has size " << pvect.size() << std::endl;

      return -1;
    }

    std::cout << "All trips given your budget of $" << budget 
              << ":" << std::endl;

    for (int i = 0; i < rvect.size(); ++i){
      if (rvect[i].path.size() != 1){
        rvect[i].display();
        std::cout << "\n\tPrice: $" << pvect[i] << std::endl;
      }
    }

  }

  if (commands.type == VIEW){

    std::cout << "####### Cities and Connections ####### \n\n";
    airlines.show(std::cout);

  }

  data.close();
  
  return 0;
}
