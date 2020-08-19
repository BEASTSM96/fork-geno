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

#include "IModal.h"

#include "GUI/Application.h"

#include <imgui.h>

void IModal::Update( void )
{
	const std::string popup_id = Title() + "##" + PopupID();

	if( open_ && !ImGui::IsPopupOpen( popup_id.c_str() ) )
	{
		ImGui::OpenPopup( popup_id.c_str() );
	}

	if( ImGui::BeginPopupModal( popup_id.c_str() ) )
	{
		UpdateDerived();

		if( IModal* next = Application::Instance().NextModal( this ) )
			next->Update();

		ImGui::EndPopup();
	}
}

void IModal::Close( void )
{
	open_ = false;

	ImGui::CloseCurrentPopup();

	Application::Instance().PopModal();

	OnClose();
}

bool IModal::Open( void )
{
	// Make sure this popup is not already opened
	if( open_ )
		return false;

	Application::Instance().PushModal( this );

	open_ = true;

	return true;
}