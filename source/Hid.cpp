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

#include "Hid.hpp"
#include "App.hpp"

void Hid::Check() {
    hidScanInput();
        
    u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

    if (kDown & KEY_PLUS) {
        bpcInitialize();
        bpcShutdownSystem();
        bpcExit();
    }
    
    if (kDown & KEY_MINUS) {
        App::LaunchApplet(AppletId_shop, LibAppletMode_AllForeground);
    }
    
    if ((kDown & KEY_DUP) || (kDown & KEY_LSTICK_UP)) {
        
    }
    if ((kDown & KEY_DDOWN) || (kDown & KEY_LSTICK_DOWN)) {
        
    }
}