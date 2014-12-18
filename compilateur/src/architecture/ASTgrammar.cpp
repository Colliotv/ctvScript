#include <iostream>
#include "architecture/ASTgrammar.h"


namespace ctvscript {
  namespace AST {
    namespace tree{};
    namespace utils{

      template<bool... retvals>
      static void void_(...) {}

      static void list_modifier(std::list<AST::node*>& t_list,
				std::list<AST::node*>::iterator t_fcut,
				std::list<AST::node*>::iterator t_ecut,
				std::function<std::list<AST::node*>(std::list<AST::node*>)> t_cut_call) {
	if (t_fcut == t_ecut) {
	  (void)t_cut_call(std::list<AST::node*>());
	  return ;
	}
	auto _fcut = t_fcut;
	auto _ecut = t_ecut;

	std::advance(_fcut, 1);
	if (_ecut != t_list.end())
	  std::advance(_ecut, 1);

	auto _list = t_cut_call(std::list<AST::node*>(t_fcut, t_ecut));
	t_list.erase(_fcut, _ecut);
	std::advance(t_fcut, 1);
	t_list.insert(t_fcut, _list.cbegin(), _list.cend());
      }

    };

    /* ########## REPEAT ############# */
    template<typename tree_node>
    struct for_< tree::Repeat<tree_node> > {
      static bool organize(std::list<node*>& t_ASTnodes, std::list<AST::node*>::iterator& t_cursor,
			   std::list<AST::node*>::iterator& t_further) {
	std::cerr << __PRETTY_FUNCTION__ << std::endl;
	bool retval = false;
	std::list<node*>::iterator save = t_cursor;

	while (for_<tree_node>::organize(t_ASTnodes, t_cursor, t_further))
	  retval = true;

	if (!retval)
	  t_cursor = save;
	return (retval);
      }
    };

    template<typename tree_node, size_t it_min>
    struct for_< tree::Repeat<tree_node, it_min> > {
      static bool organize(std::list<node*>& t_ASTnodes, std::list<AST::node*>::iterator& t_cursor,
			   std::list<AST::node*>::iterator& t_further) {
	std::cerr << __PRETTY_FUNCTION__ << std::endl;
	bool retval = false;
	size_t it = 0;
	std::list<node*>::iterator save = t_cursor;

	while (for_<tree_node>::organize(t_ASTnodes, t_cursor, t_further)) {
	  it++;
	}
	if (it >= it_min)
	  retval = true;

	if (!retval)
	  t_cursor = save;
	return (retval);
      }
    };

    template<typename tree_node, size_t it_min, size_t it_max>
    struct for_< tree::Repeat<tree_node, it_min, it_max> > {
      static bool organize(std::list<node*>& t_ASTnodes, std::list<AST::node*>::iterator& t_cursor,
			   std::list<AST::node*>::iterator& t_further) {
	std::cerr << __PRETTY_FUNCTION__ << std::endl;
	bool retval = false;
	size_t it = 0;
	std::list<node*>::iterator save = t_cursor;

	while (it < it_max && for_<tree_node>::organize(t_ASTnodes, t_cursor, t_further)) {
	  it++;
	}
	if (it >= it_min)
	  retval = true;

	if (!retval)
	  t_cursor = save;
	return (retval);
      }
    };

    /* ###### OR ###### */
    template<typename... nodes>
    struct _or;
    template<> struct _or<>{
      static bool calc(std::list<node*>&, std::list<node*>::iterator&, std::list<AST::node*>::iterator&) { return false; }
    };
    template<typename node_head, typename ... node_tail>
    struct _or<node_head, node_tail...>{
      static bool calc(std::list<node*>& t_ASTnodes, std::list<node*>::iterator& t_cursor,
		       std::list<AST::node*>::iterator& t_further) {
	if (for_<node_head>::organize(t_ASTnodes, t_cursor, t_further))
	  return true;
	return _or<node_tail...>::calc(t_ASTnodes, t_cursor, t_further);
      }
    };

    template<typename... nodes>
    struct for_< tree::Or<nodes...> > {
    public:
      static bool organize(std::list<node*>& t_ASTnodes, std::list<node*>::iterator& t_cursor,
			   std::list<AST::node*>::iterator& t_further) {
	std::cerr << __PRETTY_FUNCTION__ << std::endl;
	std::list<node*>::iterator save = t_cursor;
	bool retval = _or<nodes...>::calc(t_ASTnodes, t_cursor, t_further);
	if (!retval)
	  t_cursor = save;
	return (retval);
      }
    };


    /* ######## AND ####### */
    template<typename... nodes>
    struct _and;
    template<> struct _and<>{
      static bool calc(std::list<node*>&, std::list<node*>::iterator&, std::list<AST::node*>::iterator&) { return true; }
    };
    template<typename node_head, typename ... node_tail>
    struct _and<node_head, node_tail...>{
      static bool calc(std::list<node*>& t_ASTnodes, std::list<node*>::iterator& t_cursor,
		       std::list<AST::node*>::iterator& t_further) {
	if (for_<node_head>::organize(t_ASTnodes, t_cursor, t_further)) {
	  if (!_and<node_tail...>::calc(t_ASTnodes, t_cursor, t_further)) {
	    std::cerr << "depile false" << std::endl;
	    return false;
	  } else {
	    std::cerr << "depile true" << std::endl;
	    return true;
	  }
	}
	std::cerr << "return false" << std::endl << std::endl;
	return (false);
      }
    };

    template<typename... nodes>
    struct for_< tree::And<nodes...> > {
    public:
      static bool organize(std::list<node*>& t_ASTnodes, std::list<node*>::iterator& t_cursor,
			   std::list<AST::node*>::iterator& t_further) {
	std::cerr << __PRETTY_FUNCTION__ << std::endl;
	bool retval;
	std::list<node*>::iterator save = t_cursor;
	retval = _and<nodes...>::calc(t_ASTnodes, t_cursor, t_further);

	if (!retval)
	  std::cerr << "error in {"<< __PRETTY_FUNCTION__ << "}" << std::endl << std::endl;
	else
	  std::cerr << "clear in {"<< __PRETTY_FUNCTION__ << "}" << std::endl << std::endl;

	if (!retval)
	  t_cursor = save;
	return (retval);
      }
    };


    /* ######### CALL ########## */
    template<AST::tree::line_name line>
    struct for_< tree::Call<line> > {
      static bool organize(std::list<node*>& t_ASTnodes, std::list<node*>::iterator& t_cursor,
			   std::list<AST::node*>::iterator& t_further) {
	bool retval = false;
	std::list<node*>::iterator save = t_cursor;
	retval = for_<typename tree::Grammar::fetch<line>::grammarLine::node_line>::organize(t_ASTnodes, t_cursor, t_further);
	if (!retval) {
	  t_cursor = save;
	  utils::list_modifier(t_ASTnodes, save, t_further, tree::Grammar::fetch<line>::grammarLine::onError);
	} else {
	  utils::list_modifier(t_ASTnodes, save, t_cursor , tree::Grammar::fetch<line>::grammarLine::onMatch);
	}
	return (retval);
      }
    };

    /* ############ COMPARE ############ */
    template<typename ASTnode>
    struct for_< tree::Match<ASTnode> > {
      static bool organize(std::list<node*>&, std::list<node*>::iterator& t_cursor,
			   std::list<AST::node*>::iterator& t_further) {
	bool retval = false;
	if (dynamic_cast<ASTnode*>(*t_cursor) != nullptr) {
	  retval = true;
	  ++t_cursor;
	  if (std::distance(t_further, t_cursor) > 0)
	    t_further = t_cursor;
	}
	if (!retval)
	  std::cerr << "error in {"<< __PRETTY_FUNCTION__ << "}" << std::endl << std::endl;
	else
	  std::cerr << "clear in {"<< __PRETTY_FUNCTION__ << "}" << std::endl << std::endl;

	return (retval);
      }
    };

    # include "architecture/grammar/lines/index.hpp"

    void launch_grammar(std::list<node*>& t_ASTnodes) {
      std::list<node*>::iterator t_cursor = t_ASTnodes.begin();
      std::list<node*>::iterator t_further = t_ASTnodes.begin();
      if (!for_< tree::Call<AST::tree::line_name::global> >::organize(t_ASTnodes, t_cursor, t_further))
	std::cerr << std::endl << std::endl << std::endl << "fail in grammar structuring!!!!!!" << std::endl;
      else
	std::cerr << std::endl << std::endl << std::endl << "success in grammar structuring!!!!!!" << std::endl;
    }
  };
};
