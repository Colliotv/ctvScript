/*
 * cTV work integerAccessor
 */

#ifndef IntegerLoadable_H__
# define IntegerLoadable_H__

#include "accessor.hh"

namespace cTVScript {

  template<typename prim>
  class primaryLoadable : public Loadable {
  private:
    prim&	loadable;
  public:
    primaryLoadable(prim& _p, std::string& name)
      : Loadable(name), loadable(_p) {
      registerType(Helper::TypePriorityFor<prim>::get());
    }
  };

  template<typename prim>
  primaryLoadable<prim>* makePrimaryLoadable(prim& _p, std::string& name) {
    return (new primaryLoadable<prim>(_p, name));
  }

};

#endif
