#ifndef ASTnode_h__
# define ASTnode_h__

/*
 * Here is defined the majority of AST nodes
 * implemntation are done in src
 */

namespace ctvscript {
  namespace AST {
    /*
     * This interface will premit easier tree/list constructing
     */
    class node {};

    /*
     * The Factory help in two way: 
		-> Parsing
		-> [...]
     */
    

    /*
     * A key word is language specs
     */
    namespace keyword {
      class Var;	//: AST::node{};
      class Fun;	//: AST::node{};
      class If;		//: AST::node{}; 
      class Return;	//: AST::node{};
    };

    /*
     * Symbols
     */
    namespace symbol {
      class Semicolon;	 //: AST::node{};
      class WhiteSpace;	 //: AST::node{};
      class Bparenthesis;//: AST::node{};
      class Eparenthesis;//: AST::node{};
      class Bbracket;	 //: AST::node{};
      class Ebracket;	 //: AST::node{};
      class Bsqbrackets; //: AST::node{};
      class Esqbrackets; //: AST::node{};
    };
  };
};

#endif
