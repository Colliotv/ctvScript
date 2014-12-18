#ifndef FINALLine_h__
# define FINALLine_h__
# ifndef  INCLUDED_FROM_ASTGRAMMAR
#  error "This file should be included only in ASTgrammar.h"
# endif

enum class line_name{
  global,
    function_definition, type_definition, argument_list, variable_definition, ScopedId
};

#endif
