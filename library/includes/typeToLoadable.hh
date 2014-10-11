#ifndef TypeToLoadable_h__
# define TypeToLoadable_h__

/* defined in objectLoadable.hh */
class ObjectLoadable;
class Context;

/* defined in primaryLoadable.hh*/
template<typename t>
class primaryAcccessible;
class stringLoadable;

/* defined in functionLoadable.hh*/
class functionLoadable;
struct parametersPack;

/* defined in LoadableReferenceWrapper */
template<typename t>
class ReferenceWrapper;

/* defined in arrayLoadable.hh */
template<typename t>
class arrayLoadable;


namespace cTVScript {

  namespace Helper {

    template<typename _type>
    struct DeduceLoadableType;

    template<typename _type>
    struct DeduceLoadableType {
      typedef primaryLoadable<_type> type;
    };

    template<typename _type>
    struct DeduceLoadableType<_type&> {
      typedef ReferenceWrapper< primaryLoadable<_type> > type;
    };

    template<>
    struct DeduceLoadableType<std::string> {
      typedef stringLoadable type;
    };

    template<>
    struct DeduceLoadableType<std::string&> {
      typedef ReferenceWrapper< stringLoadable > type;
    };

  };

};

#endif
