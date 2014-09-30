#ifndef FunctionsAccessible_H__
# define FunctionsAccessible_H__

#include "error.h"

namespace cTVScript {

  class function : public Accessible{
  private:
    std::function<void(Parcel&)> function;
  };

};

#endif
