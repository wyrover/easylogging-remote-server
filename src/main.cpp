#include <QApplication>
#include "easylogging++.h"
#include "credentials.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{
    QApplication qapp(argc, argv);
    el::Helpers::setArgs(argc, argv);
    Credentials credentials(argc, argv);
    LOG_IF(credentials.users().size() > 0, INFO) << "Credentials [" << credentials << "]";
    return 0;//qapp.exec();
}
