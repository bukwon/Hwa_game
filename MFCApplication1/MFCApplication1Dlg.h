
// MFCApplication1Dlg.h : ��� ����
//

#pragma once
#include"card.h"
#include<stdlib.h>
#include<time.h>
#include "afxwin.h"
#define CARD_COUNT_MAX 48
#define CARD_SHAPE_COUNT_MAX	12//ī�� ����

#define CARD_SHAPE_COUNT	4//���� ī�� ���ӿ� Ȱ���ϴ� ī�� ����
// CMFCApplication1Dlg ��ȭ ����

struct Card
{
	bool LiveState = false; // false �ϰ�� ���̵���ְ� true�� �÷��̾ �������
	bool PushState = false; // false �ϰ�� �����ְ� true�ϰ�� �ǿ�����
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
// �����Դϴ�.
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
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
