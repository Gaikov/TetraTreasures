// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuScore.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "MenuScore.h"
#include "MenuMsg.h"
#include "CorePG/MenuEdit.h"

#ifdef _DEBUG
#define SCORE_ADD "http://localhost/free-casual-game/ttreasures/score_add.php"
#else
#define SCORE_ADD "http://free-casual-game.com/ttreasures/score_add.php"
#endif

nsMenuScore::nsMenuScore( const char *id ) :
	nsMenuWnd( id )
{

}

//---------------------------------------------------------
// nsMenuScore::OnEvent:
//---------------------------------------------------------
bool nsMenuScore::OnEvent( const char *msg )
{
	if ( StrEqual( msg, "open" ) )
	{
		UpdateScore();
		UpdateTime();
		return true;
	}

	return false;
}

//---------------------------------------------------------
// nsMenuScore::OnCtrlEvent:
//---------------------------------------------------------
bool nsMenuScore::OnCtrlEvent( nsMenuControl *ctrl, const char *msg )
{
	nsString	id = ctrl->GetID();
	
	if ( StrEqual( msg, "button_click" ) )
	{
		if ( id == "ID_CANCEL" )
		{
			Close();
			g_menu->WndActivate( "IDM_MAIN" );
			return true;
		}
		else if ( id == "ID_SUBMIT" )
		{
			const char *name = GetUserName();
			if ( !StrCheck( name ) )
			{
				nsMenuMsg::ShowMsg( "WARNING", "Please, enter your name!" );
			}
			else if ( !SumbitScore() )
			{
				nsMenuMsg::ShowMsg( "WARNING", "Can't connect to server!\nPlease, try again!" );
			}
			else
			{
				Close();
				g_menu->WndActivate( "IDM_MAIN" );
				TPlatform::GetInstance()->OpenBrowser( ONLINE_LINK );
			}
			return true;
		}
	}
	
	return false;
}

//---------------------------------------------------------
// nsMenuScore::UpdateTime:
//---------------------------------------------------------
void nsMenuScore::UpdateTime()
{
	nsStaticText	*t = GetStaticByID( "IDT_TIME" );
	if ( t )
	{
		nsString	time;
		Time_Format( time.AsChar(), g_gameStat.m_time );
		t->SetText( time );
	}
}

//---------------------------------------------------------
// nsMenuScore::UpdateScore:
//---------------------------------------------------------
void nsMenuScore::UpdateScore()
{
	nsStaticText	*t = GetStaticByID( "IDT_SCORE" );
	if ( t )
	{
		nsString	score;
		score.Format( "$%i", g_gameStat.m_score );
		t->SetText( score );
	}	
}

//---------------------------------------------------------
// nsMenuScore::SumbitScore:
//---------------------------------------------------------
bool nsMenuScore::SumbitScore()
{
	TSimpleHttp	http;
	http.Init( SCORE_ADD );
	http.AddArg( "user", GetUserName() );
	http.AddArg( "score", g_gameStat.m_score );
	http.AddArg( "time", (int32_t)g_gameStat.m_time );
	http.DoRequest( TSimpleHttp::eDoNotWriteCache );
	while ( 1 )
	{
		TSimpleHttp::EStatus	state = http.GetStatus();
		switch ( state )
		{
		case TSimpleHttp::eNetDone:
			return true;
		case TSimpleHttp::eNetError:
		case TSimpleHttp::eFileError:
			return false;
		}
	}

	return false;
}

//---------------------------------------------------------
// nsMenuScore::GetUserName:
//---------------------------------------------------------
const char* nsMenuScore::GetUserName()
{
	nsMenuEdit	*edit = (nsMenuEdit*)GetCtrlByID( "ID_NAME" );
	if ( edit )
		return edit->GetText();
	return 0;
}