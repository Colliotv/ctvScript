#ifndef Error_h__
# define Error_h__

#include <string>

namespace cTVScript{
  class InvalidAction : public std::exception{
  private:
    std::string action;
    std::string name;

  public:
    InvalidAction(std::string _c, std::string _n)
      : action(_c), name(_n) {}
    virtual ~InvalidAction() throw() {}

  public:
    virtual const char* what() throw() {
      return (std::string(  "Invalid Action : "
			  + action
			  + " For Object {"+ name +"} "
			  + causedBy()).c_str());
    }

  protected:
    virtual const std::string causedBy() { return ""; }
  };
};

#endif
