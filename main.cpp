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
              << "\t./graph v"
              << "To find the minimum spanning tree based off distance:\n"
              << "\t./graph mst\n"
              << "To find the shortest paths from source city to dest city:\n"
              << "\t./graph s -s (source) -d (dest)"
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
    
    find_shortest(airlines, source, dest, DISTANCE).show_edges(std::cout);
    
    std::cout << "\n### BASED ON PRICE ###\n";

    find_shortest(airlines, source, dest, PRICE).show_edges(std::cout);

    std::cout << "\n### BASED ON HOPS ###\n";

    BFS(airlines, source, dest).show_edges(std::cout);

  }

  if (commands.type == BUDGET){

  }

  if (commands.type == VIEW){

    std::cout << "####### Cities and Connections ####### \n\n";
    airlines.show(std::cout);

  }

  data.close();
  
  return 0;
}
