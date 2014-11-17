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
	  , parenthesis_operator, parenthesis_priorisation // cast_operator?
	  , parenthesis_operator_end, parenthesis_priorisation_end // cast_operator_end?
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
	operations::types	m_type;
	invalid_operand(operations::types t_left)
	  : std::runtime_error("invalid operation construction"), m_type(t_left) {}
      };

    public:
      class tree {
      private:
	struct node {
	  enum class type : int {none = 0, op, var, down, up};
	  struct node*	m_next;
	  node() : m_next(nullptr) {}

	  template<class T>
	  const T* get() const  { return dynamic_cast<T*>(this); }
	  virtual node::type getType() const { return node::type::none; }
	};

	struct op_node : node {
	  virtual node::type getType() const override { return node::type::op; }
	  operations::types m_type;
	  op_node(operations::types t_type) : m_type(t_type) {}
	};
	struct var_node : node {
	  virtual node::type getType() const override { return node::type::var; }
	};
	struct down_node : node {};
	
      private:
	int	m_level;
	node*	m_first;
	node*	m_last;

	parser::public_parser* m_parser;
      public:
	tree(parser::public_parser* t_parser) : m_level(0), m_first(nullptr), m_last(nullptr), m_parser(t_parser) {}

      private:
	void	addNode(node* t_node) {
	  if (m_first == nullptr) m_first = t_node, m_last = t_node;
	  else m_last->m_next = t_node, m_last = t_node;
	}
      public:
	bool	pushOperation(operations::types t_type) {
	  if (operations::m_op_specs.find(t_type) == m_op_specs.end())
	    return false; // TODO: throw unknown
	  const auto& _spec = m_op_specs.at(t_type);
	  if (_spec.m_associativity == specs::associativity::LtoR &&
	      (m_last == nullptr || m_last->getType() != node::type::var)) {
	    std::cout << static_cast<int>(m_last->getType()) << std::endl;
	    if (m_homonyms.find(t_type) != m_homonyms.end()) {
	      Ihomonyms* _h = m_homonyms.at(t_type);
	      for (size_t _it = 0;
		   _it < _h->getSize(); ++_it) {
		try {
		  pushOperation(_h->get(_it));
		} catch (invalid_operand) {/* ignore if fail */}
	      }
	    }
	    throw invalid_operand(t_type);
	  }
	  addNode(new op_node(t_type));
	  if (_spec.m_associativity == specs::associativity::RtoL)
	    return false;
	  return true;
	}
	void	pushValue() { addNode(new var_node()); }
	void	pushDown() {}
	void	pushUp() {}
	int	level() { return (0); }
      };

    private:
      struct specs{
	enum class associativity{none, LtoR, RtoL} m_associativity;
	int m_predecedence;
      };
      static const std::map<operations::types, operations::specs> m_op_specs;

    private:
      struct Ihomonyms {
	virtual operations::types get(size_t) = 0;
	virtual size_t getSize() = 0;
      };
      template<operations::types... all> struct homonyms;
      template<operations::types t_last>
      struct homonyms<t_last> : Ihomonyms{
	static const operations::types		m_type = t_last;
	static const size_t			m_size = 1;
	virtual operations::types	get(size_t n) override {
	  if (n > 0)
	    throw std::out_of_range("in homonyms extension out of range access");
	  return (t_last);
	}
	virtual size_t			getSize() override { return m_size; }
      };
      template<operations::types t_prim, operations::types ...t_rest>
      struct homonyms<t_prim, t_rest...> : Ihomonyms{
	static const operations::types		m_type = t_prim;
	static const size_t			m_size = sizeof...(t_rest) + 1;
	struct homonyms<t_rest...>		m_next;
	virtual operations::types	get(size_t n) override { return (n > 0 ? m_next.get(n-1) : m_type); }
	virtual size_t			getSize() override { return m_size; }
      };
      static const std::map<operations::types, Ihomonyms*> m_homonyms;

    };

    const std::map<operations::types, operations::specs> operations::m_op_specs ( {
	{types::new_operator,			{specs::associativity::RtoL    , 3}}
	,{types::delete_operator,		{specs::associativity::RtoL    , 3}}
	,{types::scope_resolution,		{specs::associativity::LtoR    , 1}}
	,{types::parenthesis_operator,		{specs::associativity::LtoR    , 2}}
	,{types::parenthesis_priorisation,	{specs::associativity::none    , 1}}
	,{types::ternary,			{specs::associativity::RtoL    , 2}}
	,{types::logical_or,			{specs::associativity::LtoR    , 14}}
	,{types::logical_and,			{specs::associativity::LtoR    , 13}}
	,{types::bitwise_and,			{specs::associativity::LtoR    , 10}}
	,{types::bitwise_or,			{specs::associativity::LtoR    , 12}}
	,{types::bitwise_xor,			{specs::associativity::LtoR    , 11}}
	,{types::left_shift,			{specs::associativity::LtoR    , 7}}
	,{types::right_shift,			{specs::associativity::LtoR    , 7}}
	,{types::equality,			{specs::associativity::LtoR    , 9}}
	,{types::nequality,			{specs::associativity::LtoR    , 9}}
	,{types::superior,			{specs::associativity::LtoR    , 8}}
	,{types::equal_or_superior,		{specs::associativity::LtoR    , 8}}
	,{types::equal_or_inferior,		{specs::associativity::LtoR    , 8}}
	,{types::inferior,			{specs::associativity::LtoR    , 8}}
	,{types::addition,			{specs::associativity::LtoR    , 6}}
	,{types::substraction,			{specs::associativity::LtoR    , 6}}
	,{types::multiplication,		{specs::associativity::LtoR    , 5}}
	,{types::division,			{specs::associativity::LtoR    , 5}}
	,{types::modulo,			{specs::associativity::LtoR    , 5}}
	,{types::struct_ref,			{specs::associativity::LtoR    , 2}}
	,{types::struct_deref,			{specs::associativity::LtoR    , 2}}
      });

    const std::map<operations::types, operations::Ihomonyms*> operations::m_homonyms ( {
	{types::parenthesis_operator, new homonyms<types::parenthesis_priorisation>()}
      } );

  };
};

#endif
