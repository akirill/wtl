// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once

#ifdef _X86_
#pragma comment(linker, "/nodefaultlib:libc.lib")
#pragma comment(linker, "/nodefaultlib:libcd.lib")
#pragma comment(linker, "/nodefaultlib:libcmt.lib")
#pragma comment(linker, "/nodefaultlib:libcmtd.lib")
#pragma comment(linker, "/nodefaultlib:oldnames.lib")
#endif

// NOTE - this is value is not strongly correlated to the Windows CE OS version being targeted
#define WINVER 0x0400

[!if WTL_COM_SERVER]
// The WTL wizard was instructed to create this project as a COM Server.
// On Windows CE, COM Servers are only available on platforms that include DCOM.
// Pocket PC 2000, 2002, 2003 and SmarthPhone 2002, 2003 do not include DCOM.
// The Standard SDK for Windows CE versions 3.0, 4.0, 4.1, and 4.2 do not include DCOM.
// For Windows CE OSes released after 2003, please see the associated docs.

[!endif]
[!if WTL_USE_AYGSHELL]
#define _WIN32_WCE_AYGSHELL 1

[!endif]
#include <atlbase.h>
#include <atlapp.h>

[!if WTL_COM_SERVER]
extern CServerAppModule _Module;

// This is here only to tell VC7 Class Wizard this is an ATL project
#ifdef ___VC7_CLWIZ_ONLY___
CComModule
CExeModule
#endif

[!else]
extern CAppModule _Module;

[!endif]
[!if WTL_ENABLE_AX || WTL_COM_SERVER]
#include <atlcom.h>
[!endif]
[!if WTL_ENABLE_AX]
#include <atlhost.h>
[!endif]
#include <atlwin.h>
[!if WTL_ENABLE_AX]
#include <atlctl.h>
[!endif]
[!if WTL_USE_CPP_FILES]

#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
[!endif]
