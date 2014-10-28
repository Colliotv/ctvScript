#ifndef Type_h__
# define Type_h__

#include <vector>

namespace ctvscript {
  namespace architecture {

    class type {
    public:
      struct info {
	std::string m_name;
	bool m_isResolved;

	info(const char* t_name)
	  : m_name(t_name), m_isResolved(false) {}

	void registerModifier() {}
      };

      enum class modifier : char {
	none = -1
	  , _signed = 0x01 , _unsigned  = 0x02
	  , _const  = 0x04 , _non_const = 0x08
	  , _long   = 0x10
      };

    private:
      std::vector<info*> m_types_list;
      std::map<std::string, modifier> m_modifier_map;
    public:
      modifier	getModifier(const char* t_potent_modifier, modifier t_modifier = modifier::none) {
	auto mod = m_modifier_map.find(t_potent_modifier);
	if ((mod) != m_modifier_map.end())
	  return (t_modifier == modifier::none) ? ((*mod).second) : (static_cast<modifier>(static_cast<char>(t_modifier)
											   | static_cast<char>((*mod).second)));
	return (modifier::none);
      }
      const info*	getTypeInfo(const char* t_type_name) {
	for (auto type : m_types_list)
	  if (type->m_name == t_type_name)
	    return (type);
	return (NULL);
      }
      void		registerUndefinedTypeInfo(const char* t_type_name) {
	m_types_list.push_back(new info(t_type_name));
      }

    public:
      type()
	:
	m_types_list({}) ,
	m_modifier_map({})
      {}
    };
  };
};

#endif
