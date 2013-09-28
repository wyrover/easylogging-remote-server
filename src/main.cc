#include <QApplication>
#include "easylogging++.h"
#include "credentials.h"
#include "server.h"


_INITIALIZE_EASYLOGGINGPP

static const char* kGlobalConfigurationsFileParam = "--loggers-conf";
static const char* kPortParam = "--port";
static const int kDefaultPort = 1592;

int main(int argc, char *argv[])
{
    QApplication qapp(argc, argv);
    el::Helpers::setArgs(argc, argv);
    if (el::Loggers::configureFromArg(kGlobalConfigurationsFileParam)) {
        LOG(INFO) << "Configuring loggers using configurations from [" << el::Helpers::commandLineArgs()->getParamValue(kGlobalConfigurationsFileParam) << "]";
    } else {
        LOG(WARNING) << "No logging configurations provided, using default.";
    }

    // Figure out credentials for current instance of server
    Credentials credentials;
    LOG_IF(credentials.users().size() > 0, INFO) << "Credentials [" << credentials << "]";

    el::Helpers::addFlag(el::LoggingFlag::AllowVerboseIfModuleNotSpecified);

    int port = el::Helpers::commandLineArgs()->hasParamWithValue(kPortParam) ? atoi(el::Helpers::commandLineArgs()->getParamValue(kPortParam)) : kDefaultPort;
    if (port == 0) {
        port = kDefaultPort;
    }

    LOG(INFO) << "Server is starting" << (!el::Helpers::commandLineArgs()->empty() ? " using parameters " : "...") << *el::Helpers::commandLineArgs();
    Server server(&credentials);
    server.start(port);

    return qapp.exec();
}
