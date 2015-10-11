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

#include "wx/wx.h"
#include <wx/wfstream.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/debug.h>
#include <wx/graphics.h>
#include <wx/stdpaths.h>
#include <stdlib.h>
#include "obabel_pi.h"
#include "icons.h"
#include <windows.h>

using namespace std;

#if !wxCHECK_VERSION(2,9,4) /* to work with wx 2.8 */
#define SetBitmap SetBitmapLabel
#endif

wxArrayString *EnumerateSerialPorts( void )
{
    wxArrayString *preturn = new wxArrayString;

#ifdef __WXGTK__

    //Initialize the pattern table
    if( devPatern[0] == NULL ) {
        paternAdd ( "ttyUSB" );
        paternAdd ( "ttyACM" );
        paternAdd ( "ttyGPS" );
        paternAdd ( "refcom" );
    }

 //  Looking for user privilege openable devices in /dev
 //  Fulup use scandir to improve user experience and support new generation of AIS devices.

      wxString sdev;
      int ind, fcount;
      struct dirent **filelist = {0};

      // scan directory filter is applied automatically by this call
      fcount = scandir("/dev", &filelist, paternFilter, alphasort);

      for(ind = 0; ind < fcount; ind++)  {
       wxString sdev (filelist[ind]->d_name, wxConvUTF8);
       sdev.Prepend (_T("/dev/"));

       preturn->Add (sdev);
       free(filelist[ind]);
      }


//        We try to add a few more, arbitrarily, for those systems that have fixed, traditional COM ports

    if( isTTYreal("/dev/ttyS0") )
        preturn->Add( _T("/dev/ttyS0") );

    if( isTTYreal("/dev/ttyS1") )
        preturn->Add( _T("/dev/ttyS1") );


#endif

#ifdef PROBE_PORTS__WITH_HELPER

    /*
     *     For modern Linux/(Posix??) systems, we may use
     *     the system files /proc/tty/driver/serial
     *     and /proc/tty/driver/usbserial to identify
     *     available serial ports.
     *     A complicating factor is that most (all??) linux
     *     systems require root privileges to access these files.
     *     We will use a helper program method here, despite implied vulnerability.
     */

    char buf[256]; // enough to hold one line from serial devices list
    char left_digit;
    char right_digit;
    int port_num;
    FILE *f;

    pid_t pID = vfork();

    if (pID == 0)// child
    {
//    Temporarily gain root privileges
        seteuid(file_user_id);

//  Execute the helper program
        execlp("ocpnhelper", "ocpnhelper", "-SB", NULL);

//  Return to user privileges
        seteuid(user_user_id);

        wxLogMessage(_T("Warning: ocpnhelper failed...."));
        _exit(0);// If exec fails then exit forked process.
    }

    wait(NULL);                  // for the child to quit

//    Read and parse the files

    /*
     * see if we have any traditional ttySx ports available
     */
    f = fopen("/var/tmp/serial", "r");

    if (f != NULL)
    {
        wxLogMessage(_T("Parsing copy of /proc/tty/driver/serial..."));

        /* read in each line of the file */
        while(fgets(buf, sizeof(buf), f) != NULL)
        {
            wxString sm(buf, wxConvUTF8);
            sm.Prepend(_T("   "));
            sm.Replace(_T("\n"), _T(" "));
            wxLogMessage(sm);

            /* if the line doesn't start with a number get the next line */
            if (buf[0] < '0' || buf[0] > '9')
            continue;

            /*
             * convert digits to an int
             */
            left_digit = buf[0];
            right_digit = buf[1];
            if (right_digit < '0' || right_digit > '9')
            port_num = left_digit - '0';
            else
            port_num = (left_digit - '0') * 10 + right_digit - '0';

            /* skip if "unknown" in the string */
            if (strstr(buf, "unknown") != NULL)
            continue;

            /* upper limit of 15 */
            if (port_num > 15)
            continue;

            /* create string from port_num  */

            wxString s;
            s.Printf(_T("/dev/ttyS%d"), port_num);

            /*  add to the output array  */
            preturn->Add(wxString(s));

        }

        fclose(f);
    }

    /*
     * Same for USB ports
     */
    f = fopen("/var/tmp/usbserial", "r");

    if (f != NULL)
    {
        wxLogMessage(_T("Parsing copy of /proc/tty/driver/usbserial..."));

        /* read in each line of the file */
        while(fgets(buf, sizeof(buf), f) != NULL)
        {

            wxString sm(buf, wxConvUTF8);
            sm.Prepend(_T("   "));
            sm.Replace(_T("\n"), _T(" "));
            wxLogMessage(sm);

            /* if the line doesn't start with a number get the next line */
            if (buf[0] < '0' || buf[0] > '9')
            continue;

            /*
             * convert digits to an int
             */
            left_digit = buf[0];
            right_digit = buf[1];
            if (right_digit < '0' || right_digit > '9')
            port_num = left_digit - '0';
            else
            port_num = (left_digit - '0') * 10 + right_digit - '0';

            /* skip if "unknown" in the string */
            if (strstr(buf, "unknown") != NULL)
            continue;

            /* upper limit of 15 */
            if (port_num > 15)
            continue;

            /* create string from port_num  */

            wxString s;
            s.Printf(_T("/dev/ttyUSB%d"), port_num);

            /*  add to the output array  */
            preturn->Add(wxString(s));

        }

        fclose(f);
    }

    //    As a fallback, in case seteuid doesn't work....
    //    provide some defaults
    //    This is currently the case for GTK+, which
    //    refuses to run suid.  sigh...

    if(preturn->IsEmpty())
    {
        preturn->Add( _T("/dev/ttyS0"));
        preturn->Add( _T("/dev/ttyS1"));
        preturn->Add( _T("/dev/ttyUSB0"));
        preturn->Add( _T("/dev/ttyUSB1"));
    }

//    Clean up the temporary files created by helper.
    pid_t cpID = vfork();

    if (cpID == 0)// child
    {
//    Temporarily gain root privileges
        seteuid(file_user_id);

//  Execute the helper program
        execlp("ocpnhelper", "ocpnhelper", "-U", NULL);

//  Return to user privileges
        seteuid(user_user_id);
        _exit(0);// If exec fails then exit forked process.
    }

#endif      // __WXGTK__
#ifdef __WXOSX__
#include "macutils.h"
    char* paPortNames[MAX_SERIAL_PORTS];
    int iPortNameCount;

    memset(paPortNames,0x00,sizeof(paPortNames));
    iPortNameCount = FindSerialPortNames(&paPortNames[0],MAX_SERIAL_PORTS);
    for (int iPortIndex=0; iPortIndex<iPortNameCount; iPortIndex++)
    {
        wxString sm(paPortNames[iPortIndex], wxConvUTF8);
        preturn->Add(sm);
        free(paPortNames[iPortIndex]);
    }
#endif      //__WXOSX__
#ifdef __WXMSW__
    /*************************************************************************
     * Windows provides no system level enumeration of available serial ports
     * There are several ways of doing this.
     *
     *************************************************************************/
#include <windows.h>

    //    Method 1:  Use GetDefaultCommConfig()
    // Try first {g_nCOMPortCheck} possible COM ports, check for a default configuration
    for( int i = 1; i < 10; i++ ) {
        wxString s;
        s.Printf( _T("COM%d"), i );

        COMMCONFIG cc;
        DWORD dwSize = sizeof(COMMCONFIG);
        if( GetDefaultCommConfig( s.fn_str(), &cc, &dwSize ) ) preturn->Add( wxString( s ) );
    }

#if 0
    // Method 2:  Use FileOpen()
    // Try all 255 possible COM ports, check to see if it can be opened, or if
    // not, that an expected error is returned.

    BOOL bFound;
    for (int j=1; j<256; j++)
    {
        char s[20];
        sprintf(s, "\\\\.\\COM%d", j);

        // Open the port tentatively
        BOOL bSuccess = FALSE;
        HANDLE hComm = ::CreateFile(s, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);

        //  Check for the error returns that indicate a port is there, but not currently useable
        if (hComm == INVALID_HANDLE_VALUE)
        {
            DWORD dwError = GetLastError();

            if (dwError == ERROR_ACCESS_DENIED ||
                    dwError == ERROR_GEN_FAILURE ||
                    dwError == ERROR_SHARING_VIOLATION ||
                    dwError == ERROR_SEM_TIMEOUT)
            bFound = TRUE;
        }
        else
        {
            bFound = TRUE;
            CloseHandle(hComm);
        }

        if (bFound)
        preturn->Add(wxString(s));
    }
#endif


#endif      //__WXMSW__
    return preturn;
}

obabelUIDialog::obabelUIDialog(wxWindow *parent, obabel_pi *ppi)
: obabelUIDialogBase(parent)
{
	pParent = parent;
    pPlugIn = ppi;

    wxFileConfig *pConf = GetOCPNConfigObject();

    if(pConf) {
        pConf->SetPath ( _T ( "/Settings/obabel" ) );

		pConf->Read ( _T ( "obabeldevice" ), &pPlugIn->m_GetDevice );
        pConf->Read ( _T ( "obabelformat" ), &pPlugIn->m_GetFormat);
		pConf->Read ( _T ( "obabelexe" ), &pPlugIn->m_GetExe);
    }

    this->Connect( wxEVT_MOVE, wxMoveEventHandler( obabelUIDialog::OnMove ) );
	
	wxArrayString *pSerialArray = EnumerateSerialPorts();

	 //    Fill in the listbox with all detected serial ports
    for( unsigned int iPortIndex = 0; iPortIndex < pSerialArray->GetCount(); iPortIndex++ ) {
        wxString full_port = pSerialArray->Item( iPortIndex );
        m_choice1->Append( full_port );
    }
    delete pSerialArray;
	m_choice1->SetSelection( 0 );

	m_device->SetStringSelection(pPlugIn->m_GetDevice);
	m_format->SetStringSelection(pPlugIn->m_GetFormat);
	m_textCtrl1->SetValue(pPlugIn->m_GetExe);

    DimeWindow( this );

    Fit();
    SetMinSize( GetBestSize() );

}

obabelUIDialog::~obabelUIDialog()
{
    wxFileConfig *pConf = GetOCPNConfigObject();;

    if(pConf) {
        pConf->SetPath ( _T ( "/Settings/obabel" ) );

		int c = m_choice1->GetSelection();
		wxString myP = m_choice1->GetString(c);
		pConf->Write ( _T ( "obabelcomport" ), myP );  

		wxString myG = m_textCtrl1->GetValue();
		pConf->Write ( _T ( "obabelexe" ), myG ); 

		c = m_format->GetSelection();
		wxString myF = m_format->GetString(c);
		pConf->Write ( _T ( "obabelformat" ), myF ); 

		c = m_device->GetSelection();
		wxString myD = m_device->GetString(c);
		pConf->Write ( _T ( "obabeldevice" ), myD ); 
    }	
}

void obabelUIDialog::SetCursorLatLon( double lat, double lon )
{
    m_cursor_lon = lon;
    m_cursor_lat = lat;
}

void obabelUIDialog::SetViewPort( PlugIn_ViewPort *vp )
{
    if(m_vp == vp)  return;

    m_vp = new PlugIn_ViewPort(*vp);

}

void obabelUIDialog::OnShow( wxShowEvent& event )
{

}

void obabelUIDialog::OnClose( wxCloseEvent& event )
{	
	pPlugIn->OnobabelDialogClose();
}

void obabelUIDialog::OnMove( wxMoveEvent& event )
{
    //    Record the dialog position
    wxPoint p = GetPosition();
    pPlugIn->SetobabelDialogX( p.x );
    pPlugIn->SetobabelDialogY( p.y );

    event.Skip();
}

void obabelUIDialog::OnSize( wxSizeEvent& event )
{
    //    Record the dialog size
    wxSize p = event.GetSize();
    pPlugIn->SetobabelDialogSizeX( p.x );
    pPlugIn->SetobabelDialogSizeY( p.y );

    event.Skip();
}

void obabelUIDialog::About(wxCommandEvent& event)
{
	wxMessageBox(_("Using oBabel\n--------------------------------------------------------------\nThe oBabel plugin attempts to make it easier to transfer data from OpenCPN to Garmin Chartplotters.\n\n1. Using 'right-click' on a route or waypoint in OpenCPN provides copying as KML. \nThis KML can be entered in the plugin clipboard with a 'right-click'. \nChoose the correct options for the transfer, using 'KML' from the dropdown menu.\nSend the clipboard to Garmin via GPSBabel.\n\n2. GPX files exported from OpenCPN can be sent to a Garmin Chartplotter. Again, choose the correct options, using 'oGPX' from the dropdown menu.\n\n3. For EasyGPS GPX files (and possibly some other types) you will need to select 'GPX' from the dropdown.\n\n--------------------------------------------------------------------\n"), _("About oBabel"), wxOK | wxICON_INFORMATION, this);
}

void obabelUIDialog::BuildOptions(){

	s_options[0] = wxEmptyString;
	s_options[1] = wxEmptyString;

	if (m_waypoint->IsChecked()){
		s_options[0].append(_T(" -w "));
	}

	if (m_route->IsChecked()){
		s_options[0].append(_T(" -r "));
	}

	if (m_track->IsChecked()){
		s_options[0].append(_T(" -t "));
	}
    
	int c = m_format->GetSelection();
	wxString myFormat = m_format->GetString(c);

	if (myFormat == _T("KML")){
		s_options[0].append(_T(" -i ") + myFormat + _T(",lines=0 "));
	}
	else{		
		s_options[0].append(_T(" -i GPX "));		
	}

	// Now get the string to follow the file name	

	c = m_device->GetSelection();
	wxString myDevice = m_device->GetString(c);

	if (myDevice == _T("garmin")){
		myDevice.append(_T(",baud=9600"));
	}
	
	s_options[1].append(_T(" -o ") + myDevice);

	c = m_choice1->GetSelection();
	wxString m_comport = m_choice1->GetString(c);

	s_options[1].append(_T(" -F ") + m_comport);
}

void obabelUIDialog::ShowOptions(wxCommandEvent& event){

	BuildOptions();
	wxMessageBox(s_options[0] + s_options[1], _T("Options Selected"));
}
 
void obabelUIDialog::LocateBabel( wxCommandEvent& event){

	wxFileDialog fdlg(this, _T("Locate GPSBabel"), wxEmptyString, wxEmptyString, _T("EXE files (*.exe)|*.exe"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);
	if (fdlg.ShowModal() == wxID_CANCEL){
		return;
	}
	wxString s = fdlg.GetPath();
	if (fdlg.GetPath() == wxEmptyString){
		wxMessageBox(_T("GPSBabel not found"));
	}
	else{
		m_textCtrl1->SetValue(s);
	}
}

void obabelUIDialog::OnPaste( wxMouseEvent& event ){

	// Read some text
	if (wxTheClipboard->Open())
	{
		if (wxTheClipboard->IsSupported( wxDF_TEXT ))
		{
			wxTextDataObject data;
			wxTheClipboard->GetData( data );
			m_clip->SetValue(data.GetText());
		}
		wxTheClipboard->Close();
	}

}

void obabelUIDialog::SendBabelFile(wxCommandEvent& event){
	
	 BuildOptions();

	 wxString m_gpx_path;
	 wxString m_file;
	 wxFileDialog openDialog( this, _( "Import GPX file" ), m_gpx_path, wxT ( "" ),
                wxT ( "GPX files (*.gpx)|*.gpx|All files (*.*)|*.*" ),
                wxFD_OPEN);
     int response = openDialog.ShowModal();
     if( response == wxID_OK ) {

		m_file = openDialog.GetPath();

		wxString spath;
		spath = m_textCtrl1->GetValue();
		bool b_exe = true;
		if (spath.Right(5) == _T("e.exe")){
			b_exe = false;
		}
		if (spath == wxEmptyString || !b_exe){
			wxMessageBox(_T("GPSBabel program not found"), _T("GPSBabel"));
			return;
		}
		wxString transform = wxEmptyString;
		int c = m_format->GetSelection();
		wxString myFormat = m_format->GetString(c);

		if (myFormat == _T("KML")){
			transform = _T(" -x transform,rte=wpt ");
		}
		else{
			if  (myFormat == _T("oGPX")){
				transform = _T(" -x transform,wpt=rte ");
			}
			else{
				transform = _T("");
			}
		}

		wxString cmdstart = spath + s_options[0] + _T(" -f ") + _T("\"") + m_file + _T("\"") + transform + s_options[1];

		wxMessageDialog *dial = new wxMessageDialog(NULL, cmdstart, wxT("Proceed?"), wxOK | wxCANCEL);
        response = dial->ShowModal();
        if( response == wxID_OK ) {
			m_server_pid = wxExecute( cmdstart, wxEXEC_SYNC);
		}
		else{
			return;
		}

     }
	 else{
		 return;
	 }	
}

void obabelUIDialog::SendBabelClip(wxCommandEvent& event){

	BuildOptions();

	wxString m_clipcontent = wxEmptyString;
	m_clipcontent = m_clip->GetValue();

	if (m_clipcontent == wxEmptyString){
		wxMessageBox(_T("Clipboard is empty"), _T("Clipboard"));
		return;
	}

	wxFFile babelfile;
	wxString babelfilename = wxFileName::CreateTempFileName(wxT("babs"), & babelfile);
	babelfile.Write(m_clipcontent);
	babelfile.Close();

	wxString spath;
	spath = m_textCtrl1->GetValue();
    bool b_exe = true;
	if (spath.Right(5) == _T("e.exe")){
		b_exe = false;
	}
	if (spath == wxEmptyString || !b_exe){
		wxMessageBox(_T("GPSBabel program not found"), _T("GPSBabel"));
		return;
	}

	wxString cmdstart = spath + s_options[0] + _T(" -f ") + _T("\"") + babelfilename + _T("\"") + _T(" -x transform,rte=wpt ") + s_options[1];

	wxMessageDialog *dial = new wxMessageDialog(NULL, cmdstart, wxT("Proceed?"), wxOK | wxCANCEL);
    int response = dial->ShowModal();
    if( response == wxID_OK ) {
		m_server_pid = wxExecute( cmdstart, wxEXEC_SYNC);
		wxRemoveFile(babelfilename);
		return;
	}
	else{
		wxRemoveFile(babelfilename);
		return;
	}

}





