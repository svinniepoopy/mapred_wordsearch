#include "index.h"
#include "indexer.h"
#include "util.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

void Indexer::processLine(
    const std::string& line,
    const int pagenum,
    const int doc_id) {

  std::istringstream istr{line};
  std::string word;
  while (istr>>word) {

    word = util::scrub(word);

    if (ignored_words.find(word) == ignored_words.end()) {
      index->add(word, pagenum, doc_id);
    }
  }

}

bool Indexer::processFile(const std::string& file, const int doc_id) {
      std::ifstream ifs{file, std::ios::in};
      if (!ifs.is_open()) {
	return false;
      }

      int page_num = 1;
      int line_no = 1;
      while (!ifs.eof()) {
	std::string line;
	std::getline(ifs, line);
	processLine(line, page_num, doc_id);
	++line_no;
	if (line_no>0 && line_no%100==0) {
	  ++page_num;
	  line_no = 1;
	}
      }

      ifs.close();

      index->updatePostingsList(doc_id);

      return true;
}

void Indexer::processIgnoredWords(const std::string& ignored_words_dir) {
  namespace fs = std::filesystem;
  std::vector<std::string> files;
  for (const auto& p: fs::directory_iterator(ignored_words_dir)) {
    files.push_back(p.path().c_str());
  }
  for (const auto& file:files) {
    std::ifstream ifs{file, std::ios::in};
    if (!ifs.is_open()) {
      std::cerr << "Error opening stepwords file: " << file << std::endl;
      return; // throw exception here
    }
    while (!ifs.eof()) {
      std::string word;
      std::getline(ifs, word);
      ignored_words.insert(word);
    }
    ifs.close();
  }
}

void Indexer::writeToDisk() {

}

void Indexer::summarize() const {
  std::cout << "Postings list has " << index->size() << " entries.\n";
  std::ofstream ofs{"summary.txt", std::ios::trunc};
  ofs << *index;
  ofs.close();
}
