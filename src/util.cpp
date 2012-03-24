#include <iostream>

#include "util.h"
    
void Util::importSMS(QTextStream &in) {
    QString line;
    GroupModel groupModel;
    groupModel.enableContactChanges(false);
    groupModel.setQueryMode(EventModel::SyncQuery);
    QList<Event> events;
    int count = 0;
    int groupId;
    QMap<QString, int> phoneGroupMap;
    while (!(line = in.readLine()).isNull()) {
        count ++;
        std::cout << "Handling " << count << " messages" << std::endl;
        QStringList stringList = line.split(QChar(','));

        QString remoteUid = stringList.at(0);

        QString localUid = RING_ACCOUNT;

        QDateTime startTime = QDateTime::fromString(stringList.at(2), "yyyy-MM-dd hh:mm:ss");
        QDateTime endTime = startTime;

        if (!phoneGroupMap.contains(remoteUid)) {
            if (!groupModel.getGroups(RING_ACCOUNT, QString(remoteUid))) {
                std::cout << "Error getting groups!";
                return;
            } else {
                if (groupModel.rowCount() >= 1) {
                    groupId = groupModel.group(groupModel.index(0, 0)).id();
                } else {
                    // new group
                    Group group;
                    group.setLocalUid(localUid);
                    QStringList remoteUids;
                    remoteUids << remoteUid;
                    group.setRemoteUids(remoteUids);
                    if (!groupModel.addGroup(group)) {
                        qCritical() << "Error adding group";
                        return;
                    }
                    groupId = group.id();
                }
                phoneGroupMap.insert(remoteUid, groupId);
            }
        } else {
            groupId = phoneGroupMap[remoteUid];
        }

        Event::EventDirection direction = Event::UnknownDirection;
        if (stringList.at(1) == QString("1"))
            direction = Event::Inbound;
        else
            direction = Event::Outbound;

        Event e;
        e.setDirection(direction);
        e.setType(Event::SMSEvent);
        e.setLocalUid(localUid);
        e.setMessageToken(QUuid::createUuid().toString());

        e.setStartTime(startTime);
        e.setEndTime(endTime);
        e.setIsRead(true);
        e.setStatus(Event::DeliveredStatus);
        e.setBytesReceived(0);
        e.setGroupId(groupId);
        e.setRemoteUid(remoteUid);

        QString freeText = QStringList(stringList.mid(3)).join(QString(","));
        if (freeText.count(QChar('"')) % 2 != 0)
        {
            QString nextLine;
            while (!(nextLine = in.readLine()).isNull()) {
                freeText += "\n" + nextLine;
                if (nextLine.count(QChar('"')) % 2 != 0) {
                    break;
                }
            }
        }
        freeText = freeText.mid(1, freeText.length() - 2);
        freeText.replace(QString("\"\""), QChar('"'));
        e.setFreeText(freeText);

        events.append(e);

        std::cout << "Handled " << count << " messages" << std::endl;
    }
    if (events.count() > 0) {
        std::cout << "About to commit the changes" << std::endl;
        EventModel model;
        Catcher c(&model);
        if (!model.addEvents(events, false)) {
            qCritical() << "Error adding events";
            return;
        }

        c.waitCommit(events.count());
    }
    
}

void Util::exportSMS(QTextStream &out) {
    GroupModel groupModel;
    groupModel.enableContactChanges(false);
    groupModel.setQueryMode(EventModel::SyncQuery);

    groupModel.getGroups();

    EventModel eventModel;
    ConversationModel model;
    model.enableContactChanges(false);
    model.setQueryMode(EventModel::SyncQuery);
    for (int i = 0; i < groupModel.rowCount(); i++) {
        Group g = groupModel.group(groupModel.index(i, 0));

        model.getEvents(g.id());

        // the events got by getEvents is reversed-ordered
        for (int i = model.rowCount() - 1; i >= 0; i--) {
            Event event = model.event(model.index(i, 0));
            out << QString(event.remoteUid() % QChar(',') %
                                      QString::number(event.direction()) % QChar(',') %
                                      event.startTime().toLocalTime().toString(QString("yyyy-MM-dd hh:mm:ss")) % QChar(',') %
                                      QChar('"') % event.freeText().replace(QChar('"'), QString("\"\"")) % QChar('"'));
            out << "\n";
        }
    }
}
