/*
 * cTV work integerAccessor
 */

#ifndef IntegerLoadable_H__
# define IntegerLoadable_H__

#include "helper.hh"

#include "Accessor.hh"

#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) DO_PRAGMA(message ("\nTODO - [" __FILE__ "]:" #x))

namespace cTVScript {

  class stringLoadable : public Loadable {
  private:
    std::string value;

  public:
    stringLoadable(const std::string& name, const std::string& _v = "") 
      : Loadable(name), value(_v) {
      registerPriority(Helper::TypePriorityFor<std::string>::get());
    }

  public:
    std::string  getLockedValue() { return value; }
    std::string& unlock(std::shared_ptr<cTVScript::Key> key) {
      key->notify(this);
      return value;
    }
  };

  template<typename type>
  class primaryLoadable : public Loadable {
  private:
    type&	value;

  public:
    primaryLoadable(const std::string& name, type _p = 0)
      : Loadable(name), value(_p) {
      registerPriority(Helper::TypePriorityFor<type>::get());
    }
    ~primaryLoadable() {}

  public:
    type  getLockedValue() { return value; }
    type& unlock(std::shared_ptr<cTVScript::Key> key) {
      key->notify(this);
      return value;
    }
  };
};

#endif
