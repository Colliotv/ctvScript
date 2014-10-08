/*
 * cTV work: ObjectLoadable
 **/
#ifndef ObjectLoadable_h__
# define ObjectLoadable_h__

# include <algorithm>

# include "status.h"

# include "Accessor.hh"

namespace cTVScript{

  class ObjectLoadable : public Loadable{
  private:
    std::map<std::string, Loadable*> childNodes;

  public:
    ObjectLoadable(const std::string& name) : Loadable(name) {}

  public:
    cTVScript::loading_status	addObject(Loadable* object) {
      if (childNodes.count(object->getName()))
	return (ALREADY_EXIST);
      childNodes.emplace(std::make_pair(object->getName(), object));
      object->updatePath(this->path);
    }
    virtual void	updatePath(const std::string& pathFrom,
				   const std::string& separator = ".") {
      this->Loadable::updatePath(pathFrom, separator);
      std::for_each(childNodes.begin(), childNodes.end(),
		    [this](std::pair<std::string, Loadable*> p){
		      p.second->updatePath(this->path);
		    });
    }

  public:
    virtual Loadable* operator[](const std::string& name) {
      return childNodes.at(name);
    }
  };


  class Context : public ObjectLoadable{
  public:
    static cTVScript::loading_status addObject(Loadable* object) {
      return (get()->addObject(object));
    }

  private: // singleton

    static Context* get() {
      static Context* loader;
      return (!loader ? 
	      loader = new Context():
	      loader);

    };

    Context() : ObjectLoadable("context") {};
    ~Context() {}
  };
};

#endif
