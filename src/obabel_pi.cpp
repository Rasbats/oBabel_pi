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


#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
  #include <wx/glcanvas.h>
#endif //precompiled headers

#include <wx/fileconf.h>
#include <wx/stdpaths.h>

#include "obabel_pi.h"
#include "ocpn_plugin.h"

// the class factories, used to create and destroy instances of the PlugIn

extern "C" DECL_EXP opencpn_plugin* create_pi(void *ppimgr)
{
    return new obabel_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p)
{
    delete p;
}

//---------------------------------------------------------------------------------------------------------
//
//    obabel PlugIn Implementation
//
//---------------------------------------------------------------------------------------------------------

#include "icons.h"


//---------------------------------------------------------------------------------------------------------
//
//          PlugIn initialization and de-init
//
//---------------------------------------------------------------------------------------------------------

obabel_pi::obabel_pi(void* ppimgr)
      : opencpn_plugin_116(ppimgr)
{
      // Create the PlugIn icons
    initialize_images();

    wxFileName fn;

    auto path = GetPluginDataDir("obabel_pi");
    fn.SetPath(path);
    fn.AppendDir("data");
    fn.SetFullName("obabel_panel_icon.png");

    path = fn.GetFullPath();

    wxInitAllImageHandlers();

    wxLogDebug(wxString("Using icon path: ") + path);
    if (!wxImage::CanRead(path)) {
        wxLogDebug("Initiating image handlers.");
        wxInitAllImageHandlers();
    }
    wxImage panelIcon(path);
    if (panelIcon.IsOk())
        m_panelBitmap = wxBitmap(panelIcon);
    else
        wxLogWarning("oBabel panel icon has NOT been loaded");
 
    m_bShowobabel = false;	  
}

obabel_pi::~obabel_pi(void)
{
      delete _img_babel_pi;
      delete _img_babel;
}

int obabel_pi::Init(void)
{
        
	  AddLocaleCatalog( _T("opencpn-obabel_pi") );

      // Set some default private member parameters
      m_obabel_dialog_x = 0;
      m_obabel_dialog_y = 0;
      m_obabel_dialog_sx = 200;
      m_obabel_dialog_sy = 400;
      m_pobabelDialog = NULL;
      m_pobabelOverlayFactory = NULL;

      ::wxDisplaySize(&m_display_width, &m_display_height);

      //    Get a pointer to the opencpn configuration object
      m_pconfig = GetOCPNConfigObject();
	 
      //    And load the configuration items
      LoadConfig();

      // Get a pointer to the opencpn display canvas, to use as a parent for the obabel dialog
      m_parent_window = GetOCPNCanvasWindow();

      //    This PlugIn needs a toolbar icon, so request its insertion if enabled locally
      if (m_bobabelShowIcon) {
#ifdef OBABEL_USE_SVG
        m_leftclick_tool_id = InsertPlugInToolSVG(_T( "oBabel" ),
            _svg_obabel, _svg_obabel, _svg_obabel_toggled,
            wxITEM_CHECK, _("oBabel"), _T( "" ), NULL,
            obabel_TOOL_POSITION, 0, this);
#else

        m_leftclick_tool_id = InsertPlugInTool(_T(""), _img_babel, _img_babel, wxITEM_CHECK,
                                                 _("oBabel"), _T(""), NULL,
                                                 obabel_TOOL_POSITION, 0, this);
#endif
      }
      
      return (WANTS_OVERLAY_CALLBACK |
              WANTS_OPENGL_OVERLAY_CALLBACK |
              WANTS_CURSOR_LATLON       |
              WANTS_TOOLBAR_CALLBACK    |
              INSTALLS_TOOLBAR_TOOL     |
              WANTS_CONFIG             
            );
}

bool obabel_pi::DeInit(void)
{
    if(m_pobabelDialog) { 

		m_pobabelDialog->Close();
        delete m_pobabelDialog;
        m_pobabelDialog = NULL;
    }

    return true;
}

int obabel_pi::GetAPIVersionMajor()
{
    return atoi(API_VERSION);
}

int obabel_pi::GetAPIVersionMinor()
{
    std::string v(API_VERSION);
    size_t dotpos = v.find('.');
    return atoi(v.substr(dotpos + 1).c_str());
}

int obabel_pi::GetPlugInVersionMajor()
{
    return PLUGIN_VERSION_MAJOR;
}

int obabel_pi::GetPlugInVersionMinor()
{
    return PLUGIN_VERSION_MINOR;
}

wxBitmap *obabel_pi::GetPlugInBitmap()
{
      return &m_panelBitmap;
}

wxString obabel_pi::GetCommonName()
{
      return _T("obabel");
}


wxString obabel_pi::GetShortDescription()
{
      return _("obabel PlugIn for OpenCPN");
}


wxString obabel_pi::GetLongDescription()
{
      return _("obabel PlugIn for OpenCPN \nFor uploading KML/GPX routes and waypoints to Chartplotters.\n\n\
			   ");
}

int obabel_pi::GetToolbarToolCount(void)
{
      return 1;
}

void obabel_pi::OnToolbarToolCallback(int id)
{
    if(NULL == m_pobabelDialog)
    {
		        		
		m_pobabelDialog = new obabelUIDialog(m_parent_window, this);
        wxPoint p = wxPoint(m_obabel_dialog_x, m_obabel_dialog_y);
        m_pobabelDialog->Move(0,0);        // workaround for gtk autocentre dialog behavior
        m_pobabelDialog->Move(p);
        
    }

      // Qualify the obabel dialog position
      bool b_reset_pos = false;



      //Toggle obabel overlay display
      m_bShowobabel = !m_bShowobabel;

      //    Toggle dialog?
      if(m_bShowobabel) {
          m_pobabelDialog->Show();
      } 
	  else {
         m_pobabelDialog->Hide();         
      }

      // Toggle is handled by the toolbar but we must keep plugin manager b_toggle updated
      // to actual status to ensure correct status upon toolbar rebuild
      SetToolbarItemState( m_leftclick_tool_id, m_bShowobabel );
      RequestRefresh(m_parent_window); // refresh main window
}

void obabel_pi::OnobabelDialogClose()
{
     
	m_bShowobabel = false;	
    SetToolbarItemState( m_leftclick_tool_id, m_bShowobabel );
    m_pobabelDialog->Hide();
    SaveConfig();

    RequestRefresh(m_parent_window); // refresh main window

}

void obabel_pi::SetCursorLatLon(double lat, double lon)
{
    if(m_pobabelDialog)
        m_pobabelDialog->SetCursorLatLon(lat, lon);
}

bool obabel_pi::LoadConfig(void)
{
    wxFileConfig *pConf = (wxFileConfig *)m_pconfig;

    if(!pConf)
        return false;

    pConf->SetPath ( _T( "/PlugIns/obabel" ) );

	pConf->Read ( _T ( "obabelformat" ),&m_GetFormat,wxEmptyString);
	pConf->Read ( _T ( "obabeldevice" ),&m_GetDevice,wxEmptyString);
	pConf->Read ( _T ( "obabelexe" ),&m_GetExe,wxEmptyString);

    m_obabel_dialog_sx = pConf->Read ( _T ( "obabelDialogSizeX" ), 300L );
    m_obabel_dialog_sy = pConf->Read ( _T ( "obabelDialogSizeY" ), 540L );
    m_obabel_dialog_x =  pConf->Read ( _T ( "obabelDialogPosX" ), 20L );
    m_obabel_dialog_y =  pConf->Read ( _T ( "obabelDialogPosY" ), 170L );


	
    return true;
}

bool obabel_pi::SaveConfig(void)
{
    wxFileConfig *pConf = (wxFileConfig *)m_pconfig;

    if(!pConf)
        return false;

    pConf->SetPath ( _T( "/PlugIns/obabel" ) );
    pConf->Write ( _T ( "obabelformat" ), m_GetFormat );
    pConf->Write ( _T ( "obabeldevice" ), m_GetDevice);
	pConf->Write ( _T ( "obabelexe" ), m_GetExe );

    pConf->Write ( _T ( "obabelDialogSizeX" ),  m_obabel_dialog_sx );
    pConf->Write ( _T ( "obabelDialogSizeY" ),  m_obabel_dialog_sy );
    pConf->Write ( _T ( "obabelDialogPosX" ),   m_obabel_dialog_x );
    pConf->Write ( _T ( "obabelDialogPosY" ),   m_obabel_dialog_y );

	
    return true;
}

void obabel_pi::SetColorScheme(PI_ColorScheme cs)
{
    DimeWindow(m_pobabelDialog);
}

