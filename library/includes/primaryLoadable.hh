/*
 * cTV work integerLoadable
 */

#ifndef IntegerLoadable_H__
# define IntegerLoadable_H__

#include "helper.hh"
#include "patternConstructor.hh"

#include "Loadable.hh"
#include "key.hh"

namespace cTVScript {

  class stringLoadable : public Loadable {
    DEFAULT_VALUE_DATA(std::string);
    MAKE_CONVERTER(std::string,);

  public:
    DEFAULT_VALUE_CONSTRUCTOR(stringLoadable, std::string, "");
    DEFAULT_LOCK_USE(std::string);
    DEFAULT_VALUE_GETTER();

    COMPARAND_OPERATOR(==);

    ASSIGN_OPERATOR(stringLoadable);
  };

  template<typename type, typename isFloating = void>
  class primaryLoadable;

  template<typename type>
  class primaryLoadable<type,
			typename std::enable_if<std::is_floating_point<type>
						::value>::type>
    : public Loadable {
    DEFAULT_VALUE_DATA(type);
    MAKE_CONVERTER(type, Helper::FromString<type>);

  public:
    DEFAULT_VALUE_CONSTRUCTOR(primaryLoadable, type, 0);
    DEFAULT_LOCK_USE(type);
    DEFAULT_VALUE_GETTER(std::to_string);

  public:
    COMPARAND_OPERATOR(==);
    COMPARAND_OPERATOR(< );
    COMPARAND_OPERATOR(> );
    COMPARAND_OPERATOR(<=);
    COMPARAND_OPERATOR(>=);

    ASSIGN_OPERATOR(primaryLoadable<type>);

    MATHEMATICAL_OPERATOR(+, primaryLoadable<type>);
    MATHEMATICAL_OPERATOR(*, primaryLoadable<type>);

    MATHEMATICAL_WITH_REVERT_OPERATOR
    (/, primaryLoadable<type>, invertDiv);
    MATHEMATICAL_WITH_REVERT_OPERATOR
    (-, primaryLoadable<type>, invertSub);

    MATHEMATICAL_REVERT_OPERATOR
    (/, primaryLoadable<type>, invertDiv);
    MATHEMATICAL_REVERT_OPERATOR
    (-, primaryLoadable<type>, invertSub);    
  };

  template<typename type>
  class primaryLoadable<type,
			typename std::enable_if<std::is_integral<type>::value>::type>
    : public Loadable {
    DEFAULT_VALUE_DATA(type);
    MAKE_CONVERTER(type, Helper::FromString<type>);

  public:
    DEFAULT_VALUE_CONSTRUCTOR(primaryLoadable, type, 0);
    DEFAULT_LOCK_USE(type);
    DEFAULT_VALUE_GETTER(std::to_string);

  public:
    COMPARAND_OPERATOR(==);
    COMPARAND_OPERATOR(< );
    COMPARAND_OPERATOR(> );
    COMPARAND_OPERATOR(<=);
    COMPARAND_OPERATOR(>=);

    ASSIGN_OPERATOR(primaryLoadable<type>);

    MATHEMATICAL_OPERATOR(+, primaryLoadable<type>);
    MATHEMATICAL_OPERATOR(*, primaryLoadable<type>);

    MATHEMATICAL_WITH_REVERT_OPERATOR
    (/, primaryLoadable<type>, invertDiv);
    MATHEMATICAL_WITH_REVERT_OPERATOR
    (%, primaryLoadable<type>, invertMod);
    MATHEMATICAL_WITH_REVERT_OPERATOR
    (-, primaryLoadable<type>, invertSub);

    MATHEMATICAL_REVERT_OPERATOR
    (/, primaryLoadable<type>, invertDiv);
    MATHEMATICAL_REVERT_OPERATOR
    (%, primaryLoadable<type>, invertMod);
    MATHEMATICAL_REVERT_OPERATOR
    (-, primaryLoadable<type>, invertSub);
  };
};

#endif
