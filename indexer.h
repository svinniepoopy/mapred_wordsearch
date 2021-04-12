#ifndef INDEXER_H
#define INDEXER_H

#include "index.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <unordered_set>

class Indexer {
  public:

    Indexer():do_scrub{false} {}

    void processIgnoredWords(const std::string& filename);

    bool processFile(const std::string& file, const int doc_id);

    void summarize() const;

    void writeToDisk();

  private:
    void processLine(const std::string& line, const int pagenum, const int doc_id);
    
    bool do_scrub;
    std::unordered_set<std::string> ignored_words; 
    std::unique_ptr<Index> index = std::make_unique<Index>();
};

#endif // INDEXER_H
