// file: query.cpp
//
#include "indexer.h"

#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace {
namespace fs = std::filesystem;

void usage() {
  std::cout << "Usage: create_index <ignored_words_file_dir> <word corpus dir>" << std::endl;
}

std::vector<std::string> getCorpusFiles(const std::string& path) {
  std::vector<std::string> files;
  for (const auto& file:fs::directory_iterator(path)) {
    files.push_back(file.path());
  }
  return files;
}

} // anonymous namespace

int main(int argc, char** argv) {
  if (argc<2) {
    usage();
    return -1;
  }
  const std::string ignored_corpus{argv[1]};
  const std::string text_corpus{argv[2]};

  auto indexer = std::make_unique<Indexer>();
  indexer->processIgnoredWords(ignored_corpus);
  
  auto corpus_files{getCorpusFiles(text_corpus)};
  int doc_id = 1;
  for (const auto& file : corpus_files) {
    std::cout << "processing file: " << file << " id [" << doc_id << "]" << '\n';
    indexer->processFile(file, doc_id);
    ++doc_id;
  }

  indexer->summarize();
  // indexer.writeToDisk();
}
