#ifndef Node_h__
# define Node_h__

#include <sstream>

#include "architecture/type.hh"

namespace ctvscript {
  namespace architecture{

    class node {
    public:
      virtual char getByteInfo() const { return (0x0); }
      virtual const type::info* eax_type() const { return (NULL); }
    };

    /* Variable */
    class variable_node : public node {
    private:
      type::info* m_type;
      std::string m_name;

    public:
      variable_node(type::info* t_type, std::string& t_name)
	: m_type(t_type), m_name(t_name) {}

      type::info*	getTypeInfo() { return (m_type->clone()); }
      const type::info* getConstTypeInfo() { return (m_type); }
      const std::string& getName() { return (m_name); }
    };

    /* variable access */
    class variable_accessor_node : public node {
    private:
      variable_node* m_var;
    public:
      variable_accessor_node()
	: m_var(nullptr) {}
      variable_accessor_node(variable_node* t_var)
	: m_var(t_var) {}
    };

    /* context node */
    class context_node : public node {
    private:
      std::list< variable_node* > m_var_context;
      std::list< node* > m_context;
      context_node*	m_superior_context;

    public:
      context_node(const std::list<node*>& t_context)
	: m_var_context({}), m_context(std::move(t_context)), m_superior_context(nullptr) {
	for (auto _potent_var : m_context) {
	  if (dynamic_cast<variable_node*>(_potent_var) != nullptr)
	    m_var_context
	      .push_back(dynamic_cast<variable_node*>(_potent_var));
	}
      }
      context_node()
	: m_var_context({}), m_context({}), m_superior_context(nullptr) {}
      
      void	add_superior_context(context_node* t_sup) {
	m_superior_context = t_sup;
      }

      context_node*	get_superior_context() { return (m_superior_context); }

      void	append_context(const std::list<node*>&& t_context) {
	std::move(std::begin(t_context), std::end(t_context),
		  std::back_inserter(m_context));
      }

      void	addVariable(variable_node* t_v) {
	m_var_context.push_back(t_v);
      }

      variable_node* getVariableByName(const std::string& t_name) {
	for (auto _variable : m_var_context) {
	  if (_variable->getName() == t_name)
	    return (_variable);
	}
	if (m_superior_context != nullptr)
	  return (m_superior_context->getVariableByName(t_name));
	return (nullptr);
      }

      variable_accessor_node* makeVariableAccessByName(const std::string& t_name) {
	for (auto _variable : m_var_context) {
	  if (_variable->getName() == t_name)
	    return (new variable_accessor_node(_variable));
	}
	if (m_superior_context != nullptr)
	  return (m_superior_context->makeVariableAccessByName(t_name));
	return (nullptr);
      }
    };

    /* Raw Value */
    class raw_value_node : public variable_accessor_node {};

    class raw_string_node : public raw_value_node{
    private:
      type::string_info* m_type;
      std::string	 m_value;

    public:
      raw_string_node(const std::string& t_value)
	: m_type(new architecture::type::string_info()), m_value(t_value) {}

      virtual const type::info* eax_type() const { return (m_type); }      
    };

    class raw_unsigned_integer_node : public raw_value_node{
    private:
      type::int_info*		m_type;
      unsigned long int		m_value;

    public:
      raw_unsigned_integer_node(unsigned long int t_value)
	: m_type(new architecture::type::int_info()), m_value(t_value) {
	m_type->registerModifier(architecture::type::modifier::_long);
      }

      virtual const type::info* eax_type() const { return (m_type); }      
    };

    class raw_binary_node : public raw_unsigned_integer_node{
    private:
      unsigned long int format(const std::string& t_value) {
	unsigned long int _value = 0;
	for (auto bin : t_value) {
	  if (bin == '1')
	    _value+=1;
	  _value*=2;
	} 
	return (_value);
      }
    public:
      raw_binary_node(const std::string& t_value)
	: raw_unsigned_integer_node(format(t_value)) {}
    };

    class raw_hexadecimal_node : public raw_unsigned_integer_node{
    private:
      unsigned long int format(const std::string& t_value) {
	unsigned long int _value;
	std::istringstream ss(t_value); ss >> std::hex >> _value;
	return (_value);
      }
    public:
      raw_hexadecimal_node(const std::string& t_value)
	: raw_unsigned_integer_node(format(t_value)) {}
    };

    class raw_character_node : public raw_value_node{
    private:
      type::char_info*		m_type;
      unsigned char		m_value;

    public:
      raw_character_node(char t_value)
	: m_type(new architecture::type::char_info()), m_value(t_value) {}

      virtual const type::info* eax_type() const { return (m_type); }      
    };

    class raw_floating_node : public raw_value_node{
    private:
      type::float_info*		m_type;
      double			m_value;

    public:
      raw_floating_node(double t_value)
	: m_type(new architecture::type::float_info()), m_value(t_value) {}

      virtual const type::info* eax_type() const { return (m_type); }      
    };

    class raw_integer_node : public raw_value_node{
    private:
      type::int_info*		m_type;
      long int			m_value;

    public:
      raw_integer_node(long int t_value)
	: m_type(new architecture::type::int_info()), m_value(t_value) {}

      virtual const type::info* eax_type() const { return (m_type); }      
    };


    /* type node : used for type declaration only*/
    class type_node	: public node {
    private:
      type::info* m_type;

    public:
      type_node(type::info* t_type)
	: m_type(t_type) {}

      type::info*	getTypeInfo() {return m_type;}
    };

    /* symbol node */
    class function_node : public variable_node {
    private:
      type::callable_info*		m_type;
      std::list< type::info* >		m_parameters_type;

    private:
      context_node*	m_body;

    public:
      function_node(type::info* t_return_type, std::string& t_name)
	: variable_node(m_type = type::make_callable(t_return_type),
			t_name) {}
      void registerParameters(type::info* t_param) { m_type->registerParameters(t_param); }
      void setBody(context_node* t_body) { m_body = t_body; }

      virtual const type::info* eax_type() const override { return (m_type); }      
    };


    /* operations nodes */
    class operations_node : public node {
      
    };

    class mathematical_add_node : public node {

    };
  };
};

#endif
