#ifndef COMMAND_LINE_ARGS_H
#define COMMAND_LINE_ARGS_H
#include <cstring>

extern bool hasLongParam(const char *arg, const char* paramKey);

extern const char* getLongParamValue(char* arg, const char* paramKey);

extern bool hasLongParam(const char *arg, const char* paramKey);

extern const char* getLongParamValue(const char* arg, const char* paramKey);

#endif // COMMAND_LINE_ARGS_H
