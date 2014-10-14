#ifndef  LoadableReferenceWrapper_h__
# define LoadableReferenceWrapper_h__

namespace cTVScript {

  namespace loadable {
    template < typename __loadable__ >
    class ReferenceWrapper : public __loadable__ {
    private:
      typename __loadable__ :: value_type  &valueReference;

    public:
      ReferenceWrapper(const std::string& name, typename __loadable__ :: value_type& _v)
	: __loadable__ (name, _v), valueReference(_v) {}

    public:
      virtual Loadable* operator = (const Loadable& oth) {			
	if (__loadable__ :: getPriority() > oth.getPriority())
	  throw cTVScript::InvalidAction("=", oth.getName());
	return ( new __loadable__ ("",
				   __loadable__ :: value =
				   valueReference = 
				   __loadable__ :: convert(oth.getAsString())) );
      }

    };

  };

};

#endif
