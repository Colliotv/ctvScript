/*
 * cTV work integerLoadable
 */

#ifndef IntegerLoadable_H__
# define IntegerLoadable_H__

#include "helper.hh"
#include "patternConstructor.hh"

#include "Loadable.hh"

namespace cTVScript {

  class stringLoadable : public Loadable {
  private:
    std::string value;

  public:
    DEFAULT_VALUE_CONSTRUCTOR(stringLoadable, std::string, "");
    DEFAULT_LOCK_USE(std::string);
    DEFAULT_VALUE_GETTER();

    COMPARAND_OPERATOR(==,);

    ASSIGN_OPERATOR(, stringLoadable);
  };


  template<typename type, typename isFloating = void>
  class primaryLoadable;

  template<typename type>
  class primaryLoadable<type,
			typename std::enable_if<std::is_floating_point<type>
						::value>::type>
    : public Loadable {
  private:
    type	value;

  public:
    DEFAULT_VALUE_CONSTRUCTOR(primaryLoadable, type, 0);
    DEFAULT_LOCK_USE(type);
    DEFAULT_VALUE_GETTER(std::to_string);

  public:
    COMPARAND_OPERATOR(==, Helper::FromString<type>);
    COMPARAND_OPERATOR(< , Helper::FromString<type>);
    COMPARAND_OPERATOR(> , Helper::FromString<type>);
    COMPARAND_OPERATOR(<=, Helper::FromString<type>);
    COMPARAND_OPERATOR(>=, Helper::FromString<type>);

    ASSIGN_OPERATOR(Helper::FromString<type>, primaryLoadable<type>);

    MATHEMATICAL_OPERATOR(+, Helper::FromString<type>, primaryLoadable<type>);
    MATHEMATICAL_OPERATOR(*, Helper::FromString<type>, primaryLoadable<type>);

    MATHEMATICAL_WITH_REVERT_OPERATOR
    (/, Helper::FromString<type>, primaryLoadable<type>, invertDiv);
    MATHEMATICAL_WITH_REVERT_OPERATOR
    (-, Helper::FromString<type>, primaryLoadable<type>, invertSub);

    MATHEMATICAL_REVERT_OPERATOR
    (/, Helper::FromString<type>, primaryLoadable<type>, invertDiv);
    MATHEMATICAL_REVERT_OPERATOR
    (-, Helper::FromString<type>, primaryLoadable<type>, invertSub);    
  };

  template<typename type>
  class primaryLoadable<type,
			typename std::enable_if<std::is_integral<type>::value>::type>
    : public Loadable {
  private:
    type&	value;

  public:
    DEFAULT_VALUE_CONSTRUCTOR(primaryLoadable, type, 0);
    DEFAULT_LOCK_USE(type);
    DEFAULT_VALUE_GETTER(std::to_string);

  public:
    COMPARAND_OPERATOR(==, Helper::FromString<type>);
    COMPARAND_OPERATOR(< , Helper::FromString<type>);
    COMPARAND_OPERATOR(> , Helper::FromString<type>);
    COMPARAND_OPERATOR(<=, Helper::FromString<type>);
    COMPARAND_OPERATOR(>=, Helper::FromString<type>);

    ASSIGN_OPERATOR(Helper::FromString<type>, primaryLoadable<type>);

    MATHEMATICAL_OPERATOR(+, Helper::FromString<type>, primaryLoadable<type>);
    MATHEMATICAL_OPERATOR(*, Helper::FromString<type>, primaryLoadable<type>);

    MATHEMATICAL_WITH_REVERT_OPERATOR
    (/, Helper::FromString<type>, primaryLoadable<type>, invertDiv);
    MATHEMATICAL_WITH_REVERT_OPERATOR
    (%, Helper::FromString<type>, primaryLoadable<type>, invertMod);
    MATHEMATICAL_WITH_REVERT_OPERATOR
    (-, Helper::FromString<type>, primaryLoadable<type>, invertSub);

    MATHEMATICAL_REVERT_OPERATOR
    (/, Helper::FromString<type>, primaryLoadable<type>, invertDiv);
    MATHEMATICAL_REVERT_OPERATOR
    (%, Helper::FromString<type>, primaryLoadable<type>, invertMod);
    MATHEMATICAL_REVERT_OPERATOR
    (-, Helper::FromString<type>, primaryLoadable<type>, invertSub);
  };
};

#endif
