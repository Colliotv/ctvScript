#ifndef ASTgrammar_h__
# define ASTgrammar_h__
# define INCLUDED_FROM_ASTGRAMMAR

# include <list>

# include "architecture/ASTnode.h"

namespace ctvscript {
  namespace AST {
    namespace tree{

      # include "grammar/line.h"

      template<AST::tree::line_name line, typename superior_node>
      struct GrammarLine{
	static const AST::tree::line_name name = line;
	using node_line = superior_node;
	static std::list<AST::node*> onError(std::list<AST::node*> t_list) {
	  return (t_list);
	}
	static std::list<AST::node*> onMatch(std::list<AST::node*> t_list) {
	  return (t_list);
	}
      };


      /*
       * Grammar fetch definition
       */
      template<bool b, AST::tree::line_name name, typename ... nodes>
      struct match_line;

      template<AST::tree::line_name name, typename node>
      struct match_line<true, name, node>{ using line = node; };

      template<AST::tree::line_name name>
      struct match_line<false, name>; /*error in this case*/

      template<AST::tree::line_name name, typename node, typename... nodes>
      struct match_line<true, name, node, nodes...>{ using line = node; };
      template<AST::tree::line_name name, typename cur_node, typename next_node, typename... nodes>
      struct match_line<false, name, cur_node, next_node, nodes...>
      { using line = typename match_line<name == next_node::name, name, next_node, nodes...>::line; };

      template<AST::tree::line_name name, typename node, typename... nodes>
      struct seek_line{
	using line = typename match_line<node::name == name, name, node, nodes...>::line;
      };

      /*
       * Grammar Definition
       */
      template<typename... lines>
      struct GrammarTree{
	template <AST::tree::line_name name>
	struct fetch{
	  using grammarLine = typename seek_line<name, lines...>::line;
	};
      };


      template<typename nodes, size_t...>
      struct Repeat{};
      template<typename... nodes>
      struct Or{};
      template<typename... nodes>
      struct And{};

      template<typename ASTnode>
      struct Match{};
      template<AST::tree::line_name line>
      struct Call{};

      # include "grammar/grammar.h"
    };


    template<typename node>
    struct for_;

    template<typename node>
    struct for_< tree::Repeat<node> >;
    template<typename... nodes>
    struct for_< tree::Or<nodes...> >;
    template<typename... nodes>
    struct for_< tree::And<nodes...> >;

    template<typename ASTnode>
    struct for_< tree::Match<ASTnode> >;
    template<AST::tree::line_name line>
    struct for_< tree::Call<line> >;

    void launch_grammar(std::list<node*>&);
  };
};

# undef INCLUDED_FROM_ASTGRAMMAR
#endif
