#pragma once

//Data interpreters

#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <algorithm>
#include <iterator>
#include <stdio.h>

#include "graph.hpp"
#include "graphutils.hpp"

bool isInteger(const std::string& s);
bool isCity(const std::string& s);
bool isEdge(const std::string& s);
bool isDouble(const std::string& s);

std::pair<std::string, Edge>
parseEdge(std::string line, std::vector<std::string> citynumbers);
std::vector<std::string> split(const std::string& s, char delim);

bool parse(Graph& g, std::string line, std::vector<std::string>& citynumbers){  


 //Check if the line is just an integer.
  if (isInteger(line)) {return true;}

  //Checks to see if line is just a city
  if (isCity(line)) {

    if (g.contains(line)){
      std::cerr << "Redundant city: " << line; 
      return true;
    }

    g.add(line);
    citynumbers.push_back(line);

    return true;
  }
  
  if (isEdge(line)) {

    std::pair<std::string, Edge> data = parseEdge(line, citynumbers);
    std::string city1 = data.first;
    Edge edge  = data.second;

    g.edge(city1, edge);

    std::string temp = city1;
    city1 = edge.city;
    edge.city = temp;

    g.edge(city1, edge);

    return true;
  }

  return false;

}


void fill(Graph& g, std::ifstream& file){

  std::string line;
  std::vector<std::string> citynumbers;

  while (std::getline(file, line)){
  
    if (!parse(g, line, citynumbers)){
      std::cerr << "Did not accept the line:\n\t" << line << std::endl;
    }

  }
}


bool isInteger(const std::string& s){

  for (const char& c : s){
    if (!std::isdigit(c)) { return false; }
  }

  return true;
}

bool isDouble(const std::string& s){

  std::vector<std::string> parts = split(s, '.');

  if (parts.size() >= 3) {return false;}

  if (!isInteger(parts[0])) {return false;}

  if (parts.size() == 2){
    if (!isInteger(parts[1])) {return false;}
  }

  return true;
}

bool isCity(const std::string& s){

  return !isEdge(s) && !isDouble(s);
}

bool isEdge(const std::string& s){

  std::vector<std::string> tokens = split(s, ' ');
  
  if (tokens.size() != 4) { return false; }

  if (!isInteger(tokens[0]) || !isInteger(tokens[1])) { return false; }
  if (!isDouble(tokens[2]) || !isDouble(tokens[3])) {return false; }

  return true;
}




// Edge is in format:
// (int city1) (int city2) (int miles) (double cost)
//                                           ^ CONTAINS A DECIMAL (.)
// Also, assume that it is bidirectional.

std::pair<std::string, Edge>
parseEdge(std::string line, std::vector<std::string> citynumbers){

  //Parse line:
  std::vector<std::string> tokens = split(line, ' ');
    int city1num    = atoi(tokens[0].c_str()) - 1;
    int city2num    = atoi(tokens[1].c_str()) - 1;
    double distance = strtod(tokens[2].c_str(), NULL);
    double price    = strtod(tokens[3].c_str(), NULL);

  std::string city1 = citynumbers[city1num];
  std::string city2 = citynumbers[city2num];

  Edge e;

  e.city = city2; // TODO fixme
  e.distance = distance;
  e.price = price;

  return std::make_pair(city1, e);
}


std::vector<std::string> split(const std::string& s, char delim){

  std::vector<std::string> toks;
  std::string tok;
  std::istringstream tokstream(s);
  
  while (std::getline(tokstream, tok, delim)){

    toks.push_back(tok);

  }

  return toks;
}

