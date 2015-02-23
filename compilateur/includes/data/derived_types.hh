#ifndef Derived_Types_h__
# define Derived_Types_h__

#include <iostream>

#include <string>
#include <map>

#include "data/types.hh"

namespace ctvscript {
  namespace byte_code {
    namespace data {
      namespace type {
	namespace derived {
	  class const_ {};
	  class reference_ {};
	  class pointeur_ {};
	  class array_ {};
	  class functor_ {};
	};

	namespace container {
	  /*
	   * used for high- level manipulation
	   */
	  class interface {
	  public:
	    virtual type::container::interface*		deep_copy() const = 0;
	  };

	  /*
	   * created with a base type (primary/struct)
	   */
	  class underived		: public interface {
	  private:
	    type::interface*		m_type;

	  public:
	    underived(type::interface* t_type)
	      : m_type(t_type->deep_copy()) {}
	    ~underived();

	  public:
	    virtual type::container::interface*		deep_copy() const {
	      return (new underived(m_type->deep_copy()));
	    }
	  };

	  /*
	   * created with a container_interface & a derivation type
	   */
	  template<typename __derived>
	  class derived			: public interface {
	  private:
	    container::interface*		m_derived_type;

	  public:
	    derived(container::interface* _derived_type)
	      : m_derived_type(_derived_type) {}
	    ~derived() {}

	  public:
	    virtual type::container::interface*		deep_copy() const {
	      return (new derived<__derived>(m_derived_type->deep_copy()));
	    }
	  };
	};

	/*
	 * a wrapper used for saving defined type
	 *	m_type	-> NULL if scope (namespace) ptr to derived type
	 *	m_is_scope -> if its a scope
	 *	m_table -> contained scope
	 */
	class wrapper;
	using map = std::map<std::string, type::wrapper>;
	class wrapper {
	private:
	  container::interface*	m_type;
	  bool			m_is_scope;
	  type::map		m_table;

	public:
	  bool			exist	(const std::string&) const;
	  const wrapper*	at	(const std::string&) const;
	  wrapper*		at	(const std::string&);

	private:
	  wrapper*		m_up;

	public:
	  void			setUp(wrapper*);
	  wrapper*		getUp();

	public:
	  bool			is_scope() const;

	public:
	  const container::interface*	get_type() const;

	public:
	  /* type */
	  wrapper(container::interface* t_type)
	    : m_type(t_type), m_is_scope(false), m_table(), m_up(NULL) {
	    std::cout << "type designed" << std::endl;
	  }
	
	  /* class */
	  wrapper(container::interface* t_type, type::map&& t_table)
	    : m_type(t_type), m_is_scope(true), m_table(t_table), m_up(NULL) {
	    std::cout << "class designed" << std::endl;
	    for (type::map::value_type& t : m_table)
	      t.second.setUp(this);
	  }

	  /* namespace */
	  wrapper(type::map&& t_table)
	    : m_type(NULL), m_is_scope(true), m_table(std::move(t_table)), m_up(NULL) {
	    std::cout << "scope designed" << std::endl;
	    for (type::map::value_type& t : m_table)
	      t.second.setUp(this);
	  }
	};

	extern wrapper					table;
	extern wrapper*					current_context;
      };
    };
  };
};

#endif
