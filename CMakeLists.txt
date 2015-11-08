##---------------------------------------------------------------------------
## Author:      Dave Register
##***************************************************************************
## *   Copyright (C) 2010 by David S. Register                               *
## *   This program is free software; you can redistribute it and/or modify  *
## *   it under the terms of the GNU General Public License as published by  *
## *   the Free Software Foundation; either version 2 of the License, or     *
## *   (at your option) any later version.                                   *
## *                                                                         *
## *   This program is distributed in the hope that it will be useful,       *
## *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
## *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
## *   GNU General Public License for more details.                          *
## *                                                                         *
## *   You should have received a copy of the GNU General Public License     *
## *   along with this program; if not, write to the                         *
## *   Free Software Foundation, Inc.,                                       *
## *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.             *
## ***************************************************************************

# define minimum cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.2)

PROJECT(obabel_pi)

SET(PACKAGE_NAME obabel_pi)
SET(VERBOSE_NAME oBabel)
SET(TITLE_NAME OBABEL)
SET(CPACK_PACKAGE_CONTACT "Mike Rossiter")

SET(VERSION_MAJOR "1")
SET(VERSION_MINOR "0")

#SET(CMAKE_BUILD_TYPE Debug)
SET(wxWidgets_USE_UNICODE ON)
SET(wxWidgets_CONFIGURATION mswu)

add_definitions(-DUNICODE -D_UNICODE)

INCLUDE("cmake/PluginConfigure.cmake")



SET(SRC_obabel
            src/obabel_pi.h
            src/obabel_pi.cpp
            src/obabelOverlayFactory.cpp
            src/obabelOverlayFactory.h
            src/obabelUIDialogBase.cpp
            src/obabelUIDialogBase.h
            src/obabelUIDialog.cpp
            src/obabelUIDialog.h
            src/icons.h
            src/icons.cpp
	)


ADD_LIBRARY(${PACKAGE_NAME} SHARED ${SRC_obabel})

INCLUDE("cmake/PluginInstall.cmake")
INCLUDE("cmake/PluginLocalization.cmake")
INCLUDE("cmake/PluginPackage.cmake")
