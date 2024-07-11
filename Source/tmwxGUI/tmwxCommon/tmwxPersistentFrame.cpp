/*******************************************************************************
File:         tmwxPersistentFrame.cpp
Project:      TreeMaker 5.x
Purpose:      Implementation file for class tmwxPersistentFrame
Author:       Robert J. Lang
Modified by:  
Created:      2005-02-19
Copyright:    ©2005 Robert J. Lang. All Rights Reserved.
*******************************************************************************/

#include "tmwxPersistentFrame.h"
#include "tmwxDocManager.h"

/**********
class tmwxPersistentFrame
A wxFrame that remembers its position and size in wxConfig.
**********/

/*****
Constructor for ordinary wxFrame with persistence
*****/
template <>
tmwxPersistentFrame<wxFrame>::tmwxPersistentFrame(const wxString& title, 
  long style)  : 
  wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, style),
  mPositionAndSizeInitialized(false)
{
	Bind(wxEVT_MOVE, &tmwxPersistentFrame::OnMove, this);
	Bind(wxEVT_SIZE, &tmwxPersistentFrame::OnSize, this);
#if defined(__LINUX__) || defined(__WXMSW__)
	SetIcon (wxGetApp ().GetAppIcon ());
#endif
}


/*****
Constructor for tmwxDocParentFrame frames
*****/
template <>
tmwxPersistentFrame<tmwxDocParentFrame>::tmwxPersistentFrame(
  wxDocManager* docManager, const wxString& title, long style)  : 
  tmwxDocParentFrame(docManager, NULL, wxID_ANY, title, wxDefaultPosition, 
    wxDefaultSize, style),
  mPositionAndSizeInitialized(false)
{
	Bind(wxEVT_MOVE, &tmwxPersistentFrame::OnMove, this);
	Bind(wxEVT_SIZE, &tmwxPersistentFrame::OnSize, this);
#if defined(__LINUX__) || defined(__WXMSW__)
  SetIcon (wxGetApp ().GetAppIcon ());
#endif
}
