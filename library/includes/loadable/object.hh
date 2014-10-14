/*
 * cTV work: ObjectLoadable
 **/
#ifndef ObjectLoadable_h__
# define ObjectLoadable_h__

# include <map>
# include <algorithm>

# include "status.h"
# include "helper/patternConstructor.hh"

# include "loadable/loadable.hh"

namespace cTVScript{

  namespace loadable {

    class object : public Loadable{
    public:
      DEFAULT_CONSTRUCTOR(object);
      NEGATE_VALUE_GETTER();

    private:
      std::map<std::string, Loadable*> childNodes;

    protected:
      virtual void	updateSelectedChild(Loadable* object) {
	object->updatePath(this->path);
      }

    public:
      cTVScript::loading_status	addObject(Loadable* object) {
	if (childNodes.count(object->getName()))
	  return (ALREADY_EXIST);
#if __cplusplus > 199711L
	childNodes.emplace(std::make_pair(object->getName(), object));
#else
	childNodes.insert(std::make_pair(object->getName(), object));
#endif
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


    class Context : public object{
    protected:
      virtual void	updateSelectedChild(Loadable* object) {
	object->updatePath(this->path, "");
      }

    public:
      static cTVScript::loading_status addObject(Loadable* object) {
	return (get()->object::addObject(object));
      }

    private: // singleton

      static Context* get() {
	static Context* loader;
	return (!loader ?
		loader = new Context():
		loader);

      };

      Context() : object("context") {};
      ~Context() {}
    };
  };
};

#endif
