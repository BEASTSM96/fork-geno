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

#include "WorkspaceWidget.h"

#include "Components/Project.h"
#include "GUI/Widgets/TextEditWidget.h"
#include "GUI/Application.h"

#include <imgui.h>

void WorkspaceWidget::Show( bool* p_open )
{
	if( ImGui::Begin( "Workspace", p_open ) )
	{
		if( Workspace* workspace = Application::Instance().CurrentWorkspace() )
		{
			const std::string workspace_id_string    = workspace->name_ + "##WKS_" + workspace->name_;

			if( ImGui::TreeNode( workspace_id_string.c_str() ) )
			{
				for( Project& prj : workspace->projects_ )
				{
					const std::string project_id_string = prj.name_ + "##PRJ_" + prj.name_;

					if( ImGui::TreeNode( project_id_string.c_str() ) )
					{
						for( std::filesystem::path& file : prj.files_ )
						{
							std::filesystem::path relative_file_path = *workspace / file;
							std::string           file_string        = relative_file_path.string();

							if( ImGui::Selectable( file_string.c_str() ) )
							{
								TextEditWidget::Instance().AddFile( file );
							}
						}

						ImGui::TreePop();
					}
				}

				ImGui::TreePop();
			}
		}
	}
	ImGui::End();
}