
// MFCApplication1Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CMFCApplication1Dlg ��ȭ ����



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


// CMFCApplication1Dlg �޽��� ó����


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
	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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
	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.
	CString str;
	for(int i = 0; i < CARD_COUNT_MAX; i++)
		CardindexList[i] = i;
	int Count = 0;
	for (int i = 1; i <= CARD_SHAPE_COUNT_MAX; i++)
	{
		for (int j = 1; j <= CARD_SHAPE_COUNT; j++)
		{
			str.Format(_T("res\\card\\%d-%d.bmp"), i,j);// ȭ������ �������� ���� �ƴ϶� CString Ŭ������ ���ڿ��� ������.
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
	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CDialogEx::OnPaint();

		CPaintDC dc(this);//CDCŬ������ �θ� Ŭ�����ε� HDC�� ���� ������ �����ε��� ���� �־
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

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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

void CMFCApplication1Dlg::OnBnClickedOk() //���ӽ��� ��ư
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


void CMFCApplication1Dlg::GetCard(int index, int Selectindex) //ī�� �������� ������ �ѱ�� �Լ�
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

void CMFCApplication1Dlg::OnLButtonDown(UINT nFlags, CPoint point) //Ŭ�� �̺�Ʈ
{
	int index = CardClickCheck(point); // �ڽ��� ī�带 Ŭ���ߴ��� Ȯ���ϴ� �Լ�
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CMFCApplication1Dlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}


void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}



void CMFCApplication1Dlg::OnEnChangeEdit2()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CMFCApplication1Dlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CMFCApplication1Dlg::OnEnChangeEdit4()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
