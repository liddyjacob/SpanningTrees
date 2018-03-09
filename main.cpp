#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "graph.hpp"
#include "graphutils.hpp"
#include "interpret.hpp"

int main(int argc, char** argv){

  //TODO: Change filename to input.
  std::string filename = "airline_data1.txt";

  Graph airlines;

  std::ifstream data;
  data.open(filename.c_str());

  fill(airlines, data);
  airlines.show(std::cout);

  std::cout << "##### MINIMUM SPANNING TREE ######" << std::endl << std::endl;

  find_MST(airlines).show(std::cout);

  data.close();

  return 0;
}
