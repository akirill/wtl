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

// Setup program for the Windows Mobile WTL App Wizard for VC++ 8.0 (Whidbey)

try // Check Vista need for elevated privilege
{
	// Decode command line arguments
	var bElevated = false;
	var Args = WScript.Arguments;
	for(var i = 0; i < Args.length ; i++)
		bElevated = (Args(i) == "/elevated");

	// See if UAC is enabled
	var AppShell = WScript.CreateObject("Shell.Application");
	if (!bElevated && AppShell.IsRestricted("System", "EnableLUA"))
		// Check that the script is being run interactively.
		if(WScript.Interactive)
	        throw "Restricted";
		else
			throw "ERROR: Elevation required.";
}
catch(e)
{
    if (e == "Restricted")
    {
	    var scriptParams = WScript.ScriptFullName + " /elevated";
	    AppShell.ShellExecute("WScript.exe", scriptParams, null, "RunAs");
	    WScript.Quit();	
	}
	else
	    throw e;
}

try
{
    var fso = WScript.CreateObject("Scripting.FileSystemObject");
    var SourceBase = fso.GetParentFolderName(WScript.ScriptFullName) + "\\Files";
    var Source = SourceBase + "\\WTLMobile.";
	
    var shell = WScript.CreateObject("WScript.Shell");
    var DestBase = shell.RegRead("HKLM\\Software\\Microsoft\\VisualStudio\\8.0\\Setup\\VC\\ProductDir") + "\\vcprojects";
    var Dest =DestBase + "\\WTLMobile.";
	
    var vsz = Source + "vsz" 
    var vsdir = Source + "vsdir";
    var vszText, vsdirText; 
	
    var ts = fso.OpenTextFile(vsz,1);
    vszText = ts.ReadAll();
    ts.Close();
    vszText = vszText.replace(/(.+PATH\s=).+/,"$1" + SourceBase +"\"\r");
    ts = fso.OpenTextFile(vsdir,1);
    vsdirText = ts.ReadAll();
    ts.Close();
	
    fso.CopyFile(Source + "ico", Dest + "ico");
	
    ts = fso.OpenTextFile(Dest + "vsz", 2, true);
    ts.Write(vszText);
    ts.Close();
	 
    ts = fso.OpenTextFile(Dest + "vsdir", 2, true);
    ts.Write(vsdirText);
    ts.Close(); 
	
    vsdirText = "..\\" + vsdirText;
	
    Dest = DestBase + "\\WTL\\WTLMobile.vsdir";
    ts = fso.OpenTextFile(Dest, 2, true);
    ts.Write(vsdirText);
    ts.Close();

    Dest = DestBase + "\\smartdevice\\WTLMobile.vsdir";
    ts = fso.OpenTextFile(Dest, 2, true);
    ts.Write(vsdirText);
    ts.Close();
	
    WScript.Echo("WTL Mobile App Wizard successfully installed!");
}

catch(e)
{
	WScript.Echo("Error " + e);
}
