#ifndef Y0_CCUTIL_STRING_STRINGUTIL_H
#define Y0_CCUTIL_STRING_STRINGUTIL_H

#include <algorithm>
#include <string>

namespace y0_ccutil {
  struct StringUtility {
    public:
      static bool IsStartsWith(const std::string &kstr,
                               const std::string &kprefix) {
        if (kstr.size() < kprefix.size())
          return false;

        return kstr.compare(0, kprefix.size(), kprefix) == 0;
      }
  };
} // y0_ccutil

#endif
