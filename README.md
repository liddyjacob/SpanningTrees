# Project 2 for Algorithms

Note: Input file must be a unix file currently. To change a file
to unix, type 

`dos2unix (filename)`

To compile the program:

`g++ main.cpp -o graph -std=c++11` 

...And to run it

`./graph (arguments)`

READ THIS: YOU MUST FIRST LOAD A GRAPH FILE TO USE THE OTHER ARGUMENTS!

Here are the possible arguments:

`
To load a graph file: 
  ./graph l (graph_file)
To view the routes in the graph
  ./graph v
To find the minimum spanning tree based off distance:
  ./graph mst
To find the shortest paths from source city to dest city:
  ./graph s -s (source) -d (dest)
To find the trips given a specified budget:
  ./graph b (budget)
`

Guidelines for the project:
http://www.cs.uakron.edu/~duan/class/435/projects/project2/GraphProject.htm
