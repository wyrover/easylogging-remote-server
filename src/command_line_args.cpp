#include "command_line_args.h"

bool hasLongParam(char* arg, const char* paramKey) {
    return strncmp(arg, paramKey, strlen(paramKey)) == 0 && strlen(arg) > strlen(paramKey) && arg[strlen(paramKey)] == '=';
}

const char* getLongParamValue(char* arg, const char* paramKey) {
    return arg + strlen(paramKey) + 1;
}

bool hasLongParam(const char* arg, const char* paramKey) {
    return hasLongParam(const_cast<char*>(arg), paramKey);
}

const char* getLongParamValue(const char* arg, const char* paramKey) {
    return getLongParamValue(const_cast<char*>(arg), paramKey);
}
