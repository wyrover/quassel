/***************************************************************************
 *   Copyright (C) 2005-2010 by the Quassel Project                        *
 *   devel@quassel-irc.org                                                 *
 *                                                                         *
 *   This contains code from KStatusNotifierItem, part of the KDE libs     *
 *   Copyright (C) 2009 Marco Martin <notmart@gmail.com>                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) version 3.                                           *
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

#ifndef STATUSNOTIFIERITEM_H_
#define STATUSNOTIFIERITEM_H_

#ifdef HAVE_DBUS

#include "systemtray.h"
#include "statusnotifierwatcher.h"

#ifdef QT_NO_SYSTEMTRAYICON
#  define StatusNotifierItemParent SystemTray
#else
#  define StatusNotifierItemParent LegacySystemTray
#  include "legacysystemtray.h"
#endif

class StatusNotifierItemDBus;

class StatusNotifierItem : public StatusNotifierItemParent {
  Q_OBJECT

public:
  explicit StatusNotifierItem(QWidget *parent);
  virtual ~StatusNotifierItem();

public slots:
  virtual void setState(State state);

protected:
  virtual void init();
  virtual void setMode(Mode mode);

  QString title() const;
  QString iconName() const;
  QString attentionIconName() const;
  QString toolTipIconName() const;

  virtual bool eventFilter(QObject *watched, QEvent *event);

private slots:
  void activated(const QPoint &pos);
  void serviceChange(const QString& name, const QString& oldOwner, const QString& newOwner);

private:
  void registerToDaemon();

  static const int _protocolVersion;
  StatusNotifierItemDBus *_statusNotifierItemDBus;

  org::kde::StatusNotifierWatcher *_statusNotifierWatcher;
  //org::freedesktop::Notifications *_notificationsClient;

  friend class StatusNotifierItemDBus;
};

#endif /* HAVE_DBUS */
#endif /* STATUSNOTIFIERITEM_H_ */