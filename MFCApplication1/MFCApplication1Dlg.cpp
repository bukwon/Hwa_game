
// MFCApplication1Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CMFCApplication1Dlg 대화 상자



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, Player1Point);
	DDX_Control(pDX, IDC_EDIT3, Player3Point);
	DDX_Control(pDX, IDC_EDIT1, Player2Point);
	DDX_Control(pDX, IDC_EDIT4, Winer);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDCANCEL, &CMFCApplication1Dlg::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCApplication1Dlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCApplication1Dlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT4, &CMFCApplication1Dlg::OnEnChangeEdit4)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 메시지 처리기


void CMFCApplication1Dlg::CardSuffle()
{
	int index;
	for(int i = 0; i < 50; i++)
	{
		int index1 = rand() % CARD_COUNT_MAX;
		int index2 = rand() % CARD_COUNT_MAX;
		index = CardindexList[index1];
		CardindexList[index1] = CardindexList[index2];
		CardindexList[index2] = index;
	}
}


void CMFCApplication1Dlg::SetCardSize(int index,int x,int y)
{
	CardList[index].Width = CardList[index].image.GetWidth()/2;
	CardList[index].Height = CardList[index].image.GetHeight()/2;
	CardList[index].rect.left = x;
	CardList[index].rect.top = y;
	CardList[index].rect.right = CardList[index].rect.left + CardList[index].Width;
	CardList[index].rect.bottom = CardList[index].rect.top + CardList[index].Height;
}

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	GetDlgItem(IDC_EDIT2)->SendMessage(EM_SETREADONLY, 1, 0);
	GetDlgItem(IDC_EDIT1)->SendMessage(EM_SETREADONLY, 1, 0);
	GetDlgItem(IDC_EDIT3)->SendMessage(EM_SETREADONLY, 1, 0);
	GetDlgItem(IDC_EDIT4)->SendMessage(EM_SETREADONLY, 1, 0);
	
	srand(time(NULL));
	CDialogEx::OnInitDialog();
	MoveWindow(0, 0, 1700, 768);
	PlayState = false;
	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.
	CString str;
	for(int i = 0; i < CARD_COUNT_MAX; i++)
		CardindexList[i] = i;
	int Count = 0;
	for (int i = 1; i <= CARD_SHAPE_COUNT_MAX; i++)
	{
		for (int j = 1; j <= CARD_SHAPE_COUNT; j++)
		{
			str.Format(_T("res\\card\\%d-%d.bmp"), i,j);// 화면으로 내보내는 것이 아니라 CString 클래스가 문자열을 가진다.
			CardList[Count].image.Load(str);
			if ((i == 1 || i == 3 || i == 8 || i == 11 || i == 12) && j == 1)
				CardList[Count].Point = 20;
			else if ((i == 8 && j == 2) || (i == 12 && j == 2))
				CardList[Count].Point = 10;
			else if( j== 1 && (i != 8 || i != 12 || i != 11))
				CardList[Count].Point = 10;
			else if( (j == 2 && (i != 8 && i != 11)) || (j ==3 && i == 12))
				CardList[Count].Point = 5;
			else
				CardList[Count].Point = 0;
			CardList[Count].LiveState = false;
			CardList[Count].ShpaeIndex = i;
			Count++;
		}
	}
	BackGround.Load("res\\card\\BackGround.bmp");
	TitleImage.Load("res\\card\\main_menu.bmp");
	Count = 0;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			SetCardSize(Count++, i * 80, j * 120);
		}
	}
	Mainx = 100;
	Mainy = 300;
	P[0].x = 400;
	P[0].y = 470;
	P[0].Getx = 400;
	P[0].Gety = 600;
	P[1].x = 0;
	P[1].y = 120;
	P[1].Getx = 0;
	P[1].Gety = 0;
	P[2].x = 850;
	P[2].y = 120;
	P[2].Getx = 850;
	P[2].Gety = 0;
	CurCardindex = -1;
	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CDialogEx::OnPaint();

		CPaintDC dc(this);//CDC클래스가 부모 클래스인데 HDC에 대해 연산자 오버로딩을 갖고 있어서
		CRect rect;

		BackGround.StretchBlt(dc, 0, 0, BackGround.GetWidth() * 2.5, BackGround.GetHeight() *1.7);
		if(PlayState == false)
		{
			TitleImage.BitBlt(dc, 400, 150);
		}
		else
		{
			int index;
			for(int j = 0; j < PlayerCount; j++)
			{
				for(int i = 0; i < P[j].GetCardCount; i++)
				{
					index = P[j].Getindex[i];
					rect = CardList[index].rect;
					CardList[index].image.Draw(dc, rect.left, rect.top, CardList[index].Width, CardList[index].Height);
				}
				for (int i = 0; i < P[j].GetActiveCardCount; i++)
				{
					int x = P[j].Getx;
					int y = P[j].Gety;
					index = P[j].GetActiveIndex[i];
					CardList[index].image.Draw(dc, x+ (i*50),y, CardList[index].Width, CardList[index].Height);
				}
			}
			for(int i = 0, Count = 0; i < CARD_COUNT_MAX; i++)
			{
				if(CardList[CardindexList[i]].LiveState == false && CardList[CardindexList[i]].PushState == true)
					CardList[CardindexList[i]].image.Draw(dc, Mainx + (Count++*CardList[CardindexList[i]].Width + 25), Mainy, CardList[CardindexList[i]].Width, CardList[CardindexList[i]].Height);
			}
		}
		if(CurCardindex != -1)
		{
			CardList[CurCardindex].image.Draw(dc, 1200, 300);
			SetTimer(1, 1000, NULL);
		}
		DeleteDC(dc);
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCApplication1Dlg::PlayerGetCard(int index, int cardindex)
{
	P[index].Getindex[P[index].GetCardCount] = cardindex;
	CardList[cardindex].rect.left = P[index].x + (P[index].GetCardCount * (CardList[cardindex].Width +15));
	CardList[cardindex].rect.top = P[index].y;
	CardList[cardindex].rect.right = CardList[cardindex].rect.left + CardList[cardindex].Width;
	CardList[cardindex].rect.bottom = CardList[cardindex].rect.top + CardList[cardindex].Height;
	CardList[cardindex].LiveState = true;
	P[index].GetCardCount++;
}

int CMFCApplication1Dlg::SelectCard(int index)
{
	int Point = 0;
	int Selectindex = -1;
	for(int i = 0; i < CARD_COUNT_MAX; i++)
	{
		if(CardList[i].ShpaeIndex == index && CardList[i].LiveState == false && CardList[i].PushState == true)
		{
			if(Point <= CardList[i].Point)
			{
				Point = CardList[i].Point;
				Selectindex = i;
			}
		}
	}
	return Selectindex;
}


void CMFCApplication1Dlg::DeletePlayerCard(int Playerindex, int Cardindex)
{
	int i;
	for (i = 0; i < 10; i++)
	{
		if (P[Playerindex].Getindex[i] == Cardindex)
			break;
	}
	for (; i < 9; i++)
	{
		P[Playerindex].Getindex[i] = P[Playerindex].Getindex[i + 1];
		if(i + 1 == 9)
			P[Playerindex].Getindex[i + 1] = -1;
	}
	P[Playerindex].GetCardCount--;
}


void CMFCApplication1Dlg::CardOpen()
{
	for (int i = 0; i < CARD_COUNT_MAX; i++)
	{
		if (CardList[CardindexList[i]].LiveState == false && CardList[CardindexList[i]].PushState == false)
		{
			CurCardindex = CardindexList[i];
			Invalidate();
			break;
		}
	}
	if (CurCardindex == -1)
	{
		SetTimer(2, 1000, NULL);
	}
}


int CMFCApplication1Dlg::CardClickCheck(CPoint point)
{
	if (Turn % PlayerCount != 0)
		return -1;
	for (int i = 0; i < P[Turn % PlayerCount].GetCardCount; i++)
	{
		int index = P[Turn % PlayerCount].Getindex[i];
		if (PtInRect(&CardList[index].rect, point))
			return index;
	}
	return -1;
}

void CMFCApplication1Dlg::OnBnClickedOk() //게임시작 버튼
{

}

int CMFCApplication1Dlg::MachAllCard()
{
	int MaxPoint = 0;
	int Maxindex = -1;
	for (int i = 0; i < 10; i++)
	{
		int index = P[Turn % PlayerCount].Getindex[i];
		if (index == -1)
			break;
		int Selectindex = SelectCard(CardList[index].ShpaeIndex);
		if (Selectindex != -1)
		{
			int tmpPoint = CardList[index].Point + CardList[Selectindex].Point;
			if (tmpPoint >= MaxPoint)
			{
				MaxPoint = tmpPoint;
				Maxindex = index;
			}
		}
	}
	return Maxindex;
}


void CMFCApplication1Dlg::GetCard(int index, int Selectindex) //카드 가져가고 다음턴 넘기기 함수
{
	CString str;
	CardList[Selectindex].LiveState = true;
	CardList[index].PushState = true;
	DeletePlayerCard(Turn % PlayerCount, index);
	P[Turn % PlayerCount].GetActiveIndex[P[Turn % PlayerCount].GetActiveCardCount++] = Selectindex;
	P[Turn % PlayerCount].GetActiveIndex[P[Turn % PlayerCount].GetActiveCardCount++] = index;
	P[Turn % PlayerCount].Point += CardList[index].Point;
	P[Turn % PlayerCount].Point += CardList[Selectindex].Point;
	str.Format(_T("Point : %d"), P[Turn% PlayerCount].Point);
	switch (Turn % PlayerCount)
	{
	case 0:
		Player1Point.SetWindowTextA(str);
		break;
	case 1:
		Player2Point.SetWindowTextA(str);
		break;
	case 2:
		Player3Point.SetWindowTextA(str);
		break;
	}
	Invalidate();
	CardOpen();
}

void CMFCApplication1Dlg::OnLButtonDown(UINT nFlags, CPoint point) //클릭 이벤트
{
	int index = CardClickCheck(point); // 자신의 카드를 클릭했는지 확인하는 함수
	int Selectindex = SelectCard(CardList[index].ShpaeIndex);
	if (Selectindex != -1)
		GetCard(index, Selectindex);
	else
	{
		DeletePlayerCard(Turn % PlayerCount, index);
		CardList[index].LiveState = false;
		CardList[index].PushState = true;
		CardOpen();
		Invalidate();
	}
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
}



void CMFCApplication1Dlg::GameSet()
{
	Turn = 0;
	CString str;
	str.Format(_T("Winer : "));
	Winer.SetWindowTextA(str);
	CurCardindex = -1;
	PlayState = true;
	for (int i = 0; i < PlayerCount; i++)
	{
		P[i].GetCardCount = 0;
		P[i].Point = 0;
		memset(P[i].Getindex, -1, sizeof(P[i].Getindex));
		memset(P[i].GetActiveIndex, -1, sizeof(P[i].GetActiveIndex));
		P[i].GetActiveCardCount = 0;
	}
	CString str2;
	str2.Format(_T("Point : %d"), P[0].Point);
	Player1Point.SetWindowTextA(str2);
	str2.Format(_T("Point : %d"), P[1].Point);
	Player2Point.SetWindowTextA(str2);
	if (PlayerCount == 3)
	{
		str2.Format(_T("Point : %d"), P[2].Point);
		Player3Point.SetWindowTextA(str2);
	}
	for (int i = 0; i < CARD_COUNT_MAX; i++)
	{
		CardList[i].LiveState = false;
		CardList[i].PushState = false;
	}
	CardSuffle();
	for (int i = 0; i < StartCard; i++)
		PlayerGetCard(0, CardindexList[i]);
	for (int i = 10; i < 10 + StartCard; i++)
		PlayerGetCard(1, CardindexList[i]);
	if (PlayerCount == 3)
	{
		for (int i = 20; i < 20 + StartCard; i++)
			PlayerGetCard(2, CardindexList[i]);
	}
	for (int i = 0, Count = 0; i < CARD_COUNT_MAX && Count < StartPan; i++)
	{
		if (CardList[i].LiveState == false)
		{
			CardList[i].PushState = true;
			Count++;
		}
	}
	Invalidate();
}
void CMFCApplication1Dlg::OnBnClickedButton1()
{
	if (PlayState == false)
	{
		PlayerCount = 2;
		StartCard = 10;
		StartPan = 8;
		GameSet();
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCApplication1Dlg::OnBnClickedButton2()
{
	if (PlayState == false)
	{
		PlayerCount = 3;
		StartCard = 7;
		StartPan = 6;
		GameSet();
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCApplication1Dlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString str;
	if(nIDEvent == 1)
	{
		BOOL Flag = false;
		for (int i = 0; i < CARD_COUNT_MAX; i++)
		{
			if (i == CurCardindex)
				continue;
			if (CardList[i].ShpaeIndex == CardList[CurCardindex].ShpaeIndex && CardList[i].LiveState == false && CardList[i].PushState == true)
			{
				CardList[i].LiveState = true;
				CardList[CurCardindex].LiveState = true;
				CardList[CurCardindex].PushState = true;
				P[Turn % PlayerCount].GetActiveIndex[P[Turn % PlayerCount].GetActiveCardCount++] = i;
				P[Turn % PlayerCount].GetActiveIndex[P[Turn % PlayerCount].GetActiveCardCount++] = CurCardindex;
				P[Turn % PlayerCount].Point += CardList[CurCardindex].Point;
				P[Turn % PlayerCount].Point += CardList[i].Point;
				str.Format(_T("Point : %d"), P[Turn % PlayerCount].Point);
				switch (Turn % PlayerCount)
				{
				case 0:
					Player1Point.SetWindowTextA(str);
					break;
				case 1:
					Player2Point.SetWindowTextA(str);
					break;
				case 2:
					Player3Point.SetWindowTextA(str);
					break;
				}
				Flag = true;
				break;
			}
		}
		if (Flag == false)
		{
			CardList[CurCardindex].PushState = true;
		}
		CurCardindex = -1;
		KillTimer(1);
		Turn++;
		int EndCount = 0;
		for (int i = 0; i < PlayerCount; i++)
		{
			if (P[i].Getindex[0] == -1)
				EndCount++;
		}
		if (EndCount == PlayerCount)
		{
			PlayState = false;
			int winPlayer;
			int WinPoint = 0;
			for (int i = 0; i < PlayerCount; i++)
			{
				if (WinPoint < P[i].Point)
				{
					WinPoint = P[i].Point;
					winPlayer = i;
				}
			}
			CString str;
			str.Format(_T("Winer : Player%d"), winPlayer + 1);
			Winer.SetWindowTextA(str);
			Invalidate();
			return;
		}
		if (Turn % PlayerCount != 0)
			SetTimer(2, 1000, NULL);
		Invalidate();
	}
	if (nIDEvent == 2)
	{
		int index = MachAllCard();
		if (Turn % PlayerCount != 0 && index != -1)
		{
			int Selectindex = SelectCard(CardList[index].ShpaeIndex);
			if (Selectindex != -1)
				GetCard(index, Selectindex);
		}
		else if (Turn % PlayerCount != 0 && index == -1)
		{
			P[Turn% PlayerCount].GetCardCount--;
			CardList[P[Turn% PlayerCount].Getindex[P[Turn% PlayerCount].GetCardCount]].LiveState = false;
			CardList[P[Turn% PlayerCount].Getindex[P[Turn% PlayerCount].GetCardCount]].PushState = true;
			P[Turn% PlayerCount].Getindex[P[Turn% PlayerCount].GetCardCount] = -1;
			Invalidate();
		}
		CardOpen();
		KillTimer(2);
	}
}


void CMFCApplication1Dlg::OnBnClickedButton3()
{
	if(PlayState == true && Turn% PlayerCount == 0)
		CardOpen();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



void CMFCApplication1Dlg::OnEnChangeEdit2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCApplication1Dlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCApplication1Dlg::OnEnChangeEdit4()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
