/***************************************************************************
 *   Copyright (C) 2005 by PCMan   *
 *   hzysoft@sina.com.tw   *
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
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "dialog.h"

#include <gdk/gdkkeysyms.h>

static void on_response(GtkDialog* dlg, gint arg, CDialog* _this)
{
	switch(arg)
	{
	case GTK_RESPONSE_OK:
		if(!_this->OnOK())
			g_signal_stop_emission_by_name(dlg, "response");
		break;
	case GTK_RESPONSE_CANCEL:
		if( !_this->OnCancel() )
			g_signal_stop_emission_by_name(dlg, "response");
		break;
	default:
		_this->OnCommand(arg);
	}
}


CDialog::CDialog(CWidget* parent, const char* title, bool show_okcancel)
        : CWidget()
{
	if(show_okcancel)
	{
		m_Widget = gtk_dialog_new_with_buttons(title, GTK_WINDOW(parent->m_Widget),
		 GtkDialogFlags(GTK_DIALOG_MODAL|GTK_DIALOG_DESTROY_WITH_PARENT), GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
		gtk_dialog_set_default_response((GtkDialog*)m_Widget, GTK_RESPONSE_OK);
	}
	else
		m_Widget = gtk_dialog_new_with_buttons(title, GTK_WINDOW(parent->m_Widget),
		GTK_DIALOG_MODAL, NULL, NULL);

	gtk_window_set_type_hint (GTK_WINDOW (m_Widget), GDK_WINDOW_TYPE_HINT_DIALOG);

	PostCreate();

	g_signal_connect(G_OBJECT(m_Widget), "response", G_CALLBACK(on_response), this);
}


CDialog::~CDialog()
{
}


int CDialog::ShowModal()
{
	int response = gtk_dialog_run(GTK_DIALOG(m_Widget));
	return response;
}


bool CDialog::OnOK()
{
	return true;
}


bool CDialog::OnCancel()
{
	return true;
}


void CDialog::OnCommand(int id)
{

}
