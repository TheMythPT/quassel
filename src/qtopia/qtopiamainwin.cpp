/***************************************************************************
 *   Copyright (C) 2005-07 by The Quassel IRC Development Team             *
 *   devel@quassel-irc.org                                                 *
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

#include "qtopiamainwin.h"

#include "global.h"
#include "message.h"
#include "qtopiagui.h"
#include "coreconnectdlg.h"

// This constructor is the first thing to be called for a Qtopia app, so we do the init stuff
// here (rather than in a main.cpp).
QtopiaMainWin::QtopiaMainWin(QWidget *parent, Qt::WFlags flags) : QMainWindow(parent, flags) {
  qRegisterMetaType<QVariant>("QVariant");
  qRegisterMetaType<Message>("Message");
  qRegisterMetaType<BufferId>("BufferId");
  qRegisterMetaTypeStreamOperators<QVariant>("QVariant");
  qRegisterMetaTypeStreamOperators<Message>("Message");
  qRegisterMetaTypeStreamOperators<BufferId>("BufferId");

  Global::runMode = Global::ClientOnly;

  QCoreApplication::setOrganizationDomain("quassel-irc.org");
  QCoreApplication::setApplicationName("Quassel IRC");
  QCoreApplication::setOrganizationName("Quassel IRC Development Team");

  //Style::init();
  QtopiaGui *gui = new QtopiaGui(this);
  Client::init(gui);
  //gui->init();

  setWindowTitle("Quassel IRC");
  //setWindowTitle(QString::fromUtf8("Κυασελ Εγαρζη"));
  setWindowIcon(QIcon(":/qirc-icon.png"));
  setWindowIconText("Quassel IRC");

  CoreConnectDlg *dlg = new CoreConnectDlg(this);
  //setCentralWidget(dlg);
  dlg->showMaximized();
  dlg->exec();
}

QtopiaMainWin::~QtopiaMainWin() {


}

void QtopiaMainWin::connectedToCore() {
  foreach(BufferId id, Client::allBufferIds()) {
    emit requestBacklog(id, 100, -1);
  }
}

void QtopiaMainWin::disconnectedFromCore() {


}

AbstractUiMsg *QtopiaMainWin::layoutMsg(const Message &msg) {
  //return new ChatLine(msg);
  return 0;
}
