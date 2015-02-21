#ifndef FINALLine_h__
# define FINALLine_h__
# ifndef  INCLUDED_FROM_ASTGRAMMAR
#  error "This file should be included only in ASTgrammar.h"
# endif

enum class line_name{
  global,
    function_forward_declaration,
    function_prototype, type_definition, argument_list, variable_definition, scoped_id, scoped_type
};

#endif
