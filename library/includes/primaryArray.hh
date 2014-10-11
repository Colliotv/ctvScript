#ifndef PrimaryArray_h__
# define PrimaryArray_h__

#include "patternConstructor.hh"

#include "typeToLoadable.hh"

namespace cTVScript {

  template <typename __stored_type__>
  class arrayLoadable : public Loadable {
    __stored_type__*	array;
    size_t		size;

  public:
    NEGATE_VALUE_GETTER();

  public:
    arrayLoadable(const std::string& name, size_t _size)
      : Loadable(name), array(new __stored_type__[_size]), size(_size) {}

  public:
    virtual Loadable* operator[](size_t _off) {
      if (_off >= size)
	throw (out_of_bound(getName(), _off, size));
      return (new typename Helper::DeduceLoadableType< __stored_type__& >
	      ::type (std::to_string(_off), array[_off]));
    }

    virtual __stored_type__* unlock(DestructibleKey key) {
      key->notify(this);
      return (array);
    }

  };
};


#endif
