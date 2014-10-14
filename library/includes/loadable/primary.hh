/*
 * cTV work integerLoadable
 */

#ifndef IntegerLoadable_H__
# define IntegerLoadable_H__

#include "helper/helper.hh"
#include "helper/patternConstructor.hh"

#include "loadable/loadable.hh"

namespace cTVScript {

  namespace loadable{

    class string : public Loadable {
      DEFAULT_VALUE_DATA(std::string);
      MAKE_CONVERTER(std::string,);

    public:
      DEFAULT_VALUE_CONSTRUCTOR(string, std::string, "");
      DEFAULT_LOCK_USE(std::string);
      DEFAULT_VALUE_GETTER();

      COMPARAND_OPERATOR(==);

      ASSIGN_OPERATOR(string);
    };

    template<typename type, typename isFloating = void>
    class arithmetic;

    template<typename type>
    class arithmetic<type,
		     typename std::enable_if<std::is_floating_point<type>
					     ::value>::type>
      : public Loadable {
      DEFAULT_VALUE_DATA(type);
      MAKE_CONVERTER(type, Helper::FromString<type>);

    public:
      DEFAULT_VALUE_CONSTRUCTOR(arithmetic, type, 0);
      DEFAULT_LOCK_USE(type);
      DEFAULT_VALUE_GETTER(std::to_string);

    public:
      COMPARAND_OPERATOR(==);
      COMPARAND_OPERATOR(< );
      COMPARAND_OPERATOR(> );
      COMPARAND_OPERATOR(<=);
      COMPARAND_OPERATOR(>=);

      ASSIGN_OPERATOR(arithmetic<type>);

      MATHEMATICAL_OPERATOR(+, arithmetic<type>);
      MATHEMATICAL_OPERATOR(*, arithmetic<type>);

      MATHEMATICAL_WITH_REVERT_OPERATOR
      (/, arithmetic<type>, invertDiv);
      MATHEMATICAL_WITH_REVERT_OPERATOR
      (-, arithmetic<type>, invertSub);

      MATHEMATICAL_REVERT_OPERATOR
      (/, arithmetic<type>, invertDiv);
      MATHEMATICAL_REVERT_OPERATOR
      (-, arithmetic<type>, invertSub);    
    };

    template<typename type>
    class arithmetic<type,
		     typename std::enable_if<std::is_integral<type>::value>::type>
      : public Loadable {
      DEFAULT_VALUE_DATA(type);
      MAKE_CONVERTER(type, Helper::FromString<type>);

    public:
      DEFAULT_VALUE_CONSTRUCTOR(arithmetic, type, 0);
      DEFAULT_LOCK_USE(type);
      DEFAULT_VALUE_GETTER(std::to_string);

    public:
      COMPARAND_OPERATOR(==);
      COMPARAND_OPERATOR(< );
      COMPARAND_OPERATOR(> );
      COMPARAND_OPERATOR(<=);
      COMPARAND_OPERATOR(>=);

      ASSIGN_OPERATOR(arithmetic<type>);

      MATHEMATICAL_OPERATOR(+, arithmetic<type>);
      MATHEMATICAL_OPERATOR(*, arithmetic<type>);

      MATHEMATICAL_WITH_REVERT_OPERATOR
      (/, arithmetic<type>, invertDiv);
      MATHEMATICAL_WITH_REVERT_OPERATOR
      (%, arithmetic<type>, invertMod);
      MATHEMATICAL_WITH_REVERT_OPERATOR
      (-, arithmetic<type>, invertSub);

      MATHEMATICAL_REVERT_OPERATOR
      (/, arithmetic<type>, invertDiv);
      MATHEMATICAL_REVERT_OPERATOR
      (%, arithmetic<type>, invertMod);
      MATHEMATICAL_REVERT_OPERATOR
      (-, arithmetic<type>, invertSub);
    };

  };
};

#endif
