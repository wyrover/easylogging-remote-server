#include <QApplication>
#include "easylogging++.h"
#include "command_line_args.h"
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
        if (hasLongParam(argv[i], kGlobalConfigurationsFileParam)) {
            VLOG(3) << "Configuring loggers using configurations from [" << argv[i + 1] << "]";
            el::Loggers::configureFromGlobal(getLongParamValue(argv[i], kGlobalConfigurationsFileParam));
        }
    } 
}
