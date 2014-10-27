#ifndef Type_h__
# define Type_h__

#include <vector>

namespace ctvscript {
  namespace architecture {

    class types {
    public:
      struct info {
	std::string m_name;
	bool m_isResolved;

	info(const char* t_name)
	  : m_name(t_name), m_isResolved(false) {}
      }

    private:
      std::vector<info*> types_list;
    public:
      const info*	getTypeInfo(const char* t_type_name) {
	for (auto type : types_list)
	  if (type.m_name == t_type_name)
	    return (type);
	return (NULL);
      }
    };

  };
};

#endif
