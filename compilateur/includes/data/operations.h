#ifndef Operation_Available_h__
# define Operation_Available_h__

namespace ctvscript {
  namespace byte_code {
    namespace data {
      class operations {
      public:
	enum class operators{
	  error_,
	    addition, substraction,
	    multiplication,
	    division, modulo,
	    call,
	    upcast,
	    downcast,
	};

      public:
	class operator_verifier {
	private:
	  const derived_types*					m_return_type;
	  const std::function<bool(std::list<derived_types*>)>	m_operator_verifier;

	public:
	  operator_verifier(const deriverd_types* t_return_type, std::list<const derived_types*> t_required_types);
	};

      public:	
	using operation_map = std::map< operators, std::list<operator_verifier> >;

      };
    };
  };
};

#endif
