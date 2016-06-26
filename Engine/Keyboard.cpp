/****************************************************************************************** 
 *	Chili DirectX Framework Version 14.03.22											  *	
 *	Keyboard.cpp																		  *
 *	Copyright 2014 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "Keyboard.h"

bool Keyboard::KeyIsPressed( unsigned char keycode ) const
{
	return keystates[keycode];
}

Keyboard::Event Keyboard::ReadKey()
{
	if( keybuffer.size() > 0u )
	{
		Keyboard::Event e = keybuffer.front();
		keybuffer.pop();
		return e;
	}
	else
	{
		return Keyboard::Event( Keyboard::Event::Invalid,0 );
	}
}

Keyboard::Event Keyboard::PeekKey() const
{	
	if( keybuffer.size() > 0u )
	{
		return keybuffer.front();
	}
	else
	{
		return Keyboard::Event( Keyboard::Event::Invalid,0 );
	}
}

bool Keyboard::KeyEmpty() const
{
	return keybuffer.empty();
}

unsigned char Keyboard::ReadChar()
{
	if( charbuffer.size() > 0u )
	{
		unsigned char charcode = charbuffer.front();
		charbuffer.pop();
		return charcode;
	}
	else
	{
		return 0;
	}
}

unsigned char Keyboard::PeekChar() const
{
	if( charbuffer.size() > 0u )
	{
		return charbuffer.front();
	}
	else
	{
		return 0;
	}
}

bool Keyboard::CharEmpty() const
{
	return charbuffer.empty();
}

void Keyboard::FlushKeyBuffer()
{
	std::swap( keybuffer,std::queue<Event>() );
}

void Keyboard::FlushCharBuffer()
{
	std::swap( charbuffer,std::queue<unsigned char>() );
}

void Keyboard::FlushBuffers()
{
	FlushKeyBuffer();
	FlushCharBuffer();
}

void Keyboard::EnableAutorepeat()
{
	autorepeatEnabled = true;
}

void Keyboard::DisableAutorepeat()
{
	autorepeatEnabled = false;
}

bool Keyboard::IsAutorepeatEnabled() const
{
	return autorepeatEnabled;
}

void Keyboard::OnKeyPressed( unsigned char keycode )
{
	keystates[ keycode ] = true;	
	keybuffer.push( Keyboard::Event( Keyboard::Event::Press,keycode ) );
	TrimBuffer( keybuffer );
}

void Keyboard::OnKeyReleased( unsigned char keycode )
{
	keystates[ keycode ] = false;
	keybuffer.push( Keyboard::Event( Keyboard::Event::Release,keycode ) );
	TrimBuffer( keybuffer );
}

void Keyboard::OnChar( unsigned char character )
{
	charbuffer.push( character );
	TrimBuffer( charbuffer );
}

template<typename T>
void Keyboard::TrimBuffer( std::queue<T>& buffer )
{
	if( buffer.size() > bufferSize )
	{
		buffer.pop();
	}
}
