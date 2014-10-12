#ifndef TypeToLoadable_h__
# define TypeToLoadable_h__

namespace loadable {

  /* defined in object.hh */
  class object;
  class Context;

  /* defined in primary.hh*/
  template<typename t>
  class arithmetic;
  class string;

  /* defined in function.hh*/
  class function;
  struct parametersPack;

  /* defined in ReferenceWrapper.hh */
  template<typename t>
  class ReferenceWrapper;

  /* defined in array.hh */
  template<typename t>
  class array;

};

namespace cTVScript {

  namespace Helper {

    template<typename _type>
    struct DeduceLoadableType;

    template<typename _type>
    struct DeduceLoadableType {
      typedef loadable::arithmetic<_type> type;
    };

    template<typename _type>
    struct DeduceLoadableType<_type&> {
      typedef loadable::ReferenceWrapper< loadable::arithmetic<_type> > type;
    };

    template<>
    struct DeduceLoadableType<std::string> {
      typedef loadable::string type;
    };

    template<>
    struct DeduceLoadableType<std::string&> {
      typedef loadable::ReferenceWrapper< loadable::string > type;
    };

  };

};

#endif
