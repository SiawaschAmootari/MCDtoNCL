
// MCDtoNCLDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MCDtoNCL.h"
#include "MCDtoNCLDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMCDtoNCLDlg dialog



CMCDtoNCLDlg::CMCDtoNCLDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MCDTONCL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMCDtoNCLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_FILE_PATH, m_COMBO_FILE_PATH);
	DDX_Control(pDX, IDC_EDIT_FILE_INPUT, m_EDIT_FILE_INPUT);
	//  DDX_Control(pDX, IDC_LIST_MESSAGES, m_LIST_MESSAGES);
	DDX_Control(pDX, IDC_LIST_MESSAGES, m_LIST_MESSAGES);
	//  DDX_Control(pDX, IDC_EDIT_FILE_OUTPUT, m_EDIT_FILE_OUTPUT);
	DDX_Control(pDX, IDC_EDIT_FILE_OUTPUT, m_EDIT_FILE_OUTPUT);
}

BEGIN_MESSAGE_MAP(CMCDtoNCLDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_PATH, &CMCDtoNCLDlg::OnBnClickedButtonOpenPath)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_NEW_FILE, &CMCDtoNCLDlg::OnBnClickedButtonOpenNewFile)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CMCDtoNCLDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CONVERT, &CMCDtoNCLDlg::OnBnClickedButtonConvert)
	
END_MESSAGE_MAP()


// CMCDtoNCLDlg message handlers

BOOL CMCDtoNCLDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMCDtoNCLDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMCDtoNCLDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMCDtoNCLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMCDtoNCLDlg::OnBnClickedButtonOpenPath()
{
	// TODO: Add your control notification handler code here
}


void CMCDtoNCLDlg::OnBnClickedButtonOpenNewFile()
{
	// TODO: Add your control notification handler code here
	try
	{
		CFileDialog cFileDialog(true, NULL, NULL, NULL, _T("h-files(*.h)|*.h;|All-files(*.*)|*.*;|"));

		int iId;
		iId = (int)cFileDialog.DoModal();
		bool bOk = true;
		//CString m_sInputfile;
		CStdioFile file;
		if (iId == IDOK)
		{
			g_sFilePath = cFileDialog.GetPathName();
			if (std::ifstream(g_sFilePath).good())
			{
				CString sNewName = g_sFilePath + "_backup";
				m_COMBO_FILE_PATH.InsertString(0, g_sFilePath);
				//rename(m_sInputfile, newName);
				CStdioFile file;
				file.Open(g_sFilePath, CStdioFile::modeRead);

				CString sLine =_T("");
				bool bRead;
				CString sFilecontent = _T("");
				int i = 0;

				m_sFilecontent.RemoveAll();
				m_FILE_NAME = g_sFilePath;

				while (true)
				{
					bRead = file.ReadString(sLine);
					if (bRead == false)
					{
						break;
					}
					if (sLine.Find(_T("TNC"))!=-1) {
						m_sFilecontent.Add(sLine);
						findSubprogramPathName(sLine);
						// TEST m_LIST_MESSAGES.InsertString(0, sLine);
					}
					else {
						m_sFilecontent.Add(sLine);
					}
				}
				theApp.ArrToVal(m_sFilecontent, sFilecontent);
				m_EDIT_FILE_INPUT.SetWindowText(sFilecontent);
				file.Close();
			}
			if (m_FILE_NAME.GetLength() <= 0)
			{
				m_LIST_MESSAGES.InsertString(0, _T("No file selected"));
			}
			else
			{
				UpdateData(false);
			}
		}
	}
	catch (const std::out_of_range& e)
	{
		m_LIST_MESSAGES.InsertString(0, _T("No file selected"));
	}
	catch (const std::invalid_argument& e)
	{
		m_LIST_MESSAGES.InsertString(0, _T("Invalid file"));
	}
}


void CMCDtoNCLDlg::findSubprogramPathName(CString path) {

	//path = "CALL PGM TNC : \\1601\\1601303";
	//string sPath((LPCTSTR)path);
	CString newPathNameReversed=_T("");

	if (path.Find(_T("TNC"))!=-1) {
		for (int i = path.GetLength()-1; i > 0; i--) {
			if (path.GetAt(i) == '\\') {
				break;
			}
			newPathNameReversed.AppendChar(path.GetAt(i));
		}
		CString	newPathName = _T("");
		for (int i = newPathNameReversed.GetLength()-1; i > 0; i--) {
			newPathName.AppendChar(newPathNameReversed.GetAt(i));
		}
		newPathName.Append(_T(".h"));

		//m_LIST_MESSAGES.InsertString(0, newPathName);
		//m_LIST_MESSAGES.InsertString(0, g_sFilePath);

		CString newFilePath = g_sFilePath;
		for (int i = newFilePath.GetLength() - 1; i > 0; i--) {
			if (newFilePath.GetAt(i) == '\\') {
				break;
			}
			newFilePath.Delete(i, 1);
		}
		newFilePath.Append(newPathName);
		//m_LIST_MESSAGES.InsertString(0, newFilePath);
		openSubprogramPathName(newFilePath);
	}
	
}

void CMCDtoNCLDlg::OnBnClickedButtonConvert()
{
	CString sFileConverted = _T("");
	for (int i = 0; i < m_sFilecontent.GetSize(); i++) {
		if (m_sFilecontent.GetAt(i).Find(_T("BEGIN")) != -1) {
			foundProgramName(m_sFilecontent.GetAt(i));
		}
		else if (m_sFilecontent.GetAt(i).Find(_T(";")) != -1) {
			foundComment(m_sFilecontent.GetAt(i));
		}
		else {
			m_sFileConverted.Add(m_sFilecontent.GetAt(i));
		}
	}
	theApp.ArrToVal(m_sFileConverted, sFileConverted);
	m_EDIT_FILE_OUTPUT.SetWindowText(sFileConverted);
}

void CMCDtoNCLDlg::foundProgramName(CString line) {
	CStringArray splittLine;
	CString token = _T("");
	CString convertedLine = _T("Dateiname: ");
	int i = 0;

	while (AfxExtractSubString(token, line, i, ' ')) {
		splittLine.Add(token);
		i++;
	}
	convertedLine.Append(splittLine.GetAt(4));
	m_sFileConverted.Add(convertedLine);
}

void CMCDtoNCLDlg::foundComment(CString line) {
	CString convertedLine = _T("PPRINT / ");
	bool foundSemicolon = false;

	for (int i = 0; i < line.GetLength(); i++) {
		if (foundSemicolon == true) {
			convertedLine.AppendChar(line.GetAt(i));
		}
		if (line.GetAt(i) == ';') {
			foundSemicolon = true;
		}
	}
	m_sFileConverted.Add(convertedLine);
}

void CMCDtoNCLDlg::openSubprogramPathName(CString path) {
	//CString g_sFilePath;
	CStdioFile csfFile;
	
	if (std::ifstream(path).good())
	{
		try
		{
			csfFile.Open(path, CStdioFile::modeRead);

			CString sLine = _T("");
			bool bRead;
			CString sFilecontent = _T("");


			while (true)
			{
				bRead = csfFile.ReadString(sLine);
				if (bRead == false)
				{
					break;
				}
				m_sFilecontent.Add(sLine);
			}
			theApp.ArrToVal(m_sFilecontent, sFilecontent);
			m_EDIT_FILE_INPUT.SetWindowText(sFilecontent);
			csfFile.Close();
			
		}
		catch (const std::out_of_range& e)
		{
			m_LIST_MESSAGES.InsertString(0, _T("No file selected"));
		}
		catch (const std::invalid_argument& e)
		{
			m_LIST_MESSAGES.InsertString(0, _T("Invalid file"));
		}
	}
	else
	{
		m_LIST_MESSAGES.InsertString(0, _T("Error: filepath is wrong"));
		m_LIST_MESSAGES.InsertString(0, path);
	}
}

void CMCDtoNCLDlg::OnBnClickedButtonSave()
{
	CFileDialog cFileDialog(false, _T("mpf"), m_FILE_NAME, OFN_OVERWRITEPROMPT, _T("mpf-files (*.mpf)|*.mpf;|text-Files(*.txt)|*.txt;|"));
	int iId;
	iId = (int)cFileDialog.DoModal();
	bool bOk = true;
	CString m_sSavefile;

	if (iId == IDOK)
	{
		m_sSavefile = cFileDialog.GetPathName();
		CStdioFile file(cFileDialog.GetPathName(), CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		for (int iIndexM_sFilecontentNew = 0; iIndexM_sFilecontentNew < m_sFilecontent.GetSize(); iIndexM_sFilecontentNew++)
		{
			file.WriteString(m_sFilecontent.GetAt(iIndexM_sFilecontentNew).GetString());
			file.WriteString(_T("\n"));
		}
		if (m_sFilecontent.GetSize() <= 0)
		{
			m_LIST_MESSAGES.InsertString(0, _T("File is empty!"));
		}
		file.Flush();
		file.Close();
	}
}



