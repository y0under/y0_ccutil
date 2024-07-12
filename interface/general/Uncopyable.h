#ifndef Y0_CCUTIL_INTERFACE_GENERAL_UNCOPYABLE_H
#include Y0_CCUTIL_INTERFACE_GENERAL_UNCOPYABLE_H

namespace y0_ccutil {

  /**
   * @brief forbidden copy for sub class
   * do not neet inheritance as public
   * inheritance as private is enough
   */
  class Uncopyable {
    protected:
      Uncopyable(){}
      // do not nead virtual
      ~Uncopyable(){}

    private:
      Uncopyable(const Uncopyable&);
      Uncopyable &operator=(const Uncopyable&);
  };
}  // namespace y0_ccutil

#endif
