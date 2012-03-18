#include <CommHistory/GroupModel>
#include <CommHistory/Event>
#include <CommHistory/Group>
#include <CommHistory/TrackerIO>
#include <CommHistory/ConversationModel>
#include <QStringBuilder>
#include <QUuid>
#include "catcher.h"

using namespace CommHistory;

#define TELEPATHY_ACCOUNT_PREFIX       QLatin1String("/org/freedesktop/Telepathy/Account/")
#define TELEPATHY_RING_ACCOUNT_POSTFIX QLatin1String("ring/tel/ring")
#define RING_ACCOUNT TELEPATHY_ACCOUNT_PREFIX + TELEPATHY_RING_ACCOUNT_POSTFIX

class Util {
public:
	static void importSMS(QTextStream &in);
	static void exportSMS(QTextStream &out);
};