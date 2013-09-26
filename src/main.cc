#include <QApplication>
#include "easylogging++.h"
#include "command_line_args.h"
#include "credentials.h"
#include "server.h"

_INITIALIZE_EASYLOGGINGPP

static const char* kGlobalConfigurationsFileParam = "--loggers-conf";
static const char* kPortParam = "--port";
static const int kDefaultPort = 1592;

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

    el::Helpers::addFlag(el::LoggingFlag::AllowVerboseIfModuleNotSpecified);

    int port = commandLineArgs.hasParamWithValue(kPortParam) ? atoi(commandLineArgs.getParamValue(kPortParam)) : kDefaultPort;
    if (port == 0) {
        port = kDefaultPort;
    }

    LOG(INFO) << "Server is starting" << (!commandLineArgs.empty() ? " using parameters " : "...") << commandLineArgs;
    Server server(&credentials);
    server.start(port);

    return qapp.exec();
}

void configureLoggersFromArgs(CommandLineArgs* commandLineArgs)
{
    if (commandLineArgs->hasParamWithValue(kGlobalConfigurationsFileParam)) {
        const char* logConfPath = commandLineArgs->getParamValue(kGlobalConfigurationsFileParam);
        LOG(INFO) << "Configuring loggers using configurations from [" << logConfPath << "]";
        el::Loggers::configureFromGlobal(logConfPath);
    }
}
