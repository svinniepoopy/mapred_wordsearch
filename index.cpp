#include "index.h"
#include "posting_record.h"

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>

void Index::add(const std::string& word, const int pagenum, const int doc_id) {
  ++doc2word[doc_id][word];
}

void Index::updatePostingsList(int doc_id) {
  auto& wordfreq = doc2word[doc_id];

  for (const auto& item:wordfreq) {
    postings_list[item.first].emplace(doc_id, item.second);
  }
}

bool Index::loadPostings(const std::string& indexfile) {
  std::ifstream ifs{indexfile, std::ios::in};
  if (!ifs.is_open()) {
    return false;
  }

  while (!ifs.eof()) {
    std::string line;
    std::getline(ifs, line);
    std::istringstream istr{line};
    // std::cout << "line: " << line << '\n';
    std::string word;
    istr>>word;
    std::string w;
    while (istr>>w) {
      if (!w.empty()) {
	auto pos = w.find(",");
	int doc_id = std::stoi(w.substr(0, pos));
	int freq = std::stoi(w.substr(pos+1));
	postings_list[word].emplace(doc_id, freq);
      }
    }
  }

  return true;
}

bool Index::find(const std::string& w) {
  return postings_list.find(w) != postings_list.end();
}

std::vector<std::pair<int, int>> Index::get(const std::string& w) {
  std::vector<std::pair<int, int>> doc_ids;
  const auto& docs = postings_list[w];
  for (const auto& item:docs) {
    doc_ids.emplace_back(item.doc_id, item.freq);
  }
  return doc_ids;
}

std::ostream& operator<<(std::ostream& os, const Index& index) {
  for (const auto& item:index.postings_list) {
    os <<  item.first;
    for (const auto& posting:item.second) {
      os << " " << posting.doc_id << ","<< posting.freq << " ";
    }
    os << "\n";
  }
  return os;
}
