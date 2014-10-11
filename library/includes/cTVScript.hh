#ifndef __cTVScript__
# define __cTVScript__

#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) DO_PRAGMA(message ("\nTODO - [" __FILE__ "]:" #x))


#include "helper.hh"

TODO("Loader, Surveyor, ScriptExecutor")
TODO(" - Prio : Key and Surveyor")
TODO(" - Secundo : ScriptExecutor")
TODO(" - Tertio ; Loader");

#include "Surveyor.hh"
#include "Loader.hh"
#include "Loadable.hh"

#include "objectLoadable.hh"
#include "primaryLoadable.hh"
#include "functionsLoadable.hh"
#include "LoadableReferenceWrapper.hh"


TODO("undef all includes pre-empter")

#endif
