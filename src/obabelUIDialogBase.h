///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __obabelUIDIALOGBASE_H__
#define __obabelUIDIALOGBASE_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/dialog.h>
#include <wx/choice.h>
#include <wx/event.h>

///////////////////////////////////////////////////////////////////////////////
/// Class obabelUIDialogBase
///////////////////////////////////////////////////////////////////////////////
class obabelUIDialogBase : public wxDialog 
{
	private:
	
	protected:

		wxButton* m_locatebabel;
		wxButton* m_button32;
		wxButton* m_button33;
		wxButton* m_sendbabelclip;
		wxButton* m_sendbabelfile;
		wxButton* m_button6;
		wxTextCtrl* m_txtctrl;
		wxTextCtrl* m_clipboard;
		wxTextCtrl* m_clip;
		wxChoice* m_device;
		wxCheckBox* m_waypoint;
		wxCheckBox* m_route;
		wxCheckBox* m_track;
		wxChoice* m_format;

		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnShow( wxShowEvent& event ) { event.Skip(); }
		virtual void OnSize( wxSizeEvent& event ) { event.Skip(); }
			
		virtual void About( wxCommandEvent& event ) { event.Skip(); }
	    virtual void ShowOptions( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPaste( wxMouseEvent& event ) { event.Skip(); }
		virtual void SendBabelClip( wxCommandEvent& event ) { event.Skip(); }
		virtual void SendBabelFile( wxCommandEvent& event ) { event.Skip(); }
		virtual void LocateBabel( wxCommandEvent& event ) { event.Skip(); }

	public:
	
		wxChoice* m_choice1;
		wxTextCtrl* m_textCtrl1;


		void WriteText(const wxString& text) { m_txtctrl->WriteText(text); }   

		obabelUIDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("oBabel KML/GPX exporter for Chartplotters"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxCLOSE_BOX|wxDIALOG_NO_PARENT|wxRESIZE_BORDER|wxSYSTEM_MENU ); 
		~obabelUIDialogBase();
	
};


#endif //__obabelUIDIALOGBASE_H__
