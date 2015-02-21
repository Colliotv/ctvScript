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

	
	void		wrapper::setUp(const wrapper* t_up)	{ m_up = t_up; }
	const wrapper*	wrapper::getUp() const			{ return (m_up); }

	/*
	 * Table Definitions
	 */
	wrapper	table(type::map({
	      {"int",		{new container::underived(new primary<false, true, 4>())} },
	      {"signed int",	{new container::underived(new primary<false, true, 4>())} },
	      {"unsigned int",	{new container::underived(new primary<false, false, 4>())} },
	      {"double",		{new container::underived(new primary<true, true, 8>())} },
	      { "std", type::map({
		    {"size_t",		{new container::underived(new primary<false, false, 8>())} },
		      }) },
	      }));

	/*
	 * Current Context
	 */
	wrapper*		current_context(&table);
      };
    };
  };
};
