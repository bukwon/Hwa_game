
// MFCApplication1Dlg.h : 헤더 파일
//

#pragma once
#include"card.h"
#include<stdlib.h>
#include<time.h>
#include "afxwin.h"
#define CARD_COUNT_MAX 48
#define CARD_SHAPE_COUNT_MAX	12//카드 갯수

#define CARD_SHAPE_COUNT	4//실제 카드 게임에 활용하는 카드 갯수
// CMFCApplication1Dlg 대화 상자

struct Card
{
	bool LiveState = false; // false 일경우 덱이들고있고 true는 플레이어가 들고있음
	bool PushState = false; // false 일경우 덱에있고 true일경우 판에있음
	CImage image;
	CRect rect;
	int ShpaeIndex;
	int Width;
	int Height;
	int Point;
	
};
struct Player
{
	int Point = 0;
	int GetActiveIndex[CARD_COUNT_MAX] = { 0 };
	int Getindex[10] = { 0 };
	int GetCardCount = 0;
	int GetActiveCardCount = 0;
	int x;
	int y;
	int Getx;
	int Gety;
};
class CMFCApplication1Dlg : public CDialogEx
{
private:
	int PlayerCount;
	CImage BackGround;
	CImage TitleImage;
	Card CardList[CARD_COUNT_MAX];
	int CardindexList[CARD_COUNT_MAX];
	Player P[3];
	BOOL PlayState;
	int Turn = 0;
	int Mainx;
	int Mainy;
	int CurCardindex;
	int StartCard;
	int StartPan;
// 생성입니다.
public:
	void GameSet();
	void GetCard(int index, int Selectindex);
	int MachAllCard();
	int CardClickCheck(CPoint point);
	void CardOpen();
	void DeletePlayerCard(int Playerindex, int Cardindex);
	int SelectCard(int index);
	void CardSuffle();
	void PlayerGetCard(int index, int cardindex);
	void SetCardSize(int index,int x,int y);
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEnChangeEdit2();
	CEdit Player1Point;
	CEdit Player3Point;
	afx_msg void OnEnChangeEdit1();
	CEdit Player2Point;
	afx_msg void OnEnChangeEdit4();
	CEdit Winer;
};
