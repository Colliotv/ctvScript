/*
 * cTV work integerAccessor
 */

#ifndef IntegerAcccessor_H__
# define IntegerAcccessor_H__

#include "accessor.hh"

namespace cTVScript {
  template<typename integer>
  class IntegerAccessible : public Accessible{
  private:
    integer	accessible;
  };
};

#endif
