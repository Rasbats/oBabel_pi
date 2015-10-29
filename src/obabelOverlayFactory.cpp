/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  obabel Object
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
 *
 */

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

#include <wx/glcanvas.h>
#include <wx/graphics.h>
#include <wx/progdlg.h>

#include "obabelUIDialog.h"
#include "obabelUIDialogBase.h"
#include "obabelOverlayFactory.h"

//#include "dychart.h"
//#include "cutil.h"

using namespace std;

class obabelUIDialog;
class PlugIn_ViewPort;

enum OVERLAP { _IN, _ON, _OUT };

obabelOverlayFactory::obabelOverlayFactory( obabelUIDialog &dlg )
	: m_dlg(dlg)
{
    m_dFont_map = new wxFont( 10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL );
    m_dFont_war = new wxFont( 16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL );

    m_last_vp_scale = 0.;

}

obabelOverlayFactory::~obabelOverlayFactory()
{
  ///  ClearCachedData();
}

void obabelOverlayFactory::Reset()
{

  ///  ClearCachedData();
}

bool obabelOverlayFactory::RenderGLobabelOverlay( wxGLContext *pcontext, PlugIn_ViewPort *vp )
{
    m_pdc = NULL;                  // inform lower layers that this is OpenGL render
    return DoRenderobabelOverlay( vp );
}

bool obabelOverlayFactory::RenderobabelOverlay( wxDC &dc, PlugIn_ViewPort *vp )
{

#if wxUSE_GRAPHICS_CONTEXT
    wxMemoryDC *pmdc;
    pmdc = wxDynamicCast(&dc, wxMemoryDC);
    wxGraphicsContext *pgc = wxGraphicsContext::Create( *pmdc );
    m_gdc = pgc;
    m_pdc = &dc;
#else
    m_pdc = &dc;
#endif
	   
	m_pdc = &dc;
    return DoRenderobabelOverlay( vp );
}



bool obabelOverlayFactory::DoRenderobabelOverlay( PlugIn_ViewPort *vp )
{
    

    m_Message_Hiden.Empty();

	    //    If the scale has changed, clear out the cached bitmaps

    m_last_vp_scale = vp->view_scale_ppm;    

    return true;
}








                   