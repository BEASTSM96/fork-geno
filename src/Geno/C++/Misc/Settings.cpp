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

#include "Settings.h"

#include <Common/LocalAppData.h>
#include <GCL/Deserializer.h>
#include <GCL/Serializer.h>

#include <fstream>

#include <imgui.h>

Settings::Settings( void )
{
	Load();
}

Settings::~Settings( void )
{
	Save();
}

void Settings::Load( void )
{
	GCL::Deserializer deserializer( LocalAppData::Instance() / "settings.gcl" );
	if( !deserializer.IsOpen() )
		return;

	deserializer.Objects( this,
		[]( GCL::Object object, void* user )
		{
			Settings* self = static_cast< Settings* >( user );

			/**/ if( object.Key() == "Theme" )      self->theme_      = object.String();
		#if defined( _WIN32 )
			else if( object.Key() == "MinGW-Path" ) self->mingw_path_ = object.String();
		#endif // _WIN32
		}
	);

	UpdateTheme();
}

void Settings::Save( void )
{
	GCL::Serializer serializer( LocalAppData::Instance() / "settings.gcl" );
	if( !serializer.IsOpen() )
		return;

	if( !theme_.empty() )
	{
		GCL::Object obj( "Theme" );
		obj.SetString( theme_ );
		serializer.WriteObject( obj );
	}

#if defined( _WIN32 )

	if( !mingw_path_.empty() )
	{
		std::string mingw_path_string = mingw_path_.lexically_normal().string();
		GCL::Object obj( "MinGW-Path" );
		obj.SetString( mingw_path_string );
		serializer.WriteObject( obj );
	}
#endif // _WIN32

}

void Settings::UpdateTheme( void )
{
	/**/ if( theme_ == "Classic" ) ImGui::StyleColorsClassic();
	else if( theme_ == "Light" )   ImGui::StyleColorsLight();
	else if( theme_ == "Dark" )    ImGui::StyleColorsDark();
}
