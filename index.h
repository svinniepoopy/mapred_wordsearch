#ifndef INDEX_H
#define INDEX_H

#include "posting_record.h"

#include <ostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
#include <utility>

class Index {
  public:
    void add(const std::string&, const int pagenum, const int doc_id);

    void updatePostingsList(int doc_id);

    bool loadPostings(const std::string& indexfile);    

    bool find(const std::string& w);

    std::vector<std::pair<int, int>> get(const std::string& w);

    inline size_t size() const {
      return postings_list.size();
    }

    friend std::ostream& operator<<(std::ostream& os, const Index& idx);

  private:
    // mapping from doc_id to {word:freq}
    std::unordered_map<int, std::unordered_map<std::string, int>> doc2word;

    // mapping from word to an ordered list of records 
    std::unordered_map<std::string, std::set<PostingRecord, PostingRecordCompare>> postings_list;
};

#endif // INDEX_STORE_H
