
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
	CStringArray m_sFileConverted;
	CString     m_FILE_NAME;

	CString g_x;
	CString g_y;
	CString g_z;
	CString g_convertedLoadToolLine;
	CString g_convertedSpindlLine;
	
	//bool g_cooling;

	void findSubprogramPathName(CString path);
	void openSubprogramPathName(CString path);
	void foundProgramName(CString line);
	void foundComment(CString line);
	void foundCycl(CString line);
	void foundMovement(CString line);
	void addDecimalPlace(CString& line);
	void fillCoordinates(CString line, char c, int index, CString& g_coordinate);
	void foundCooling(CString line);
	void OpenNewFile();
	void findToolCycle(int index);
	void findToolCall(CString line);
	void findCircle(CString lineCC,CString lineC);
public:
	//CMCDtoNCLDlg();
	afx_msg void OnBnClickedButtonSave();
//	CEdit m_EDIT_FILE_OUTPUT;
	CEdit m_EDIT_FILE_OUTPUT;
	afx_msg void OnBnClickedButtonConvert();
	
	
};
