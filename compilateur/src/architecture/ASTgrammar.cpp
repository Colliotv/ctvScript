#include "architecture/ASTgrammar.h"


namespace ctvscript {
  namespace AST {
    namespace tree{};
    namespace utils{

      template<typename, typename>
      struct variadic_append;
      template<typename rev_head, typename ... rev_tail>
      struct variadic_append<rev_head, std::tuple<rev_tail...> >
      {	using list = std::tuple< rev_tail..., rev_head >; };

      template<typename ... inverting>
      struct variadic_template_inverter
      {	using list = std::tuple<>; };

      template<typename head, typename ... tail>
      struct variadic_template_inverter<head, tail...> {
	using list = typename variadic_append< head, typename variadic_template_inverter<tail...>::list >::list;
      };

      template<bool... retvals>
      static void void_() {}

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

    template<typename tree_node>
    struct for_< tree::Repeat<tree_node> > {
      static bool organize(std::list<node*>& t_ASTnodes, std::list<AST::node*>::iterator& t_cursor,
			   std::list<AST::node*>::iterator& t_further) {
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
    private:
      template<typename... _inverted>
      struct sub_;
      template<typename... _nodes> //prevent template reversion
      struct sub_< std::tuple<_nodes...> > {
	static bool organize(std::list<node*>& t_ASTnodes, std::list<node*>::iterator& t_cursor,
			     std::list<AST::node*>::iterator& t_further) {
	  bool retval = false;
	  std::list<node*>::iterator save = t_cursor;
	  utils::void_(
		(retval || for_<nodes>::organize(t_ASTnodes, t_cursor) ?
		 (retval = true) :
		 (false))...
		);
	  if (!retval)
	    t_cursor = save;
	  return (retval);
	}
      };

    public:
      static bool organize(std::list<node*>& t_ASTnodes, std::list<node*>::iterator& t_cursor,
			   std::list<AST::node*>::iterator& t_further) {
	return sub_<utils::variadic_template_inverter<nodes...> >::organize(t_ASTnodes, t_cursor);
      }
    };

    template<typename... nodes>
    struct for_< tree::And<nodes...> > {
    private:
      template<typename... _inverted>
      struct sub_;
      template<typename... _nodes>
      struct sub_< std::tuple<_nodes...> > {
	static bool organize(std::list<node*>& t_ASTnodes, std::list<node*>::iterator& t_cursor,
			     std::list<AST::node*>::iterator& t_further) {
	  bool inv_retval = true;
	  std::list<node*>::iterator save = t_cursor;
	  utils::void_(
		(!inv_retval || for_<nodes>::organize(t_ASTnodes, t_cursor) ?
		 (true) :
		 (inv_retval = false))...
		);
	  if (inv_retval)
	    t_cursor = save;
	  return (!inv_retval);
	}
      };

    public:
      static bool organize(std::list<node*>& t_ASTnodes, std::list<node*>::iterator& t_cursor,
			   std::list<AST::node*>::iterator& t_further) {
	return sub_<utils::variadic_template_inverter<nodes...> >::organize(t_ASTnodes, t_cursor);
      }
    };

    template<AST::tree::line_name line>
    struct for_< tree::Call<line> > {
      static bool organize(std::list<node*>& t_ASTnodes, std::list<node*>::iterator& t_cursor,
			   std::list<AST::node*>::iterator& t_further) {
	bool retval = false;
	std::list<node*>::iterator save = t_cursor;
	retval = for_<typename tree::Grammar::fetch<line>::grammarLine::node_line>::organize(t_ASTnodes, t_cursor);
	if (!retval) {
	  t_cursor = save;
	  utils::list_modifier(t_ASTnodes, save, t_further, tree::Grammar::fetch<line>::grammarLine::onError);
	} else {
	  utils::list_modifier(t_ASTnodes, save, t_cursor , tree::Grammar::fetch<line>::grammarLine::onMatch);
	}
	return (retval);
      }
    };

    template<typename ASTnode>
    struct for_< tree::Compare<ASTnode> > {
      static bool organize(std::list<node*>& t_ASTnodes, std::list<node*>::iterator& t_cursor,
			   std::list<AST::node*>::iterator& t_further) {
	bool retval = false;
	if (dynamic_cast<ASTnode>(*t_cursor) != nullptr) {
	  retval = true;
	  ++t_cursor;
	  if (std::distance(t_further, t_cursor) > 0)
	    t_further = t_cursor;
	}
	return (retval);
      }
    };

  };
};
