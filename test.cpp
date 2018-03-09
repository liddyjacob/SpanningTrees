
#include "graph.hpp"
#include "edge.hpp"
/* Edge :

  string city
  double distance
  double price

*/
#include <vector>
#include <string>
#include <cassert>

int main(){

  // GRAPH(ADJACENCY LIST) TESTS 

  /* Test 1: Initialization */
  {
    Graph graph;
    assert(graph.size() == 0);
  }

  /* Test 2: Node Initialization */
  {
    std::vector<std::string> nodes = {"N1", "N2", "N3"};
  
    Graph graph(nodes);
    graph.add("N4");

    Edge e;
    e.city = "N1";
    e.distance = 100;
    e.price = 40.0;

    graph.edge("N2", e);

    std::cout << graph.size() << "\n";

    assert(graph.size() == 4);
  }
    


}
