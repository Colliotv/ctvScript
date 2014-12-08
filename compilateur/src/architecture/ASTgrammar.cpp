#include "architecture/ASTgrammar.h"


namespace ctvscript {
  namespace AST {
    namespace tree{};

    template<bool... retvals>
    static void void_() {}

    template<typename tree_node>
    struct for_< tree::Repeat<tree_node> > {
      static bool organize(std::list<node*> t_ASTnodes, std::list<AST::node*>::iterator& t_cursor) {
	bool retval = false;
	std::list<node*>::iterator save = t_cursor;

	while (for_<tree_node>::organize(t_ASTnodes, t_cursor))
	  retval = true;

	if (!retval)
	  t_cursor = save;
	return (retval);
      }
    };

    template<typename... nodes>
    struct for_< tree::Or<nodes...> > {
      static bool organize(std::list<node*> t_ASTnodes, std::list<node*>::iterator& t_cursor) {
	bool retval = false;
	std::list<node*>::iterator save = t_cursor;
	void_(
	       (retval || for_<nodes>::organize(t_ASTnodes, t_cursor) ?
		(retval = true) :
		(false))...
	       );
	if (!retval)
	  t_cursor = save;
	return (retval);
      }
    };

    template<typename... nodes>
    struct for_< tree::And<nodes...> > {
      static bool organize(std::list<node*> t_ASTnodes, std::list<node*>::iterator& t_cursor) {
	bool inv_retval = true;
	std::list<node*>::iterator save = t_cursor;
	void_(
	       (!inv_retval || for_<nodes>::organize(t_ASTnodes, t_cursor) ?
		(true) :
		(inv_retval = false))...
	       );
	if (inv_retval)
	  t_cursor = save;
	return (!inv_retval);
      }
    };

    template<AST::tree::line_name line>
    struct for_< tree::Call<line> > {
      static bool organize(std::list<node*> t_ASTnodes, std::list<node*>::iterator& t_cursor) {
	bool retval = false;
	std::list<node*>::iterator save = t_cursor;
	retval = for_<typename tree::Grammar::fetch<line>::grammarLine>::organize(t_ASTnodes, t_cursor);
	if (!retval)
	  t_cursor = save;
	return (retval);
      }
    };

    template<typename ASTnode>
    struct for_< tree::Compare<ASTnode> > {
      static bool organize(std::list<node*> t_ASTnodes, std::list<node*>::iterator& t_cursor) {
	bool retval = false;
	if (dynamic_cast<ASTnode>(*t_cursor) != nullptr) {
	  retval = true;
	  ++t_cursor;
	}
	return (retval);
      }
    };

  };
};
