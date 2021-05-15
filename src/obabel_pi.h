/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  obabel Plugin
 * Author:   David Register, Mike Rossiter
 *
 ***************************************************************************
 *   Copyright (C) 2010 by David S. Register   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.             *
 ***************************************************************************
 */

#ifndef _obabelPI_H_
#define _obabelPI_H_

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
  #include <wx/glcanvas.h>
#endif //precompiled headers

#include "config.h"

#include "ocpn_plugin.h"
#include "obabelUIDialog.h"

//----------------------------------------------------------------------------------------------------------
//    The PlugIn Class Definition
//----------------------------------------------------------------------------------------------------------

#define obabel_TOOL_POSITION    -1          // Request default positioning of toolbar tool

class obabel_pi : public opencpn_plugin_116
{
public:
      obabel_pi(void *ppimgr);
      ~obabel_pi(void);

//    The required PlugIn Methods
      int Init(void);
      bool DeInit(void);

      int GetAPIVersionMajor();
      int GetAPIVersionMinor();
      int GetPlugInVersionMajor();
      int GetPlugInVersionMinor();
      wxBitmap *GetPlugInBitmap();
      wxString GetCommonName();
      wxString GetShortDescription();
      wxString GetLongDescription();

//    The override PlugIn Methods      
      void SetCursorLatLon(double lat, double lon);
      int  GetToolbarToolCount(void);
      void OnToolbarToolCallback(int id);

// Other public methods
      void SetobabelDialogX    (int x){ m_obabel_dialog_x = x;};
      void SetobabelDialogY    (int x){ m_obabel_dialog_y = x;}
      void SetobabelDialogSizeX(int x){ m_obabel_dialog_sx = x;}
      void SetobabelDialogSizeY(int x){ m_obabel_dialog_sy = x;}
      void SetColorScheme(PI_ColorScheme cs);

      void OnobabelDialogClose();
	  
	  wxString m_GetDevice;
	  wxString m_GetFormat;
	  wxString m_GetExe;
	  wxString m_GetComport;
	  
	  
	  wxWindow         *m_parent_window;

private:
      bool LoadConfig(void);
      bool SaveConfig(void);

      wxFileConfig     *m_pconfig;
      obabelUIDialog   *m_pobabelDialog;

      int              m_display_width, m_display_height;
      int              m_leftclick_tool_id;

      int              m_obabel_dialog_x, m_obabel_dialog_y;
      int              m_obabel_dialog_sx, m_obabel_dialog_sy;

      wxString          m_RequestConfig;
        
      bool              m_bobabelShowIcon;
      int               m_height;
      bool				m_bShowobabel;	  
	  wxBitmap m_panelBitmap;
};

#endif
