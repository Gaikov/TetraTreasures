// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file GameApp.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "GameApp.h"
#include "MenuInGame.h"
#include "MenuMain.h"
#include "MenuScore.h"
#include "MenuMsg.h"
#include "MenuEsc.h"
#include "Field.h"
#include "FigureBase.h"
#include "Treasures.h"
#include "MenuAds.h"

nsGameApp	*g_app = 0;

//---------------------------------------------------------
// App_GetInfo:
//---------------------------------------------------------
IAppInfo* App_GetInfo()
{
	if ( !g_app )
		g_app = new nsGameApp;
	return g_app;
}

//---------------------------------------------------------
// nsGameApp::Init:
//---------------------------------------------------------
bool nsGameApp::Init()
{
	TPlatform	*p = TPlatform::GetInstance();
	p->SetDisplay( 640, 480, false );
	p->SetWindowTitle( "Tetra-Treasures 1.0a" );

	if ( !nsFigureBase::Init() ) return false;
	if ( !nsField::Init() ) return false;
	if ( !nsTreasures::Init() ) return false;

	g_menu->StylesLoad( "scripts/menu_styles.txt" );

	g_menu->WndRegister( new nsMenuInGame( "IDM_INGAME" ), "scripts/menu_ingame.txt" );
	g_menu->WndRegister ( new nsMenuMain( "IDM_MAIN" ), "scripts/menu_main.txt" );
	g_menu->WndRegister( new nsMenuScore( "IDM_SCORE" ), "scripts/menu_score.txt" );
	g_menu->WndRegister( new nsMenuMsg( "IDM_MESSAGE" ), "scripts/menu_msg.txt" );
	g_menu->WndRegister( new nsMenuEsc( "IDM_ESC" ), "scripts/menu_esc.txt" );
	g_menu->WndRegister( new nsMenuAds( "IDM_ADS" ), 0 );
	g_menu->WndActivate( "IDM_INGAME" );
	g_menu->WndActivate( "IDM_MAIN" );

	return true;
}

//---------------------------------------------------------
// nsGameApp::Release:
//---------------------------------------------------------
void nsGameApp::Release()
{
	nsTreasures::Release();
	nsField::Release();
	nsFigureBase::Release();

	delete g_app;
	g_app = 0;
}

//---------------------------------------------------------
// nsGameApp::GetAppName:
//---------------------------------------------------------
const char* nsGameApp::GetAppName()
{
	return "TTreasure";
}

//---------------------------------------------------------
// nsGameApp::GetUserInput:
//---------------------------------------------------------
void nsGameApp::GetUserInput( IUserInput::list_t &ui )
{
}

//---------------------------------------------------------
// nsGameApp::Loop:
//---------------------------------------------------------
void nsGameApp::Loop( float frameTime )
{

}

//---------------------------------------------------------
// nsGameApp::DrawWorld:
//---------------------------------------------------------
void nsGameApp::DrawWorld()
{
	g_menu->Draw();
}
