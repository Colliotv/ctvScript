#ifndef __cTVScript__
# define __cTVScript__

#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) DO_PRAGMA(message ("\nTODO - [" __FILE__ "]:" #x))

TODO("Loader, Surveyor, ScriptExecutor")
TODO(" - Prio : Key and Surveyor")
TODO(" - Secundo : ScriptExecutor")
TODO(" - Tertio ; Loader");
TODO(" - Whenever : make a little lift in the name (end the length><)")


#include "binary.h"
#include "loadable.h"


TODO("undef all includes pre-empter")

#endif
