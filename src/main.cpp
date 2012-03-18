#include <QtCore>
#include <iostream>
#include "util.h"

void usage() {
	std::cout << "Usage:" << std::endl;
	std::cout << "import [filename]" << std::endl;
	std::cout << "export [filename]" << std::endl;
}

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    QStringList args = app.arguments();

    if (args.count() < 3) {
    	usage();
    	exit(0);
    }

    if (args.at(1) == "export") {
	    QFile file(args.at(2));
	    file.open(QIODevice::WriteOnly);
	    QTextStream out(&file);
	    Util::exportSMS(out);
	} else if (args.at(1) == "import") {
		QFile file(args.at(2));
	    file.open(QIODevice::ReadOnly);
	    QTextStream in(&file);
	    Util::importSMS(in);
	} else {
		usage();
	}
    return 0;
}