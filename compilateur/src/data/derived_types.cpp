#include "data/derived_types.h"

namespace ctvscript {
  namespace byte_code {
    namespace data {
      namespace type {

	/*
	 * Wrapper Definition
	 */
	bool		wrapper::exist(const std::string& t_key) const {
	  return (m_table.find(t_key) != m_table.end());
	};

	const wrapper*	wrapper::at(const std::string& t_key) const {
	  if (!exist(t_key))
	    return NULL; // (later throw)
	  return (&m_table.at(t_key));
	};

	wrapper*	wrapper::at(const std::string& t_key) {
	  if (!exist(t_key))
	    return NULL; // (later throw)
	  return (&m_table.at(t_key));
	};

	
	void		wrapper::setUp(wrapper* t_up)	{ m_up = t_up; }
	wrapper*	wrapper::getUp()		{ return (m_up); }

	bool		wrapper::is_scope() const	{ return m_is_scope; }

	container::interface*	wrapper::get_type()	{ return m_type; }

	/*
	 * Table Definitions
	 */
	wrapper	table(type::map({
	      {"int",		{new container::underived(new primary<false, true, 4>())} },
	      {"signed int",	{new container::underived(new primary<false, true, 4>())} },
	      {"unsigned int",	{new container::underived(new primary<false, false, 4>())} },
	      {"double",	{new container::underived(new primary<true, true, 8>())} },
	      {"string",	{new container::underived(new string())} },
	      }));

	/*
	 * Current Context
	 */
	wrapper*		current_context(&table);
      };
    };
  };
};
