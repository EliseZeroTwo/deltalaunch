/*
* ΔLaunch
* Copyright (C) 2018  Reisyukaku
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#include <SDL2/SDL.h>
#include <switch.h>
#include "Game.hpp"
#include "Forms.hpp"
#include "../Core/Graphics.hpp"
#include "../Services/Time.hpp"
#include "../Services/Hid.hpp"

class NewsMenu: public Menu
{
    public:
        NewsMenu(SDL_Rect pos);
        ~NewsMenu();
        void Initialize();
		
        //Draw/set
        void DrawButtons();
        
		//Overrides
		void Update() override;
        
    private:
        u32 Width, Height;
        std::vector<SDL_Texture*> Pics;
};