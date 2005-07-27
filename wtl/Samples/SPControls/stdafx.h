// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__DDC60FC7_1FA4_4F28_8C9A_528991A31A86__INCLUDED_)
#define AFX_STDAFX_H__DDC60FC7_1FA4_4F28_8C9A_528991A31A86__INCLUDED_

// The WTL wizard was instructed to create this project as a COM Server.
// On Windows CE, COM Servers are only available on platforms that include DCOM.
// Pocket PC 2000, 2002, 2003 and SmarthPhone 2002, 2003 do not include DCOM.
// The Standard SDK for Windows CE versions 3.0, 4.0, 4.1, and 4.2 do not include DCOM.
// For Windows CE OSes released after 2003, please see the associated docs.

// Change these values to use different versions
#define WINVER		0x0420

#include <atlbase.h>
#include <atlapp.h>

extern CAppModule _Module;

#include <atlwin.h>

#include <aygshell.h>
#include <tpcshell.h>
#pragma comment(lib, "aygshell.lib")


//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__DDC60FC7_1FA4_4F28_8C9A_528991A31A86__INCLUDED_)
