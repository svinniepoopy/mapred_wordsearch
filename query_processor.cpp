#include "query_processor.h"

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

bool QueryProcessor::loadIndex(const std::string& indexfile) {
  return index->loadPostings(indexfile);
}

void QueryProcessor::report(const std::vector<std::string>& queries) {
  std::unordered_map<std::string, std::vector<std::pair<int, int>>> postings;
  for (const auto& query:queries) {
    if (index->find(query)) {
      std::vector<std::pair<int, int>> doc_ids{index->get(query)};
      postings[query] = doc_ids;
    }
  }

  for (const auto& posting:postings) {
    std::cout << "Word: " << posting.first << std::endl;
    std::cout << "Found in:\n";
    for (const auto& p:posting.second) {
      std::cout << "\t\tdoc_id: " << p.first << " " << p.second << " times.\n";
    }
    std::cout << "\n";
  }
}
