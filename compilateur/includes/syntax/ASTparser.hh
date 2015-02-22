#ifndef ASTparser_h__
# define ASTparser_h__

#include <string>
#include <list>

#include "syntax/utils.hh"
#include "architecture/ASTnode.hh"

namespace ctvscript {
  namespace parser {

    class ASTparser {
    public:
      static void parse(const std::string& file, std::list<AST::node*> &_list);
    };

  };
};

#endif
