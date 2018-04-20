// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuWnd.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "MenuWnd.h"
#include "MenuMgr.h"
#include "StrTools.h"

//---------------------------------------------------------
// nsMenuWnd::nsMenuWnd:
//---------------------------------------------------------
nsMenuWnd::nsMenuWnd( const char *menuID ) :
	m_id( menuID ),
	m_focusCtrl( 0 ),
	m_captureCtrl( 0 ),
	m_parent( 0 )
{

}

//---------------------------------------------------------
// nsMenuWnd::~nsMenuWnd:
//---------------------------------------------------------
nsMenuWnd::~nsMenuWnd()
{

}

//---------------------------------------------------------
// nsMenuWnd::GetStaticByID:
//---------------------------------------------------------
nsStaticText* nsMenuWnd::GetStaticByID( const char *id )
{
	if ( !StrCheck( id ) ) return 0;

	textList_t::iterator	it;
	for ( it = m_textList.begin(); it != m_textList.end(); ++it )
	{
		nsStaticText::sp_t	&text = (*it);
		if ( StrEqual( text->GetID(), id ) )
			return text;
	}
	return 0;
}

//---------------------------------------------------------
// nsMenuWnd::GetCtrlByID:
//---------------------------------------------------------
nsMenuControl* nsMenuWnd::GetCtrlByID( const char *id, const char *classID )
{
	if ( !StrCheck( id ) ) return 0;

	ctrlList_t::iterator	it;
	for ( it = m_ctrlList.begin(); it != m_ctrlList.end(); ++it )
	{
		nsMenuControl::sp_t	&ctrl = (*it);
		if ( StrEqual( ctrl->GetID(), id ) )
		{
			if ( StrCheck( classID ) )
			{
				if ( StrEqual( ctrl->GetClassID(), classID ) )
					return ctrl;
			}
			else
				return ctrl;
		}
	}

	return 0;
}

//---------------------------------------------------------
// nsMenuWnd::Parse:
//---------------------------------------------------------
bool nsMenuWnd::Parse( script_state_t *ss )
{
	m_drawParent = ps_get_f( ss, "draw_parent" ) ? true : false;

	if ( ps_block_begin( ss, "frame" ) )
	{
		do 
		{
			nsMenuFrame	*frame = new nsMenuFrame;
			if ( frame->Parse( ss ) )
				m_frameList.push_back( frame );
			else
				delete frame;
		}
		while( ps_block_next( ss ) );
		ps_block_end( ss );
	}

	if ( ps_block_begin( ss, "text" ) )
	{
		do 
		{
			nsStaticText	*text = new nsStaticText;
			if ( text->Parse( ss ) )
				m_textList.push_back( text );
			else
				delete text;
		}
		while( ps_block_next( ss ) );
		ps_block_end( ss );
	}

	if ( ps_block_begin( ss, "image" ) )
	{
		do 
		{
			nsStaticImage	*img = new nsStaticImage;
			if ( img->Parse( ss ) )
				m_imgList.push_back( img );
			else
				delete img;
		}
		while( ps_block_next( ss ) );
		ps_block_end( ss );
	}

	if ( ps_block_begin( ss, 0 ) )
	{
		do 
		{
			char	name[256];
			ps_block_get( ss, name, 256 );
			nsMenuControl *ctrl = g_menu->CtrlCreate( name );
			if ( ctrl )
			{
				ctrl->m_owner = this;
				if ( ctrl->Parse( ss ) )
					m_ctrlList.push_back( ctrl );
				else
					delete ctrl;
			}
		}
		while( ps_block_next( ss ) );
		ps_block_end( ss );
	}

	return true;
}

//---------------------------------------------------------
// nsMenuWnd::Loop:
//---------------------------------------------------------
void nsMenuWnd::Loop( float time )
{
	ctrlList_t::iterator	it;
	for ( it = m_ctrlList.begin(); it != m_ctrlList.end(); ++it )
	{
		nsMenuControl::sp_t	&ctrl = (*it);
		ctrl->Move( time );
	}
}

//---------------------------------------------------------
// nsMenuWnd::Draw:
//---------------------------------------------------------
void nsMenuWnd::Draw()
{
	{
		frameList_t::iterator	it;
		for ( it = m_frameList.begin(); it != m_frameList.end(); ++it )
		{
			nsMenuFrame::sp_t	&frame = (*it);
			frame->Draw();
		}
	}

	{
		imgList_t::iterator	it;
		for ( it = m_imgList.begin(); it != m_imgList.end(); ++it )
		{
			nsStaticImage::sp_t	&img = (*it);
			img->Draw();
		}
	}

	{
		textList_t::iterator	it;
		for ( it = m_textList.begin(); it != m_textList.end(); ++it )
		{
			nsStaticText::sp_t	&text = (*it);
			text->Draw();
		}
	}

	{
		ctrlList_t::iterator	it;
		for ( it = m_ctrlList.begin(); it != m_ctrlList.end(); ++it )
		{
			nsMenuControl::sp_t	&ctrl = (*it);
			ctrl->Draw();
			//ctrl->DrawDebug();	//HACK:
		}
	}
}

//---------------------------------------------------------
// nsMenuWnd::OnEvent:
//---------------------------------------------------------
bool nsMenuWnd::OnEvent( const char *msg )
{
	return false;
}

//---------------------------------------------------------
// nsMenuWnd::OnCtrlEvent:
//---------------------------------------------------------
bool nsMenuWnd::OnCtrlEvent( nsMenuControl *ctrl, const char *msg )
{
	return false;
}

//---------------------------------------------------------
// nsMenuWnd::OnChildEvent:
//---------------------------------------------------------
bool nsMenuWnd::OnChildEvent( nsMenuWnd *wnd, const char *msg )
{
	return false;
}

//---------------------------------------------------------
// nsMenuWnd::Close:
//---------------------------------------------------------
void nsMenuWnd::Close()
{
	g_menu->WndCloseTop();
}

//---------------------------------------------------------
// nsMenuWnd::OnKeyUp:
//---------------------------------------------------------
void nsMenuWnd::OnKeyUp( int key )
{
	if ( m_focusCtrl && !m_captureCtrl )
		m_focusCtrl->OnKeyUp( key );
}

//---------------------------------------------------------
// nsMenuWnd::OnKeyDown:
//---------------------------------------------------------
void nsMenuWnd::OnKeyDown( int key, bool rept )
{
	if ( m_focusCtrl && !m_captureCtrl )
		m_focusCtrl->OnKeyDown( key, rept );
}

//---------------------------------------------------------
// nsMenuWnd::OnChar:
//---------------------------------------------------------
void nsMenuWnd::OnChar( char ch )
{
	if ( m_focusCtrl && !m_captureCtrl )
		m_focusCtrl->OnChar( ch );
}

//---------------------------------------------------------
// nsMenuWnd::OnLButtonUp:
//---------------------------------------------------------
void nsMenuWnd::OnLButtonUp( float x, float y )
{
	if ( m_captureCtrl )
	{
		m_captureCtrl->OnLButtonUp( x, y );
		m_captureCtrl->CaptureDec();
		if ( !m_captureCtrl->IsCaptured() )
			m_captureCtrl = 0;
	}

}

//---------------------------------------------------------
// nsMenuWnd::OnLButtonDown:
//---------------------------------------------------------
void nsMenuWnd::OnLButtonDown( float x, float y )
{
	if ( m_focusCtrl )
	{
		m_focusCtrl->OnLButtonDown( x, y );
		m_focusCtrl->CaptureInc();
		m_captureCtrl = m_focusCtrl;
	}
}

//---------------------------------------------------------
// nsMenuWnd::OnMouseMove:
//---------------------------------------------------------
void nsMenuWnd::OnMouseMove( float x, float y )
{
	if ( m_captureCtrl )
		m_captureCtrl->OnMouseMove( x, y );
	else if ( m_focusCtrl )
	{
		if ( !m_focusCtrl->HitTest( x, y ) )
		{
			m_focusCtrl->OnMouseOut();
			m_focusCtrl = 0;
		}

		if ( m_focusCtrl )
			m_focusCtrl->OnMouseMove( x, y );
	}
	else
	{
		ctrlList_t::iterator	it;
		for ( it = m_ctrlList.begin(); it != m_ctrlList.end(); ++it )
		{
			nsMenuControl::sp_t	&ctrl = (*it);
			if ( ctrl->HitTest( x, y ) )
			{
				ctrl->OnMouseMove( x, y );
				ctrl->OnMouseIn();
				m_focusCtrl = ctrl;
				break;
			}
		}
	}
}