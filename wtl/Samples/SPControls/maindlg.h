// maindlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(_MAINDLG_H_)
#define _MAINDLG_H_

#pragma once

/////////////////////////////////////////////////////////////////////////////

class CMainDlg : public CStdDialogImpl<CMainDlg, WTL_SP_SHIDIF, false>,
		public CMessageFilter, public CIdleHandler, 
		public CAppWindow<CMainDlg>
{
public:

	DECLARE_FRAME_DLG_CLASS(NULL,IDR_MAINFRAME);

	typedef CStdDialogImpl<CMainDlg, WTL_SP_SHIDIF, false> baseDlg;

	enum { IDD = IDD_MAINDLG };

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return ::IsDialogMessage(m_hWnd, pMsg);
	}

	virtual BOOL OnIdle()
	{
		return FALSE;
	}

	void AppSave()
	{
		CAppInfo info;

		CExpandCapEdit ece = GetDlgItem(IDC_CAPEDIT);
		CString s;
		int nLength = ece.GetWindowTextLength();
		ece.GetWindowText(s.GetBufferSetLength(nLength + 1), nLength + 1);
		s.ReleaseBuffer();
		info.Save(s, L"Cap");

		DWORD dwSel = ece.GetSel();
		info.Save(dwSel, L"CapSel");

		CSpinListBox slb = GetDlgItem(IDC_LISTBOX);
		int iSel = slb.GetCurSel();
		info.Save(iSel, L"Spin");
		
		CExpandListBox elb = GetDlgItem(IDC_LISTBOX2);
		int n = elb.GetSelCount();
		int *aiSel = new int[n];
		elb.GetSelItems(n, aiSel);
		info.Save( n, L"Mult");
		info.Save( n, (int&)*aiSel, L"MultSel");
		delete[] aiSel;

		CExpandEdit eed= GetDlgItem(IDC_EDIT1);
		nLength = eed.GetWindowTextLength();
		eed.GetWindowText(s.GetBufferSetLength(nLength + 1), nLength + 1);
		s.ReleaseBuffer();
		info.Save(s, L"Ed");

		dwSel = eed.GetSel();
		info.Save(dwSel, L"EdSel");
	}

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_CLOSE, OnSystemClose)
		COMMAND_RANGE_HANDLER(IDOK, IDCANCEL, OnClose)
		COMMAND_RANGE_HANDLER(ID_MENU_OK, ID_MENU_CANCEL, OnMenuClose)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		CHAIN_MSG_MAP(baseDlg)
		CHAIN_MSG_MAP(CAppWindow<CMainDlg>)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		// set icons
		HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
			IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
		SetIcon(hIcon, TRUE);
		HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
			IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
		SetIcon(hIconSmall, FALSE);

		// register object for message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop(); 
		ATLASSERT(pLoop != NULL);
		pLoop->AddMessageFilter(this);
		pLoop->AddIdleHandler(this);

		// create MenuBar
		HWND hMenuBar = AtlCreateMenuBar(m_hWnd, ATL_IDM_MENU_DONECANCEL);
		ATLASSERT(hMenuBar != NULL);

		// Application state initialization/restoration
		CAppInfo info;

		// CapEdit restoration or initialization
		CExpandCapEdit ece = GetDlgItem(IDC_CAPEDIT);
		CString s = L"capedit controls are not emulated with EVC 4 emulator.";
		info.Restore(s, L"Cap");
		ece.SetWindowText(s);

		DWORD dwSel = 0;
		info.Restore(dwSel, L"CapSel");
		ece.SetSel(dwSel);
		ece.SetFocus();


		// SpinListBox initialization
		CSpinListBox slb= GetDlgItem(IDC_LISTBOX);
		slb.AddString(L"Spin choice 1");
		slb.AddString(L"Spin choice 2");
		slb.AddString(L"Spin choice 3");
		// SpinListBox control restoration
		int iSel = 0;
		info.Restore(iSel, L"Spin");
		slb.SetCurSel(iSel);

		// Multiple choice ExpandListBox initialization
		CExpandListBox elb= GetDlgItem(IDC_LISTBOX2);
		elb.AddString(L"Multiple choice 1");
		elb.AddString(L"Multiple choice 2");
		elb.AddString(L"Multiple choice 3");
		// Multiple choice ExpandListBox restoration
		int n = 0;
		info.Restore( n, L"Mult");
		if (n)
		{
			int *aiSel = new int[n];
			info.Restore( n, (int&)*aiSel, L"MultSel");
			for( int i = 0 ; i < n; i++)
				elb.SetSel(aiSel[i]);
			delete[] aiSel;
		}

		// ExpandEdit restoration or initialization
		CExpandEdit eed= GetDlgItem(IDC_EDIT1);
		s = L"What more do you want?";
		info.Restore(s, L"Ed");
		eed.SetWindowText(s);
		dwSel = 0;
		info.Restore(dwSel, L"EdSel");
		eed.SetSel(dwSel);

		return bHandled = FALSE;
	}

	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CStdSimpleDialog<IDD_ABOUTBOX> dlg;
		dlg.DoModal();
		return 0;
	}

	LRESULT OnMenuClose(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		PostMessage(WM_COMMAND, wID == ID_MENU_OK ? IDOK : IDCANCEL);
		return 0;
	}

	LRESULT OnClose(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CloseDialog(wID);
		return 0;
	}

	LRESULT OnSystemClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CloseDialog(IDCANCEL);
		return 0;
	}

	void CloseDialog(int nVal)
	{
		if (nVal != IDCANCEL)
			AppSave();
		DestroyWindow();
		::PostQuitMessage(nVal);
	}

};


/////////////////////////////////////////////////////////////////////////////

#endif // !defined(_MAINDLG_H_)
