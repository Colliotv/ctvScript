#ifndef Instruction_h__
# define Instruction_h__

namespace ctvscript {
  namespace architecture {
    namespace registers {
      class eax {};
    };

    class operations {
    public:
      enum class types : unsigned char {
	_default = 0, undefined = 0
	  , new_operator, delete_operator
	  , scope_resolution
	  , parenthesis_operator
	  , ternary
	  , logical_or, logical_and
	  , bitwise_or, bitwise_xor, bitwise_and
	  , equality, nequality
	  , superior, equal_or_superior
	  , inferior, equal_or_inferior
	  , addition, substraction
	  , left_shift, right_shift
	  , multiplication, division, modulo
	  , struct_deref
	  , struct_ref

      };

    public:
      struct lvalue_required : std::runtime_error {
	operations::types	m_type;
	lvalue_required(operations::types t_type) : std::runtime_error("need lvalue"), m_type(t_type) {}
      };

      struct const_assignement : std::runtime_error {

      };

      struct invalid_operand : std::runtime_error {
	operations::types	m_left_type;
	operations::types	m_added_type;
	invalid_operand(operations::types t_left, operations::types t_added)
	  : std::runtime_error("invalid operation construction"), m_left_type(t_left), m_added_type(t_added) {}
      };

    public:
      class tree {
      private:
	struct node {
	  struct node*	m_next;
	  node() : m_next(nullptr) {}

	  template<class T>
	  const T* get() { return dynamic_cast<T*>(this); }
	  template<class T>
	  const T* is() { return dynamic_cast<T*>(this) != nullptr;}
	};

	struct op_node : node {};
	struct var_node : node {};
	struct down_node : node {};
	
      private:
	int	m_level;

      public:
	void	pushOperation(operations::types) {}
	void	pushValue() {}
	void	pushDown() {}
	void	pushUp() {}
	int	level() { return (0); }
      };

    public:
      operations* get() {static operations* _this = new operations(); return (_this);}

    private:
      struct specs{
	bool m_pre, m_post; // later for ++ --
	enum post_size{_none = -1, _unknown = 0, _one = 1, _two = 2} m_post_size;
	int m_predecedence;
      };
      const std::map<operations::types, operations::specs> m_op_parameters;

      operations() :
	m_op_parameters({
	    {types::new_operator,		{false, true, specs::_one    , 3}}
	    ,{types::delete_operator,		{false, true, specs::_one    , 3}}

	    ,{types::scope_resolution,		{false, true, specs::_one    , 1}}

	    ,{types::parenthesis_operator,	{true,  true, specs::_unknown, 2}}
	    ,{types::ternary,			{true,  true, specs::_two    , 2}}

	    ,{types::logical_or,		{true,  true, specs::_one    , 14}}
	    ,{types::logical_and,		{true,  true, specs::_one    , 13}}

	    ,{types::bitwise_and,		{true,  true, specs::_one    , 10}}
	    ,{types::bitwise_or,		{true,  true, specs::_one    , 12}}
	    ,{types::bitwise_xor,		{true,  true, specs::_one    , 11}}

	    ,{types::left_shift,		{true,  true, specs::_one    , 7}}
	    ,{types::right_shift,		{true,  true, specs::_one    , 7}}

	    ,{types::equality,			{true,  true, specs::_one    , 9}}
	    ,{types::nequality,			{true,  true, specs::_one    , 9}}

	    ,{types::superior,			{true,  true, specs::_one    , 8}}
	    ,{types::equal_or_superior,		{true,  true, specs::_one    , 8}}
	    ,{types::equal_or_inferior,		{true,  true, specs::_one    , 8}}
	    ,{types::inferior,			{true,  true, specs::_one    , 8}}

	    ,{types::addition,			{true,  true, specs::_one    , 3}}
	    ,{types::substraction,		{true,  true, specs::_one    , 3}}

	    ,{types::multiplication,		{true,  true, specs::_one    , 3}}
	    ,{types::division,			{true,  true, specs::_one    , 3}}
	    ,{types::modulo,			{true,  true, specs::_one    , 3}}

	    ,{types::struct_ref,		{true,  true, specs::_one    , 2}}
	    ,{types::struct_deref,		{true,  true, specs::_one    , 2}}
	  }) {}
    };
  };
};

#endif
