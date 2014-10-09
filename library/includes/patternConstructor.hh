#ifndef PatternConstructor_h__
# define PatternConstructor_h__


/* Singleton Pattern */

# define MAKE_SINGLETON(__class_name__, __initializer_list__,		\
			__onCreate__, __onDestroy__)			\
  static __class_name__ * get() {					\
    static __class_name__ * singleton;					\
    return (! singleton ?						\
	    singleton = new __class_name__ () : singleton);		\
  }									\
  static void destroy() {						\
    __class_name__ * singleton = get();					\
    delete singleton;							\
  }									\
private:								\
 __class_name__ () __initializer_list__ { __onCreate__ }		\
 ~ __class_name__ () { __onDestroy__ }					\

/* loadable Easier Class construction */
# define COMPARAND_OPERATOR(__op__, __conv__)				\
  virtual bool operator __op__ (const Loadable& oth) const {		\
    if (getPriority() > oth.getPriority())				\
      return (oth __op__ *this);					\
    return (value __op__ __conv__ (oth.getAsString()));			\
  }
# define ASSIGN_OPERATOR(__conv__, __type__)				\
  virtual Loadable* operator = (const Loadable& oth) {			\
    if (getPriority() > oth.getPriority())				\
      throw cTVScript::InvalidAction("=", oth.getName());		\
    Surveyor::get()->update(this);					\
    return ( new __type__ ("", value = __conv__ (oth.getAsString())) ); \
  }
# define MATHEMATICAL_OPERATOR(__op__, __conv__, __type__)		\
  virtual Loadable* operator __op__ (const Loadable& oth) const {	\
    if(getPriority() > oth.getPriority())				\
      return (oth __op__ *this);					\
    return ( new __type__ ("", value __op__ __conv__ (oth.getAsString())) ); \
  }
# define MATHEMATICAL_WITH_REVERT_OPERATOR(__op__, __conv__, __type__, __revert__) \
  virtual Loadable* operator __op__ (const Loadable& oth) const {		\
    if(getPriority() > oth.getPriority())					\
      return (oth. __revert__ (*this));						\
    return ( new __type__ ("", value __op__ __conv__ (oth.getAsString())) );	\
  }
# define MATHEMATICAL_REVERT_OPERATOR(__op__, __conv__, __type__, __revert__)	\
  virtual Loadable* __revert__ (const Loadable& oth) const {			\
    return ( new __type__ ("", (__conv__ (oth.getAsString())) __op__ value));	\
  }

# define DEFAULT_CONSTRUCTOR(__class_type__)			\
  __class_type__ (const std::string& name) : Loadable(name) {}	\
  ~ __class_type__ () {}


# define DEFAULT_VALUE_CONSTRUCTOR(__class_type__, __sub_type__, __default_value__)		\
  __class_type__ (const std::string& name, __sub_type__ _v = __default_value__)			\
    : Loadable(name), value(_v) { registerPriority(Helper::TypePriorityFor< __sub_type__ >	\
						   ::get()); }					\
  ~ __class_type__ () {}									\

# define DEFAULT_LOCK_USE(__type__)		\
  __type__   getLockedValue() { return value; }	\
  __type__ & unlock(DestructibleKey& key) {	\
    key->notify(this);				\
    return value ;				\
  }

# define DEFAULT_VALUE_GETTER(__conv__)		\
  const std::string	getAsString() const {	\
    return ( __conv__ (value));			\
  }
# define NEGATE_VALUE_GETTER()				\
  const std::string	getAsString() const {		\
    throw cTVScript::unSerialized(getName());		\
    return ("");					\
  }

#endif
