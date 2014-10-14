#ifndef PrimaryArray_h__
# define PrimaryArray_h__

#include "helper/patternConstructor.hh"
#include "helper/deduce.hh"

#include "loadable/primary.hh"

namespace cTVScript {

  namespace loadable {

    template <typename __stored_type__>
    class array : public Loadable {
      __stored_type__*	_array;
      size_t		size;

    public:
      NEGATE_VALUE_GETTER();

    public:
      array(const std::string& name, size_t _size)
	: Loadable(name), _array(new __stored_type__[_size]), size(_size) {}

    public:
      virtual Loadable* operator[](size_t _off) {
	if (_off >= size)
	  throw (out_of_bound(getName(), _off, size));
	return (new typename Helper::DeduceLoadableType< __stored_type__& >
		::type (std::to_string(_off), _array[_off]));
      }

      virtual __stored_type__* unlock() {
	return (_array);
      }

    };

  };
};


#endif
