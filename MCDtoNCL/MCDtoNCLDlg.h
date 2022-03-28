
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

private:
	CListBox m_LIST_MESSAGES;
	CComboBox m_COMBO_FILE_PATH;

	CStringArray m_sFilecontent;
	CStringArray m_sFileConverted;
	CStringArray g_conversionHistory;
	CStringArray g_pprintList;
	CStringArray g_toolList;

	CEdit m_EDIT_FILE_OUTPUT;
	CEdit m_EDIT_FILE_INPUT;

	CString g_x;
	CString g_y;
	CString g_z;
	CString g_fedRat;
	CString g_diameter;
	CString g_radius;
	int g_toolListIndex;
	CString g_convertedLoadToolLine;
	CString g_convertedSpindlLine;
	CString g_sFilePath;
	CString m_FILE_NAME;


	void findSubprogramPathName(CString path);
	void findProgramName(CString line);
	void findComment(CString line);
	void findTolerance(CString line);
	void findMovement(CString line);
	void findCooling(CString line);
	void findToolCycle(int index);
	void findToolCall(CString line);
	void findCircle(CString lineCC,CString lineC);
	
	void OpenNewFile();
	void fillCoordinates(CString line, char c, int index, CString& g_coordinate);
	void findFedRat(CString line,int index, CString& g_fedRat);
	void addDecimalPlace(CString& line);
	void openSubprogramPathName(CString path);
	void commentCycle(int& index);
	void removeLeadingZero(CString& value);

public:
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonConvert();
	afx_msg void OnBnClickedButtonOpenPath();
	afx_msg void OnBnClickedButtonOpenNewFile();

};
