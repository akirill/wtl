// stdafx.cpp : source file that includes just the standard includes
//	[!output PROJECT_NAME].pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

[!if WTL_ENABLE_AX]
#include <wceatl.cpp>
[!endif]
[!if WTL_COM_SERVER]

#ifdef _ATL_STATIC_REGISTRY
#include <statreg.h>
#if (_ATL_VER < 0x0700)
#include <statreg.cpp>
#endif //(_ATL_VER < 0x0700)
#endif //_ATL_STATIC_REGISTRY
[!endif]
