#include <QApplication>
#include "easylogging++.h"
#include "command_line_args.h"
#include "credentials.h"

_INITIALIZE_EASYLOGGINGPP

static const char* kGlobalConfigurationsFileParam = "--loggers-conf";

void configureLoggersFromArgs(CommandLineArgs*);

int main(int argc, char *argv[])
{
    QApplication qapp(argc, argv);
    el::Helpers::setArgs(argc, argv);
    CommandLineArgs commandLineArgs(argc, argv);
    // Configure loggers globally if arguments have global configurations
    configureLoggersFromArgs(&commandLineArgs);
    // Figure out credentials for current instance of server
    Credentials credentials(&commandLineArgs);
    LOG_IF(credentials.users().size() > 0, INFO) << "Credentials [" << credentials << "]";
    return 0;//qapp.exec();
}

void configureLoggersFromArgs(CommandLineArgs* commandLineArgs)
{
    if (commandLineArgs->hasParamWithValue(kGlobalConfigurationsFileParam)) {
        const char* logConfPath = commandLineArgs->getParamValue(kGlobalConfigurationsFileParam);
        VLOG(3) << "Configuring loggers using configurations from [" << logConfPath << "]";
        el::Loggers::configureFromGlobal(logConfPath);
    }
}
