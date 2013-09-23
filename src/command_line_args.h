#ifndef COMMAND_LINE_ARGS_H
#define COMMAND_LINE_ARGS_H

#include <string>
#include <map>
#include <vector>

class CommandLineArgs {
public:
    explicit CommandLineArgs(int argc, char** argv);
    bool hasParamWithValue(const char* paramKey) const;
    const char* getParamValue(const char* paramKey) const;
private:
    int m_argc;
    char** m_argv;
    std::map<std::string, std::string> m_paramsWithValue;
};

#endif // COMMAND_LINE_ARGS_H
