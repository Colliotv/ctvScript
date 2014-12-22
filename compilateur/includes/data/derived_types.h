#ifndef Derived_Types_h__
# define Derived_Types_h__

#include "data/types.h"

namespace ctvscript {
  namespace byte_code {
    namespace data {
      class derived_types{
      public:
	class const_;
	class reference_;
	class pointeur_;
	class array_;
	class functor_;
      private:

	class types_interface_{};
	class types_container_		: public types_interface{};

	template<typename __derived>
	class derived_container_	: public types_interface{
	public:
	  derived_container_();
	  ~derived_container_();

	public:
	  bool is_operation_available(data::operations::operators t_op, std::list<const derived_types*> t_operators) override {
	    operation_map::iterator m_op_verifier = __derived::operator_map.find(t_op);
	    if (m_op_verifier == __derived::operator_map.end())
	      return __derived::call_error(t_op);
	    for (auto verifiers : m_op_verifier.second)
	      if (verifiers(t_operators))
		return true;
	    return false;
	  }
	  
	};
      };
    };
  };
};

#endif
