///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "obabelUIDialogBase.h"

///////////////////////////////////////////////////////////////////////////

obabelUIDialogBase::obabelUIDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("GPSBabel") ), wxHORIZONTAL );
	
	m_textCtrl1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition,  wxSize( 180,-1 ), wxTE_READONLY|wxSIMPLE_BORDER );
	sbSizer3->Add( m_textCtrl1, 0, wxALL|wxEXPAND, 5 );
	
	sbSizer3->Add( 0, 0, 1, wxEXPAND, 5 );

	m_locatebabel = new wxButton( this, wxID_ANY , _("Locate GPSBabel"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_locatebabel->SetToolTip(_("Select location of GPSBabel"));	
	sbSizer3->Add( m_locatebabel, 0, wxALL, 5 );

	sbSizer3->Add( 0, 0, 1, wxEXPAND, 5 );

	// Start About Information Button
	m_button33 = new wxButton( this, wxID_ANY , wxT("???"), wxDefaultPosition, wxSize( 40,-1 ), 0 );
	m_button33->SetToolTip(wxT("About oBabel"));	
	sbSizer3->Add( m_button33, 0, wxALL, 5 );

	sbSizer3->Add( 0, 0, 1, wxEXPAND, 5 );

	bSizer1->Add( sbSizer3, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Options") ), wxHORIZONTAL );
	
	wxString m_deviceChoices[] = { wxT("garmin"), wxT("nmea") };
	int m_deviceNChoices = sizeof( m_deviceChoices ) / sizeof( wxString );
	m_device = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_deviceNChoices, m_deviceChoices, 0 );
	m_device->SetSelection( 0 );
	sbSizer4->Add( m_device, 0, wxALL, 5 );
	
	
	sbSizer4->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_waypoint = new wxCheckBox( this, wxID_ANY, wxT("Wayoints"), wxDefaultPosition, wxDefaultSize, 0 );
	m_waypoint->SetValue(false); 
	sbSizer4->Add( m_waypoint, 0, wxALL, 5 );
	
	
	sbSizer4->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_route = new wxCheckBox( this, wxID_ANY, wxT("Routes"), wxDefaultPosition, wxDefaultSize, 0 );
	m_waypoint->SetValue(false); 
	sbSizer4->Add( m_route, 0, wxALL, 5 );
	
	
	sbSizer4->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_track = new wxCheckBox( this, wxID_ANY, wxT("Tracks"), wxDefaultPosition, wxDefaultSize, 0 );
	m_waypoint->SetValue(false); 
	sbSizer4->Add( m_track, 0, wxALL, 5 );
	
	bSizer1->Add( sbSizer4, 0, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Finalise") ), wxHORIZONTAL );
	
	sbSizer2->SetMinSize( wxSize( 215, -1 ) ); 

	wxArrayString m_choice1Choices ;
	m_choice1 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice1Choices, 0);	
		
	sbSizer2->Add( m_choice1, 0, wxEXPAND, 5 );

	sbSizer2->Add( 0, 0, 1, wxEXPAND, 5 );

	wxString m_formatChoices[] = { wxT("oGPX"), wxT("KML"),wxT("GPX")};
	int m_formatNChoices = sizeof( m_formatChoices ) / sizeof( wxString );
	m_format = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_formatNChoices, m_formatChoices, 0 );
	m_format->SetSelection( 0 );
	sbSizer2->Add( m_format, 0, wxALL, 5 );

	m_button32 = new wxButton( this, wxID_ANY , wxT("Chosen Options"), wxDefaultPosition, wxSize( 120,-1 ), 0 );
	m_button32->SetToolTip(wxT("Show options for the transfer"));	
	sbSizer2->Add( m_button32, 0, wxALL, 5 );
	
	bSizer1->Add( sbSizer2, 0,  wxEXPAND, 5 );

	wxStaticBoxSizer* bSizer2;
	bSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Source and Send") ), wxHORIZONTAL );
	
	m_sendbabelclip = new wxButton( this, 6, wxT("Clipboard->GPSBabel"), wxDefaultPosition, wxSize( 160,-1 ), 0 );
	bSizer2->Add( m_sendbabelclip, 0, wxALL, 5 );
	
   	
	m_sendbabelfile = new wxButton( this, 0 , wxT("File->GPSBabel"), wxDefaultPosition, wxSize( 160,-1 ), 0 );
	bSizer2->Add( m_sendbabelfile, 0, wxALL, 5 );
	bSizer1->Add( bSizer2, 0,  wxEXPAND, 5 );

	wxStaticBoxSizer* Clipboard;
	Clipboard = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Clipboard") ), wxVERTICAL );
	
	m_clip = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_WORDWRAP|wxVSCROLL );
	m_clip->SetMinSize( wxSize( 30,100 ) );
	
	Clipboard->Add( m_clip, 100, wxALL|wxEXPAND, 5 );
	
	bSizer1->Add( Clipboard, 1, wxEXPAND, 5 );

	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	
	this->Connect( wxEVT_SHOW, wxShowEventHandler( obabelUIDialogBase::OnShow ) );
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( obabelUIDialogBase::OnClose ) );
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( obabelUIDialogBase::OnSize ) );
	
	m_locatebabel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( obabelUIDialogBase::LocateBabel), NULL, this );
	m_button32->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( obabelUIDialogBase::ShowOptions ), NULL, this );
	m_button33->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( obabelUIDialogBase::About ), NULL, this );

	m_sendbabelclip->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( obabelUIDialogBase::SendBabelClip), NULL, this );
	m_sendbabelfile->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( obabelUIDialogBase::SendBabelFile), NULL, this );

	m_clip->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( obabelUIDialogBase::OnPaste ), NULL, this );

}

obabelUIDialogBase::~obabelUIDialogBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_SHOW, wxShowEventHandler( obabelUIDialogBase::OnShow ) );
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( obabelUIDialogBase::OnClose ) );
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( obabelUIDialogBase::OnSize ) );

	m_locatebabel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( obabelUIDialogBase::LocateBabel ), NULL, this );
	m_button32->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( obabelUIDialogBase::ShowOptions ), NULL, this );
	m_button33->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( obabelUIDialogBase::About ), NULL, this );

	m_sendbabelclip->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( obabelUIDialogBase::SendBabelClip), NULL, this );
	m_sendbabelfile->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( obabelUIDialogBase::SendBabelFile), NULL, this );
	m_clip->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( obabelUIDialogBase::OnPaste ), NULL, this );

}

