// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Core.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "Core.h"
#include "Config.h"
#include "log.h"
#include "Name.h"
#include "FontManager.h"
#include "LocalMgr.h"
#include "MenuMgr.h"
#include "AppInfo.h"
#include "GameWnd.h"
#include "PartManager.h"
#include <pf/windowmanager.h>
#include <pf/script.h>
#include <pf/event.h>

float g_frameTime = 0;

void nsCore::RunGame()
{
	TPlatform	*pPlatform = TPlatform::GetInstance();
	TRenderer	*r = TRenderer::GetInstance();
	r->SetOption( "new_subtractive", "1" );
	r->SetOption( "fps", "0" );

	IUserInput::list_t	uiList;

	if ( nsCore::Init() )
	{
		uint32_t prevTime = pPlatform->Timer();

		// The main C++ loop
		TEvent event;
		while(true)
		{
			pPlatform->GetEvent(&event);
			if(event.mType == TEvent::kQuit)
			{
				break;
			}

			if (event.mType == TEvent::kClose)
			{
				break;
			}

			if (event.mType == TEvent::kFullScreenToggle)
			{
				//TSettings::GetInstance()->UpdateFullScreen();
			}

			uiList.clear();
			if ( g_menu->IsActive() )
				uiList.push_back( g_menu->WndGetActive() );
			App_GetInfo()->GetUserInput( uiList );

			int	i = 0;

			for ( int i = 0; i < (int)uiList.size(); ++i )
			{
				IUserInput	*ui = uiList[i];
				switch ( event.mType )
				{
				case TEvent::kMouseMove:
					ui->OnMouseMove( (float)event.mPoint.mX, (float)event.mPoint.mY );
					break;

				case TEvent::kMouseDown:
					ui->OnLButtonDown( (float)event.mPoint.mX, (float)event.mPoint.mY );
					break;

				case TEvent::kExtendedMouseEvent:
					if ( event.mKey == 1 )
						ui->OnRButtonDown( (float)event.mPoint.mX, (float)event.mPoint.mY );
					else if ( event.mKey == 0 )
						ui->OnRButtonUp( (float)event.mPoint.mX, (float)event.mPoint.mY );
					break;

				case TEvent::kMouseUp:
					ui->OnLButtonUp( (float)event.mPoint.mX, (float)event.mPoint.mY );
					break;

				case TEvent::kKeyDown:
					ui->OnKeyDown( event.mKey, false );
					break;

				case TEvent::kKeyUp:
					ui->OnKeyUp( event.mKey );
					break;

				case TEvent::kChar:
					ui->OnChar( event.mKey );
					break;
				}
			}


			g_menu->Loop( g_frameTime );
			App_GetInfo()->Loop( g_frameTime );
			g_partManager->MoveAll();
			TWindowManager::GetInstance()->InvalidateScreen();

			// Pass the event to the Window manager for further processing
			TPlatform::GetInstance()->GetWindowManager()->HandleEvent(&event);

			uint currTime = pPlatform->Timer();
			g_frameTime = float(currTime - prevTime) / 1000.0f;
			prevTime = currTime;
		}
	}

	nsCore::Release();
}

//---------------------------------------------------------
// nsCore::Init:
//---------------------------------------------------------
bool nsCore::Init()
{
	Log_Init();
	nsConfig::Init();
	nsFontManager::Init();
	nsLocalMgr::Init();
	nsMenuMgr::Init();
	nsPartManager::Init();
	
	if ( !App_GetInfo()->Init() ) return false;

	TPlatform	*pPlatform = TPlatform::GetInstance();

	TWindowManager	*wm = pPlatform->GetWindowManager();
	wm->AddWindowType( "GameWindow", nsGameWnd::ClassId() );

	uint32_t	w, h;
	bool		fs;
	pPlatform->GetDisplay( &w, &h, &fs );
	str	lua;
	lua.format( "MakeDialog { GameWindow { x = 0, y = 0, w = %d, h = %d }, }", w, h );
	wm->GetScript()->DoLuaString( lua );

	return true;
}

//---------------------------------------------------------
// nsCore::Release:
//---------------------------------------------------------
void nsCore::Release()
{
	App_GetInfo()->Release();
	nsPartManager::Release();
	nsMenuMgr::Release();
	nsLocalMgr::Release();
	nsFontManager::Release();
	nsConfig::Release();
	Log_Release();
	
	nsNamePool::Free();
}
