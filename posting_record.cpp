#include "posting_record.h"

bool PostingRecordCompare::operator()(const PostingRecord& a, const PostingRecord& b) const {
    return a.doc_id < b.doc_id;
}
