#ifndef INCLUDED_FROM_SCRIPT
# error "Should be included from Script.hh"
#else

class callback {
private:
  class ValueState {
  private:
    bool		ok;
    std::string	path;

  protected:
    virtual bool matchValue(const loadable::Loadable* value) = 0;
    ValueState(const std::string& _path) : ok(false), path(_path) {}
  public:
    virtual ~ValueState() {}

  public:
    bool compPath(const loadable::Loadable* value) { return (value ? value->path == path : false); }
    bool isReady() { return (ok); }
    bool isValueReady(const loadable::Loadable* value = NULL)
    { return ((isReady()) ? true : (ok = matchValue(value))); }
  };

  TODO("now by value, later by function calling!");
  template<typename __loadable_class_type__, typename __value_type__>
  class SubValueState : public ValueState{
  private:
    __value_type__ value;

  public:
    SubValueState(const std::string& path, __value_type__ v)
      : ValueState(path), value(v) {}
    virtual ~SubValueState() {}

  protected:
    virtual bool matchValue(const loadable::Loadable* loadable) {
      const __loadable_class_type__* class_wrap =
	dynamic_cast< const __loadable_class_type__* > (loadable);
      return (class_wrap? class_wrap->getLockedValue() == value: false);
    }
  };

  std::vector<ValueState*>	associatedValue;
  TODO("see main TODO, create script::symbol...ect");
  /*script::symbol*		symbol;*/

public:
  bool refreshValue(const loadable::Loadable* loadable) {
    bool isReady = true;
    for (auto state : associatedValue) {
      bool subReady =
	state->compPath(loadable) ? 
	state->isValueReady(loadable) : state->isValueReady();
      isReady = !isReady ? isReady : subReady;
    }
    return isReady ;
  }

  script::symbol::id getSymbolId() { return (0/*symbol.getId()*/); }
  void callSymbol() {/*script::execute(symbol);*/}
  void addEventValue(ValueState* v) {associatedValue.push_back(v);}
    
public:
  callback() {}
  ~callback() { for (auto k: associatedValue) delete k; }
};

#endif
