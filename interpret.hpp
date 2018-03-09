#pragma once

//Data interpreters

#include <fstream>
#include <string>
#include <sstream>
#include <utility>

#include <stdio.h>

#include "graph.hpp"

bool isInteger(const std::string& s);
bool isCity(const std::string& s);
bool isEdge(const std::string& s);

std::pair<std::string, Edge>
parseEdge(std::string line, std::vector<std::string> citynumbers);

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
    g.edge(data.first, data.second);

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


// Code BELOW borrowed from: 
// https://stackoverflow.com/questions/2844817/how-do-i-check-if-a-c-string-is-an-int
bool isInteger(const std::string& s){

  for (const char& c : s){
    if (!std::isdigit(c)) { return false; }
  }

  return true;
}


bool isCity(const std::string& s){

  for (char c : s){
    if (!isalpha(c)) { return false; }
  }

  return true;
}

bool isEdge(const std::string& s){

  return true;
}

std::pair<std::string, Edge>
parseEdge(std::string line, std::vector<std::string> citynumbers){

  Edge e;
  e.city = citynumbers[0]; // TODO fixme
  e.distance = -1;
  e.price = -1;

  std::string city = citynumbers[0];

  return std::make_pair(city, e);
}
