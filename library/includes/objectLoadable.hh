/*
 * cTV work: ObjectLoadable
 **/
#ifndef ObjectLoadable_h__
# define ObjectLoadable_h__

# include <algorithm>

# include "status.h"

# include "Accessor.hh"

namespace cTVScript{

  class objectLoadable : public Loadable{
  private:
    std::map<std::string, Loadable*> childNodes;

  public:
    objectLoadable(const std::string& name) : Loadable(name) {}

  protected:
    virtual void	updateSelectedChild(Loadable* object) {
      object->updatePath(this->path);
    }

  public:
    cTVScript::loading_status	addObject(Loadable* object) {
      if (childNodes.count(object->getName()))
	return (ALREADY_EXIST);
      childNodes.emplace(std::make_pair(object->getName(), object));
      updateSelectedChild(object);
      return (CLEAR);
    }
    virtual void	updatePath(const std::string& pathFrom,
				   const std::string& separator = ".") {
      this->Loadable::updatePath(pathFrom, separator);
      std::for_each(childNodes.begin(), childNodes.end(),
		    [this](std::pair<std::string, Loadable*> p){
		      updateSelectedChild(p.second);
		    });
    }

  public:
    virtual Loadable* operator[](const std::string& name) {
      return childNodes.at(name);
    }
  };


  class Context : public objectLoadable{
  protected:
    virtual void	updateSelectedChild(Loadable* object) {
      object->updatePath(this->path, "");
    }

  public:
    static cTVScript::loading_status addObject(Loadable* object) {
      return (get()->objectLoadable::addObject(object));
    }

  private: // singleton

    static Context* get() {
      static Context* loader;
      return (!loader ?
	      loader = new Context():
	      loader);

    };

    Context() : objectLoadable("context") {};
    ~Context() {}
  };
};

#endif
