#ifndef __cTVScript__
# define __cTVScript__

#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) DO_PRAGMA(message ("\nTODO - [" __FILE__ "]:" #x))


#include "helper.hh"

TODO("Loader, Accessor, ScriptExecutor")
TODO(" - Prio : Key and Accessor")
TODO(" - Secundo : ScriptExecutor")
TODO(" - Tertio ; Loader");

#include "Loader.hh"
#include "Accessor.hh"

#include "objectLoadable.hh"
#include "primaryLoadable.hh"
#include "functionsLoadable.hh"

#endif
