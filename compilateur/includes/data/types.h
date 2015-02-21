#ifndef type_data_h__
# define type_data_h__

# include <map>
# include <cstdlib>

/*
 * [ctv todo]
 *   no definition in .h
 */
namespace ctvscript {
  namespace byte_code {
    namespace data {
      namespace type {

	namespace container {
	  class interface;
	};

	class interface {
	public:
	  virtual type::interface*		deep_copy() const = 0;
	};

	template<bool m_is_floating, bool m_is_signed, unsigned char m_type_size>
	class primary : public interface {
	public:

	public:
	  virtual type::interface*		deep_copy() const {
	    return (new primary<m_is_floating, m_is_signed, m_type_size>());
	  }
	};

	class string : public interface {
	public:


	public:
	  virtual type::interface*		deep_copy() const {
	    return (new string());
	  }
	};

	class structure : public interface {
	private:
	  std::map<std::string, container::interface>	m_private_members;
	  std::map<std::string, container::interface>	m_public_members;

	public:
	  structure(std::map<std::string, container::interface>&&, std::map<std::string, container::interface>&&);
	  structure();
	};
	
      };
    };
  };
};

#endif
