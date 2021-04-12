#ifndef UTIL_H
#define UTIL_H

#include <cctype>
#include <string>

namespace util {
    std::string scrub(const std::string& s) {
      std::string scrubbed;
      for (int i=0;i<s.size();++i) {
	if (std::ispunct(s[i])) {
	  continue;
	} else {
	  scrubbed += std::tolower(s[i]);
	}
      }
      return scrubbed;
    }
}

#endif // UTIL_H
