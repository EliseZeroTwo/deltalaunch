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

#include "Dashboard.hpp"

Dashboard::Dashboard(Renderer &rend, std::string fnt, u32 fntSize) {
    Rend = rend;
    lastErr = 0;
    IsMenuOpen = false;
    smallFnt = TTF_OpenFont(fnt.c_str(), fntSize);
    Wallpaper = SDL_CreateTexture(Rend._renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1280, 720);
    dbg = new Debug(smallFnt, true);
}

Dashboard::~Dashboard() {
    delete dbg;
    Buttons.clear();
    SDL_DestroyTexture(Wallpaper);
}

void Dashboard::DrawWallpaper() {
    SDL_Rect pos;
    pos.x = 0; pos.y = 0;
    pos.w = 1280; pos.h = 720;
    SDL_RenderCopy(Rend._renderer, Wallpaper, NULL, &pos);
}

void Dashboard::DrawButtons() {
    for(auto &button: Buttons) {
        if(button.Sprite != "")
            Draw::Texture(button.Sprite, button.X, button.Y, Rend);
        else
            Draw::Rectangle(button.X, button.Y, button.W, button.H, button.Color, Rend);
        
        if(Hid::IsTouched(button.X, button.Y, button.X + button.W, button.Y + button.H) && !IsMenuOpen)
            lastErr = button.Run();
    }
}

void Dashboard::DrawMenus() {
    for(auto &menu: Menus) {
        if(menu.IsOpen()) {
            Draw::Rectangle(menu.Pos, menu.Color, Rend);
        }
    }
}

void Dashboard::DrawDebugText() {
    //Debug text
    touchPosition touchPos;
    hidTouchRead(&touchPos, 0);
    dbg->Print(Rend, "DeltaLaunch alpha!");
    dbg->Print(Rend, "Firmware: " + Settings::GetFirmwareVersion());
    dbg->Print(Rend, "Touch: X=" + std::to_string(touchPos.px) + "; y=" + std::to_string(touchPos.py));
    if(lastErr != 0) 
        dbg->Print(Rend, "Errors: " + std::to_string(lastErr));
    dbg->Clear();
}

void Dashboard::SetWallpaper(std::string lay0, std::string lay1, std::string lay2) {
    SDL_Surface *l0 = IMG_Load(lay0.c_str());
    SDL_Surface *l1 = IMG_Load(lay1.c_str());
    SDL_Surface *l2 = IMG_Load(lay2.c_str());
    SDL_Surface *wall = SDL_CreateRGBSurface(0,l0->w,l0->h,32,0,0,0,0);
    SDL_Rect pos;
    pos.x = 0; pos.y = 0;
    pos.w = l0->w; pos.h = l0->h;
    SDL_BlitSurface(l0, &pos, wall, NULL);
    SDL_BlitSurface(l1, &pos, wall, NULL);
    SDL_BlitSurface(l2, &pos, wall, NULL);
    Wallpaper = SDL_CreateTextureFromSurface(Rend._renderer, wall);
    SDL_FreeSurface(l0);
    SDL_FreeSurface(l1);
    SDL_FreeSurface(l2);
    SDL_FreeSurface(wall);
}

Result Dashboard::OpenMenu(std::string name) {
	for(auto &menu: Menus) {
        if(menu.GetTitle() == name) {
			IsMenuOpen = true;;
			menu.Show();
		}
    }
    return 0;
}

Result Dashboard::CloseMenus() {
	for(auto &menu: Menus) {
        if(menu.IsOpen()) {
            IsMenuOpen = false;
			menu.Hide();
		}
    }
    return 0;
}

void Dashboard::AddButton(Button button) {
    Buttons.push_back(button);
}

void Dashboard::AddMenu(Menu menu) {
    Menus.push_back(menu);
}