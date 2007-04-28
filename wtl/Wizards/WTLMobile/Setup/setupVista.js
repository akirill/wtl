// Windows Template Library - WTL version 8.0
// Copyright (C) Microsoft Corporation. All rights reserved.
//
// This file is a part of the Windows Template Library.
// The use and distribution terms for this software are covered by the
// Common Public License 1.0 (http://opensource.org/osi3.0/licenses/cpl1.0.php)
// which can be found in the file CPL.TXT at the root of this distribution.
// By using this software in any fashion, you are agreeing to be bound by
// the terms of this license. You must not remove this notice, or
// any other, from this software.

// Vista setup program for the Windows Mobile WTL App Wizard for VC++ 8.0 (Whidbey)

// Execute setup80.js with elevated privilege
try
{
	var scriptName = WScript.ScriptFullName;
	scriptName = scriptName.replace("Vista.js","80.js");
	var AppShell = WScript.CreateObject("Shell.Application");
	AppShell.ShellExecute("WScript.exe", scriptName, null, "RunAs");
}
catch(e)
{
	WScript.Echo("Error " + e);
}
