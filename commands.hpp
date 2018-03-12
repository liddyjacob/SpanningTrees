//commands.hpp
// commands the user can pass in to the arguments to be parsed
#pragma once

#include <string>
#include <cstring>

enum CommandType {ERROR = -1, HELP, LOAD, MST, SHORTEST, BUDGET, VIEW};

struct Arguments{

  std::string filename;
  std::pair<std::string, std::string> source_dest;
  double budget;

};

struct Commands{

  Commands()
    : type(ERROR) 
  {}

  CommandType type;  
  Arguments args;

};

void parse(int argc, char** argv, Commands& commands){

  if (argc == 1){
    commands.type = HELP;
    return;
  }

  if (strcmp(argv[1], "--help") == 0) { commands.type = HELP; }

  if (strcmp(argv[1], "mst") == 0){
    commands.type = MST; 
  }

  if (strcmp(argv[1], "l") == 0){
  
    commands.type = LOAD;

    if (argc != 3){
      std::cerr << "Please type exactly one filename." << std::endl;
      commands.type = ERROR;
      return;
    }

    std::string filename(argv[2]);
    commands.args.filename = filename;
  }

  if (strcmp(argv[1], "v") == 0){

    commands.type = VIEW;

  }

  if (strcmp(argv[1], "s") == 0){

    commands.type = SHORTEST;

    if (argc != 6){
      std::cerr << "Please follow exactly the format given in --help\n" 
                << "(Be careful with spaces: Type spaces as:' ' or \\ )"
                << std::endl;
      commands.type = ERROR;
      return;
    }

    if (strcmp(argv[2], "-s") != 0 && strcmp(argv[2], "-d") != 0){
      std::cerr << argv[2] << " Is not a valid tag\n";
      commands.type = ERROR;
      return;
    }
 
    if (strcmp(argv[4], "-s") != 0 && strcmp(argv[4], "-d") != 0){
      std::cerr << argv[4] << " Is not a valid tag\n";
      commands.type = ERROR;
      return;
    }

    if (strcmp(argv[2], "-s") == 0){

      std::string source(argv[3]); 
      std::string dest(argv[5]);
      commands.args.source_dest = std::make_pair(source, dest);

    } else {

      std::string source(argv[5]);
      std::string dest(argv[3]);
      commands.args.source_dest = std::make_pair(source, dest);

    }

  }

  if (strcmp(argv[1], "b") == 0){

    commands.type = BUDGET;

    if (argc != 3){
      std::cerr << "Type in exactly one value after b\n";
      commands.type = ERROR;
      return;
    }

    if (!isDouble(argv[2])){
      std::cerr << argv[2] << " is not a valid budget\n";
      commands.type = ERROR;
      return; 
    }

    commands.args.budget = strtod(argv[2], NULL);
  }

}



