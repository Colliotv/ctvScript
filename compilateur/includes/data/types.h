#ifndef type_data_h__
# define type_data_h__

# include <map>
# include <cstdlib>

# include <thread>
# include <mutex>

namespace ctvscript {
  namespace byte_code {
    namespace data {
      class types {
      public:
	class base_type{
	private:
	  std::string		name;

	public:
	  base_type(const std::string&);
	};

	class struct_type : public base_type{
	private:
	  std::map<std::string /* member*/, std::size_t> m_members;

	public:
	  struct_type(const std::string&);
	};

	class unknown_type : public base_type{
	public:
	  unknown_type(const std::string&);
	};

      private:
	static std::mutex			m_lock;
	static const std::vector<base_type*>	m_base_types;
	static const std::vector<struct_type*>	m_struct_types;

      public:
	enum class status_t {
	  NO_ERROR,
	    ALREADY_EXIST, 
	    NOT_A_STRUCT,
	    DONT_EXIST};
	static types::status_t	addType();
	static types::status_t	addStruct();

      public:
	static bool		does_type_exist(const std::string& t_type);
	static types::status_t	can_access(const base_type*,
					   const std::string& t_member);
      };
    };
  };
};

#endif
