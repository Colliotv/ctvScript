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
      };
      enum class modifier : char {
	none
	  , _signed, _unsigned
	  , _const , _non_const
	  , _long
      };

    private:
      std::vector<info*> types_list;
      static const std::map<std::string, modifier> m_modifier_map;
    public:
      const modifier	getModifier(const char* t_potent_prefix) {
	if ((auto mod = m_modifier_map.find(t_potent_prefix)) != m_modifier_map.end())
	  return *mod;
	return (none);
      }
      const info*	getTypeInfo(const char* t_type_name) {
	for (auto type : types_list)
	  if (type->m_name == t_type_name)
	    return (type);
	return (NULL);
      }
    };

  };
};

#endif
