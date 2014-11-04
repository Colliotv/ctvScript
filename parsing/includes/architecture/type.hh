#ifndef Type_h__
# define Type_h__

#include <vector>

namespace ctvscript {
  namespace architecture {

    class type {
    public:
      enum class modifier : char {
	none = -1
	  , _signed = 0x01 , _unsigned  = 0x02
	  , _const  = 0x04 , _non_const = 0x08
	  , _long   = 0x10
      };

      struct info {
	std::string m_name;
	bool m_isResolved;

	info(const char* t_name, bool t_isResolved = false)
	  : m_name(t_name), m_isResolved(t_isResolved) {}

	virtual info* clone() const { return (new info(m_name.c_str())); }
	virtual bool  registerModifier(modifier) { return (false); }
	virtual bool  isNestedType(const std::string&) const { return (false); }
	virtual bool  isConstructor(const std::string&) const  { return (false); }
      };

      static bool is_constructor(const info* t_type, const std::string& t_oth) { return (t_type->isConstructor(t_oth)); }
      static bool is_nested_type(const info* t_type, const std::string& t_oth) { return (t_type->isNestedType(t_oth)); }

      struct namespace_info : info {
	std::map<std::string, const type::info*> m_nested_types;
	namespace_info(const char* t_name)
	  : info(t_name, true) {}
	virtual bool isNestedType(const std::string& t_type) const override {
	  return (m_nested_types.find(t_type) != m_nested_types.end());
	}
	info* make_nested_type(const std::string& t_type) const {
	  if (m_nested_types.find(t_type) != m_nested_types.end())
	    return (m_nested_types.at(t_type)->clone());
	  return (nullptr);
	}
      };

      struct class_info : namespace_info {
	std::string m_class_name;

	class_info(const char* t_class_name)
	  : namespace_info(t_class_name), m_class_name(t_class_name) {}
	virtual bool isConstructor(const std::string& t_id) const override { return (m_class_name == t_id); }
      };

      static info* make_nested_type(const info* t_potent_namespace, const std::string& t_type) {
	const namespace_info* _namespace = dynamic_cast<const namespace_info*>(t_potent_namespace);
	if (_namespace == nullptr)
	  return (nullptr);
	return (_namespace->make_nested_type(t_type));
      }

      struct int_info : info { int_info() : info("int", true) {}
	virtual bool  isConstructor(const std::string& t_t) const override  { return (t_t == "int"); }
      };
      struct byte_info : info { byte_info() : info("byte", true) {}
	virtual bool  isConstructor(const std::string& t_t) const override  { return (t_t == "byte"); }
      };
      struct float_info : info { float_info() : info("float", true) {}
      	virtual bool  isConstructor(const std::string& t_t) const override  { return (t_t == "float"); }
      };
      struct void_info : info { void_info() : info("void", true) {}
	virtual bool  isConstructor(const std::string& t_t) const override  { return (t_t == "void"); }
      };
      struct string_info : info { string_info() : info("string", true) {}
	virtual bool  isConstructor(const std::string& t_t) const override  { return (t_t == "string"); }
      };
      struct char_info : info { char_info() : info("char", true) {}
	virtual bool  isConstructor(const std::string& t_t) const override  { return (t_t == "char"); }
      };

      struct pointeur_info : info {
	info*	m_subType;
	bool	m_const;

	pointeur_info(info* t_subType)
	  : info((t_subType->m_name + "*").c_str(), true),
	    m_subType(t_subType), m_const(false) {}
	virtual info* clone() const override { return (new pointeur_info(m_subType->clone())); }
	virtual bool registerModifier(modifier t_modifier) override {
	  if (t_modifier != modifier::_const)
	    return (false);
	  m_const = true;
	  return (true);
	}
      };
      static pointeur_info* make_pointeur(info* t_type) { return (new pointeur_info(t_type)); }

      struct callable_info : info {
	info*			m_return_type;
	std::vector<info*>	m_parameters_type;

	callable_info(info* t_return_type)
	  : info((t_return_type->m_name + "()").c_str(), true),
	    m_return_type(t_return_type) {}
	virtual info* clone() const override {
	  callable_info* _info = new callable_info(m_return_type);
	  for (auto _type : m_parameters_type)
	    _info->registerParameters(_type->clone());
	  return (_info);
	}
	virtual bool registerModifier(modifier) override {
	  return (false);
	}
	void registerParameters(info* t_param_type) {
	  m_parameters_type.push_back(t_param_type);
	}
      };
      static callable_info* make_callable(info* t_return_type) {
	return (new callable_info(t_return_type));
      }

      struct array_info : info {
	info*	m_subType;
	size_t	m_size;
	bool	m_const;

	array_info(info* t_subType, size_t t_size)
	  : info((t_subType->m_name + "[" + std::to_string(t_size) + "]").c_str(), true),
	    m_subType(t_subType), m_size(t_size), m_const(false) {}

	virtual info* clone() const { return (new array_info(m_subType->clone(), m_size)); }
	virtual bool registerModifier(modifier t_modifier) override {
	  if (t_modifier != modifier::_const)
	    return (false);
	  m_const = true;
	  return (true);
	}
      };
      static array_info* make_array(info* t_type, size_t t_size) { return (new array_info(t_type, t_size)); }

    private:
      std::vector<info*> m_types_list;
      std::map<std::string, modifier> m_modifier_map;
      modifier	m_getModifier(const char* t_potent_modifier, modifier t_modifier = modifier::none) {
	auto mod = m_modifier_map.find(t_potent_modifier);
	if ((mod) != m_modifier_map.end())
	  return (t_modifier == modifier::none) ? ((*mod).second) : (static_cast<modifier>(static_cast<char>(t_modifier)
											   | static_cast<char>((*mod).second)));
	return (modifier::none);
      }
      const info*	m_getTypeInfo(const char* t_type_name) {
	for (auto type : m_types_list)
	  if (type->m_name == t_type_name)
	    return (type);
	return (NULL);
      }
      void		m_registerImportedTypeInfo(const char* t_type_name) {
	m_types_list.push_back(new info(t_type_name));
      }
    public:
      static type::info*	make_type(const type::info* t_base_type, modifier t_modifier_type) {
	type::info* _type = t_base_type->clone();
	if (t_modifier_type != modifier::none && !_type->registerModifier(t_modifier_type))
	  return (NULL);
	return (_type);
      }
      static modifier		getModifier(const char* t_potent_modifier, modifier t_modifier = modifier::none) {
	return (get()->m_getModifier(t_potent_modifier, t_modifier));
      }

      static const info*	getTypeInfo(const char* t_type_name) {
	return (get()->m_getTypeInfo(t_type_name));
      }
    private:
      type()
	:
	m_types_list({
	    new info("auto")
	      , new int_info()
	      , new byte_info()
	      , new float_info()
	      , new void_info()
	      , new string_info()
	      , new char_info()
	  }) ,
	m_modifier_map({
	    {"" , modifier::none}
	    , {"signed"   ,	modifier::_signed}
	    , {"unsigned" ,	modifier::_unsigned}
	    , {"const"    ,	modifier::_const}
	    , {"long"     ,	modifier::_long}
	  })
      {}

      static type* get() {
	static type* _type= new type();
	return (_type);
      }
    };
  };
};

#endif
