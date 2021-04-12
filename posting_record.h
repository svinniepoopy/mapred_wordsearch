#ifndef POSTING_RECORD_H
#define POSTING_RECORD_H

#include <utility>
#include <vector>

// first item is document id
// second item is the page number
// third is the freq
struct PostingRecord {
  PostingRecord(int id, int f):doc_id{id}, freq{f} {}
  int doc_id;
  int freq;
  // add frequency by pagenumber
  // std::vector<std::pair<int, int>> freq_by_pagenum;
};

struct PostingRecordCompare {
  bool operator()(const PostingRecord&, const PostingRecord&) const;
};

#endif // POSTING_RECORD_H
