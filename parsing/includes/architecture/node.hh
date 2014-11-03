#ifndef Node_h__
# define Node_h__

#include "architecture/type.hh"

namespace ctvscript {
  namespace architecture{

    class node {
    public:
      virtual char getByteInfo() { return (0x0); }
    };

    class variable_node : public node {
    private:
      type::info* m_type;
      std::string m_name;

    public:
      variable_node(type::info* t_type, std::string& t_name)
	: m_type(t_type), m_name(std::move(t_name)) {}

      type::info*	getTypeInfo() { return (m_type->clone()); }
      const type::info* getConstTypeInfo() { return (m_type); }
    };

    class variable_node;
    class context_node : public node {
    private:
      std::list< variable_node* > m_var_context;
      std::list< node* > m_context;

    public:
      context_node(const std::list<node*>& t_context)
	: m_var_context({}), m_context(std::move(t_context)) {
	for (auto _potent_var : m_context)
	  if (dynamic_cast<variable_node*>(_potent_var) != nullptr)
	    m_var_context
	      .push_back(dynamic_cast<variable_node*>(_potent_var));
      }
      context_node()
	: m_var_context({}), m_context({}) {}
      

      void	append_context(const std::list<node*>&& t_context) {
	std::move(std::begin(t_context), std::end(t_context),
		  std::back_inserter(m_context));
      }
    };

    class type_node	: public node {
    private:
      type::info* m_type;

    public:
      type_node(type::info* t_type)
	: m_type(t_type) {}

      type::info*	getTypeInfo() {return m_type;}
    };

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
    };

  };
};

#endif
