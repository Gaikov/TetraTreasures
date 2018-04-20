// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuInGame.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_MenuInGame_H_
#define	_MenuInGame_H_

#include "common.h"
#include "FigureView.h"
#include "FigureRotator.h"

class nsMenuInGame : public nsMenuWnd
{
public:
	nsMenuInGame( const char *id );
	~nsMenuInGame();

	virtual bool OnCtrlEvent( nsMenuControl *ctrl, const char *msg );
	virtual void Loop( float time );
	virtual void Draw();
	virtual void OnMouseMove( float x, float y );
	virtual void OnLButtonDown( float x, float y );
	virtual void OnRButtonDown( float x, float y );

	virtual void OnKeyDown( int key, bool rept );

private:
	nsFigureView	m_fig1, m_fig2;
	nsFigureView	*m_currFig, *m_nextFig;
	nsFigureRotator	m_figRot;

	nsVec2			m_mouse;

	nsImageView		m_placeYes, m_placeNo;
	int				m_figCellX, m_figCellY;
	bool			m_figCanPlace;

	bool			m_nextFigure;

	int				m_prevScore;

private:
	void			NewGame();
	void			NextFigure();
	void			DrawPlace( bool yes );
	void			DrawNextFigure();
	bool			CalcFigureCell();

	void			UpdateTime();
	void			UpdateScore();

	virtual bool	OnChildEvent( nsMenuWnd *wnd, const char *msg );
};

#endif	//_MenuInGame_H_
