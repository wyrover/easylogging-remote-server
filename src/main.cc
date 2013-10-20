#include <QApplication>
#include "easylogging++.h"
#include "credentials.h"
#include "server.h"

_INITIALIZE_EASYLOGGINGPP

static const char* kGlobalConfigurationsFileParam = "--loggers-conf";

int main(int argc, char *argv[])
{
    QApplication qapp(argc, argv);
    el::Helpers::setArgs(argc, argv);
    
    el::Helpers::addFlag(el::LoggingFlag::StrictLogFileSizeCheck);
    el::Helpers::addFlag(el::LoggingFlag::DisableApplicationAbortOnFatalLog);
    el::Helpers::addFlag(el::LoggingFlag::AllowVerboseIfModuleNotSpecified);
    //el::Helpers::addFlag(el::LoggingFlag::ColoredTerminalOutput);
    
    if (el::Loggers::configureFromArg(kGlobalConfigurationsFileParam)) {
        LOG(INFO) << "Configuring loggers using configurations from [" << el::Helpers::commandLineArgs()->getParamValue(kGlobalConfigurationsFileParam) << "]";
    } else {
        LOG(WARNING) << "No logging configurations provided, using default.";
    }

    // Figure out credentials for current instance of server
    Credentials credentials;
    LOG_IF(credentials.users().size() > 0, INFO) << "Credentials [" << credentials << "]";

    Server server(&credentials);
    server.start();

    return qapp.exec();
}
