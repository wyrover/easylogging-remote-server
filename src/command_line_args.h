#ifndef COMMAND_LINE_ARGS_H
#define COMMAND_LINE_ARGS_H

#include <string>
#include <map>
#include <vector>
#include "easylogging++.h"

class CommandLineArgs : public el::Loggable {
public:
    CommandLineArgs(int argc, char** argv);
    bool hasParamWithValue(const char* paramKey) const;
    const char* getParamValue(const char* paramKey) const;
    bool hasParam(const char* paramKey) const;
    bool empty(void) const;
    virtual void log(std::ostream &) const;
private:
    int m_argc;
    char** m_argv;
    std::map<std::string, std::string> m_paramsWithValue;
    std::vector<std::string> m_params;
};

#endif // COMMAND_LINE_ARGS_H
