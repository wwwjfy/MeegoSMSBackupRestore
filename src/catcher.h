/******************************************************************************
**
** This file is part of libcommhistory.
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Alexander Shalamov <alexander.shalamov@nokia.com>
**
** This library is free software; you can redistribute it and/or modify it
** under the terms of the GNU Lesser General Public License version 2.1 as
** published by the Free Software Foundation.
**
** This library is distributed in the hope that it will be useful, but
** WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
** or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
** License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this library; if not, write to the Free Software Foundation, Inc.,
** 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
**
******************************************************************************/

#ifndef CATCHER_H
#define CATCHER_H

#include <QObject>
#include <QList>
#include <QCoreApplication>

#include <CommHistory/EventModel>

namespace CommHistory {
    class GroupModel;
};

class Catcher : public QObject
{
    Q_OBJECT
public:
    Catcher(CommHistory::EventModel *model) : count(0) {
        connect(model, SIGNAL(eventsCommitted(QList<CommHistory::Event>,bool)),
                this, SLOT(eventsCommittedSlot(QList<CommHistory::Event>,bool)));
    };

    Catcher(CommHistory::GroupModel *model) : count(0) {
        connect((QObject*)model, SIGNAL(groupsCommitted(QList<int>,bool)),
                this, SLOT(groupsCommittedSlot(QList<int>,bool)));
    };

    void waitCommit(int numEvents = 1) {
        count = 0;
        stop = false;
        while(count < numEvents || (numEvents == 0 && !stop)) {
            QCoreApplication::instance()->processEvents(QEventLoop::WaitForMoreEvents);
        }
    };

    bool ok;
    QList<CommHistory::Event> events;
    int count;
    bool stop;

public Q_SLOTS:
    void eventsCommittedSlot(QList<CommHistory::Event> committedEvents, bool success) {
        ok = success;
        events = committedEvents;
        count += committedEvents.count();
        stop = true;
    };

    void groupsCommittedSlot(QList<int> committedGroups, bool success) {
        Q_UNUSED(committedGroups);

        ok = success;
        stop = true;
    }
};

#endif // CATCHER_H
