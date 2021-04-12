#ifndef QUERY_PROCESSOR_H
#define QUERY_PROCESSOR_H

#include "index.h"

#include <memory>
#include <string>
#include <vector>

class QueryProcessor {
  public:
    bool loadIndex(const std::string& indexfile);
    void report(const std::vector<std::string>&);
  private:  
    std::unique_ptr<Index> index = std::make_unique<Index>();
};

#endif // QUERY_PROCESSOR
