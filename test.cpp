
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
    
  {
    std::vector<std::string> nodes = {"N1", "N2", "N3"};
  
    Graph graph(nodes);
    graph.add("N4");

    Edge e1;
      e1.city = "N1";
      e1.distance = 100;
      e1.price = 40.0;

    graph.edge("N2", e1);

    Edge e2;
      e2.city = "N3";
      e2.distance = 120;
      e2.price = 50;

    graph.edge("N2", e2);

    Edge e3;
      e3.city = "N2";
      e3.distance = 20;
      e3.price = 2001;

    graph.edge("N1", e3);

    graph.show(std::cout);


    std::cout << graph.size() << "\n";

    assert(graph.size() == 4);



  }



}
