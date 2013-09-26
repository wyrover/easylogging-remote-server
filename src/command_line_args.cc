#include "command_line_args.h"
#include <cstring>
#include <algorithm>

CommandLineArgs::CommandLineArgs(int argc, char** argv) :
    m_argc(argc),
    m_argv(argv)
{
    for (int i = 1; i < m_argc; ++i) {
        const char* v = (strstr(m_argv[i], "="));
        if (v != nullptr && strlen(v) > 0) {
            std::string key = std::string(m_argv[i]);
            key = key.substr(0, key.find_first_of('='));
            m_paramsWithValue.insert(std::make_pair(key, std::string(v + 1)));
        }
        if (v == nullptr) {
            m_params.push_back(std::string(m_argv[i]));
        }
    }
}

bool CommandLineArgs::hasParamWithValue(const char* paramKey) const
{
    return m_paramsWithValue.find(std::string(paramKey)) != m_paramsWithValue.end();
}

const char* CommandLineArgs::getParamValue(const char* paramKey) const
{
    return m_paramsWithValue.find(std::string(paramKey))->second.c_str();
}

bool CommandLineArgs::hasParam(const char *paramKey) const
{
    return std::find(m_params.begin(), m_params.end(), std::string(paramKey)) != m_params.end();
}

bool CommandLineArgs::empty(void) const
{
    return m_params.empty() && m_paramsWithValue.empty();
}

void CommandLineArgs::log(std::ostream& os) const
{
    for (int i = 1; i < m_argc; ++i) {
        os << "[" << m_argv[i] << "]";
        if (i < m_argc - 1)
            os << " ";
    }
}
