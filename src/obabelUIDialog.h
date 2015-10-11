/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  obabel Plugin Friends
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
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.         *
 ***************************************************************************
 */
#include <wx/wx.h>

#ifndef __obabelUIDIALOG_H__
#define __obabelUIDIALOG_H__

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif //precompiled headers
#include <wx/fileconf.h>
#include <wx/glcanvas.h>

#include "obabelUIDialogBase.h"
#include <wx/progdlg.h>
#include "wx/stattext.h"
#include "ocpn_plugin.h"
#include <wx/utils.h>
#include <wx/clipbrd.h>
#include <wx/event.h>
#include <wx/Ffile.h>
#include <wx/filedlg.h>
#include <wx/combobox.h>

using namespace std;

class obabelOverlayFactory;
class PlugIn_ViewPort;
class wxFileConfig;
class obabel_pi;
class wxGraphicsContext;

class obabelUIDialog: public obabelUIDialogBase {
public:

    obabelUIDialog(wxWindow *parent, obabel_pi *ppi);
    ~obabelUIDialog();
    
    void SetCursorLatLon( double lat, double lon );
    void SetFactoryOptions( bool set_val = false );

    void SetViewPort( PlugIn_ViewPort *vp );
	PlugIn_ViewPort *vp;

	void About(wxCommandEvent& event);
	void BuildOptions();
	void ShowOptions(wxCommandEvent& event);
    void OnPaste(wxMouseEvent& event );
	void SendBabelClip(wxCommandEvent& event);
	void SendBabelFile(wxCommandEvent& event);
	void LocateBabel( wxCommandEvent& event);
	
	obabelUIDialog *m_dlg;

    long  m_server_pid;
	

private:
	
	int code;
	wxString FileToSave;
	char fBuf[3];
	
    void OnShow( wxShowEvent& event );
    void OnClose( wxCloseEvent& event );

    void OnMove( wxMoveEvent& event );
    void OnSize( wxSizeEvent& event );

	wxString xpath;		
	
    //    Data
    wxWindow *pParent;
    obabel_pi *pPlugIn;

    PlugIn_ViewPort  *m_vp;
    int m_lastdatatype;

    double m_cursor_lat, m_cursor_lon;
	wxString s_options[2];

protected:
    wxString m_Filename;
	
	
};

#endif

class HelperData
{
public:    
    wxString lat, lon;
    HelperData *prev, *next; /* doubly linked circular list of positions */
    wxString dir;
	wxString spd;
	wxString portno;
	wxString *xpathdata;
	
};
