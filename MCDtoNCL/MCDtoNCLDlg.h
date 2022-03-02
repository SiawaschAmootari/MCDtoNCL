
// MCDtoNCLDlg.h : header file
//

#pragma once


// CMCDtoNCLDlg dialog
class CMCDtoNCLDlg : public CDialogEx
{
// Construction
public:
	CMCDtoNCLDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MCDTONCL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpenPath();
	afx_msg void OnBnClickedButtonOpenNewFile();

private:
	CListBox m_LIST_MESSAGES;
	CComboBox m_COMBO_FILE_PATH;
	CEdit m_EDIT_FILE_INPUT;
	CString     g_sFilePath;
	CStringArray m_sFilecontent;
	CString     m_FILE_NAME;
};
