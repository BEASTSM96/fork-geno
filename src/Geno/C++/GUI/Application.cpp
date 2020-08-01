/*
 * Copyright (c) 2020 Sebastian Kylander https://gaztin.com/
 *
 * This software is provided 'as-is', without any express or implied warranty. In no event will
 * the authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the
 *    original software. If you use this software in a product, an acknowledgment in the product
 *    documentation would be appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as
 *    being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include "Application.h"

#include "GUI/MainMenuBar.h"
#include "GUI/MainWindow.h"

#include <iostream>

int Application::Run( void )
{
	MainWindow::Instance().Init();

	while( MainWindow::Instance().BeginFrame() )
	{
		MainMenuBar::Instance().Show();

		MainWindow::Instance().EndFrame();
	}

	return 0;
}

void Application::NewWorkspace( const std::filesystem::path& where )
{
	CloseWorkspace();

	current_workspace_.emplace( where );
}

void Application::LoadWorkspace( const std::filesystem::path& path )
{
	NewWorkspace( path );

	current_workspace_->Deserialize();
}

void Application::CloseWorkspace( void )
{
	if( current_workspace_ )
		current_workspace_->Serialize();

	current_workspace_.reset();
}

Workspace* Application::CurrentWorkspace( void )
{
	return current_workspace_.has_value() ? &current_workspace_.value() : nullptr;
}