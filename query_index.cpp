#include "query_processor.h"

#include <iostream>
#include <vector>
#include <string>

int main(int argc, char** argv) {
  if (argc<1) {
    std::cout << "Usage: query_idx  query1 query2 ... queryn\n";
    return -1;
  }
  // load index
  QueryProcessor qp;
  if (!qp.loadIndex("summary.txt")) {
    std::cerr << "Unable to load index: " << argv[1] << std::endl;
    return -1;
  }
  std::cout << "loaded index...\n";
  std::vector<std::string> queries;
  std::string query;
  while (!std::cin.eof() && std::cin>>query) {
    queries.push_back(query);
  }

  qp.report(queries);

  return 0;
}
