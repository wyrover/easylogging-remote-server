#include <QApplication>
#include "easylogging++.h"
#include "credentials.h"

_INITIALIZE_EASYLOGGINGPP

static const char* kGlobalConfigurationsFileParam = "--loggers-conf";

void configureLoggersFromArgs(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    QApplication qapp(argc, argv);
    el::Helpers::setArgs(argc, argv);
    // Configure loggers globally if arguments have global configurations
    configureLoggersFromArgs(argc, argv);
    // Figure out credentials for current instance of server
    Credentials credentials(argc, argv);
    LOG_IF(credentials.users().size() > 0, INFO) << "Credentials [" << credentials << "]";
    return 0;//qapp.exec();
}

void configureLoggersFromArgs(int argc, char *argv[]) 
{
   for (int i = 1; i < argc; ++i) {
        if (i != argc - 1) {
            if (strcmp(argv[i], kGlobalConfigurationsFileParam) == 0) {
                LOG(INFO) << "Configuring loggers using configurations from [" << argv[i + 1] << "]";
                el::Loggers::configureFromGlobal(argv[i + 1]);
            }
        }
    } 
}
