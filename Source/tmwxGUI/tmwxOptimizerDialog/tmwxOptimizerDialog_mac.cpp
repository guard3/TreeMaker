/*******************************************************************************
File:         tmwxOptimizerDialog_mac.cpp
Project:      TreeMaker 5.x
Purpose:      Source file for class tmwxOptimizerDialog, specialization for Mac
                Derived from wx/src/mac/wxDialog
Author:       Stefan Csomor
Modified by:  Robert J. Lang
              Konstantinos Bolosis
Created:     (original), 2004-04-22 (modifications)
Copyright (original):       ©2004 by Stefan Csomor, 
                              released under the wxWidgets license
Copyright (modifications):  ©2004 Robert J. Lang. All Rights Reserved.
*******************************************************************************/

#ifdef __WXMAC__

// Platform-specific includes
#if 0
#include <Carbon/Carbon.h>
#else
#warning "TODO: Check what's going on here"
#endif

#include "tmwxOptimizerDialog.h"


/**********
class tmwxOptimizerDialog
Dialog for long, cancellable calculations
**********/
#if 0
#if !TARGET_CARBON
extern bool s_macIsInModalLoop;
static bool s_formerModal;
#endif

extern wxWindowList wxModalDialogs;
#else
#warning "TODO: Check what's going on here"
#endif

/*****
Put up and show the modal dialog. This code is basically everything that happens
in a call to wxDialog::ShowModal(), up to the start of the dialog event loop.
*****/
void tmwxOptimizerDialog::DoStartModal()
{
  ::wxBeginBusyCursor();
#if 0
  SetModal(true);
#else
#warning "TODO: Check what's going on here"
#endif
  if (!wxDialogBase::Show(true)) 
    TMFAIL("error, dialog was already visible in "\
      "tmwxOptimizerDialog::DoStartModal()");
  InitDialog();
#if 0
  wxModalDialogs.Append(this);
#if TARGET_CARBON
  BeginAppModalStateForWindow((WindowRef) MacGetWindowRef());
#else
  s_formerModal = s_macIsInModalLoop;
  s_macIsInModalLoop = true;
#endif
#else
#warning "TODO: Check what's going on here"
#endif
}


/*****
Process a single event. Subclasses that implement their own event loop must
call this routine periodically through the loop.
*****/
void tmwxOptimizerDialog::DoEventLoopOnce()
{
#if 0
  wxTheApp->MacDoOneEvent();
#else
#warning "TODO: Check what's going on here"
#endif
}


/*****
Take down the modal dialog and do cleanup. This code is basically 
wxDialog::Show(false), followed by everything
that happens in a call to wxDialog::ShowModal() after the event loop.
*****/
void tmwxOptimizerDialog::DoFinishModal()
{
  if (!wxDialogBase::Show(false))
    TMFAIL("error, dialog was already hidden in "\
      "tmwxOptimizerDialog::DoFinishModal()");
#if 0
  wxModalDialogs.DeleteObject(this);
#if TARGET_CARBON
  EndAppModalStateForWindow((WindowRef) MacGetWindowRef());
#else
  s_macIsInModalLoop = s_formerModal;
#endif
#else
#warning "TODO: Check what's going on here"
#endif
  ::wxEndBusyCursor();
}

#endif // __WXMAC__
