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

	info(const char* t_name)
	  : m_name(t_name), m_isResolved(false) {}

	virtual info* clone() const { return (new info(m_name.c_str())); }
	virtual void registerModifier(modifier) {}
      };
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
	_type->registerModifier(t_modifier_type);
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
	m_types_list({}) ,
	m_modifier_map({})
      {}
      static type* get() {
	static type* _type= new type();
	return (_type);
      }
    };
  };
};

#endif
