//
//  Easylogging++ v9.20
//  Single-header only, cross-platform logging library for C++ applications
//
//  Author Majid Khan
//
//  support@easylogging.org
//  http://easylogging.org
//  https://github.com/easylogging/easyloggingpp
//
//  The MIT License (MIT)
//
//  Copyright (c) 2013 Majid Khan
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of
//  this software and associated documentation files (the "Software"), to deal in
//  the Software without restriction, including without limitation the rights to
//  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
//  the Software, and to permit persons to whom the Software is furnished to do so,
//  subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
//  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
//  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
//  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
#ifndef EASYLOGGINGPP_H
#define EASYLOGGINGPP_H
//////////////////////////////////////////////////////////////////////
// Compilers and C++0x/C++11 Evaluation
// We define one of the following macros:
//  * _ELPP_CXX0X
//  * _ELPP_CXX11
//////////////////////////////////////////////////////////////////////
#if defined(__GNUC__)
#   define _ELPP_COMPILER_GCC 1
#   define _ELPP_GCC_VERSION (__GNUC__ * 10000 \
                               + __GNUC_MINOR__ * 100 \
                               + __GNUC_PATCHLEVEL__)
#   if defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define _ELPP_CXX0X 1
#   elif (_ELPP_GCC_VERSION >= 40801)
#      define _ELPP_CXX11 1
#   endif // defined(__GXX_EXPERIMENTAL_CXX0X__)
#endif // defined(__GNUC__)
// Visual C++
#if defined(_MSC_VER)
#   define _ELPP_COMPILER_MSVC 1
#   define _ELPP_CRT_DBG_WARNINGS 1
#   if (_MSC_VER == 1600)
#      define _ELPP_CXX0X 1
#   elif (_MSC_VER >= 1700)
#      define _ELPP_CXX11 1
#   endif // (_MSC_VER == 1600)
#else
#   define _ELPP_CRT_DBG_WARNINGS 0
#endif // defined(_MSC_VER)
// Clang++
#if defined(__clang__) && (__clang__ == 1)
#   define _ELPP_COMPILER_CLANG 1
#   define _ELPP_CLANG_VERSION (__clang_major__ * 10000 \
                                + __clang_minor__ * 100 \
                                + __clang_patchlevel__)
#   if (_ELPP_CLANG_VERSION >= 30300)
#      define _ELPP_CXX11 1
#   endif // (_ELPP_CLANG_VERSION >= 30300)
#endif // defined(__clang__) && (__clang__ == 1)
// MinGW
#if defined(__MINGW32__) || defined(__MINGW64__)
#   define _ELPP_MINGW 1
#endif // defined(__MINGW32__) || defined(__MINGW64__)
// Cygwin
#if defined(__CYGWIN__) && (__CYGWIN__ == 1)
#   define _ELPP_CYGWIN 1
#endif // defined(__CYGWIN__) && (__CYGWIN__ == 1)
// Intel C++
#if defined(__INTEL_COMPILER)
#   define _ELPP_COMPILER_INTEL 1
#endif
//////////////////////////////////////////////////////////////////////
// Operating System Evaluation
// We define one of the following macros:
//   * _ELPP_OS_WINDOWS
//   * _ELPP_OS_LINUX (_ELPP_OS_UNIX)
//   * _ELPP_OS_MAC (_ELPP_OS_UNIX)
//   * _ELPP_OS_ANDROID
///////////////////////////////////////////////////////////////////////
// Windows
#if defined(_WIN32) || defined(_WIN64)
#   define _ELPP_OS_WINDOWS 1
#else
#   define _ELPP_OS_WINDOWS 0
#endif // defined(_WIN32) || defined(_WIN64)
// Linux
#if (defined(__linux) || defined(__linux__))
#   define _ELPP_OS_LINUX 1
#else
#   define _ELPP_OS_LINUX 0
#endif // (defined(__linux) || defined(__linux__))
// Mac
#if defined(__APPLE__)
#   define _ELPP_OS_MAC 1
#else
#   define _ELPP_OS_MAC 0
#endif // defined(__APPLE__)
// Unix
#define _ELPP_OS_UNIX ((_ELPP_OS_LINUX || _ELPP_OS_MAC) && (!_ELPP_OS_WINDOWS))
// Android
#if defined(__ANDROID__)
#   define _ELPP_OS_ANDROID 1
#else
#   define _ELPP_OS_ANDROID 0
#endif // defined(__ANDROID__)
// Evaluating Cygwin as unix OS
#if (!_ELPP_OS_UNIX && !_ELPP_OS_WINDOWS && _ELPP_CYGWIN)
#   undef _ELPP_OS_UNIX
#   undef _ELPP_OS_LINUX
#   define _ELPP_OS_UNIX 1
#   define _ELPP_OS_LINUX 1
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Internal Assertions and errors
// Depending on users definition of several macros, we define assertion macros used internally to notify developer
// of any internal failure.
// If developer wants to disable internal assertion they will need to define of of following macros
//    _ELPP_DISABLE_ASSERT                  Disables assertion
//    _ELPP_STOP_ON_FIRST_ASSERTION         Stops execution on first assert failure
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if (!defined(_ELPP_DISABLE_ASSERT))
#   if (defined(_ELPP_STOP_ON_FIRST_ASSERTION))
#      define ELPP_ASSERT(expr, msg) if (!(expr)) { \
          std::cerr << "EASYLOGGING++ ASSERTION FAILED (LINE: " << __LINE__ << ") [" #expr << "] WITH MESSAGE \"" \
              << msg << "\"" << std::endl; exit(1); }
#   else
#      define ELPP_ASSERT(expr, msg) if (!(expr)) { std::cerr << "ASSERTION FAILURE FROM EASYLOGGING++ (LINE: " <<\
        __LINE__ << ") [" #expr << "] WITH MESSAGE \"" << msg << "\"" << std::endl; }
#   endif // (defined(_ELPP_STOP_ON_FIRST_ASSERTION))
#else
#   define ELPP_ASSERT(x, y)
#endif // (!defined(_ELPP_DISABLE_ASSERT))
#if (defined(_ELPP_ENABLE_ERRORS))
#   define ELPP_INTERNAL_ERROR(msg, pe) std::cerr << "ERROR FROM EASYLOGGING++ (LINE: " << __LINE__ << ") " << \
    msg << std::endl; if (pe) { std::cerr << "    "; perror(""); }
#else
#   define ELPP_INTERNAL_ERROR(msg, pe)
#endif // (defined(_ELPP_ENABLE_ERRORS))
#if (defined(_ELPP_ENABLE_INFO))
#   define ELPP_INTERNAL_INFO(msg) std::cout << msg << std::endl;
#else
#   define ELPP_INTERNAL_INFO(msg)
#endif // (defined(_ELPP_ENABLE_INFO))
#if defined(_ELPP_STACKTRACE_ON_CRASH)
#   if (_ELPP_COMPILER_GCC && !_ELPP_MINGW)
#      define _ELPP_STACKTRACE 1
#   else
#      if _ELPP_COMPILER_MSVC
#         pragma message("Stack trace not available for this compiler")
#      else
#         warning "Stack trace not available for this compiler";
#      endif // _ELPP_COMPILER_MSVC
#   endif // _ELPP_COMPILER_GCC
#endif // (defined(_ELPP_STACKTRACE_ON_CRASH))
//////////////////////////////
// Miscellaneous macros
/////////////////////////////
#define _ELPP_UNUSED(x) (void)x;
#if _ELPP_OS_UNIX
// Log file permissions for unix-based systems
#   define _ELPP_LOG_PERMS S_IRUSR | S_IWUSR | S_IXUSR | S_IWGRP | S_IRGRP | S_IXGRP | S_IWOTH | S_IXOTH
#endif // _ELPP_OS_UNIX
////////////////////////////////////////////////////////////////////////////////////////////////////
// Some special functions that are special for VC++
// This is to prevent CRT security warnings and to override deprecated methods but at the same time
// MinGW does not support some functions, so we need to make sure that proper function is used.
////////////////////////////////////////////////////////////////////////////////////////////////////
#undef SPRINTF
#undef STRTOK
#if _ELPP_CRT_DBG_WARNINGS
#   define SPRINTF sprintf_s
#   define STRTOK(a,b,c) strtok_s(a,b,c)
#else
#   define SPRINTF sprintf
#   define STRTOK(a,b,c) strtok(a,b)
#endif
////////////////////////////////////////////////
// Some compiler specific support evaluations
////////////////////////////////////////////////
#if _ELPP_MINGW || _ELPP_COMPILER_CLANG
#   define _ELPP_USE_STD_THREADING 0
#else
#   define _ELPP_USE_STD_THREADING 1
#endif // _ELPP_MINGW || _ELPP_COMPILER_CLANG
#undef FINAL
#if _ELPP_COMPILER_INTEL || (_ELPP_GCC_VERSION < 40702)
#   define FINAL
#else
#   define FINAL final
#endif // _ELPP_COMPILER_INTEL || (_ELPP_GCC_VERSION < 40702)
#if defined(_ELPP_THREAD_SAFE)
#   define _ELPP_THREADING_ENABLED 1
#endif // defined(_ELPP_THREAD_SAFE)
//////////////////////////////////////////////////////////////////////
// Function macro _ELPP_FUNC
// This macro is used to find log source function
//////////////////////////////////////////////////////////////////////
#undef _ELPP_FUNC
#if defined(_MSC_VER) && (_MSC_VER >= 1020) // Visual C++
#   define _ELPP_FUNC __FUNCSIG__
#elif (defined(__GNUC__) && (__GNUC__ >= 2)) // GCC
#   define _ELPP_FUNC __PRETTY_FUNCTION__
#elif (defined(__INTEL_COMPILER)) // Intel C++
#   define _ELPP_FUNC __PRETTY_FUNCTION__
#elif defined(__clang__) && (__clang__ == 1) // Clang++
#   define _ELPP_FUNC __PRETTY_FUNCTION__
#else
#   if defined(__func__)
#      define _ELPP_FUNC __func__
#   else
#      define _ELPP_FUNC ""
#   endif // defined(__func__)
#endif // defined(_MSC_VER) && (_MSC_VER >= 1020)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Logging Enable/Disable macros
// This defines whether or not certain or all logs are enabled. We define macros for internal use based on
// what developer has defined.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if (defined(_ELPP_DISABLE_LOGS))
#   define _ELPP_LOGGING_ENABLED 0
#else
#   define _ELPP_LOGGING_ENABLED 1
#endif // (defined(_ELPP_DISABLE_LOGS))
#if (!defined(_ELPP_DISABLE_DEBUG_LOGS) && (_ELPP_LOGGING_ENABLED) && ((defined(_DEBUG)) || (!defined(NDEBUG))))
#   define _ELPP_DEBUG_LOG 1
#else
#   define _ELPP_DEBUG_LOG 0
#endif // (!defined(_ELPP_DISABLE_DEBUG_LOGS) && (_ELPP_LOGGING_ENABLED) && ((defined(_DEBUG)) || (!defined(NDEBUG))))
#if (!defined(_ELPP_DISABLE_INFO_LOGS) && (_ELPP_LOGGING_ENABLED))
#   define _ELPP_INFO_LOG 1
#else
#   define _ELPP_INFO_LOG 0
#endif // (!defined(_ELPP_DISABLE_INFO_LOGS) && (_ELPP_LOGGING_ENABLED))
#if (!defined(_ELPP_DISABLE_WARNING_LOGS) && (_ELPP_LOGGING_ENABLED))
#   define _ELPP_WARNING_LOG 1
#else
#   define _ELPP_WARNING_LOG 0
#endif // (!defined(_ELPP_DISABLE_WARNING_LOGS) && (_ELPP_LOGGING_ENABLED))
#if (!defined(_ELPP_DISABLE_ERROR_LOGS) && (_ELPP_LOGGING_ENABLED))
#   define _ELPP_ERROR_LOG 1
#else
#   define _ELPP_ERROR_LOG 0
#endif // (!defined(_ELPP_DISABLE_ERROR_LOGS) && (_ELPP_LOGGING_ENABLED))
#if (!defined(_ELPP_DISABLE_FATAL_LOGS) && (_ELPP_LOGGING_ENABLED))
#   define _ELPP_FATAL_LOG 1
#else
#   define _ELPP_FATAL_LOG 0
#endif // (!defined(_ELPP_DISABLE_FATAL_LOGS) && (_ELPP_LOGGING_ENABLED))
#if (!defined(_ELPP_DISABLE_TRACE_LOGS) && (_ELPP_LOGGING_ENABLED))
#   define _ELPP_TRACE_LOG 1
#else
#   define _ELPP_TRACE_LOG 0
#endif // (!defined(_ELPP_DISABLE_TRACE_LOGS) && (_ELPP_LOGGING_ENABLED))
#if (!defined(_ELPP_DISABLE_VERBOSE_LOGS) && (_ELPP_LOGGING_ENABLED))
#   define _ELPP_VERBOSE_LOG 1
#else
#   define _ELPP_VERBOSE_LOG 0
#endif // (!defined(_ELPP_DISABLE_VERBOSE_LOGS) && (_ELPP_LOGGING_ENABLED))
///////////////////////////////////////////////////////////////////////
// Now let user know that we only support C++0x/C++11 applications
//////////////////////////////////////////////////////////////////////
#if (!(_ELPP_CXX0X || _ELPP_CXX11))
#   error "Easylogging++ 9.0+ is only compatible with C++0x (or higher) compliant compiler"
#endif // (!(_ELPP_CXX0X || _ELPP_CXX11))
///////////////////////////////////////////////////////////////////////////
// Headers inclusion
// We include in following order:
//  * C-headers
//  * OS specific headers
//  * C++ Headers
//  * C++11 Headers
//  * Headers supported by STL Logging
//  * Headers supported by third party libraries logging e.g, Qt, boost etc
///////////////////////////////////////////////////////////////////////////
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <cwchar>
#include <csignal>
#if _ELPP_STACKTRACE
#   include <cxxabi.h>
#   include <execinfo.h>
#endif // _ELPP_STACKTRACE
#if _ELPP_OS_ANDROID
#   include <sys/system_properties.h>
#endif // _ELPP_OS_ANDROID
#if _ELPP_OS_UNIX
#   include <sys/stat.h>
#   include <sys/time.h>
#elif _ELPP_OS_WINDOWS
#   include <direct.h>
#   include <Windows.h>
#endif // _ELPP_OS_UNIX
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#if _ELPP_THREADING_ENABLED
#   if _ELPP_USE_STD_THREADING
#      include <mutex>
#      include <thread>
#   else
#      if _ELPP_OS_UNIX
#         include <pthread.h>
#      endif // _ELPP_OS_UNIX
#   endif // _ELPP_USE_STD_THREADING
#endif // _ELPP_THREADING_ENABLED
#if defined(_ELPP_STL_LOGGING)
// For logging STL based templates
#   include <list>
#   include <queue>
#   include <deque>
#   include <set>
#   include <bitset>
#   include <stack>
#   if defined(_ELPP_LOG_STD_ARRAY)
#      include <array>
#   endif // defined(_ELPP_LOG_STD_ARRAY)
#   if defined(_ELPP_LOG_UNORDERED_MAP)
#      include <unordered_map>
#   endif // defined(_ELPP_LOG_UNORDERED_MAP)
#   if defined(_ELPP_LOG_UNORDERED_SET)
#      include <unordered_set>
#   endif // defined(_ELPP_UNORDERED_SET)
#endif // defined(_ELPP_STL_LOGGING)
#if defined(_ELPP_QT_LOGGING)
// For logging Qt based classes & templates
#   include <QString>
#   include <QByteArray>
#   include <QVector>
#   include <QList>
#   include <QPair>
#   include <QMap>
#   include <QQueue>
#   include <QSet>
#   include <QLinkedList>
#   include <QHash>
#   include <QMultiHash>
#   include <QStack>
#endif // defined(_ELPP_QT_LOGGING)
#if defined(_ELPP_BOOST_LOGGING)
// For logging boost based classes & templates
#   include <boost/container/vector.hpp>
#   include <boost/container/stable_vector.hpp>
#   include <boost/container/list.hpp>
#   include <boost/container/deque.hpp>
#   include <boost/container/map.hpp>
#   include <boost/container/flat_map.hpp>
#   include <boost/container/set.hpp>
#   include <boost/container/flat_set.hpp>
#endif // defined(_ELPP_BOOST_LOGGING)
#if defined(_ELPP_WXWIDGETS_LOGGING)
// For logging wxWidgets based classes & templates
#   include <wx/vector.h>
#endif // defined(_ELPP_WXWIDGETS_LOGGING)
/// @brief Easylogging++ entry namespace. Classes present <b>directly</b> in this namespace can be used by
/// developer. Any other class is for internal use only.
namespace el {
/// @brief Namespace containing base/internal functionality used by easylogging++
namespace base {

/// @brief Internal helper class that prevent copy constructor for class
///
/// @detail When using this class simply inherit it privately
class NoCopy {
protected:
    NoCopy(void) {}
private:
    NoCopy(const NoCopy&);
    NoCopy& operator=(const NoCopy&);
};

/// @brief Internal helper class that makes all default constructors private.
///
/// @detail This prevents initializing class making it static unless an explicit constructor is declared.
/// When using this class simply inherit it privately
class StaticClass {
private:
    StaticClass(void);
    StaticClass(const StaticClass&);
    StaticClass& operator=(const StaticClass&);
};
} // namespace internal
/// @brief Represents enumeration for severity level used to determine level of logging
///
/// @detail Easylogging++ has different concept of level. Developers may disable or enable any level regardless of
/// what the severity is
/// @see el::LevelHelper
enum class Level : unsigned short {
        /// @brief Generic level that represents all the levels. Useful when setting global configuration for all levels
        Global = 1,
        /// @brief Informational events most useful for developers to debug application
        Debug = 2,
        /// @brief Mainly useful to represent current progress of application
        Info = 4,
        /// @brief Useful when application has potentially harmful situtaions
        Warning = 8,
        /// @brief Information representing errors in application but application will keep running
        Error = 16,
        /// @brief Severe error information that will presumably abort application
        Fatal = 32,
        /// @brief Information that can be highly useful and vary with verbose logging level.
        Verbose = 64,
        /// @brief Information that can be useful to back-trace certain events - mostly useful than debug logs.
        Trace = 128,
        /// @brief Represents unknown level
        Unknown = 1010
};
/// @brief Static class that contains helper functions for el::Level
class LevelHelper: private base::StaticClass {
public:
    /// @brief Represents minimum valid level. Useful when iterating through enum.
    static const unsigned short kMinValid = static_cast<unsigned short>(Level::Debug);

    /// @brief Represents maximum valid level. This is used internally and you should not need it.
    static const unsigned short kMaxValid = static_cast<unsigned short>(Level::Trace);

    /// @brief Casts level to int, useful for iterating through enum.
    static unsigned short castToInt(const Level& level) {
        return static_cast<unsigned short>(level);
    }

    /// @brief Casts int(ushort) to level, useful for iterating through enum.
    static Level castFromInt(unsigned short l) {
        return static_cast<Level>(l);
    }

    /// @brief Converts level to associated const char*
    /// @return Upper case string based level.
    static const char* convertToString(const Level& level) {
        // Do not use switch over strongly typed enums because Intel C++ compilers dont support them yet.
        if (level == Level::Global)
            return "GLOBAL";
        if (level == Level::Debug)
            return "DEBUG";
        if (level == Level::Info)
            return "INFO";
        if (level == Level::Warning)
            return "WARNING";
        if (level == Level::Error)
            return "ERROR";
        if (level == Level::Fatal)
            return "FATAL";
        if (level == Level::Verbose)
            return "VERBOSE";
        if (level == Level::Trace)
            return "TRACE";
        return "UNKNOWN";
    }

    /// @brief Converts from levelStr to Level
    /// @param levelStr Upper case string based level.
    ///        Lower case is also valid but providing upper case is recommended.
    static Level convertFromString(const char* levelStr) {
        if ((strcmp(levelStr, "GLOBAL") == 0) || (strcmp(levelStr, "global") == 0))
            return Level::Global;
        if ((strcmp(levelStr, "DEBUG") == 0) || (strcmp(levelStr, "debug") == 0))
            return Level::Debug;
        if ((strcmp(levelStr, "INFO") == 0) || (strcmp(levelStr, "info") == 0))
            return Level::Info;
        if ((strcmp(levelStr, "WARNING") == 0) || (strcmp(levelStr, "warning") == 0))
            return Level::Warning;
        if ((strcmp(levelStr, "ERROR") == 0) || (strcmp(levelStr, "error") == 0))
            return Level::Error;
        if ((strcmp(levelStr, "FATAL") == 0) || (strcmp(levelStr, "fatal") == 0))
            return Level::Fatal;
        if ((strcmp(levelStr, "VERBOSE") == 0) || (strcmp(levelStr, "verbose") == 0))
            return Level::Verbose;
        if ((strcmp(levelStr, "TRACE") == 0) || (strcmp(levelStr, "trace") == 0))
            return Level::Trace;
        return Level::Unknown;
    }

    /// @brief Applies specified lambda to each level starting from startIndex
    /// @param startIndex initial value to start the iteration from. This is passed by reference and is incremented (left-shifted)
    ///        so this can be used inside lambda function as well to represent current level.
    /// @param lambdaFn Lambda function having no param with bool return type to apply with each level. See more details below
    ///
    /// @detail The bool return type of lambda expression represents whether or not to skip rest of levels. Consider following example;
    /// <pre>unsigned short currLevel = LevelHelper::kMinValid;
    ///    bool result = false;
    ///    forEachLevel(min, [&]() -> bool {
    ///       if (hasConfiguration(currLevel)) {
    ///          result = true;
    ///       }
    ///       return result;
    ///    });
    ///    return result;</pre>
    /// Code above is very good example of possible usages, returns inside lambda tells function not to exit/break iteration yet. Meaning
    /// if result is true the expression will return right away and result from main function will be return as soon as second <code>return result;</code>
    /// is hit.
    static void forEachLevel(unsigned short& startIndex, const std::function<bool(void)>& lambdaFn) {
        unsigned short lIndexMax = LevelHelper::kMaxValid;
        do {
            if (lambdaFn())
                break;
            startIndex = startIndex << 1;
        } while (startIndex <= lIndexMax);
    }
};

/// @brief Represents enumeration of ConfigurationType used to configure or access certain aspect
/// of logging
///
/// @detail NOTE: All the configurations for corresponding level also depend on loggers. You can use one
/// configuration for one logger and different for other logger.
/// @see el::ConfigurationTypeHelper
enum class ConfigurationType : unsigned short {
    /// @brief Determines whether or not corresponding level and logger of logging is enabled
    /// You may disable all logs by using el::Level::Global
    Enabled = 1,
    /// @brief Whether or not to write corresponding log to log file
    ToFile = 2,
    /// @brief Whether or not to write corresponding level and logger log to standard output.
    /// By standard output meaning termnal, command prompt etc
    ToStandardOutput = 4,
    /// @brief Determines format of logging corresponding level and logger.
    Format = 8,
    /// @brief Determines log file (full path) to write logs to for correponding level and logger
    Filename = 16,
    /// @brief Specifies milliseconds width. Width can be within range (1-6)
    MillisecondsWidth = 32,
    /// @brief Determines whether or not performance tracking is enabled.
    ///
    /// @detail This does not depend on logger or level. Performance tracking always uses 'performance' logger
    PerformanceTracking = 64,
    /// @brief Specifies log file max size.
    ///
    /// @detail If file size of corresponding log file (for corresponding level) is >= specified size, log file will be truncated
    /// and re-initiated.
    MaxLogFileSize = 128,
    /// @brief Represents unknown configuration
    Unknown = 1010
};

/// @brief Static class that contains conversion helper functions for el::ConfigurationType
class ConfigurationTypeHelper: private base::StaticClass {
public:

    /// @brief Represents minimum valid configuration type. Useful when iterating through enum.
    static const unsigned short kMinValid = static_cast<unsigned short>(ConfigurationType::Enabled);

    /// @brief Represents maximum valid configuration type. This is used internally and you should not need it.
    static const unsigned short kMaxValid = static_cast<unsigned short>(ConfigurationType::MaxLogFileSize);

    /// @brief Casts configuration type to int, useful for iterating through enum.
    static unsigned short castToInt(const ConfigurationType& configurationType) {
        return static_cast<unsigned short>(configurationType);
    }

    /// @brief Casts int(ushort) to configurationt type, useful for iterating through enum.
    static ConfigurationType castFromInt(unsigned short c) {
        return static_cast<ConfigurationType>(c);
    }

    /// @brief Converts configuration type to associated const char*
    /// @returns Upper case string based configuration type.
    static const char* convertToString(const ConfigurationType& configurationType) {
        // Do not use switch over strongly typed enums because Intel C++ compilers dont support them yet.
        if (configurationType == ConfigurationType::Enabled)
            return "ENABLED";
        if (configurationType == ConfigurationType::Filename)
            return "FILENAME";
        if (configurationType == ConfigurationType::Format)
            return "FORMAT";
        if (configurationType == ConfigurationType::ToFile)
            return "TO_FILE";
        if (configurationType == ConfigurationType::ToStandardOutput)
            return "TO_STANDARD_OUTPUT";
        if (configurationType == ConfigurationType::MillisecondsWidth)
            return "MILLISECONDS_WIDTH";
        if (configurationType == ConfigurationType::PerformanceTracking)
            return "PERFORMANCE_TRACKING";
        if (configurationType == ConfigurationType::MaxLogFileSize)
            return "MAX_LOG_FILE_SIZE";
        return "UNKNOWN";
    }

    /// @brief Converts from configStr to ConfigurationType
    /// @param configStr Upper case string based configuration type.
    ///        Lower case is also valid but providing upper case is recommended.
    static ConfigurationType convertFromString(const char* configStr) {
        if ((strcmp(configStr, "ENABLED") == 0) || (strcmp(configStr, "enabled") == 0))
            return ConfigurationType::Enabled;
        if ((strcmp(configStr, "TO_FILE") == 0) || (strcmp(configStr, "to_file") == 0))
            return ConfigurationType::ToFile;
        if ((strcmp(configStr, "TO_STANDARD_OUTPUT") == 0) || (strcmp(configStr, "to_standard_output") == 0))
            return ConfigurationType::ToStandardOutput;
        if ((strcmp(configStr, "FORMAT") == 0) || (strcmp(configStr, "format") == 0))
            return ConfigurationType::Format;
        if ((strcmp(configStr, "FILENAME") == 0) || (strcmp(configStr, "filename") == 0))
            return ConfigurationType::Filename;
        if ((strcmp(configStr, "MILLISECONDS_WIDTH") == 0) || (strcmp(configStr, "milliseconds_width") == 0))
            return ConfigurationType::MillisecondsWidth;
        if ((strcmp(configStr, "PERFORMANCE_TRACKING") == 0) || (strcmp(configStr, "performance_tracking") == 0))
            return ConfigurationType::PerformanceTracking;
        if ((strcmp(configStr, "MAX_LOG_FILE_SIZE") == 0) || (strcmp(configStr, "max_log_file_size") == 0))
            return ConfigurationType::MaxLogFileSize;
        return ConfigurationType::Unknown;
    }

    /// @brief Applies specified lambda to each configuration type starting from startIndex
    /// @param startIndex initial value to start the iteration from. This is passed by reference and is incremented (left-shifted)
    ///        so this can be used inside lambda function as well to represent current configuration type.
    /// @param lambdaFn Lambda function having no param with bool return type to apply with each configuration type. This bool represent
    ///        whether or not to continue iterating through configurations. For details please see
    ///        LevelHelper::forEachLevel
    static void forEachConfigType(unsigned short& startIndex, const std::function<bool(void)>& lambdaFn) {
        unsigned short cIndexMax = ConfigurationTypeHelper::kMaxValid;
        do {
            if (lambdaFn())
                break;
            startIndex = startIndex << 1;
        } while (startIndex <= cIndexMax);
    }
};

/// @brief Flags used while writing logs. This flags are set by user
///
/// @see el::Helpers
enum class LoggingFlag : unsigned short {
    /// @brief Makes sure we have new line for each container log entry
    NewLineForContainer = 1,

    /// @brief Makes sure if -vmodule is used and does not specifies a module, then verbose
    /// logging is allowed via that module.
    ///
    /// @detail Say param was -vmodule=main*=3 and a verbose log is being written from a file
    /// called something.cpp then if this flag is enabled, log will be written otherwise
    /// it will be disallowed.
    AllowVerboseIfModuleNotSpecified = 2,

    /// @brief When handling crashes by default, detailed crash reason will be logged as well
    LogDetailedCrashReason = 4
};
namespace base {
///
/// @brief Namespace containing constants used internally. This is in seperate namespace to avoid confusions.
///
namespace consts {
    // Level log values - These are values that are replaced in place of %level format specifier
    static const char* kInfoLevelLogValue     =   "INFO ";
    static const char* kDebugLevelLogValue    =   "DEBUG";
    static const char* kWarningLevelLogValue  =   "WARN ";
    static const char* kErrorLevelLogValue    =   "ERROR";
    static const char* kFatalLevelLogValue    =   "FATAL";
    static const char* kVerboseLevelLogValue  =   "VER";
    static const char* kTraceLevelLogValue    =   "TRACE";

    // Format specifiers - These are used to define log format
    static const char* kAppNameFormatSpecifier          =      "%app";
    static const char* kLoggerIdFormatSpecifier         =      "%logger";
    static const char* kThreadIdFormatSpecifier         =      "%thread";
    static const char* kSeverityLevelFormatSpecifier    =      "%level";
    static const char* kDateTimeFormatSpecifier         =      "%datetime";
    static const char* kLogFileFormatSpecifier          =      "%file";
    static const char* kLogLineFormatSpecifier          =      "%line";
    static const char* kLogLocationFormatSpecifier      =      "%loc";
    static const char* kLogFunctionFormatSpecifier      =      "%func";
    static const char* kCurrentUserFormatSpecifier      =      "%user";
    static const char* kCurrentHostFormatSpecifier      =      "%host";
    static const char* kMessageFormatSpecifier          =      "%log";
    static const char* kVerboseLevelFormatSpecifier     =      "%vlevel";

    // Date/time
    static const char* kDays[7]                         =      { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    static const char* kDaysAbbrev[7]                   =      { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
    static const char* kMonths[12]                      =      { "January", "February", "March", "April", "May", "June", "July", "August",
            "September", "October", "November", "December" };
    static const char* kMonthsAbbrev[12]                =      { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    static const char* kDefaultDateTimeFormat           =      "%d/%M/%Y %h:%m:%s,%g";
    static const int kYearBase                          =      1900;
    static const char* kAm                              =      "AM";
    static const char* kPm                              =      "PM";

    // Miscellaneous constants
    static const char* kDefaultLoggerId                        =      "default";
    static const char* kPerformanceLoggerId                    =      "performance";
    static const char* kInternalHelperLoggerId                 =      "el_internal_helper_logger";
    static const char* kNullPointer                            =      "nullptr";
    static const char  kFormatEscapeChar                       =      '%';
    static const unsigned short kMaxLogPerContainer            =      100;
    static const unsigned int kMaxLogPerCounter                =      100000;
    static const unsigned int  kDefaultMillisecondsOffset      =      1000;
    static const short kMaxVerboseLevel                        =      9;
    static const char* kUnknownUser                            =      "user";
    static const char* kUnknownHost                            =      "unknown-host";
#if defined(_ELPP_DEFAULT_LOG_FILE)
    static const char* kDefaultLogFile                         =      _ELPP_DEFAULT_LOG_FILE;
#else
#   if _ELPP_OS_UNIX
#      if _ELPP_OS_ANDROID
    static const char* kDefaultLogFile                         =      "logs/myeasylog.log";
#      else
    static const char* kDefaultLogFile                         =      "logs/myeasylog.log";
#      endif // _ELPP_OS_ANDROID
#   elif _ELPP_OS_WINDOWS
       static const char* kDefaultLogFile                      =      "logs\\myeasylog.log";
#   endif // _ELPP_OS_UNIX
#endif // defined(_ELPP_DEFAULT_LOG_FILE)

#if _ELPP_OS_WINDOWS
    static const char* kFilePathSeperator                      =      "\\";
#else
    static const char* kFilePathSeperator                      =      "/";
#endif // _ELPP_OS_WINDOWS
    static const char* kValidLoggerIdSymbols                   =      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-._";

    static const char* kConfigurationComment                   =      "##";
    static const char* kConfigurationLevel                     =      "*";
    static const char* kConfigurationLoggerId                  =      "--";

    static const int kMaxTimeFormats                           =      6;
    const struct {
        double value;
        const char* unit;
    } kTimeFormats[kMaxTimeFormats] = {
       { 1000.0f, "mis" },
       { 1000.0f, "ms" },
       { 60.0f, "seconds" },
       { 60.0f, "minutes" },
       { 24.0f, "hours" },
       { 7.0f, "days" }
    };

    static const int kMaxCrashSignals                          =      5;
    const struct {
        int numb;
        const char* name;
        const char* brief;
        const char* detail;
    } kCrashSignals[kMaxCrashSignals] = {
        // NOTE: Do not re-order, if you do please check CrashHandler(bool) constructor and CrashHandler::setHandler(..)
        { SIGABRT, "SIGABRT", "Abnormal termination",
                "Program was abnormally terminated." },
        { SIGFPE, "SIGFPE", "Erroneous arithmetic operation",
                "Arithemetic operation issue such as division by zero or operation resulting in overflow." },
        { SIGILL, "SIGILL", "Illegal instruction",
                "Generally due to a corruption in the code or to an attempt to execute data."},
        { SIGSEGV, "SIGSEGV", "Invalid access to memory",
                "Program is trying to read an invalid (unallocated, deleted or corrupted) or inaccessible memory." },
        { SIGINT, "SIGINT", "Interactive attention signal",
                 "Interruption generated (generally) by user or operating system." },
    };
} // namespace consts
typedef std::function<void(const char*, std::size_t)> PreRollOutHandler;
static inline void defaultPreRollOutHandler(const char*, std::size_t) {}
/// @brief Enum to represent timestamp unit
enum class TimestampUnit : unsigned short {
    Microsecond = 0, Millisecond = 1, Second = 2, Minute = 3, Hour = 4, Day = 5
};
/// @brief Format flags used to determine specifiers that are active for performance improvements.
enum class FormatFlags : unsigned short {
    DateTime = 2, LoggerId = 4, File = 8, Line = 16, Location = 32, Function = 64,
    User = 128, Host = 256, LogMessage = 512, VerboseLevel = 1024, AppName = 2048, ThreadId = 4096,
    Level = 8192
};
/// @brief Namespace containing utility functions/static classes used internally
namespace utils {
/// @brief Deletes memory safely
///
/// @detail if this is used whereever we need to delete memory it will always be safe because
/// we will never delete a dangling or wild pointer
/// @param pointer Valid pointer to be deleted
template <typename T>
inline static void safeDelete(T*& pointer) {
    if (pointer == nullptr)
        return;
    delete pointer;
    pointer = nullptr;
}
/// @brief Gets value of const char* but if it is nullptr, a string nullptr is returned
inline static const char* charPtrVal(const char* pointer) {
    return pointer == nullptr ? base::consts::kNullPointer : pointer;
}
/// @brief Bitwise operations for C++11 strong enum class. This casts e into Flag_T and returns value after bitwise operation
/// Use these function as <pre>flag = bitOr<MyEnum>(MyEnum::val1, flag);</pre>
namespace bitwise {
template <typename EnumType>
inline static unsigned short And(EnumType e, unsigned short flag) {
    return static_cast<unsigned short>(flag) & static_cast<unsigned short>(e);
}
template <typename EnumType>
inline static unsigned short Not(EnumType e, unsigned short flag) {
    return static_cast<unsigned short>(flag) & ~(static_cast<unsigned short>(e));
}
template <typename EnumType>
inline static unsigned short Or(EnumType e, unsigned short flag) {
    return static_cast<unsigned short>(flag) | static_cast<unsigned short>(e);
}
} // namespace bitwise
/// @brief Adds flag
template <typename EnumType>
inline static void addFlag(EnumType e, unsigned short& flag) {
    flag = base::utils::bitwise::Or<EnumType>(e, flag);
}
/// @brief Removes flag
template <typename EnumType>
inline static void removeFlag(EnumType e, unsigned short& flag) {
    flag = base::utils::bitwise::Not<EnumType>(e, flag);
}
/// @brief Determines whether flag is set or not
template <typename EnumType>
inline static unsigned short hasFlag(EnumType e, unsigned short flag) {
    return base::utils::bitwise::And<EnumType>(e, flag);
}
} // namespace utils
namespace threading {
#if _ELPP_THREADING_ENABLED
#   if !_ELPP_USE_STD_THREADING
/// @brief A mutex wrapper for compiler that dont yet support std::mutex
class Mutex {
public:
    Mutex(void) {
#   if _ELPP_OS_UNIX
        pthread_mutex_init(&m_underlyingMutex, nullptr);
#   elif _ELPP_OS_WINDOWS
        InitializeCriticalSection(&m_underlyingMutex);
#   endif // _ELPP_OS_UNIX
    }

    virtual ~Mutex(void) {
#   if _ELPP_OS_UNIX
        pthread_mutex_destroy(&m_underlyingMutex);
#   elif _ELPP_OS_WINDOWS
        DeleteCriticalSection(&m_underlyingMutex);
#   endif // _ELPP_OS_UNIX
    }

    inline void lock(void) {
#   if _ELPP_OS_UNIX
        pthread_mutex_lock(&m_underlyingMutex);
#   elif _ELPP_OS_WINDOWS
        EnterCriticalSection(&m_underlyingMutex);
#   endif // _ELPP_OS_UNIX
    }

    inline bool try_lock(void) {
#   if _ELPP_OS_UNIX
        return (pthread_mutex_trylock(&m_underlyingMutex) == 0);
#   elif _ELPP_OS_WINDOWS
        return TryEnterCriticalSection(&m_underlyingMutex);
#   endif // _ELPP_OS_UNIX
    }

    inline void unlock(void) {
#   if _ELPP_OS_UNIX
        pthread_mutex_unlock(&m_underlyingMutex);
#   elif _ELPP_OS_WINDOWS
        LeaveCriticalSection(&m_underlyingMutex);
#   endif // _ELPP_OS_UNIX
    }
private:
#   if _ELPP_OS_UNIX
    pthread_mutex_t m_underlyingMutex;
#   elif _ELPP_OS_WINDOWS
    CRITICAL_SECTION m_underlyingMutex;
#   endif // _ELPP_OS_UNIX
};
/// @brief Scoped lock for compiler that dont yet support std::lock_guard
template <typename M>
class ScopedLock : private base::NoCopy {
public:
    explicit ScopedLock(M& mutex) {
        m_mutex = &mutex;
        m_mutex->lock();
    }

    virtual ~ScopedLock(void) {
        m_mutex->unlock();
    }
private:
    M* m_mutex;
    ScopedLock(void);
};
/// @brief Gets ID of currently running threading in windows systems. On unix, nothing is returned.
static inline const char* getCurrentThreadId(void) {
    std::stringstream ss;
#      if (_ELPP_OS_WINDOWS)
    ss << GetCurrentThreadId();
#      endif // (_ELPP_OS_WINDOWS)
    return ss.str().c_str();
}
typedef base::threading::Mutex mutex;
typedef base::threading::ScopedLock<base::threading::Mutex> lock_guard;
#   else
/// @brief Gets ID of currently running threading using std::this_thread::get_id()
static inline const char* getCurrentThreadId(void) {
    std::stringstream ss;
    ss << std::this_thread::get_id();
    return ss.str().c_str();
}
typedef std::mutex mutex;
typedef std::lock_guard<std::mutex> lock_guard;
#   endif // !_ELPP_USE_STD_THREADING
#else
/// @brief Mutex wrapper used when multi-threading is disabled.
class NoMutex {
public:
    NoMutex(void) {}
    inline void lock(void) {}
    inline bool try_lock(void) { return true; }
    inline void unlock(void) {}
};
/// @brief Lock guard wrapper used when multi-threading is disabled.
template <typename Mutex>
class NoScopedLock : private base::NoCopy {
public:
    explicit NoScopedLock(Mutex&) {
    }
    virtual ~NoScopedLock(void) {
    }
private:
    NoScopedLock(void);
};
static inline const char* getCurrentThreadId(void) {
    return "";
}
typedef base::threading::NoMutex mutex;
typedef base::threading::NoScopedLock<base::threading::NoMutex> lock_guard;
#endif // _ELPP_THREADING_ENABLED
/// @brief Base of thread safe class, this class is inheritable-only
class ThreadSafe {
public:
    virtual inline void lock(void) FINAL {
        m_mutex.lock();
    }
    virtual inline void unlock(void) FINAL {
        m_mutex.unlock();
    }
    virtual inline base::threading::mutex& mutex(void) FINAL {
        return m_mutex;
    }
protected:
    ThreadSafe(void) {}
    virtual ~ThreadSafe(void) {}
private:
    base::threading::mutex m_mutex;
};
} // namespace threading
namespace utils {
class File : private base::StaticClass {
public:
    /// @brief Creates new out file stream for specified filename.
    /// @return Newly created filestream or nullptr
    static std::fstream* newFileStream(const std::string& filename) {
        std::fstream *fs = new std::fstream(filename.c_str(), std::fstream::out | std::fstream::app);
        if (fs->is_open()) {
            fs->flush();
        } else {
            base::utils::safeDelete(fs);
            ELPP_INTERNAL_ERROR("Bad file [" << filename << "]", true);
        }
        return fs;
    }
    /// @brief Gets size of file provided in stream
    ///
    /// @detail It is expected to have stream already opened.
    static std::size_t getSizeOfFile(std::fstream* fs) {
        if (!fs) {
            return 0;
        }
        std::streampos currPos = fs->tellg();
        fs->seekg(0, fs->end);
        std::size_t size = static_cast<std::size_t>(fs->tellg());
        fs->seekg(currPos);
        return size;
    }
    /// @brief Determines whether or not provided path exist in current file system
    /// @param path Path to check
    static inline bool pathExists(const char* path, bool considerFile = false) {
        if (path == nullptr) {
            return false;
        }
#if _ELPP_OS_UNIX
        _ELPP_UNUSED(considerFile);
        struct stat st;
        return (stat(path, &st) == 0);
#elif _ELPP_OS_WINDOWS
        DWORD fileType = GetFileAttributesA(path);
        if (fileType == INVALID_FILE_ATTRIBUTES) {
            return false;
        }
        return considerFile ? true : ((fileType & FILE_ATTRIBUTE_DIRECTORY) == 0 ? false : true);
#endif // _ELPP_OS_UNIX
    }

    /// @brief Creates specified path on file system
    /// @param path Path to create.
    static bool createPath(const std::string& path) {
        if (path.empty()) {
            return false;
        }
        if (base::utils::File::pathExists(path.c_str())) {
            return true;
        }
        int status = -1;

        char* currPath = const_cast<char*>(path.c_str());
        std::string builtPath = std::string();
#if _ELPP_OS_UNIX
        if (path[0] == '/') {
            builtPath = "/";
        }
        currPath = STRTOK(currPath, base::consts::kFilePathSeperator, 0);
#elif _ELPP_OS_WINDOWS
        // Use secure functions API
        char* nextTok_;
        currPath = STRTOK(currPath, base::consts::kFilePathSeperator, &nextTok_);
#endif // _ELPP_OS_UNIX
        while (currPath != nullptr) {
            builtPath.append(currPath);
            builtPath.append(base::consts::kFilePathSeperator);
#if _ELPP_OS_UNIX
            status = mkdir(builtPath.c_str(), _ELPP_LOG_PERMS);
            currPath = STRTOK(nullptr, base::consts::kFilePathSeperator, 0);
#elif _ELPP_OS_WINDOWS
            status = _mkdir(builtPath.c_str());
            currPath = STRTOK(nullptr, base::consts::kFilePathSeperator, &nextTok_);
#endif // _ELPP_OS_UNIX
        }
        if (status == -1) {
            ELPP_INTERNAL_ERROR("Error while creating path [" << path << "]", true);
            return false;
        }
        return true;
    }
    /// @brief Extracts path of filename with leading slash
    /// @param fullPath Full path to filename
    /// @param seperator Path delimiter, for unix it is / for win it is \\, by default value from
    ///        constant is used
    /// @return String copy
    static std::string extractPathFromFilename(const std::string& fullPath,
            const char* seperator = base::consts::kFilePathSeperator) {
        if ((fullPath == "") || (fullPath.find(seperator) == std::string::npos)) {
            return fullPath;
        }
        std::size_t lastSlashAt = fullPath.find_last_of(seperator);
        if (lastSlashAt == 0) {
            return std::string(seperator);
        }
        return fullPath.substr(0, lastSlashAt + 1);
    }
};
/// @brief String utilities helper class used internally. You should not use it.
class Str : private base::StaticClass {
public:
    /// @brief Checks if character is digit. Dont use libc implementation of it to prevent locale issues.
    static inline bool isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    /// @brief Matches wildcards, '*' and '?' only supported.
    static inline bool wildCardMatch(const char* str, const char* pattern) {
        while (*pattern) {
            switch (*pattern) {
            case '?':
                if (!*str)
                    return false;
                ++str;
                ++pattern;
                break;
            case '*':
                if (wildCardMatch(str, pattern + 1))
                    return true;
                if (*str && wildCardMatch(str + 1, pattern))
                    return true;
                return false;
                break;
            default:
                if (*str++ != *pattern++)
                    return false;
                break;
            }
        }
        return !*str && !*pattern;
    }

    /// @brief Trims string from start
    /// @param [in,out] str String to trim
    static inline std::string& ltrim(std::string& str) {
        str.erase(str.begin(), std::find_if(str.begin(), str.end(), std::not1(std::ptr_fun<int, int>(&std::isspace))));
        return str;
    }

    /// @brief Trim string from end
    /// @param [in,out] str String to trim
    static inline std::string& rtrim(std::string& str) {
        str.erase(std::find_if(str.rbegin(), str.rend(), std::not1(std::ptr_fun<int, int>(&std::isspace))).base(), str.end());
        return str;
    }

    /// @brief Trims string from left and right
    /// @param [in,out] str String to trim
    static inline std::string& trim(std::string& str) {
        return ltrim(rtrim(str));
    }

    /// @brief Determines whether or not str starts with specified string
    /// @param str String to check
    /// @param start String to check against
    /// @return Returns true if starts with specified string, false otherwise
    static inline bool startsWith(const std::string& str, const std::string& start) {
        return (str.length() >= start.length()) && (str.compare(0, start.length(), start) == 0);
    }

    /// @brief Determines whether or not str ends with specified string
    /// @param str String to check
    /// @param end String to check against
    /// @return Returns true if ends with specified string, false otherwise
    static inline bool endsWith(const std::string& str, const std::string& end) {
        return (str.length() >= end.length()) && (str.compare(str.length() - end.length(), end.length(), end) == 0);
    }

    /// @brief Replaces all instances of replaceWhat with 'replaceWith'. Original variable is changed for performance.
    /// @param [in,out] str String to replace from
    /// @param replaceWhat Character to replace
    /// @param replaceWith Character to replace with
    /// @return Modified version of str
    static inline std::string& replaceAll(std::string& str, char replaceWhat, char replaceWith) {
        std::replace(str.begin(), str.end(), replaceWhat, replaceWith);
        return str;
    }

    /// @brief Replaces all instances of 'replaceWhat' with 'replaceWith'. (String version) Replaces in place
    /// @param str String to replace from
    /// @param replaceWhat Character to replace
    /// @param replaceWith Character to replace with
    /// @return Modified (original) str
    static inline std::string& replaceAll(std::string& str, const std::string& replaceWhat, const std::string& replaceWith) {
        if (replaceWhat == replaceWith)
            return str;
        std::size_t foundAt = std::string::npos;
        while ((foundAt = str.find(replaceWhat)) != std::string::npos) {
            str.replace(foundAt, replaceWhat.length(), replaceWith);
        }
        return str;
    }

    /// @brief Replaces first occurance of 'replaceWhat' with 'replaceWith' and ignores escaped string
    static void replaceFirstWithEscape(std::string& str, const std::string& replaceWhat, const std::string& replaceWith) {
        std::size_t foundAt = std::string::npos;
        while ((foundAt = str.find(replaceWhat, foundAt + 1)) != std::string::npos){
            if (foundAt > 0 && str[foundAt - 1] == base::consts::kFormatEscapeChar) {
                str.erase(foundAt > 0 ? foundAt - 1 : 0, 1);
                ++foundAt;
            } else {
                str = str.replace(foundAt, replaceWhat.size(), replaceWith);
                return;
            }
        }
    }

    /// @brief Converts string to uppercase
    /// @param str String to convert
    /// @return Uppercase string
    static inline std::string& toUpper(std::string& str) {
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
        return str;
    }

    /// @brief Compares cstring equality - uses strcmp
    static inline bool cStringEq(const char* s1, const char* s2) {
        if (s1 == nullptr && s2 == nullptr) return true;
        if (s1 == nullptr || s2 == nullptr) return false;
        return strcmp(s1, s2) == 0;
    }

    /// @brief Compares cstring equality (case-insensitive) - uses toupper(char)
    /// Dont use strcasecmp because of CRT (VC++)
    static bool cStringCaseEq(const char* s1, const char* s2) {
        if (s1 == nullptr && s2 == nullptr) return true;
        if (s1 == nullptr || s2 == nullptr) return false;
        if (strlen(s1) != strlen(s2)) return false;
        while (*s1 != '\0' && *s2 != '\0') {
            if (::toupper(*s1) != ::toupper(*s2)) return false;
            ++s1;
            ++s2;
        }
        return true;
    }

    /// @brief Returns true if c exist in str
    static inline bool contains(const char* str, char c) {
        for (; *str; ++str) {
            if (*str == c)
                return true;
        }
        return false;
    }
};
/// @brief Operating System helper static class used internally. You should not use it.
class OS : private base::StaticClass {
public:
#if _ELPP_OS_WINDOWS
    /// @brief Gets environment variables for Windows based OS. We are not using <code>getenv(const char*)</code> because of CRT deprecation
    /// @param varname Variable name to get environment variable value for
    /// @return If variable exist the value of it otherwise nullptr
    static const char* getWindowsEnvironmentVariable(const char* varname) {
        const DWORD bufferLen = 50;
        static char buffer[bufferLen];
        if (GetEnvironmentVariableA(varname, buffer, bufferLen)) {
            return buffer;
        }
        return nullptr;
    }
#endif // _ELPP_OS_WINDOWS
#if _ELPP_OS_ANDROID
    /// @brief Reads android property value
    static inline char* getProperty(const char* prop) {
        char propVal[PROP_VALUE_MAX + 1];
        int ret = __system_property_get(prop, propVal);
        if (ret != 0) {
            return propVal;
        }
        return nullptr;
    }

    /// @brief Reads android device name
    static std::string getDeviceName(void) {
        std::stringstream ss;
        char* manufacturer = getProperty("ro.product.manufacturer");
        char* model = getProperty("ro.product.model");
        if (manufacturer == nullptr || model == nullptr) {
            return std::string();
        }
        ss << manufacturer << "-" << model;
        return ss.str();
    }
#endif // _ELPP_OS_ANDROID

    /// @brief Runs command on terminal and returns the output.
    ///
    /// @detail This is applicable only on unix based systems, for all other OS, an empty string is returned.
    /// @param command Bash command
    /// @return Result of bash output or empty string if no result found.
    static const std::string getBashOutput(const char* command) {
#if (_ELPP_OS_UNIX && !_ELPP_OS_ANDROID && !_ELPP_CYGWIN)
        if (command == nullptr) {
            return std::string();
        }
        FILE* proc = nullptr;
        if ((proc = popen(command, "r")) == nullptr) {
            ELPP_INTERNAL_ERROR("\nUnable to run command [" << command << "]", true);
            return std::string();
        }
        char hBuff[4096];
        if (fgets(hBuff, sizeof(hBuff), proc) != nullptr) {
            pclose(proc);
            if (hBuff[strlen(hBuff) - 1] == '\n') {
                hBuff[strlen(hBuff) - 1] = '\0';
            }
            return std::string(hBuff);
        }
        return std::string();
#else
        _ELPP_UNUSED(command);
        return std::string();
#endif // (_ELPP_OS_UNIX && !_ELPP_OS_ANDROID && !_ELPP_CYGWIN)
    }

    /// @brief Gets environment variable. This is cross-platform and CRT safe (for VC++)
    /// @param variableName Environment variable name
    /// @param defaultVal If no environment variable or value found the value to return by default
    /// @param alternativeBashCommand If environment variable not found what would be alternative bash command
    ///        in order to look for value user is looking for. E.g, for 'user' alternative command will 'whoami'
    static std::string getEnvironmentVariable(const char* variableName, const char* defaultVal, const char* alternativeBashCommand = nullptr) {
#if _ELPP_OS_UNIX
        const char* val = getenv(variableName);
#elif _ELPP_OS_WINDOWS
        const char* val = getWindowsEnvironmentVariable(variableName);
#endif // _ELPP_OS_UNIX
        if ((val == nullptr) || ((strcmp(val, "") == 0))) {
#if _ELPP_OS_UNIX && defined(_ELPP_FORCE_ENV_VAR_FROM_BASH)
            /// Try harder on unix-based systems
            std::string valBash = base::utils::OS::getBashOutput(alternativeBashCommand);
            if (valBash.empty()) {
                return std::string(defaultVal);
            } else {
                return valBash;
            }
#elif _ELPP_OS_WINDOWS || _ELPP_OS_UNIX
            _ELPP_UNUSED(alternativeBashCommand);
            return std::string(defaultVal);
#endif // _ELPP_OS_UNIX && defined(_ELPP_FORCE_ENV_VAR_FROM_BASH)
        }
        return std::string(val);
    }

    /// @brief Gets current username.
    static inline const std::string currentUser(void) {
#if _ELPP_OS_UNIX && !_ELPP_OS_ANDROID
        return getEnvironmentVariable("USER", base::consts::kUnknownUser, "whoami");
#elif _ELPP_OS_WINDOWS
        return getEnvironmentVariable("USERNAME", base::consts::kUnknownUser);
#elif _ELPP_OS_ANDROID
        return std::string("android");
#else
        return std::string();
#endif // _ELPP_OS_UNIX && !_ELPP_OS_ANDROID
    }

    /// @brief Gets current host name or computer name.
    ///
    /// @detail For android systems this is device name with its manufacturer and model seperated by hyphen
    static inline const std::string currentHost(void) {
#if _ELPP_OS_UNIX && !_ELPP_OS_ANDROID
        return getEnvironmentVariable("HOSTNAME", base::consts::kUnknownHost, "hostname");
#elif _ELPP_OS_WINDOWS
        return getEnvironmentVariable("COMPUTERNAME", base::consts::kUnknownHost);
#elif _ELPP_OS_ANDROID
        return getDeviceName();
#else
        return std::string();
#endif // _ELPP_OS_UNIX && !_ELPP_OS_ANDROID
    }
};
/// @brief Contains utilities for cross-platform date/time. This class make use of el::base::utils::Str
class DateTime : private base::StaticClass {
public:
    /// @brief Cross platform gettimeofday for Windows and unix platform. This can be used to determine current millisecond.
    ///
    /// @detail For unix system it uses gettimeofday(timeval*, timezone*) and for Windows, a seperate implementation is provided
    /// @param [in,out] tv Pointer that gets updated
    static void gettimeofday(struct timeval* tv) {
#if _ELPP_OS_WINDOWS
        if (tv != nullptr) {
#   if _ELPP_COMPILER_MSVC || defined(_MSC_EXTENSIONS)
            const unsigned __int64 delta_ = 11644473600000000Ui64;
#   else
            const unsigned __int64 delta_ = 11644473600000000ULL;
#   endif // _ELPP_COMPILER_MSVC || defined(_MSC_EXTENSIONS)
            const double secOffSet = 0.000001;
            const unsigned long usecOffSet = 1000000;
            FILETIME fileTime;
            GetSystemTimeAsFileTime(&fileTime);
            unsigned __int64 present = 0;
            present |= fileTime.dwHighDateTime;
            present = present << 32;
            present |= fileTime.dwLowDateTime;
            present /= 10; // mic-sec
            // Subtract the difference
            present -= delta_;
            tv->tv_sec = static_cast<long>(present * secOffSet);
            tv->tv_usec = static_cast<long>(present % usecOffSet);
        }
#else
        ::gettimeofday(tv, nullptr);
#endif // _ELPP_OS_WINDOWS
    }

    /// @brief Function that is used to parse date/time format.
    /// @param [out] buf Target buffer
    /// @param bufSz Size of target buffer
    /// @param format User provided format for date/time
    /// @param tInfo underlying time info pointer to be used in order to determine the actual time
    /// @param tVal underlying timeval pointer in order to determine milliseconds
    /// @param millisecondsOffset Milliseconds offset. This is used to determine milliseconds width; 1000 = 3, 100 = 4, 10 = 5, 1 = 6
    /// @return Parsed buffer
    static char* parseFormat(char* buf, size_t bufSz, const char* format, const struct tm* tInfo, const struct timeval* tVal, std::size_t millisecondsOffset = 1000) {
        if (buf == nullptr || tInfo == nullptr || format == nullptr) {
            ELPP_INTERNAL_ERROR("Cannot parse format; buf: '" << base::utils::charPtrVal(buf) << "'; bufSz: " << bufSz << "; "
                    "format '" << base::utils::charPtrVal(format) << "';", false);
            return buf;
        }
        const char* bufLim = buf + bufSz;
        if (millisecondsOffset <= 0 || millisecondsOffset >= 1000) {
            millisecondsOffset = base::consts::kDefaultMillisecondsOffset;
        }
        for (; *format; ++format) {
            if (*format == '%') {
                switch (*++format) {
                case base::consts::kFormatEscapeChar: // Escape
                    break;
                case '\0':  // End
                    --format;
                    break;
                case 'd':  // Day
                    buf = appendToBuff(tInfo->tm_mday, "%02d", buf, bufLim);
                    continue;
                case 'a': // Day of week (short)
                    buf = appendToBuff(((tInfo->tm_wday < 0 || tInfo->tm_wday > 6) ? "?" : base::consts::kDaysAbbrev[tInfo->tm_wday]), buf, bufLim);
                    continue;
                case 'A': // Day of week (long)
                    buf = appendToBuff(((tInfo->tm_wday < 0 || tInfo->tm_wday > 6) ? "?" : base::consts::kDays[tInfo->tm_wday]), buf, bufLim);
                    continue;
                case 'M': // month
                    buf = appendToBuff(tInfo->tm_mon, "%02d", buf, bufLim);
                    continue;
                case 'b': // month (short)
                    buf = appendToBuff(((tInfo->tm_mon < 0 || tInfo->tm_mon > 11) ? "?" : base::consts::kMonthsAbbrev[tInfo->tm_mon]), buf, bufLim);
                    continue;
                case 'B': // month (long)
                    buf = appendToBuff(((tInfo->tm_mon < 0 || tInfo->tm_mon > 11) ? "?" : base::consts::kMonths[tInfo->tm_mon]), buf, bufLim);
                    continue;
                case 'y': // year (two digits)
                    buf = appendToBuff(tInfo->tm_year + base::consts::kYearBase, "%02d", buf, bufLim);
                    continue;
                case 'Y': // year (four digits)
                    buf = appendToBuff(tInfo->tm_year + base::consts::kYearBase, "%04d", buf, bufLim);
                    continue;
                case 'h': // hour (12-hour)
                    buf = appendToBuff((tInfo->tm_hour % 12) ? (tInfo->tm_hour % 12) : 12, "%02d", buf, bufLim);
                    continue;
                case 'H': // hour (24-hour)
                    buf = appendToBuff(tInfo->tm_hour, "%02d", buf, bufLim);
                    continue;
                case 'm': // minute
                    buf = appendToBuff(tInfo->tm_min, "%02d", buf, bufLim);
                    continue;
                case 's': // second
                    buf = appendToBuff(tInfo->tm_sec, "%02d", buf, bufLim);
                    continue;
                case 'z': // milliseconds
                case 'g':
                    buf = appendToBuff(tVal == nullptr ? 0 : (tVal->tv_usec / millisecondsOffset), "%03ld", buf, bufLim);
                    continue;
                case 'F': // AM/PM
                    buf = appendToBuff((tInfo->tm_hour >= 12) ? base::consts::kPm : base::consts::kAm, buf, bufLim);
                    continue;
                default:
                    continue;
                }
            }
            if (buf == bufLim) {
                break;
            }
            *buf++ = *format;
        }
        return buf;
    }

    /// @brief Gets current date and time with milliseconds.
    /// @param format User provided date/time format
    /// @param millisecondsOffset Milliseconds offset. This is used to determine milliseconds width; 1000 = 3, 100 = 4, 10 = 5, 1 = 6
    /// @returns string based date time in specified format.
    static std::string getDateTime(const char* format, std::size_t milliSecondOffset = 1000) {
        const int kBuffSize = 30;
        char buff_[kBuffSize] = "";
        struct timeval currTime;
        gettimeofday(&currTime);
        struct tm* timeInfo = nullptr;
#if _ELPP_OS_UNIX
        struct tm* localTime = localtime(&currTime.tv_sec);
        timeInfo = localTime;
#else
#   if _ELPP_COMPILER_MSVC
        struct tm localTime;
        time_t t;
        _time64(&t);
        localtime_s(&localTime, &t);
        timeInfo = &localTime;
#   else
        // For any other compilers that don't have CRT warnings issue e.g, MinGW or TDM GCC- we use different method
        time_t rawTime = time(nullptr);
        struct tm* localTime = localtime(&rawTime);
        timeInfo = localTime;
#   endif // _ELPP_COMPILER_MSVC
#endif // _ELPP_OS_UNIX
        DateTime::parseFormat(buff_, kBuffSize, format, timeInfo, &currTime, milliSecondOffset);
        return std::string(buff_);
    }

    /// @brief Formats time to get unit accordingly, units like second if > 1000 or minutes if > 60000 etc
    static std::string formatTime(unsigned long long time, const base::TimestampUnit& timestampUnit) {
        double result = static_cast<double>(time);
        unsigned short start = static_cast<unsigned short>(timestampUnit);
        const char* unit = base::consts::kTimeFormats[start].unit;
        for (unsigned short i = start; i < base::consts::kMaxTimeFormats - 1; ++i) {
            if (result <= base::consts::kTimeFormats[i].value) {
                break;
            }
            result /= base::consts::kTimeFormats[i].value;
            unit = base::consts::kTimeFormats[i + 1].unit;
        }
        std::stringstream ss;
        ss << result << " " << unit;
        return ss.str();
    }

    /// @brief Gets time difference in milli/micro second depending on timestampUnit
    static inline unsigned long long getTimeDifference(const struct timeval& endTime, const struct timeval& startTime, const base::TimestampUnit& timestampUnit) {
        if (timestampUnit == base::TimestampUnit::Microsecond) {
            return static_cast<unsigned long long>(static_cast<unsigned long long>(1000000 * endTime.tv_sec + endTime.tv_usec) -
                    static_cast<unsigned long long>(1000000 * startTime.tv_sec + startTime.tv_usec));
        } else {
            return static_cast<unsigned long long>((((endTime.tv_sec - startTime.tv_sec) * 1000000) + (endTime.tv_usec - startTime.tv_usec)) / 1000);
        }
    }
private:
    /// @brief Appends values to buf pointer
    static inline char* appendToBuff(const std::size_t n, const char* format, char* buf, const char* bufLim) {
        char localBuff[32];
        SPRINTF(localBuff, format, n);
        return appendToBuff(localBuff, buf, bufLim);
    }

    /// @brief Appends values to buf pointer
    static inline char* appendToBuff(const char* str, char* buf, const char* bufLim) {
        while ((buf < bufLim) && ((*buf = *str++) != '\0')) {
            ++buf;
        }
        return buf;
    }
};
/// @brief Command line arguments for application if specified using el::Helpers::setArgs(..) or _START_EASYLOGGINGPP(..)
class CommandLineArgs {
public:
    CommandLineArgs(void) {
        setArgs(0, static_cast<char**>(nullptr));
    }
    CommandLineArgs(int argc, const char** argv) {
        setArgs(argc, argv);
    }
    CommandLineArgs(int argc, char** argv) {
        setArgs(argc, argv);
    }
    virtual ~CommandLineArgs(void) {}
    /// @brief Sets arguments and parses them
    inline void setArgs(int argc, const char** argv) {
        setArgs(argc, const_cast<char**>(argv));
    }
    /// @brief Sets arguments and parses them
    inline void setArgs(int argc, char** argv) {
        m_params.clear();
        m_paramsWithValue.clear();
        if (argc == 0 || argv == nullptr) {
            return;
        }
        m_argc = argc;
        m_argv = argv;
        for (int i = 1; i < m_argc; ++i) {
            const char* v = (strstr(m_argv[i], "="));
            if (v != nullptr && strlen(v) > 0) {
                std::string key = std::string(m_argv[i]);
                key = key.substr(0, key.find_first_of('='));
                if (hasParamWithValue(key.c_str())) {
                    ELPP_INTERNAL_INFO("Skipping [" << key << "] arg since it already has value [" << getParamValue(key.c_str()) << "]");
                } else {
                    m_paramsWithValue.insert(std::make_pair(key, std::string(v + 1)));
                }
            }
            if (v == nullptr) {
                if (hasParam(m_argv[i])) {
                    ELPP_INTERNAL_INFO("Skipping [" << m_argv[i] << "] arg since it already exists");
                } else {
                    m_params.push_back(std::string(m_argv[i]));
                }
            }
        }
    }
    /// @brief Returns true if arguments contain paramKey with a value (seperated by '=')
    inline bool hasParamWithValue(const char* paramKey) const {
        return m_paramsWithValue.find(std::string(paramKey)) != m_paramsWithValue.end();
    }
    /// @brief Returns value of arguments
    /// @see hasParamWithValue(const char*)
    inline const char* getParamValue(const char* paramKey) const {
        return m_paramsWithValue.find(std::string(paramKey))->second.c_str();
    }
    /// @brief Return true if arguments has a param (not having a value) i,e without '='
    inline bool hasParam(const char* paramKey) const {
        return std::find(m_params.begin(), m_params.end(), std::string(paramKey)) != m_params.end();
    }
    /// @brief Returns true if no params available. This exclude argv[0]
    inline bool empty(void) const {
        return m_params.empty() && m_paramsWithValue.empty();
    }
    /// @brief Returns total number of arguments. This exclude argv[0]
    inline std::size_t size(void) const {
        return m_params.size() + m_paramsWithValue.size();
    }
    inline friend std::ostream& operator<<(std::ostream& os, const CommandLineArgs& c) {
        for (int i = 1; i < c.m_argc; ++i) {
            os << "[" << c.m_argv[i] << "]";
            if (i < c.m_argc - 1)
                os << " ";
        }
        return os;
    }
private:
    int m_argc;
    char** m_argv;
    std::map<std::string, std::string> m_paramsWithValue;
    std::vector<std::string> m_params;
};
/// @brief Abstract registry (aka repository) that provides basic interface for pointer repository specified by T_Ptr type.
///
/// @detail Most of the functions are virtual final methods but anything implementing this abstract class should implement
/// unregisterAll() and deepCopy(const AbstractRegistry<T_Ptr, Container>&) and write registerNew() method according to container
/// and few more methods; get() to find element, unregister() to unregister single entry.
/// Please note that this is thread-unsafe and should also implement thread-safety mechanisms in implementation.
template <typename T_Ptr, typename Container>
class AbstractRegistry : public base::threading::ThreadSafe {
public:
    typedef typename Container::iterator iterator;
    typedef typename Container::const_iterator const_iterator;

    /// @brief Default constructor
    AbstractRegistry(void) {}

    /// @brief Move constructor that is useful for base classes
    AbstractRegistry(AbstractRegistry&& sr) {
        if (this == &sr) {
            return;
        }
        unregisterAll();
        m_list = std::move(sr.m_list);
    }

    bool operator==(const AbstractRegistry<T_Ptr, Container>& other) {
        if (size() != other.size()) {
            return false;
        }
        for (std::size_t i = 0; i < m_list.size(); ++i) {
            if (m_list.at(i) != other.m_list.at(i)) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const AbstractRegistry<T_Ptr, Container>& other) {
        if (size() != other.size()) {
            return true;
        }
        for (std::size_t i = 0; i < m_list.size(); ++i) {
            if (m_list.at(i) != other.m_list.at(i)) {
                return true;
            }
        }
        return false;
    }

    /// @brief Assignment move operator
    AbstractRegistry& operator=(AbstractRegistry&& sr) {
        if (this == &sr) {
            return *this;
        }
        unregisterAll();
        m_list = std::move(sr.m_list);
        return *this;
    }

    virtual ~AbstractRegistry(void) {
    }

    /// @return Iterator pointer from start of repository
    virtual inline iterator begin(void) FINAL {
        return m_list.begin();
    }

    /// @return Iterator pointer from end of repository
    virtual inline iterator end(void) FINAL {
        return m_list.end();
    }


    /// @return Constant iterator pointer from start of repository
    virtual inline const_iterator cbegin(void) const FINAL {
        return m_list.cbegin();
    }

    /// @return End of repository
    virtual inline const_iterator cend(void) const FINAL {
        return m_list.cend();
    }

    /// @return Whether or not repository is empty
    virtual inline bool empty(void) const FINAL {
        return m_list.empty();
    }

    /// @return Size of repository
    virtual inline std::size_t size(void) const FINAL {
        return m_list.size();
    }

    /// @brief Returns underlying container by reference
    virtual inline Container& list(void) FINAL {
        return m_list;
    }

    /// @brief Returns underlying container by constant reference.
    virtual inline const Container& list(void) const FINAL {
        return m_list;
    }

    /// @brief Unregisters all the pointers from current repository.
    virtual void unregisterAll(void) = 0;

protected:

    virtual void deepCopy(const AbstractRegistry<T_Ptr, Container>&) = 0;

    void reinitDeepCopy(const AbstractRegistry<T_Ptr, Container>& sr) {
        unregisterAll();
        deepCopy(sr);
    }
private:
    Container m_list;
};

/// @brief A pointer registry mechanism to manage memory and provide search functionalities. (non-predicate version)
///
/// @detail NOTE: This is thread-unsafe implementation of AbstractRegistry<T_Ptr, Container>. Any implementation of this class
/// should be made thread-safe explicitly
template <typename T_Ptr, typename T_Key = const char*>
class Registry : public AbstractRegistry<T_Ptr, std::map<T_Key, T_Ptr*>> {
public:
    typedef typename Registry<T_Ptr, T_Key>::iterator iterator;
    typedef typename Registry<T_Ptr, T_Key>::const_iterator const_iterator;

    Registry(void) {}

    /// @brief Copy constructor that is useful for base classes. Try to avoid this constructor, use move constructor.
    Registry(const Registry& sr) : AbstractRegistry<T_Ptr, std::vector<T_Ptr*>>() {
        if (this == &sr) {
            return;
        }
        this->reinitDeepCopy(sr);
    }

    /// @brief Assignment operator that unregisters all the existing registeries and deeply copies each of repo element
    /// @see unregisterAll()
    /// @see deepCopy(const AbstractRegistry&)
    Registry& operator=(const Registry& sr) {
        if (this == &sr) {
            return *this;
        }
        this->reinitDeepCopy(sr);
        return *this;
    }

    virtual ~Registry(void) {
        unregisterAll();
    }
protected:
    virtual inline void unregisterAll(void) FINAL {
        if (!this->empty()) {
            for (auto&& curr : this->list()) {
                base::utils::safeDelete(curr.second);
            }
            this->list().clear();
        }
    }

    /// @brief Registers new registry to repository.
    virtual inline void registerNew(const T_Key& uniqKey, T_Ptr* ptr) FINAL {
        unregister(uniqKey);
        this->list().insert(std::make_pair(uniqKey, ptr));
    }

    /// @brief Unregisters single entry mapped to specified unique key
    inline void unregister(const T_Key& uniqKey) {
        T_Ptr* existing = get(uniqKey);
        if (existing != nullptr) {
            base::utils::safeDelete(existing);
            this->list().erase(uniqKey);
        }
    }

    /// @brief Gets pointer from repository. If none found, nullptr is returned.
    inline T_Ptr* get(const T_Key& uniqKey) {
        T_Ptr* ptrExisting = nullptr;
        try {
            ptrExisting = this->list().at(uniqKey);
        } catch (...) {
        }
        return ptrExisting;
    }
private:
    virtual inline void deepCopy(const AbstractRegistry<T_Ptr, std::map<T_Key, T_Ptr*>>& sr) FINAL {
        for (const_iterator it = sr.cbegin(); it != sr.cend(); ++it) {
            registerNew(it->first, new T_Ptr(*it->second));
        }
    }
};

/// @brief A pointer registry mechanism to manage memory and provide search functionalities. (predicate version)
///
/// @detail NOTE: This is thread-unsafe implementation of AbstractRegistry<T_Ptr, Container>. Any implementation of this class
/// should be made thread-safe explicitly
template <typename T_Ptr, typename Pred>
class RegistryWithPred : public AbstractRegistry<T_Ptr, std::vector<T_Ptr*>> {
public:
    typedef typename RegistryWithPred<T_Ptr, Pred>::iterator iterator;
    typedef typename RegistryWithPred<T_Ptr, Pred>::const_iterator const_iterator;

    RegistryWithPred(void) {
    }

    virtual ~RegistryWithPred(void) {
        unregisterAll();
    }

    /// @brief Copy constructor that is useful for base classes. Try to avoid this constructor, use move constructor.
    RegistryWithPred(const RegistryWithPred& sr) : AbstractRegistry<T_Ptr, std::vector<T_Ptr*>>() {
        if (this == &sr) {
            return;
        }
        this->reinitDeepCopy(sr);
    }

    /// @brief Assignment operator that unregisters all the existing registeries and deeply copies each of repo element
    /// @see unregisterAll()
    /// @see deepCopy(const AbstractRegistry&)
    RegistryWithPred& operator=(const RegistryWithPred& sr) {
        if (this == &sr) {
            return *this;
        }
        this->reinitDeepCopy(sr);
        return *this;
    }

    friend inline std::ostream& operator<<(std::ostream& os, const RegistryWithPred& sr) {
        for (const_iterator it = sr.list().begin(); it != sr.list().end(); ++it) {
            os << "    " << **it << "\n";
        }
        return os;
    }
protected:
    virtual inline void unregisterAll(void) FINAL {
        if (!this->empty()) {
            for (auto&& curr : this->list()) {
                base::utils::safeDelete(curr);
            }
            this->list().clear();
        }
    }

    virtual void unregister(T_Ptr*& ptr) FINAL {
        if (ptr) {
            iterator iter = this->begin();
            for (; iter != this->end(); ++iter) {
                if (ptr == *iter) {
                    break;
                }
            }
            if (iter != this->end() && *iter != nullptr) {
                this->list().erase(iter);
                base::utils::safeDelete(*iter);
            }
        }
    }

    virtual inline void registerNew(T_Ptr* ptr) FINAL {
        this->list().push_back(ptr);
    }

    /// @brief Gets pointer from repository with speicifed arguments. Arguments are passed to predicate
    /// in order to validate pointer.
    ///
    /// @detail Varidiac templates are not yet supported by Visual C++ 11.0 and since Easylogging++ has to be available
    /// for latest flavour of Visual C++ so we explicitely define templates arguments. Once the varidiac templates
    /// are available for all the compiler that are supported by easylogging++, we will replace this function with
    /// following signature
    ///     <pre>
    ///          template <typename... T>
    ///          inline T_Ptr* get(const T&... args) {
    ///             std::find_if(this->list().begin(), this->list().end(), Pred(args...));
    ///                ... rest will be same
    ///     </pre>
    template <typename T, typename T2>
    inline T_Ptr* get(const T& arg1, const T2 arg2) {
        iterator iter = std::find_if(this->list().begin(), this->list().end(), Pred(arg1, arg2));
        if (iter != this->list().end() && *iter != nullptr) {
            return *iter;
        }
        return nullptr;
    }
private:
    virtual inline void deepCopy(const AbstractRegistry<T_Ptr, std::vector<T_Ptr*>>& sr) {
        for (const_iterator it = sr.list().begin(); it != sr.list().end(); ++it) {
            registerNew(new T_Ptr(**it));
        }
    }
};

} // namespace utils
/// @brief Represents log format containing flags and date format. This is used internally to start initial log
class LogFormat {
public:
    LogFormat(void) :
        m_level(Level::Unknown),
        m_userFormat(std::string()),
        m_format(std::string()),
        m_dateTimeFormat(std::string()),
        m_flags(0x0) {
    }

    LogFormat(const Level& level, const std::string& format)
            : m_level(level), m_userFormat(format) {
        parseFromFormat(m_userFormat);
    }

    LogFormat(const LogFormat& logFormat) {
        m_level = logFormat.m_level;
        m_userFormat = logFormat.m_userFormat;
        m_format = logFormat.m_format;
        m_dateTimeFormat = logFormat.m_dateTimeFormat;
        m_flags = logFormat.m_flags;
    }

    LogFormat(LogFormat&& logFormat) {
        m_level = std::move(logFormat.m_level);
        m_userFormat = std::move(logFormat.m_userFormat);
        m_format = std::move(logFormat.m_format);
        m_dateTimeFormat = std::move(logFormat.m_dateTimeFormat);
        m_flags = std::move(logFormat.m_flags);
    }

    LogFormat& operator=(const LogFormat& logFormat) {
        m_level = logFormat.m_level;
        m_userFormat = logFormat.m_userFormat;
        m_dateTimeFormat = logFormat.m_dateTimeFormat;
        m_flags = logFormat.m_flags;
        return *this;
    }

    virtual ~LogFormat(void) {
    }

    inline bool operator==(const LogFormat& other) {
        return m_level == other.m_level && m_userFormat == other.m_userFormat && m_format == other.m_format &&
                m_dateTimeFormat == other.m_dateTimeFormat && m_flags == other.m_flags;
    }

    /// @brief Updates format to be used while logging.
    /// @param userFormat User provided format
    void parseFromFormat(const std::string& userFormat) {
        // We make copy because we will be changing the format
        // i.e, removing user provided date format from original format
        // and then storing it.
        std::string formatCopy = userFormat;
        auto conditionalAddFlag = [&](const char* specifier, const base::FormatFlags& flag) {
            if (formatCopy.find(specifier) != std::string::npos) {
                addFlag(flag);
            }
        };
        m_flags = 0x0;
        conditionalAddFlag(base::consts::kAppNameFormatSpecifier, base::FormatFlags::AppName);
        conditionalAddFlag(base::consts::kSeverityLevelFormatSpecifier, base::FormatFlags::Level);
        conditionalAddFlag(base::consts::kLoggerIdFormatSpecifier, base::FormatFlags::LoggerId);
        conditionalAddFlag(base::consts::kThreadIdFormatSpecifier, base::FormatFlags::ThreadId);
        conditionalAddFlag(base::consts::kLogFileFormatSpecifier, base::FormatFlags::File);
        conditionalAddFlag(base::consts::kLogLineFormatSpecifier, base::FormatFlags::Line);
        conditionalAddFlag(base::consts::kLogLocationFormatSpecifier, base::FormatFlags::Location);
        conditionalAddFlag(base::consts::kLogFunctionFormatSpecifier, base::FormatFlags::Function);
        conditionalAddFlag(base::consts::kCurrentUserFormatSpecifier, base::FormatFlags::User);
        conditionalAddFlag(base::consts::kCurrentHostFormatSpecifier, base::FormatFlags::Host);
        conditionalAddFlag(base::consts::kMessageFormatSpecifier, base::FormatFlags::LogMessage);
        conditionalAddFlag(base::consts::kVerboseLevelFormatSpecifier, base::FormatFlags::VerboseLevel);
        // For date/time we need to extract user's date format first
        std::size_t dateIndex = std::string::npos;
        if ((dateIndex = formatCopy.find(base::consts::kDateTimeFormatSpecifier)) != std::string::npos) {
            while (dateIndex > 0 && formatCopy[dateIndex - 1] == base::consts::kFormatEscapeChar) {
                dateIndex = formatCopy.find(base::consts::kDateTimeFormatSpecifier, dateIndex + 1);
            }
            if (dateIndex != std::string::npos) {
                addFlag(base::FormatFlags::DateTime);
                updateDateFormat(dateIndex, formatCopy);
            }
        }
        m_format = formatCopy;
        updateLevelFormatSpec();
    }

    inline const Level& level(void) const {
        return m_level;
    }

    inline const std::string& userFormat(void) const {
        return m_userFormat;
    }

    inline const std::string& format(void) const {
       return m_format;
    }

    inline const std::string& dateTimeFormat(void) const {
       return m_dateTimeFormat;
    }

    inline unsigned short flags(void) const {
       return m_flags;
    }

    inline bool hasFlag(const base::FormatFlags& flag) {
        return base::utils::hasFlag(flag, m_flags) > 0;
    }

    friend inline std::ostream& operator<<(std::ostream& os, const LogFormat& format) {
        os << format.m_format;
        return os;
    }
protected:
    /// @brief Updates date time format if available in currFormat.
    /// @param index Index where %datetime, %date or %time was found
    /// @param [in,out] currFormat current format that is being used to format
    virtual void updateDateFormat(std::size_t index, std::string& currFormat) FINAL {
        if (hasFlag(base::FormatFlags::DateTime)) {
            index += strlen(base::consts::kDateTimeFormatSpecifier);
        }
        const char* ptr = currFormat.c_str() + index;
        if ((currFormat.size() > index) && (ptr[0] == '{')) {
            // User has provided format for date/time
            ++ptr;
            int count = 1; // Start by 1 in order to remove starting brace
            std::stringstream ss;
            for(; *ptr; ++ptr, ++count) {
                if (*ptr == '}') {
                    ++count; // In order to remove ending brace
                    break;
                }
                ss << *ptr;
            }
            currFormat.erase(index, count);
            m_dateTimeFormat = ss.str();
        } else {
            // No format provided, use default
            if (hasFlag(base::FormatFlags::DateTime)) {
                m_dateTimeFormat = std::string(base::consts::kDefaultDateTimeFormat);
            }
        }
    }

    /// @brief Updates %level from format. This is so that we dont have to do it at log-writing-time. It uses m_format and m_level
    virtual void updateLevelFormatSpec(void) FINAL {
        // Do not use switch over strongly typed enums because Intel C++ compilers dont support them yet.
        if (m_level == Level::Debug) {
            base::utils::Str::replaceFirstWithEscape(m_format, base::consts::kSeverityLevelFormatSpecifier,
                    base::consts::kDebugLevelLogValue);
            return;
        }
        if (m_level == Level::Info) {
            base::utils::Str::replaceFirstWithEscape(m_format, base::consts::kSeverityLevelFormatSpecifier,
                    base::consts::kInfoLevelLogValue);
            return;
        }
        if (m_level == Level::Warning) {
            base::utils::Str::replaceFirstWithEscape(m_format, base::consts::kSeverityLevelFormatSpecifier,
                    base::consts::kWarningLevelLogValue);
            return;
        }
        if (m_level == Level::Error) {
            base::utils::Str::replaceFirstWithEscape(m_format, base::consts::kSeverityLevelFormatSpecifier,
                    base::consts::kErrorLevelLogValue);
            return;
        }
        if (m_level == Level::Fatal) {
            base::utils::Str::replaceFirstWithEscape(m_format, base::consts::kSeverityLevelFormatSpecifier,
                    base::consts::kFatalLevelLogValue);
            return;
        }
        if (m_level == Level::Verbose) {
            base::utils::Str::replaceFirstWithEscape(m_format, base::consts::kSeverityLevelFormatSpecifier,
                    base::consts::kVerboseLevelLogValue);
            return;
        }
        if (m_level == Level::Trace) {
            base::utils::Str::replaceFirstWithEscape(m_format, base::consts::kSeverityLevelFormatSpecifier,
                    base::consts::kTraceLevelLogValue);
            return;
        }
        // Ignore Level::Global and Level::Unknown
    }

    inline void addFlag(const base::FormatFlags& flag) {
        base::utils::addFlag(flag, m_flags);
    }
private:
    Level m_level;
    std::string m_userFormat;
    std::string m_format;
    std::string m_dateTimeFormat;
    unsigned short m_flags;
};
} // namespace base
class Loggers;
class Helpers;
/// @brief Represents single configuration that has representing level, configuration type and a string based value.
///
/// @detail String based value means any value either its boolean, integer or string itself, it will be embedded inside quotes
/// and will be parsed later.
///
/// Consider some examples below:
/// <ul>
///   <li>  el::Configuration confEnabledInfo(el::Level::Info, el::ConfigurationType::Enabled, "true");  </li>
///   <li>  el::Configuration confMaxLogFileSizeInfo(el::Level::Info, el::ConfigurationType::MaxLogFileSize, "2048");  </li>
///   <li>  el::Configuration confFilenameInfo(el::Level::Info, el::ConfigurationType::Filename, "/var/log/my.log");  </li>
/// </ul>
class Configuration {
public:
    Configuration(const Configuration& c) :
            m_level(c.m_level),
            m_configurationType(c.m_configurationType),
            m_value(c.m_value) {
    }

    Configuration& operator=(const Configuration& c) {
        m_level = c.m_level;
        m_configurationType = c.m_configurationType;
        m_value = c.m_value;
        return *this;
    }

    virtual ~Configuration(void) {
    }

    /// @brief Full constructor used to sets value of configuration
    Configuration(const Level& level, const ConfigurationType& configurationType, const std::string& value) :
        m_level(level),
        m_configurationType(configurationType),
        m_value(value) {
    }

    /// @brief Gets level of current configuration
    inline const Level& level(void) const {
        return m_level;
    }

    /// @brief Gets configuration type of current configuration
    inline const ConfigurationType& configurationType(void) const {
        return m_configurationType;
    }

    /// @brief Gets string based configuration value
    inline const std::string& value(void) const {
        return m_value;
    }

    /// @brief Set string based configuration value
    /// @param value_ Value to set. Values have to be std::string; For boolean values use "true", "false", for any integral values
    ///        use them in quotes. They will be parsed when configuring
    inline void setValue(const std::string& value) {
        m_value = value;
    }

    friend std::ostream& operator<<(std::ostream& os, const Configuration& c) {
        os << LevelHelper::convertToString(c.m_level)
            << " " << ConfigurationTypeHelper::convertToString(c.m_configurationType)
            << " = " << c.m_value;
        return os;
    }

    /// @brief Used to find configuration from configuration (pointers) repository. Avoid using it.
    class Predicate {
    public:
        Predicate(const Level& level, const ConfigurationType& configurationType) :
            m_level(level),
            m_configurationType(configurationType) {
        }

        inline bool operator()(const Configuration* conf) const {
            return ((conf != nullptr) && (conf->level() == m_level) && (conf->configurationType() == m_configurationType));
        }

    private:
        Level m_level;
        ConfigurationType m_configurationType;
    };
private:
    Level m_level;
    ConfigurationType m_configurationType;
    std::string m_value;
};

/// @brief Thread-safe Configuration repository
///
/// @detail This repository represents configurations for all the levels and configuration type mapped to a value.
class Configurations : public base::utils::RegistryWithPred<Configuration, Configuration::Predicate> {
public:
    /// @brief Default constructor with empty repository
    Configurations(void) :
            m_configurationFile(std::string()),
            m_isFromFile(false) {
    }

    /// @brief Constructor used to set configurations using configuration file.
    /// @param configurationFile Full path to configuration file
    /// @param useDefaultsForRemaining Lets you set the remaining configurations to default.
    /// @param base If provided, this configuration will be based off existing repository that this argument is pointing to.
    /// @see parseFromFile(const std::string&, Configurations* base)
    /// @see setRemainingToDefault()
    Configurations(const std::string& configurationFile, bool useDefaultsForRemaining = true, Configurations* base = nullptr) :
            m_configurationFile(configurationFile),
            m_isFromFile(false) {
        parseFromFile(configurationFile, base);
        if (useDefaultsForRemaining) {
            setRemainingToDefault();
        }

    }

    virtual ~Configurations(void) {
    }

    /// @brief Parses configuration from file.
    /// @param configurationFile Full path to configuration file
    /// @param baseConfigurations to base new configuration repository off. This value is used when you want to use
    ///        existing Configurations to base all the values and then set rest of configuration via configuration file.
    /// @return True if successfully parsed, false otherwise. You may define '_STOP_ON_FIRST_ELPP_ASSERTION' to make sure you
    ///         do not proceed without successful parse.
    inline bool parseFromFile(const std::string& configurationFile, Configurations* base = nullptr) {
        bool assertionPassed = false;
        ELPP_ASSERT((assertionPassed = base::utils::File::pathExists(configurationFile.c_str(), true)),
                "Configuration file [" << configurationFile << "] does not exist!");
        if (!assertionPassed) {
            return false;
        }
        bool success = Parser::parseFromFile(configurationFile, this, base);
        m_isFromFile = success;
        return success;
    }

    /// @brief Parse configurations from configuration string.
    ///
    /// @detail This configuration string has same syntax as configuration file contents. Make sure all the necessary
    /// new line characters are provided.
    /// @param configurationsString
    /// @return True if successfully parsed, false otherwise. You may define '_STOP_ON_FIRST_ELPP_ASSERTION' to make sure you
    ///         do not proceed without successful parse.
    inline bool parseFromText(const std::string& configurationsString) {
        bool success = Parser::parseFromText(configurationsString, this);
        if (success) {
            m_isFromFile = false;
        }
        return success;
    }

    /// @brief Sets configuration based-off an existing configurations.
    /// @param base Pointer to existing configurations.
    inline void setFromBase(Configurations* base) {
        if (base == nullptr || base == this) {
            return;
        }
        base::threading::lock_guard lock(base->mutex());
        for (Configuration*& conf : base->list()) {
            set(conf);
        }
    }

    /// @brief Determines whether or not specified configuration type exists in the repository.
    ///
    /// @detail Returns as soon as first level is found.
    /// @param configurationType Type of configuration to check existence for.
    bool hasConfiguration(const ConfigurationType& configurationType) {
        unsigned short lIndex = LevelHelper::kMinValid;
        bool result = false;
        LevelHelper::forEachLevel(lIndex, [&](void) -> bool {
            if (hasConfiguration(LevelHelper::castFromInt(lIndex), configurationType)) {
                result = true;
            }
            return result;
        });
        return result;
    }

    /// @brief Determines whether or not specified configuration type exists for specified level
    /// @param level Level to check
    /// @param configurationType Type of configuration to check existence for.
    inline bool hasConfiguration(const Level& level, const ConfigurationType& configurationType) {
        base::threading::lock_guard lock(mutex());
#if _ELPP_COMPILER_INTEL
        // We cant specify template types here, Intel C++ throws compilation error
        // "error: type name is not allowed"
        return RegistryWithPred::get(level, configurationType) != nullptr;
#else
        return RegistryWithPred<Configuration, Configuration::Predicate>::get(level, configurationType) != nullptr;
#endif // _ELPP_COMPILER_INTEL
    }

    /// @brief Sets value of configuration for specified level.
    ///
    /// @detail Any existing configuration for specified level will be replaced. Also note that configuration types
    /// ConfigurationType::MillisecondsWidth and ConfigurationType::PerformanceTracking will be ignored if not set for
    /// Level::Global because these configurations are not dependant on level.
    /// @param level Level to set configuration for (el::Level).
    /// @param configurationType Type of configuration (el::ConfigurationType)
    /// @param value A string based value. Regardless of what the data type of configuration is, it will always be string
    /// from users' point of view. This is then parsed later to be used internally.
    /// @see Configuration::setValue(const std::string& value)
    /// @see el::Level
    /// @see el::ConfigurationType
    inline void set(const Level& level, const ConfigurationType& configurationType, const std::string& value) {
        base::threading::lock_guard lock(mutex());
        unsafeSet(level, configurationType, value); // This is not unsafe anymore as we have locked mutex
        if (level == Level::Global) {
            unsafeSetGlobally(configurationType, value, false); // Again this is not unsafe either
        }
    }

    /// @brief Sets single configuration based on other single configuration.
    /// @see set(const Level& level, const ConfigurationType& configurationType, const std::string& value)
    inline void set(Configuration* conf) {
        if (conf == nullptr) {
            return;
        }
        set(conf->level(), conf->configurationType(), conf->value());
    }

    inline Configuration* get(const Level& level, const ConfigurationType& configurationType) {
        base::threading::lock_guard lock(mutex());
        return RegistryWithPred<Configuration, Configuration::Predicate>::get(level, configurationType);
    }

    /// @brief Sets configuration for all levels.
    /// @param configurationType Type of configuration
    /// @param value String based value
    /// @see Configurations::set(const Level& level, const ConfigurationType& configurationType, const std::string& value)
    inline void setGlobally(const ConfigurationType& configurationType, const std::string& value) {
        setGlobally(configurationType, value, false);
    }

    /// @brief Clears repository so that all the configurations are unset
    inline void clear(void) {
        base::threading::lock_guard lock(mutex());
        unregisterAll();
    }

    /// @brief Gets configuration file used in parsing this configurations.
    ///
    /// @detail If this repository was set manually or by text this returns empty string.
    inline const std::string& configurationFile(void) const {
        return m_configurationFile;
    }

    /// @brief Sets configurations to "factory based" configurations.
    void setToDefault(void) {
        setGlobally(ConfigurationType::Enabled, "true", true);
#if !defined(_ELPP_NO_DEFAULT_LOG_FILE)
        setGlobally(ConfigurationType::Filename, std::string(base::consts::kDefaultLogFile), true);
#else
        _ELPP_UNUSED(base::consts::kDefaultLogFile);
#endif // !defined(_ELPP_NO_DEFAULT_LOG_FILE)
        setGlobally(ConfigurationType::ToFile, "true", true);
        setGlobally(ConfigurationType::ToStandardOutput, "true", true);
        setGlobally(ConfigurationType::MillisecondsWidth, "3", true);
        setGlobally(ConfigurationType::PerformanceTracking, "true", true);
        setGlobally(ConfigurationType::MaxLogFileSize, "0", true);

        setGlobally(ConfigurationType::Format, "%datetime %level [%logger] %log", true);
        set(Level::Debug, ConfigurationType::Format, "%datetime %level [%logger] [%user@%host] [%func] [%loc] %log");
        // INFO and WARNING are set to default by Level::Global
        set(Level::Error, ConfigurationType::Format, "%datetime %level [%logger] %log");
        set(Level::Fatal, ConfigurationType::Format, "%datetime %level [%logger] %log");
        set(Level::Verbose, ConfigurationType::Format, "%datetime %level-%vlevel [%logger] %log");
        set(Level::Trace, ConfigurationType::Format, "%datetime %level [%logger] [%func] [%loc] %log");
    }

    /// @brief Lets you set the remaining configurations to default.
    ///
    /// @detail By remaining, it means that the level/type a configuration does not exist for.
    /// This function is useful when you want to minimize chances of failures, e.g, if you have a configuration file that sets
    /// configuration for all the configurations except for Enabled or not, we use this so that ENABLED is set to default i.e,
    /// true. If you dont do this explicitley (either by calling this function or by using second param in Constructor
    /// and try to access a value, an error is thrown
    void setRemainingToDefault(void) {
        base::threading::lock_guard lock(mutex());
        unsafeSetIfNotExist(Level::Global, ConfigurationType::Enabled, "true");
#if !defined(_ELPP_NO_DEFAULT_LOG_FILE)
        unsafeSetIfNotExist(Level::Global, ConfigurationType::Filename, std::string(base::consts::kDefaultLogFile));
#endif // !defined(_ELPP_NO_DEFAULT_LOG_FILE)
        unsafeSetIfNotExist(Level::Global, ConfigurationType::ToFile, "true");
        unsafeSetIfNotExist(Level::Global, ConfigurationType::ToStandardOutput, "true");
        unsafeSetIfNotExist(Level::Global, ConfigurationType::MillisecondsWidth, "3");
        unsafeSetIfNotExist(Level::Global, ConfigurationType::PerformanceTracking, "true");
        unsafeSetIfNotExist(Level::Global, ConfigurationType::MaxLogFileSize, "0");
        unsafeSetIfNotExist(Level::Global, ConfigurationType::Format, "%datetime %level [%logger] %log");
        unsafeSetIfNotExist(Level::Debug, ConfigurationType::Format, "%datetime %level [%logger] [%user@%host] [%func] [%loc] %log");
        // INFO and WARNING are set to default by Level::Global
        unsafeSetIfNotExist(Level::Error, ConfigurationType::Format, "%datetime %level [%logger] %log");
        unsafeSetIfNotExist(Level::Fatal, ConfigurationType::Format, "%datetime %level [%logger] %log");
        unsafeSetIfNotExist(Level::Verbose, ConfigurationType::Format, "%datetime %level-%vlevel [%logger] %log");
        unsafeSetIfNotExist(Level::Trace, ConfigurationType::Format, "%datetime %level [%logger] [%func] [%loc] %log");
    }

    /// @brief Parser used internally to parse configurations from file or text.
    ///
    /// @detail This class makes use of base::utils::Str.
    /// You should not need this unless you are working on some tool for Easylogging++
    class Parser : private base::StaticClass {
    public:
        /// @brief Parses configuration from file.
        /// @param configurationFile Full path to configuration file
        /// @param sender Sender configurations pointer. Usually 'this' is used from calling class
        /// @param baseConfigurations to base new configuration repository off. This value is used when you want to use
        ///        existing Configurations to base all the values and then set rest of configuration via configuration file.
        /// @return True if successfully parsed, false otherwise. You may define '_STOP_ON_FIRST_ELPP_ASSERTION' to make sure you
        ///         do not proceed without successful parse.
        static bool parseFromFile(const std::string& configurationFile, Configurations* sender, Configurations* base = nullptr) {
            sender->setFromBase(base);
            std::ifstream fileStream_(configurationFile.c_str(), std::ifstream::in);
            ELPP_ASSERT(fileStream_.is_open(), "Unable to open configuration file [" << configurationFile << "] for parsing.");
            bool parsedSuccessfully = false;
            std::string line = std::string();
            Level currLevel = Level::Unknown;
            std::string currConfigStr = std::string();
            std::string currLevelStr = std::string();
            while (fileStream_.good()) {
                std::getline(fileStream_, line);
                parsedSuccessfully = parseLine(line, currConfigStr, currLevelStr, currLevel, sender);
                ELPP_ASSERT(parsedSuccessfully, "Unable to parse configuration line: " << line);
            }
            return parsedSuccessfully;
        }

        /// @brief Parse configurations from configuration string.
        ///
        /// @detail This configuration string has same syntax as configuration file contents. Make sure all the necessary
        /// new line characters are provided. You may define '_STOP_ON_FIRST_ELPP_ASSERTION' to make sure you
        /// do not proceed without successful parse (This is recommended)
        /// @param configurationsString
        /// @param sender Sender configurations pointer. Usually 'this' is used from calling class
        /// @return True if successfully parsed, false otherwise.
        static bool parseFromText(const std::string& configurationsString, Configurations* sender) {
            bool parsedSuccessfully = false;
            std::stringstream ss(configurationsString);
            std::string line = std::string();
            Level currLevel = Level::Unknown;
            std::string currConfigStr = std::string();
            std::string currLevelStr = std::string();
            while (std::getline(ss, line)) {
                parsedSuccessfully = parseLine(line, currConfigStr, currLevelStr, currLevel, sender);
                ELPP_ASSERT(parsedSuccessfully, "Unable to parse configuration line: " << line);
            }
            return parsedSuccessfully;
        }
    private:
        friend class el::Loggers;
        static void ignoreComments(std::string& line) {
            std::size_t foundAt = 0;
            std::size_t quotesStart = line.find("\"");
            std::size_t quotesEnd = std::string::npos;
            if (quotesStart != std::string::npos) {
                quotesEnd = line.find("\"", quotesStart + 1);
                while (quotesEnd != std::string::npos && line.at(quotesEnd - 1) == '\\') {
                    // Do not erase slash yet - we will erase it in parseLine(..) while loop
                    quotesEnd = line.find("\"", quotesEnd + 2);
                }
            }
            if ((foundAt = line.find(base::consts::kConfigurationComment)) != std::string::npos) {
                if (foundAt < quotesEnd) {
                    foundAt = line.find(base::consts::kConfigurationComment, quotesEnd + 1);
                }
                line = line.substr(0, foundAt);
            }
        }
        static inline bool isLevel(const std::string& line) {
            return base::utils::Str::startsWith(line, base::consts::kConfigurationLevel);
        }

        static inline bool isComment(const std::string& line) {
            return base::utils::Str::startsWith(line, base::consts::kConfigurationComment);
        }

        static inline bool isConfig(const std::string& line) {
            std::size_t assignment = line.find('=');
            return line != "" &&
                    (line[0] >= 65 || line[0] <= 90 || line[0] >= 97 || line[0] <= 122) &&
                    (assignment != std::string::npos) &&
                    (line.size() > assignment);
        }

        static bool parseLine(std::string& line, std::string& currConfigStr, std::string& currLevelStr, Level& currLevel, Configurations* conf) {
            ConfigurationType currConfig = ConfigurationType::Unknown;
            std::string currValue = std::string();
            line = base::utils::Str::trim(line);
            if (isComment(line)) return true;
            ignoreComments(line);
            line = base::utils::Str::trim(line);
            if (line == "") {
                // Comment ignored
                return true;
            }
            if (isLevel(line)) {
                if (line.size() <= 2) {
                    return true;
                }
                currLevelStr = line.substr(1, line.size() - 2);
                currLevelStr = base::utils::Str::toUpper(currLevelStr);
                currLevelStr = base::utils::Str::trim(currLevelStr);
                currLevel = LevelHelper::convertFromString(currLevelStr.c_str());
                return true;
            }
            if (isConfig(line)) {
                std::size_t assignment = line.find('=');
                currConfigStr = line.substr(0, assignment);
                currConfigStr = base::utils::Str::toUpper(currConfigStr);
                currConfigStr = base::utils::Str::trim(currConfigStr);
                currConfig = ConfigurationTypeHelper::convertFromString(currConfigStr.c_str());
                currValue = line.substr(assignment + 1);
                currValue = base::utils::Str::trim(currValue);
                std::size_t quotesStart = currValue.find("\"", 0);
                std::size_t quotesEnd = std::string::npos;
                if (quotesStart != std::string::npos) {
                    quotesEnd = currValue.find("\"", quotesStart + 1);
                    while (quotesEnd != std::string::npos && currValue.at(quotesEnd - 1) == '\\') {
                        currValue = currValue.erase(quotesEnd - 1, 1);
                        quotesEnd = currValue.find("\"", quotesEnd + 2);
                    }

                }
                if (quotesStart != std::string::npos && quotesEnd != std::string::npos) {
                    // Quote provided - check and strip if valid
                    ELPP_ASSERT((quotesStart < quotesEnd), "Configuration error - No ending quote found in [" << currConfigStr << "]");
                    ELPP_ASSERT((quotesStart + 1 != quotesEnd), "Empty configuration value for [" << currConfigStr << "]");
                    if ((quotesStart != quotesEnd) && (quotesStart + 1 != quotesEnd)) {
                        // Explicit check in case if assertion is disabled
                        currValue = currValue.substr(quotesStart + 1, quotesEnd - 1);
                    }
                }
            }
            ELPP_ASSERT(currLevel != Level::Unknown, "Unrecognized severity level [" << currLevelStr << "]");
            ELPP_ASSERT(currConfig != ConfigurationType::Unknown, "Unrecognized configuration [" << currConfigStr << "]");
            if (currLevel == Level::Unknown || currConfig == ConfigurationType::Unknown) {
                return false; // unrecognizable level or config
            }
            conf->set(currLevel, currConfig, currValue);
            return true;
        }
    };
private:
    std::string m_configurationFile;
    bool m_isFromFile;
    friend class el::Loggers;

    /// @brief Unsafely sets configuration if does not already exist
    void unsafeSetIfNotExist(const Level& level, const ConfigurationType& configurationType, const std::string& value) {
        Configuration* conf = RegistryWithPred<Configuration, Configuration::Predicate>::get(level, configurationType);
        if (conf == nullptr) {
            unsafeSet(level, configurationType, value);
        }
    }

    /// @brief Thread unsafe set
    void unsafeSet(const Level& level, const ConfigurationType& configurationType, const std::string& value) {
        Configuration* conf = RegistryWithPred<Configuration, Configuration::Predicate>::get(level, configurationType);
        if (conf == nullptr) {
            registerNew(new Configuration(level, configurationType, value));
        } else {
            conf->setValue(value);
        }
        if (level == Level::Global) {
            unsafeSetGlobally(configurationType, value, false);
        }
    }

    /// @brief Sets configurations for all levels including Level::Global if includeGlobalLevel is true
    /// @see Configurations::setGlobally(const ConfigurationType& configurationType, const std::string& value)
    void setGlobally(const ConfigurationType& configurationType, const std::string& value, bool includeGlobalLevel) {
        if (includeGlobalLevel) {
            set(Level::Global, configurationType, value);
        }
        unsigned short lIndex = LevelHelper::kMinValid;
        LevelHelper::forEachLevel(lIndex, [&](void) -> bool {
            set(LevelHelper::castFromInt(lIndex), configurationType, value);
            return false; // Do not break lambda function yet as we need to set all levels regardless
        });
    }

    /// @brief Sets configurations (Unsafely) for all levels including Level::Global if includeGlobalLevel is true
    /// @see Configurations::setGlobally(const ConfigurationType& configurationType, const std::string& value)
    void unsafeSetGlobally(const ConfigurationType& configurationType, const std::string& value, bool includeGlobalLevel) {
        if (includeGlobalLevel) {
            unsafeSet(Level::Global, configurationType, value);
        }
        unsigned short lIndex = LevelHelper::kMinValid;
        LevelHelper::forEachLevel(lIndex, [&](void) -> bool  {
            unsafeSet(LevelHelper::castFromInt(lIndex), configurationType, value);
            return false; // Do not break lambda function yet as we need to set all levels regardless
        });
    }
};

namespace base {
typedef std::map<std::string, std::shared_ptr<std::fstream>> LogStreamsReferenceMap;
class Writer;
class LogDispatcher;
/// @brief Configurations with data types.
///
/// @detail el::Configurations have string based values. This is whats used internally in order to read correct configurations.
/// This is to perform faster while writing logs using correct configurations.
///
/// This is thread safe and final class containing non-virtual destructor (means nothing should inherit this class)
class TypedConfigurations : public base::threading::ThreadSafe {
public:
    /// @brief Constructor to initialize (construct) the object off el::Configurations
    /// @param configurations Configurations pointer/reference to base this typed configurations off.
    /// @param logStreamsReference Use el::base::elStorage->registeredLoggers()->logStreamsReference()
    explicit TypedConfigurations(Configurations* configurations, base::LogStreamsReferenceMap* logStreamsReference) {
        m_configurations = configurations;
        m_logStreamsReference = logStreamsReference;
        build(m_configurations);
    }

    virtual ~TypedConfigurations(void) {
    }

    const Configurations* configurations(void) const {
        return m_configurations;
    }

    inline bool enabled(const Level& level) {
        return getConfigByVal<bool>(level, m_enabledMap, "enabled");
    }

    inline bool toFile(const Level& level) {
        return getConfigByVal<bool>(level, m_toFileMap, "toFile");
    }

    inline const std::string& filename(const Level& level) {
        return getConfigByRef<std::string>(level, m_filenameMap, "filename");
    }

    inline bool toStandardOutput(const Level& level) {
        return getConfigByVal<bool>(level, m_toStandardOutputMap, "toStandardOutput");
    }

    inline const base::LogFormat& logFormat(const Level& level) {
        return getConfigByRef<base::LogFormat>(level, m_logFormatMap, "logFormat");
    }

    inline unsigned int millisecondsWidth(const Level& level = Level::Global) {
        return getConfigByVal<unsigned int>(level, m_millisecondsWidthMap, "millisecondsWidth");
    }

    inline bool performanceTracking(const Level& level = Level::Global) {
        return getConfigByVal<bool>(level, m_performanceTrackingMap, "performanceTracking");
    }

    inline std::fstream* fileStream(const Level& level) {
        return getConfigByRef<std::shared_ptr<std::fstream>>(level, m_fileStreamMap, "fileStream").get();
    }

    inline std::size_t maxLogFileSize(const Level& level) {
        return getConfigByVal<std::size_t>(level, m_maxLogFileSizeMap, "maxLogFileSize");
    }

private:
    Configurations* m_configurations;
    std::map<Level, bool> m_enabledMap;
    std::map<Level, bool> m_toFileMap;
    std::map<Level, std::string> m_filenameMap;
    std::map<Level, bool> m_toStandardOutputMap;
    std::map<Level, base::LogFormat> m_logFormatMap;
    std::map<Level, unsigned int> m_millisecondsWidthMap;
    std::map<Level, bool> m_performanceTrackingMap;
    std::map<Level, std::shared_ptr<std::fstream>> m_fileStreamMap;
    std::map<Level, std::size_t> m_maxLogFileSizeMap;
    base::LogStreamsReferenceMap* m_logStreamsReference;
    friend class Writer;
    friend class LogDispatcher;

    template <typename Conf_T>
    inline Conf_T getConfigByVal(const Level& level, const std::map<Level, Conf_T>& confMap, const char* confName) {
        base::threading::lock_guard lock(mutex());
        return unsafeGetConfigByVal(level, confMap, confName); // This is not unsafe anymore - mutex locked in scope
    }

    template <typename Conf_T>
    inline Conf_T& getConfigByRef(const Level& level, std::map<Level, Conf_T>& confMap, const char* confName) {
        base::threading::lock_guard lock(mutex());
        return unsafeGetConfigByRef(level, confMap, confName); // This is not unsafe anymore - mutex locked in scope
    }

    template <typename Conf_T>
    inline Conf_T unsafeGetConfigByVal(const Level& level, const std::map<Level, Conf_T>& confMap, const char* confName) {
        _ELPP_UNUSED(confName);
        typename std::map<Level, Conf_T>::const_iterator it = confMap.find(level);
        if (it == confMap.end()) {
            try {
                return confMap.at(Level::Global);
            } catch (...) {
                ELPP_INTERNAL_ERROR("Unable to get configuration [" << confName << "] for level [" << LevelHelper::convertToString(level) << "]"
                        << std::endl << "Please ensure you have properly configured logger.", false);
                return Conf_T();
            }
        }
        return it->second;
    }

    template <typename Conf_T>
    inline Conf_T& unsafeGetConfigByRef(const Level& level, std::map<Level, Conf_T>& confMap, const char* confName) {
        _ELPP_UNUSED(confName);
        typename std::map<Level, Conf_T>::iterator it = confMap.find(level);
        if (it == confMap.end()) {
            try {
                return confMap.at(Level::Global);
            } catch (...) {
                ELPP_INTERNAL_ERROR("Unable to get configuration [" << confName << "] for level [" << LevelHelper::convertToString(level) << "]"
                        << std::endl << "Please ensure you have properly configured logger.", false);
            }
        }
        return it->second;
    }

    template <typename Conf_T>
    void setValue(const Level& level, const Conf_T& value, std::map<Level, Conf_T>& confMap, bool includeGlobalLevel = true) {
        // If map is empty and we are allowed to add into generic level (Level::Global), do it!
        if (confMap.empty() && includeGlobalLevel) {
            confMap.insert(std::make_pair(Level::Global, value));
            return;
        }
        // If same value exist in generic level already, dont add it to explicit level
        typename std::map<Level, Conf_T>::iterator it = confMap.find(Level::Global);
        if (it != confMap.end() && it->second == value) {
            return;
        }
        // Now make sure we dont double up values if we really need to add it to explicit level
        it = confMap.find(level);
        if (it == confMap.end()) {
            // Value not found for level, add new
            confMap.insert(std::make_pair(level, value));
        } else {
            // Value found, just update value
            confMap[level] = value;
        }
    }

    void build(Configurations* configurations) {
        base::threading::lock_guard lock(mutex());
        auto getBool = [] (std::string boolStr) -> bool { // Pass by value for trimming
            base::utils::Str::trim(boolStr);
            return (boolStr == "TRUE" || boolStr == "true" || boolStr == "1");
        };
        for (Configurations::const_iterator it = configurations->begin(); it != configurations->end(); ++it) {
            Configuration* conf = *it;
            // We cannot use switch on strong enums because Intel C++ dont support them yet
            if (conf->configurationType() == ConfigurationType::Enabled) {
                setValue(conf->level(), getBool(conf->value()), m_enabledMap);
            } else if (conf->configurationType() == ConfigurationType::ToFile) {
                setValue(conf->level(), getBool(conf->value()), m_toFileMap);
            } else if (conf->configurationType() == ConfigurationType::ToStandardOutput) {
                setValue(conf->level(), getBool(conf->value()), m_toStandardOutputMap);
            } else if (conf->configurationType() == ConfigurationType::Filename) {
                insertFile(conf->level(), conf->value());
            } else if (conf->configurationType() == ConfigurationType::Format) {
                setValue(conf->level(), LogFormat(conf->level(), conf->value()), m_logFormatMap);
            } else if (conf->configurationType() == ConfigurationType::MillisecondsWidth) {
                unsigned int msOffset;
                switch (static_cast<int>(getULong(conf->value()))) {
                case 3:
                    msOffset = 1000;
                    break;
                case 4:
                    msOffset = 100;
                    break;
                case 5:
                    msOffset = 10;
                    break;
                case 6:
                    msOffset = 1;
                    break;
                default:
                    msOffset = base::consts::kDefaultMillisecondsOffset;
                    break;
                }
                setValue(Level::Global, msOffset, m_millisecondsWidthMap);
            } else if (conf->configurationType() == ConfigurationType::PerformanceTracking) {
                setValue(Level::Global, getBool(conf->value()), m_performanceTrackingMap);
            } else if (conf->configurationType() == ConfigurationType::MaxLogFileSize) {
                setValue(conf->level(), static_cast<std::size_t>(getULong(conf->value())), m_maxLogFileSizeMap);
#if !defined(_ELPP_NO_DEFAULT_LOG_FILE)
                unsafeValidateFileRolling(conf->level(), base::defaultPreRollOutHandler); // This is not unsafe as mutex is locked in currect scope
#endif // !defined(_ELPP_NO_DEFAULT_LOG_FILE)
            }
        }
    }

    unsigned long getULong(std::string confVal) {
        bool valid = true;
        base::utils::Str::trim(confVal);
        valid = !confVal.empty() && std::find_if(confVal.begin(), confVal.end(),
                [](char c) { return !base::utils::Str::isDigit(c); }) == confVal.end();
        if (!valid) {
            valid = false;
            ELPP_ASSERT(valid, "Configuration value not a valid integer [" << confVal << "]");
            return 0;
        }
        return atol(confVal.c_str());
    }

    void insertFile(const Level& level, const std::string& fullFilename) {
        if (fullFilename.empty()) {
            std::cerr << "Could not load empty file for logging, please re-check your configurations for level ["
                    << LevelHelper::convertToString(level) << "]";
        }
        std::string filePath = base::utils::File::extractPathFromFilename(fullFilename, base::consts::kFilePathSeperator);
        if (filePath.size() < fullFilename.size()) {
            base::utils::File::createPath(filePath);
        }
        auto create = [&](const Level& level) {
            base::LogStreamsReferenceMap::iterator filestreamIter = m_logStreamsReference->find(fullFilename);
            if (filestreamIter == m_logStreamsReference->end()) {
                // We need a completely new stream, nothing to share with
                std::fstream* fs = base::utils::File::newFileStream(fullFilename);
                if (fs != nullptr) {
                    m_filenameMap.insert(std::make_pair(level, fullFilename));
                    m_fileStreamMap.insert(std::make_pair(level, std::shared_ptr<std::fstream>(fs)));
                    m_logStreamsReference->insert(std::make_pair(fullFilename, std::shared_ptr<std::fstream>(m_fileStreamMap.at(level))));
                }
                // else we already display error from File::newFileStream()
            } else {
                // Woops! we have an existing one, share it!
                m_filenameMap.insert(std::make_pair(level, filestreamIter->first));
                m_fileStreamMap.insert(std::make_pair(level, std::shared_ptr<std::fstream>(filestreamIter->second)));
            }
        };
        if (m_filenameMap.empty() && m_fileStreamMap.empty()) {
            // If we dont have file conf for any level, create it for Level::Global first
            create(Level::Global);
        } else {
            // Create a shared or new file stream depending on file path
            create(level);
        }
    }

    bool unsafeValidateFileRolling(const Level& level, const PreRollOutHandler& preRollOutHandler) {
        std::fstream* fs = unsafeGetConfigByRef(level, m_fileStreamMap, "fileStream").get();
        if (fs == nullptr) {
            return true;
        }
        std::size_t maxLogFileSize = unsafeGetConfigByVal(level, m_maxLogFileSizeMap, "maxLogFileSize");
        std::size_t currFileSize = base::utils::File::getSizeOfFile(fs);
        if (maxLogFileSize != 0 && currFileSize >= maxLogFileSize) {
            std::string fname = unsafeGetConfigByRef(level, m_filenameMap, "filename");
            ELPP_INTERNAL_INFO("Truncating log file [" << fname << "] as a result of configurations for level ["
                    << LevelHelper::convertToString(level) << "]");
            fs->close();
            preRollOutHandler(fname.c_str(), currFileSize);
            fs->open(fname, std::fstream::out | std::fstream::trunc);
            return true;
        }
        return false;
    }

    bool validateFileRolling(const Level& level, const PreRollOutHandler& preRollOutHandler) {
        base::threading::lock_guard lock(mutex());
        return unsafeValidateFileRolling(level, preRollOutHandler);
    }
};
/// @brief Class that keeps record of current line hit for occasional logging
class HitCounter {
public:
    HitCounter(void) :
        m_filename(""),
        m_lineNumber(0),
        m_hitCounts(0) {
    }

    HitCounter(const char* filename, unsigned long int lineNumber) :
        m_filename(filename),
        m_lineNumber(lineNumber),
        m_hitCounts(0) {
    }

    HitCounter(const HitCounter& hitCounter) :
        m_filename(hitCounter.m_filename),
        m_lineNumber(hitCounter.m_lineNumber),
        m_hitCounts(hitCounter.m_hitCounts) {
    }

    HitCounter& operator=(const HitCounter& hitCounter) {
        m_filename = hitCounter.m_filename;
        m_lineNumber = hitCounter.m_lineNumber;
        m_hitCounts = hitCounter.m_hitCounts;
        return *this;
    }

    virtual ~HitCounter(void) {
    }

    /// @brief Resets location of current hit counter
    inline void resetLocation(const char* filename, unsigned long int lineNumber) {
        m_filename = filename;
        m_lineNumber = lineNumber;
    }

    /// @brief Validates hit counts and resets it if necessary
    inline void validateHitCounts(std::size_t occasion) {
        if (m_hitCounts >= base::consts::kMaxLogPerCounter) {
            m_hitCounts = (occasion >= 1 ? base::consts::kMaxLogPerCounter % occasion : 0);
        }
        ++m_hitCounts;
    }

    inline const char* filename(void) const {
        return m_filename;
    }

    inline unsigned long int lineNumber(void) const {
        return m_lineNumber;
    }

    inline std::size_t hitCounts(void) const {
        return m_hitCounts;
    }

    class Predicate {
    public:
        Predicate(const char* filename, unsigned long int lineNumber)
            : m_filename(filename),
              m_lineNumber(lineNumber) {
        }
        inline bool operator()(const HitCounter* counter) {
            return ((counter != nullptr) &&
                    (strcmp(counter->m_filename, m_filename) == 0) &&
                    (counter->m_lineNumber == m_lineNumber));
        }
    private:
        const char* m_filename;
        unsigned long int m_lineNumber;
    };
private:
    const char* m_filename;
    unsigned long int m_lineNumber;
    std::size_t m_hitCounts;
};
/// @brief Repository for hit counters used across the application
class RegisteredHitCounters : public base::utils::RegistryWithPred<base::HitCounter, base::HitCounter::Predicate> {
public:
    /// @brief Validates counter, i.e, registers new if does not exist otherwise updates original one
    /// @return True if validation resulted in triggering hit. Meaning logs will be written everytime true is returned
    ///          and won't be written otherwise.
    bool validate(const char* filename, unsigned long int lineNumber, std::size_t occasion) {
        base::threading::lock_guard lock(mutex());
        base::HitCounter* counter = get(filename, lineNumber);
        if (counter == nullptr) {
            registerNew(counter = new base::HitCounter(filename, lineNumber));
        }
        counter->validateHitCounts(occasion);
        bool result = (occasion >= 1 && counter->hitCounts() != 0 && counter->hitCounts() % occasion == 0);
        return result;
    }

    /// @brief Gets hit counter registered at specified position
    inline const base::HitCounter* getCounter(const char* filename, unsigned long int lineNumber) {
        base::threading::lock_guard lock(mutex());
        return get(filename, lineNumber);
    }
};
class Storage;
class Trackable;
class LogDispatcher;
} // namespace base
/// @brief Represents a logger holding ID and configurations we need to write logs
///
/// @detail This class does not write logs itself instead its used by writer to read configuations from.
class Logger : public base::threading::ThreadSafe {
public:
    explicit Logger(const std::string& id, base::LogStreamsReferenceMap* logStreamsReference) :
            m_id(id),
            m_typedConfigurations(nullptr),
            m_parentApplicationName(std::string()),
            m_isConfigured(false),
            m_logStreamsReference(logStreamsReference) {
    }

    Logger(const std::string& id, const Configurations& configurations, base::LogStreamsReferenceMap* logStreamsReference) :
            m_id(id),
            m_typedConfigurations(nullptr),
            m_parentApplicationName(std::string()),
            m_isConfigured(false),
            m_logStreamsReference(logStreamsReference)  {
        configure(configurations);
    }

    Logger(const Logger& logger) {
        base::utils::safeDelete(m_typedConfigurations);
        m_id = logger.m_id;
        m_typedConfigurations = logger.m_typedConfigurations;
        m_parentApplicationName = logger.m_parentApplicationName;
        m_isConfigured = logger.m_isConfigured;
        m_configurations = logger.m_configurations;
        m_logStreamsReference = logger.m_logStreamsReference;
    }

    Logger& operator=(const Logger& logger) {
        base::utils::safeDelete(m_typedConfigurations);
        m_id = logger.m_id;
        m_typedConfigurations = logger.m_typedConfigurations;
        m_parentApplicationName = logger.m_parentApplicationName;
        m_isConfigured = logger.m_isConfigured;
        m_configurations = logger.m_configurations;
        m_logStreamsReference = logger.m_logStreamsReference;
        return *this;
    }

    virtual ~Logger(void) {
        base::utils::safeDelete(m_typedConfigurations);
    }

    friend std::ostream& operator<<(std::ostream& os, const Logger& logger) {
        os << logger.m_id;
        return os;
    }

    /// @brief Configures the logger using specified configurations.
    void configure(const Configurations& configurations) {
        base::threading::lock_guard lock(mutex());
        ELPP_INTERNAL_INFO("Configuring logger [" << id() << "] with configurations [\n" << configurations << "]");
        Configurations base = m_configurations;
        if (m_configurations != configurations) {
            m_configurations = configurations;
            base.setFromBase(const_cast<Configurations*>(&configurations));
        }
        base::utils::safeDelete(m_typedConfigurations);
        m_typedConfigurations = new base::TypedConfigurations(&base, m_logStreamsReference);
        m_isConfigured = true;
    }

    /// @brief Reconfigures logger using configurations previously provided.
    inline void reconfigure(void) {
        configure(m_configurations);
    }

    inline const std::string& id(void) const {
        return m_id;
    }

    inline const std::string& parentApplicationName(void) const {
        return m_parentApplicationName;
    }

    inline void setParentApplicationName(const std::string& parentApplicationName) {
        m_parentApplicationName = parentApplicationName;
    }

    inline Configurations* configurations(void) {
        return &m_configurations;
    }

    inline base::TypedConfigurations* typedConfigurations(void) {
        return m_typedConfigurations;
    }

    inline static bool isValidId(const std::string& id) {
        for (std::string::const_iterator it = id.begin(); it != id.end(); ++it) {
            if (!base::utils::Str::contains(base::consts::kValidLoggerIdSymbols, *it)) {
                return false;
            }
        }
        return true;
    }

private:
    std::string m_id;
    base::TypedConfigurations* m_typedConfigurations;
    std::stringstream m_stream;
    std::string m_parentApplicationName;
    bool m_isConfigured;
    Configurations m_configurations;
    base::LogStreamsReferenceMap* m_logStreamsReference;

    friend class base::LogDispatcher;
    friend class base::Writer;
    friend class el::Loggers;
    friend class el::Helpers;
    friend class base::Storage;
    friend class base::Trackable;

    Logger(void);

    inline std::stringstream& stream(void) {
        return m_stream;
    }

    inline Configurations& refConfigurations(void) {
        return m_configurations;
    }
};
class Helpers;
namespace base {
class Storage;
/// @brief Loggers repository
class RegisteredLoggers : public base::utils::Registry<Logger, std::string> {
public:
    RegisteredLoggers(void) {
        m_defaultConfigurations.setToDefault();
    }

    inline void setDefaultConfigurations(const Configurations& configurations) {
        base::threading::lock_guard lock(mutex());
        m_defaultConfigurations.setFromBase(const_cast<Configurations*>(&configurations));
    }

    Logger* get(const std::string& id, bool forceCreation = true) {
        base::threading::lock_guard lock(mutex());
        Logger* logger_ = base::utils::Registry<Logger, std::string>::get(id);
        if (logger_ == nullptr && forceCreation) {
            bool validId = Logger::isValidId(id);
            if (!validId) {
                ELPP_ASSERT(validId, "Invalid logger ID [" << id << "]. Not registering this logger.");
                return nullptr;
            }
            logger_ = new Logger(id, m_defaultConfigurations, &m_logStreamsReference);
            registerNew(id, logger_);
        }
        return logger_;
    }

    inline bool has(const std::string& id) {
        return get(id, false) != nullptr;
    }

    inline void unregister(Logger*& logger) {
        base::threading::lock_guard lock(mutex());
        base::utils::Registry<Logger, std::string>::unregister(logger->id());
    }

    inline LogStreamsReferenceMap* logStreamsReference(void) {
        return &m_logStreamsReference;
    }
private:
    Configurations m_defaultConfigurations;
    base::LogStreamsReferenceMap m_logStreamsReference;
    friend class base::Storage;
};
/// @brief Represents registries for verbose logging
class VRegistry : private base::NoCopy, public base::threading::ThreadSafe {
public:
    typedef int VLevel;

    explicit VRegistry(VLevel level) : m_level(level) {
    }

    /// @brief Sets verbose level. Accepted range is 0-9
    inline void setLevel(VLevel level) {
        base::threading::lock_guard lock(mutex());
        if (level < 0)
            m_level = 0;
        else if (level > 9)
            m_level = base::consts::kMaxVerboseLevel;
        else
            m_level = level;
    }

    inline VLevel level(void) const {
        return m_level;
    }

    void setModules(const char* modules) {
        base::threading::lock_guard lock(mutex());
#if !defined(_ELPP_DISABLE_VMODULES_EXTENSION)
        auto addSuffix = [](std::stringstream& ss, const char* sfx, const char* prev) {
            if (prev != nullptr && base::utils::Str::endsWith(ss.str(), prev)) {
                std::string chr(ss.str().substr(0, ss.str().size() - strlen(prev)));
                ss.str("");
                ss << chr;
            }
            if (base::utils::Str::endsWith(ss.str(), sfx)) {
                std::string chr(ss.str().substr(0, ss.str().size() - strlen(sfx)));
                ss.str("");
                ss << chr;
            }
            ss << sfx;
        };
#endif // !defined(_ELPP_DISABLE_VMODULES_EXTENSION)
        auto insert = [&](std::stringstream& ss, VLevel level) {
#if !defined(_ELPP_DISABLE_VMODULES_EXTENSION)
            addSuffix(ss, ".h", nullptr);
            m_modules.insert(std::make_pair(ss.str(), level));
            addSuffix(ss, ".c", ".h");
            m_modules.insert(std::make_pair(ss.str(), level));
            addSuffix(ss, ".cpp", ".c");
            m_modules.insert(std::make_pair(ss.str(), level));
            addSuffix(ss, ".cc", ".cpp");
            m_modules.insert(std::make_pair(ss.str(), level));
            addSuffix(ss, ".cxx", ".cc");
            m_modules.insert(std::make_pair(ss.str(), level));
            addSuffix(ss, ".-inl.h", ".cxx");
            m_modules.insert(std::make_pair(ss.str(), level));
            addSuffix(ss, ".hxx", ".-inl.h");
            m_modules.insert(std::make_pair(ss.str(), level));
            addSuffix(ss, ".hpp", ".hxx");
#endif // !defined(_ELPP_DISABLE_VMODULES_EXTENSION)
            m_modules.insert(std::make_pair(ss.str(), level));
        };
        bool isMod = true;
        bool isLevel = false;
        std::stringstream ss;
        int level = -1;
        for (; *modules; ++modules) {
            switch (*modules) {
            case '=':
                isLevel = true;
                isMod = false;
                break;
            case ',':
                isLevel = false;
                isMod = true;
                if (!ss.str().empty() && level != -1) {
                    insert(ss, level);
                    ss.str("");
                    level = -1;
                }
                break;
            default:
                if (isMod) {
                    ss << *modules;
                } else if (isLevel) {
                    if (isdigit(*modules)) {
                        level = static_cast<VLevel>(*modules) - 48;
                    }
                }
                break;
            }
        }
        if (!ss.str().empty() && level != -1) {
            insert(ss, level);
        }
    }

    bool allowed(VLevel vlevel, const char* file, unsigned int flags = 0x0) {
        base::threading::lock_guard lock(mutex());
        if (m_modules.empty() || file == nullptr) {
            return vlevel <= m_level;
        } else {
            std::map<std::string, VLevel>::iterator it = m_modules.begin();
            for (; it != m_modules.end(); ++it) {
                if (base::utils::Str::wildCardMatch(file, it->first.c_str())) {
                    return vlevel <= it->second;
                }
            }
            if (base::utils::hasFlag(LoggingFlag::AllowVerboseIfModuleNotSpecified, flags)) {
                return true;
            }
            return false;
        }
    }

    inline const std::map<std::string, VLevel>& modules(void) const {
        return m_modules;
    }

    void setFromArgs(const base::utils::CommandLineArgs* commandLineArgs) {
        if (commandLineArgs->hasParam("-v") || commandLineArgs->hasParam("--verbose") ||
            commandLineArgs->hasParam("-V") || commandLineArgs->hasParam("--VERBOSE")) {
            setLevel(base::consts::kMaxVerboseLevel);
        } else if (commandLineArgs->hasParamWithValue("--v")) {
            setLevel(atoi(commandLineArgs->getParamValue("--v")));
        } else if (commandLineArgs->hasParamWithValue("--V")) {
            setLevel(atoi(commandLineArgs->getParamValue("--V")));
        }
#if (!defined(_ELPP_DISABLE_VMODULES))
        else if (commandLineArgs->hasParamWithValue("-vmodule")) {
            setModules(commandLineArgs->getParamValue("-vmodule"));
        } else if (commandLineArgs->hasParamWithValue("-VMODULE")) {
            setModules(commandLineArgs->getParamValue("-VMODULE"));
        }
#endif // (!defined(_ELPP_DISABLE_VMODULES))
    }

private:
    VLevel m_level;
    std::map<std::string, VLevel> m_modules;
};
class LogMessage {
public:
    LogMessage(const Level& level, const char* file, unsigned long int line, const char* func,
                          VRegistry::VLevel verboseLevel, Logger* logger, std::string&& message) :
                  m_level(level), m_file(file), m_line(line), m_func(func),
                  m_verboseLevel(verboseLevel), m_logger(logger), m_message(std::move(message)) {
    }
    inline Level& level(void) { return m_level; }
    inline const char* file(void) { return m_file; }
    inline unsigned long int line(void) { return m_line; }
    inline const char* func(void) { return m_func; }
    inline VRegistry::VLevel verboseLevel(void) { return m_verboseLevel; }
    inline Logger* logger(void) { return m_logger; }
    inline std::string& message(void) { return m_message; }
private:
    Level m_level;
    const char* m_file;
    unsigned long int m_line;
    const char* m_func;
    VRegistry::VLevel m_verboseLevel;
    Logger* m_logger;
    std::string m_message;
};
/// @brief Contains all the storages that is needed by writer
///
/// @detail This is initialized when Easylogging++ is initialized and is used by Writer
class Storage : private base::NoCopy, public base::threading::ThreadSafe {
public:
    Storage(void) :
        m_username(base::utils::OS::currentUser()),
        m_hostname(base::utils::OS::currentHost()),
        m_registeredHitCounters(new base::RegisteredHitCounters()),
        m_registeredLoggers(new base::RegisteredLoggers()),
        m_vRegistry(new base::VRegistry(0)),
        m_flags(0x0),
        m_preRollOutHandler(base::defaultPreRollOutHandler) {

        // Register default logger
        m_registeredLoggers->get(std::string(base::consts::kDefaultLoggerId));

        // Register performance logger and reconfigure format
        Logger* performanceLogger = m_registeredLoggers->get(std::string(base::consts::kPerformanceLoggerId));
        performanceLogger->refConfigurations().setGlobally(ConfigurationType::Format, "%datetime %level %log");
        performanceLogger->reconfigure();

        // Register template helper test logger - see Helpers::convertTemplateToStdString(const T&)
        Logger* templateHelperLogger = m_registeredLoggers->get(std::string(base::consts::kInternalHelperLoggerId));
        templateHelperLogger->refConfigurations().setGlobally(ConfigurationType::Format, "[DO NOT USE THIS LOGGER '%logger']");
        templateHelperLogger->reconfigure();

        addFlag(LoggingFlag::AllowVerboseIfModuleNotSpecified);
        ELPP_INTERNAL_INFO("Easylogging++ has been initialized");
    }

    virtual ~Storage(void) {
        base::utils::safeDelete(m_registeredHitCounters);
        base::utils::safeDelete(m_registeredLoggers);
        base::utils::safeDelete(m_vRegistry);
    }

    inline bool validateCounter(const char* filename, unsigned long int lineNumber, std::size_t occasion) {
        return m_registeredHitCounters->validate(filename, lineNumber, occasion);
    }

    inline base::RegisteredHitCounters* hitCounters(void) const {
        return m_registeredHitCounters;
    }

    inline base::RegisteredLoggers* registeredLoggers(void) const {
        return m_registeredLoggers;
    }

    inline base::VRegistry* vRegistry(void) const {
        return m_vRegistry;
    }

    inline const base::utils::CommandLineArgs* commandLineArgs(void) const {
        return &m_commandLineArgs;
    }

    inline void addFlag(const LoggingFlag& flag) {
        base::utils::addFlag(flag, m_flags);
    }

    inline void removeFlag(const LoggingFlag& flag) {
        base::utils::removeFlag(flag, m_flags);
    }

    inline bool hasFlag(const LoggingFlag& flag) const {
        return base::utils::hasFlag(flag, m_flags) > 0;
    }

    inline unsigned short flags(void) const {
        return m_flags;
    }

    inline void setFlags(unsigned int flags) {
        m_flags = flags;
    }

    inline std::stringstream& tempStream(void) {
        return m_tempStream;
    }

    inline void setPreRollOutHandler(const PreRollOutHandler& handler) {
        m_preRollOutHandler = handler;
    }

    inline PreRollOutHandler& preRollOutHandler(void) {
        return m_preRollOutHandler;
    }
private:
    std::string m_username;
    std::string m_hostname;
    base::RegisteredHitCounters* m_registeredHitCounters;
    base::RegisteredLoggers* m_registeredLoggers;
    base::VRegistry* m_vRegistry;
    base::utils::CommandLineArgs m_commandLineArgs;
    unsigned short m_flags;
    PreRollOutHandler m_preRollOutHandler;
    std::stringstream m_tempStream;

    friend class base::LogDispatcher;
    friend class base::Writer;
    friend class el::Helpers;

    inline const std::string& username(void) const {
        return m_username;
    }

    inline const std::string& hostname(void) const {
        return m_hostname;
    }

    void setApplicationArguments(int argc, char** argv) {
        m_commandLineArgs.setArgs(argc, argv);
        m_vRegistry->setFromArgs(commandLineArgs());
    }

    inline void setApplicationArguments(int argc, const char** argv) {
        setApplicationArguments(argc, const_cast<char**>(argv));
    }
};
extern std::unique_ptr<base::Storage> elStorage;
/// @brief Dispatches log messages
class LogDispatcher : private base::NoCopy {
public:
    LogDispatcher(bool proceed, base::LogMessage&& log) :
        m_proceed(proceed),
        m_log(std::move(log)) {
    }

    void dispatch(bool needToLockLogger) {
        if (!m_proceed) {
            return;
        }
        // We minimize the time of elStorage's lock - this lock is released after log is written
        base::elStorage->lock();
        if (needToLockLogger) {
            m_log.logger()->lock();
        }
#if (defined(_ELPP_STRICT_SIZE_CHECK))
        m_log.logger()->m_typedConfigurations->validateFileRolling(m_log.level(), base::elStorage->preRollOutHandler());
#endif // (defined(_ELPP_STRICT_SIZE_CHECK))

        base::TypedConfigurations* tc = m_log.logger()->m_typedConfigurations;
        base::LogFormat* logFormat = const_cast<base::LogFormat*>(&tc->logFormat(m_log.level()));
        std::string logLine = logFormat->format();
        if (logFormat->hasFlag(base::FormatFlags::AppName)) {
          // App name
          base::utils::Str::replaceFirstWithEscape(logLine, base::consts::kAppNameFormatSpecifier,
                   m_log.logger()->parentApplicationName());
        }
        if (logFormat->hasFlag(base::FormatFlags::LoggerId)) {
          // Logger ID
          base::utils::Str::replaceFirstWithEscape(logLine, base::consts::kLoggerIdFormatSpecifier, m_log.logger()->id());
        }
        if (logFormat->hasFlag(base::FormatFlags::ThreadId)) {
          // Thread ID
          base::utils::Str::replaceFirstWithEscape(logLine, base::consts::kThreadIdFormatSpecifier,
                  base::threading::getCurrentThreadId());
        }
        if (logFormat->hasFlag(base::FormatFlags::DateTime)) {
          // DateTime
          base::utils::Str::replaceFirstWithEscape(logLine, base::consts::kDateTimeFormatSpecifier,
                  base::utils::DateTime::getDateTime(logFormat->dateTimeFormat().c_str(), tc->millisecondsWidth(m_log.level())));
        }
        if (logFormat->hasFlag(base::FormatFlags::Function)) {
          // Function
          base::utils::Str::replaceFirstWithEscape(logLine, base::consts::kLogFunctionFormatSpecifier, std::string(m_log.func()));
        }
        if (logFormat->hasFlag(base::FormatFlags::File)) {
          // File
          base::utils::Str::replaceFirstWithEscape(logLine, base::consts::kLogFileFormatSpecifier, std::string(m_log.file()));
        }
        if (logFormat->hasFlag(base::FormatFlags::Line)) {
          // Line
          base::elStorage->tempStream() << m_log.line();
          base::utils::Str::replaceFirstWithEscape(logLine, base::consts::kLogLineFormatSpecifier, base::elStorage->tempStream().str());
          base::elStorage->tempStream().str("");
        }
        if (logFormat->hasFlag(base::FormatFlags::Location)) {
          // Location
          base::elStorage->tempStream() << m_log.file() << ":" << m_log.line();
          base::utils::Str::replaceFirstWithEscape(logLine, base::consts::kLogLocationFormatSpecifier, base::elStorage->tempStream().str());
          base::elStorage->tempStream().str("");
        }
        if (logFormat->hasFlag(base::FormatFlags::User)) {
          // User
          base::utils::Str::replaceFirstWithEscape(logLine, base::consts::kCurrentUserFormatSpecifier, elStorage->username());
        }
        if (logFormat->hasFlag(base::FormatFlags::Host)) {
          // Host
          base::utils::Str::replaceFirstWithEscape(logLine, base::consts::kCurrentHostFormatSpecifier, elStorage->hostname());
        }
        if (m_log.level() == Level::Verbose &&
              logFormat->hasFlag(base::FormatFlags::VerboseLevel)) {
          // Verbose level
          base::elStorage->tempStream() << m_log.verboseLevel();
          base::utils::Str::replaceFirstWithEscape(logLine, base::consts::kVerboseLevelFormatSpecifier, base::elStorage->tempStream().str());
          base::elStorage->tempStream().str("");
        }
        if (logFormat->hasFlag(base::FormatFlags::LogMessage)) {
          // Log message
          base::utils::Str::replaceFirstWithEscape(logLine, base::consts::kMessageFormatSpecifier, m_log.message());
        }
        dispatch(logLine, needToLockLogger);
    }
private:
    bool m_proceed;
    base::LogMessage m_log;

    void dispatch(const std::string& logLine, bool needToUnlockLogger) {
        if (m_log.logger()->m_typedConfigurations->toFile(m_log.level())) {
            std::fstream* fs = m_log.logger()->m_typedConfigurations->fileStream(m_log.level());
            if (fs != nullptr) {
                *fs << logLine << std::endl;
                 if (fs->fail()) {
                    ELPP_INTERNAL_ERROR("Unable to write log to file [" << m_log.logger()->m_typedConfigurations->filename(m_log.level()) << "].\n"
                            << "Few possible reasons (could be something else):\n"
                            << "      * Permission denied\n"
                            << "      * Disk full\n"
                            << "      * Disk is not writable"
                            , true);
                }
            } else {
                ELPP_INTERNAL_ERROR("Log file has not been configured and TO_FILE is configured to TRUE.", false);
            }
        }
        base::elStorage->unlock();
        if (m_log.logger()->m_typedConfigurations->toStandardOutput(m_log.level())) {
            if (m_log.level() == Level::Error || m_log.level() == Level::Fatal) {
                std::cerr << logLine << std::endl;
            } else {
                std::cout << logLine << std::endl;
            }
        }
        if (needToUnlockLogger) {
            m_log.logger()->unlock();
        }
    }
};
#if defined(_ELPP_STL_LOGGING)
/// @brief Workarounds to write some STL logs
///
/// @detail There is workaround needed to loop through some stl containers. In order to do that, we need iterable containers
/// of same type and provide iterator interface and pass it on to writeIterator().
/// Remember, this is passed by value in constructor so that we dont change original containers.
/// This operation is as expensive as Big-O(std::min(class_.size(), base::consts::kMaxLogPerContainer))
namespace workarounds {
/// @brief Abstract IterableContainer template that provides interface for iterable classes of type T
template <typename T, typename Container>
class IterableContainer {
public:
    typedef typename Container::iterator iterator;
    typedef typename Container::const_iterator const_iterator;
    IterableContainer(void){}
    virtual ~IterableContainer(void) {}
    iterator begin(void) { return getContainer().begin(); }
    iterator end(void) { return getContainer().end(); }
private:
    virtual Container& getContainer(void) = 0;
};
/// @brief Implements IterableContainer and provides iterable std::priority_queue class
template<typename T, typename Container = std::vector<T>, typename Comparator = std::less<typename Container::value_type>>
class IterablePriorityQueue : public IterableContainer<T, Container>, public std::priority_queue<T, Container, Comparator> {
public:
    IterablePriorityQueue(std::priority_queue<T, Container, Comparator> queue_) {
        std::size_t count_ = 0;
        while (++count_ < base::consts::kMaxLogPerContainer && !queue_.empty()) {
            this->push(queue_.top());
            queue_.pop();
        }
    }
private:
    inline Container& getContainer(void) {
        return this->c;
    }
};
/// @brief Implements IterableContainer and provides iterable std::queue class
template<typename T, typename Container = std::deque<T>>
class IterableQueue : public IterableContainer<T, Container>, public std::queue<T, Container> {
public:
    IterableQueue(std::queue<T, Container> queue_) {
        std::size_t count_ = 0;
        while (++count_ < base::consts::kMaxLogPerContainer && !queue_.empty()) {
            this->push(queue_.front());
            queue_.pop();
        }
    }
private:
    inline Container& getContainer(void) {
        return this->c;
    }
};
/// @brief Implements IterableContainer and provides iterable std::stack class
template<typename T, typename Container = std::deque<T>>
class IterableStack : public IterableContainer<T, Container>, public std::stack<T, Container> {
public:
    IterableStack(std::stack<T, Container> stack_) {
        std::size_t count_ = 0;
        while (++count_ < base::consts::kMaxLogPerContainer && !stack_.empty()) {
            this->push(stack_.top());
            stack_.pop();
        }
    }
private:
    inline Container& getContainer(void) {
        return this->c;
    }
};
} // namespace workarounds
#endif // defined(_ELPP_STL_LOGGING)
/// @brief Writes nothing - Used when certain log is disabled
class NullWriter : private base::NoCopy {
public:
    NullWriter(void) {}

    template <typename T>
    inline NullWriter& operator<<(const T&) {
        return *this;
    }
};
/// @brief Main entry point of each logging
class Writer : private base::NoCopy {
public:
    Writer(const std::string& loggerId, const Level& level, const char* file, unsigned long int line,
               const char* func, VRegistry::VLevel verboseLevel = 0, bool skipDispatch = false) :
                   m_level(level), m_file(file), m_line(line), m_func(func), m_verboseLevel(verboseLevel),
                   m_proceed(true), m_skipDispatch(skipDispatch), m_containerLogSeperator("") {
        m_logger = elStorage->registeredLoggers()->get(loggerId, false);
        if (m_logger == nullptr) {
            if (!elStorage->registeredLoggers()->has(std::string(base::consts::kDefaultLoggerId))) {
                // Somehow default logger has been unregistered. Not good! Register again
                elStorage->registeredLoggers()->get(std::string(base::consts::kDefaultLoggerId));
            }
            Writer(el::base::consts::kDefaultLoggerId, Level::Error, file, line, func)
                    << "Logger [" << loggerId << "] is not registered yet!";
            m_proceed = false;
        } else {
            m_logger->lock(); // This should not be unlocked by checking m_proceed because
                              // m_proceed can be changed by lines below
            m_proceed = m_logger->m_typedConfigurations->enabled(level);
            m_containerLogSeperator = base::elStorage->hasFlag(LoggingFlag::NewLineForContainer) ? "\n    " : ", ";
        }
    }

    virtual ~Writer(void) {
        if (m_proceed && !m_skipDispatch) {
            base::LogDispatcher(m_proceed, base::LogMessage(m_level, m_file, m_line, m_func, m_verboseLevel,
                          m_logger, m_logger->stream().str())).dispatch(false);
        }
        if (m_logger != nullptr) {
            m_logger->stream().str("");
            m_logger->unlock();
        }
#if !defined(_ELPP_PREVENT_FATAL_ABORT)
        if (m_proceed && m_level == Level::Fatal) {
            exit(1);
        }
#endif // !defined(_ELPP_PREVENT_FATAL_ABORT)
    }

    inline Writer& operator<<(const std::string& log_) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << log_;
        return *this;
    }
    inline Writer& operator<<(char log_) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << log_;
        return *this;
    }
    inline Writer& operator<<(bool log_) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << log_;
        return *this;
    }
    inline Writer& operator<<(signed short log_) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << log_;
        return *this;
    }
    inline Writer& operator<<(unsigned short log_) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << log_;
        return *this;
    }
    inline Writer& operator<<(signed int log_) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << log_;
        return *this;
    }
    inline Writer& operator<<(unsigned int log_) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << log_;
        return *this;
    }
    inline Writer& operator<<(signed long log_) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << log_;
        return *this;
    }
    inline Writer& operator<<(unsigned long log_) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << log_;
        return *this;
    }
    inline Writer& operator<<(float log_) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << log_;
        return *this;
    }
    inline Writer& operator<<(double log_) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << log_;
        return *this;
    }
    inline Writer& operator<<(char* log_) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << log_;
        return *this;
    }
    inline Writer& operator<<(const char* log_) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << log_;
        return *this;
    }
    inline Writer& operator<<(const void* log_) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << log_;
        return *this;
    }
    inline Writer& operator<<(long double log_) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << log_;
        return *this;
    }
    inline Writer& operator<<(const std::wstring& log_) {
        if (!m_proceed) { return *this; }
        return operator<<(log_.c_str());
    }
    inline Writer& operator<<(const wchar_t* log_) {
        if (!m_proceed) { return *this; }
        if (log_ == nullptr) {
            m_logger->stream() << base::consts::kNullPointer;
            return *this;
        }
        std::size_t len_ = wcslen(log_) + 1;
        char* buff_ = (char*)malloc(len_ + 1);
#   if _ELPP_OS_UNIX || (_ELPP_OS_WINDOWS && !_ELPP_CRT_DBG_WARNINGS)
        std::wcstombs(buff_, log_, len_);
#   elif _ELPP_OS_WINDOWS
        std::size_t convCount_ = 0;
        mbstate_t mbState_;
        ::memset((void*)&mbState_, 0, sizeof(mbState_));
        wcsrtombs_s(&convCount_, buff_, len_, &log_, len_, &mbState_);
#   endif // _ELPP_OS_UNIX || (_ELPP_OS_WINDOWS && !_ELPP_CRT_DBG_WARNINGS)
        m_logger->stream() << buff_;
        free(buff_);
        return *this;
    }
    inline Writer& operator<<(const std::stringstream& ss) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << ss.str();
        return *this;
    }
    // ostream manipulators
    inline Writer& operator<<(std::ostream& (*OStreamMani)(std::ostream&)) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << OStreamMani;
        return *this;
    }
#define ELPP_ITERATOR_CONTAINER_LOG_ONE_ARG(temp)                                                    \
    template <typename T>                                                                            \
    inline Writer& operator<<(const temp<T>& template_inst) {                                        \
        if (!m_proceed) { return *this; }                                                            \
        return writeIterator(template_inst.begin(), template_inst.end(), template_inst.size());      \
    }
#define ELPP_ITERATOR_CONTAINER_LOG_TWO_ARG(temp)                                                    \
    template <typename T1, typename T2>                                                              \
    inline Writer& operator<<(const temp<T1, T2>& template_inst) {                                   \
        if (!m_proceed) { return *this; }                                                            \
        return writeIterator(template_inst.begin(), template_inst.end(), template_inst.size());      \
    }
#define ELPP_ITERATOR_CONTAINER_LOG_THREE_ARG(temp)                                                  \
    template <typename T1, typename T2, typename T3>                                                 \
    inline Writer& operator<<(const temp<T1, T2, T3>& template_inst) {                               \
        if (!m_proceed) { return *this; }                                                            \
        return writeIterator(template_inst.begin(), template_inst.end(), template_inst.size());      \
    }
#define ELPP_ITERATOR_CONTAINER_LOG_FOUR_ARG(temp)                                                   \
    template <typename T1, typename T2, typename T3, typename T4>                                    \
    inline Writer& operator<<(const temp<T1, T2, T3, T4>& template_inst) {                           \
        if (!m_proceed) { return *this; }                                                            \
        return writeIterator(template_inst.begin(), template_inst.end(), template_inst.size());      \
    }
#define ELPP_ITERATOR_CONTAINER_LOG_FIVE_ARG(temp)                                                   \
    template <typename T1, typename T2, typename T3, typename T4, typename T5>                       \
    inline Writer& operator<<(const temp<T1, T2, T3, T4, T5>& template_inst) {                       \
        if (!m_proceed) { return *this; }                                                            \
        return writeIterator(template_inst.begin(), template_inst.end(), template_inst.size());      \
    }

#if defined(_ELPP_STL_LOGGING)
    ELPP_ITERATOR_CONTAINER_LOG_TWO_ARG(std::vector)
    ELPP_ITERATOR_CONTAINER_LOG_TWO_ARG(std::list)
    ELPP_ITERATOR_CONTAINER_LOG_TWO_ARG(std::deque)
    ELPP_ITERATOR_CONTAINER_LOG_THREE_ARG(std::set)
    ELPP_ITERATOR_CONTAINER_LOG_THREE_ARG(std::multiset)
    ELPP_ITERATOR_CONTAINER_LOG_FOUR_ARG(std::map)
    ELPP_ITERATOR_CONTAINER_LOG_FOUR_ARG(std::multimap)
    template <class T, class Container>
    inline Writer& operator<<(const std::queue<T, Container>& queue_) {
        if (!m_proceed) { return *this; }
        base::workarounds::IterableQueue<T, Container> iterableQueue_ =
                static_cast<base::workarounds::IterableQueue<T, Container> >(queue_);
        return writeIterator(iterableQueue_.begin(), iterableQueue_.end(), iterableQueue_.size());
    }
    template <class T, class Container>
    inline Writer& operator<<(const std::stack<T, Container>& stack_) {
        if (!m_proceed) { return *this; }
        base::workarounds::IterableStack<T, Container> iterableStack_ =
                static_cast<base::workarounds::IterableStack<T, Container> >(stack_);
        return writeIterator(iterableStack_.begin(), iterableStack_.end(), iterableStack_.size());
    }
    template <class T, class Container, class Comparator>
    inline Writer& operator<<(const std::priority_queue<T, Container, Comparator>& priorityQueue_) {
        if (!m_proceed) { return *this; }
        base::workarounds::IterablePriorityQueue<T, Container, Comparator> iterablePriorityQueue_ =
                static_cast<base::workarounds::IterablePriorityQueue<T, Container, Comparator> >(priorityQueue_);
        return writeIterator(iterablePriorityQueue_.begin(), iterablePriorityQueue_.end(), iterablePriorityQueue_.size());
    }
    template <class First, class Second>
    inline Writer& operator<<(const std::pair<First, Second>& pair_) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << "(";
        operator << (static_cast<First>(pair_.first));
        m_logger->stream() << ", ";
        operator << (static_cast<Second>(pair_.second));
        m_logger->stream() << ")";
        return *this;
    }
    template <std::size_t Size>
    inline Writer& operator<<(const std::bitset<Size>& bitset_) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << "[";
        m_logger->stream() << bitset_.to_string();
        m_logger->stream() << "]";
        return *this;
    }
#   if defined(_ELPP_LOG_STD_ARRAY)
    template <class T, std::size_t Size>
    inline Writer& operator<<(const std::array<T, Size>& array) {
        if (!m_proceed) { return *this; }
        return writeIterator(array.begin(), array.end(), array.size());
    }
#   endif // defined(_ELPP_LOG_STD_ARRAY)
#   if defined(_ELPP_LOG_UNORDERED_MAP)
    ELPP_ITERATOR_CONTAINER_LOG_FIVE_ARG(std::unordered_map)
    ELPP_ITERATOR_CONTAINER_LOG_FIVE_ARG(std::unordered_multimap)
#   endif // defined(_ELPP_LOG_UNORDERED_MAP)
#   if defined(_ELPP_LOG_UNORDERED_SET)
    ELPP_ITERATOR_CONTAINER_LOG_FOUR_ARG(std::unordered_set)
    ELPP_ITERATOR_CONTAINER_LOG_FOUR_ARG(std::unordered_multiset)
#   endif // defined(_ELPP_LOG_UNORDERED_SET)
#endif // defined(_ELPP_STL_LOGGING)
#if defined(_ELPP_QT_LOGGING)
    inline Writer& operator<<(const QString& log_) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << log_.toStdString();
        return *this;
    }
    inline Writer& operator<<(const QByteArray& log_) {
        if (!m_proceed) { return *this; }
        return operator << (QString(log_));
    }
    inline Writer& operator<<(const QStringRef& log_) {
        if (!m_proceed) { return *this; }
        return operator<<(log_.toString());
    }
    inline Writer& operator<<(qint64 log_) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << QString::number(log_).toStdString();
        return *this;
    }
    inline Writer& operator<<(quint64 log_) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << QString::number(log_).toStdString();
        return *this;
    }
    inline Writer& operator<<(QChar log_) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << log_.toLatin1();
        return *this;
    }
    inline Writer& operator<<(const QLatin1String& log_) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << log_.latin1();
        return *this;
    }
    ELPP_ITERATOR_CONTAINER_LOG_ONE_ARG(QList)
    ELPP_ITERATOR_CONTAINER_LOG_ONE_ARG(QVector)
    ELPP_ITERATOR_CONTAINER_LOG_ONE_ARG(QQueue)
    ELPP_ITERATOR_CONTAINER_LOG_ONE_ARG(QSet)
    ELPP_ITERATOR_CONTAINER_LOG_ONE_ARG(QLinkedList)
    ELPP_ITERATOR_CONTAINER_LOG_ONE_ARG(QStack)
    template <typename First, typename Second>
    inline Writer& operator<<(const QPair<First, Second>& pair_) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << "(";
        operator << (static_cast<First>(pair_.first));
        m_logger->stream() << ", ";
        operator << (static_cast<Second>(pair_.second));
        m_logger->stream() << ")";
        return *this;
    }
    template <typename K, typename V>
    inline Writer& operator<<(const QMap<K, V>& map_) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << "[";
        QList<K> keys = map_.keys();
        typename QList<K>::const_iterator begin = keys.begin();
        typename QList<K>::const_iterator end = keys.end();
        int max_ = static_cast<int>(base::consts::kMaxLogPerContainer); // to prevent warning
        for (int index_ = 0; begin != end && index_ < max_; ++index_, ++begin) {
            m_logger->stream() << "(";
            operator << (static_cast<K>(*begin));
            m_logger->stream() << ", ";
            operator << (static_cast<V>(map_.value(*begin)));
            m_logger->stream() << ")";
            m_logger->stream() << ((index_ < keys.size() -1) ? m_containerLogSeperator : "");
        }
        if (begin != end) {
            m_logger->stream() << "...";
        }
        m_logger->stream() << "]";
        return *this;
    }
    template <typename K, typename V>
    inline Writer& operator<<(const QMultiMap<K, V>& map_) {
        if (!m_proceed) { return *this; }
        operator << (static_cast<QMap<K, V>>(map_));
        return *this;
    }
    template <typename K, typename V>
    inline Writer& operator<<(const QHash<K, V>& hash_) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << "[";
        QList<K> keys = hash_.keys();
        typename QList<K>::const_iterator begin = keys.begin();
        typename QList<K>::const_iterator end = keys.end();
        int max_ = static_cast<int>(base::consts::kMaxLogPerContainer); // prevent type warning
        for (int index_ = 0; begin != end && index_ < max_; ++index_, ++begin) {
            m_logger->stream() << "(";
            operator << (static_cast<K>(*begin));
            m_logger->stream() << ", ";
            operator << (static_cast<V>(hash_.value(*begin)));
            m_logger->stream() << ")";
            m_logger->stream() << ((index_ < keys.size() -1) ? m_containerLogSeperator : "");
        }
        if (begin != end) {
            m_logger->stream() << "...";
        }
        m_logger->stream() << "]";
        return *this;
    }
    template <typename K, typename V>
    inline Writer& operator<<(const QMultiHash<K, V>& multiHash_) {
        if (!m_proceed) { return *this; }
        operator << (static_cast<QHash<K, V>>(multiHash_));
        return *this;
    }
#endif // defined(_ELPP_QT_LOGGING)
#if defined(_ELPP_BOOST_LOGGING)
    ELPP_ITERATOR_CONTAINER_LOG_TWO_ARG(boost::container::vector)
    ELPP_ITERATOR_CONTAINER_LOG_TWO_ARG(boost::container::stable_vector)
    ELPP_ITERATOR_CONTAINER_LOG_TWO_ARG(boost::container::list)
    ELPP_ITERATOR_CONTAINER_LOG_TWO_ARG(boost::container::deque)
    ELPP_ITERATOR_CONTAINER_LOG_FOUR_ARG(boost::container::map)
    ELPP_ITERATOR_CONTAINER_LOG_FOUR_ARG(boost::container::flat_map)
    ELPP_ITERATOR_CONTAINER_LOG_THREE_ARG(boost::container::set)
    ELPP_ITERATOR_CONTAINER_LOG_THREE_ARG(boost::container::flat_set)
#endif // defined(_ELPP_BOOST_LOGGING)

/// @brief Macro used internally that can be used externally to make containers easylogging++ friendly
///
/// @detail This macro expands to write an ostream& operator<< for container. This container is expected to
///         have begin() and end() methods that return respective iterators
/// @param ContainerType Type of container e.g, MyList from WX_DECLARE_LIST(int, MyList); in wxwidgets
/// @param SizeMethod Method used to get size of container.
/// @param ElementInstance Instance of element to be fed out. Insance name is "elem". See WX_ELPP_ENABLED macro
///        for an example usage
#define MAKE_CONTAINER_ELPP_FRIENDLY(ContainerType, SizeMethod, ElementInstance) \
    std::ostream& operator<<(std::ostream& ss, const ContainerType& container) {\
        const char* sep = el::base::elStorage->hasFlag(el::LoggingFlag::NewLineForContainer) ? "\n    " : ", ";\
        ContainerType::const_iterator elem = container.begin();\
        ContainerType::const_iterator endElem = container.end();\
        std::size_t size_ = container.SizeMethod; \
        ss << "[";\
        for (std::size_t i = 0; elem != endElem && i < el::base::consts::kMaxLogPerContainer; ++i, ++elem) {\
            ss << ElementInstance;\
            ss << ((i < size_ - 1) ? sep : "");\
        }\
        if (elem != endElem) {\
            ss << "...";\
        }\
        ss << "]";\
        return ss;\
    }
#if defined(_ELPP_WXWIDGETS_LOGGING)
    ELPP_ITERATOR_CONTAINER_LOG_ONE_ARG(wxVector)
#   define ELPP_WX_PTR_ENABLED(ContainerType) MAKE_CONTAINER_ELPP_FRIENDLY(ContainerType, size(), *(*elem))
#   define ELPP_WX_ENABLED(ContainerType) MAKE_CONTAINER_ELPP_FRIENDLY(ContainerType, size(), (*elem))
#   define ELPP_WX_HASH_MAP_ENABLED(ContainerType) MAKE_CONTAINER_ELPP_FRIENDLY(ContainerType, size(), \
        "(" << elem->first << ", " << elem->second << ")")
#else
#   define ELPP_WX_PTR_ENABLED(ContainerType)
#   define ELPP_WX_ENABLED(ContainerType)
#   define ELPP_WX_HASH_MAP_ENABLED(ContainerType)
#endif // defined(_ELPP_WXWIDGETS_LOGGING)
    template <class Class>
    inline Writer& operator<<(const Class& class_) {
        if (!m_proceed) { return *this; }
        m_logger->stream() << class_;
        return *this;
    }
#undef ELPP_ITERATOR_CONTAINER_LOG_ONE_ARG
#undef ELPP_ITERATOR_CONTAINER_LOG_TWO_ARG
#undef ELPP_ITERATOR_CONTAINER_LOG_THREE_ARG
#undef ELPP_ITERATOR_CONTAINER_LOG_FOUR_ARG
#undef ELPP_ITERATOR_CONTAINER_LOG_FIVE_ARG
private:
    Level m_level;
    const char* m_file;
    const unsigned long int m_line;
    const char* m_func;
    VRegistry::VLevel m_verboseLevel;
    Logger* m_logger;
    bool m_proceed;
    bool m_skipDispatch;
    const char* m_containerLogSeperator;
    friend class el::Helpers;

    template<class Iterator>
    inline Writer& writeIterator(Iterator begin_, Iterator end_, std::size_t size_) {
        m_logger->stream() << "[";
        for (std::size_t i = 0; begin_ != end_ && i < base::consts::kMaxLogPerContainer; ++i, ++begin_) {
            operator << (*begin_);
            m_logger->stream() << ((i < size_ - 1) ? m_containerLogSeperator : "");
         }
        if (begin_ != end_) {
            m_logger->stream() << "...";
        }
        m_logger->stream() << "]";
        return *this;
    }
};
#define _ELPP_WRITE_LOG(loggerId, level) el::base::Writer(loggerId, level, __FILE__, __LINE__, _ELPP_FUNC)
#define _ELPP_WRITE_LOG_IF(condition, loggerId, level) if (condition) \
    el::base::Writer(loggerId, level, __FILE__, __LINE__, _ELPP_FUNC)
#define _ELPP_WRITE_LOG_EVERY_N(occasion, loggerId, level) if (el::base::elStorage->validateCounter(__FILE__, __LINE__, occasion)) \
    el::base::Writer(loggerId, level, __FILE__, __LINE__, _ELPP_FUNC)

/// @brief Represents trackable block of code that conditionally adds performance status to log
///        either when goes outside the scope of when checkpoint() is called
class Trackable : private base::NoCopy, public base::threading::ThreadSafe {
public:
    Trackable(const char* blockName,
            const base::TimestampUnit& timestampUnit = base::TimestampUnit::Millisecond,
            const char* logger = base::consts::kPerformanceLoggerId, bool scopedLog = true, const Level& level = Level::Info) :
        m_blockName(blockName), m_timestampUnit(timestampUnit), m_loggerId(logger), m_scopedLog(scopedLog),
        m_level(level), m_hasChecked(false), m_lastCheckpointId(nullptr), m_enabled(false) {
#if !defined(_ELPP_DISABLE_PERFORMANCE_TRACKING)
        el::Logger* loggerPtr = elStorage->registeredLoggers()->get(logger, false);
        m_enabled = loggerPtr != nullptr;
        // We store it locally so that if user happen to change configuration by the end of scope
        // or before calling checkpoint, we still depend on state of configuraton at time of construction
        m_enabled = m_enabled && loggerPtr->m_typedConfigurations->performanceTracking(m_level);
        if (m_enabled) {
            base::utils::DateTime::gettimeofday(&m_startTime);
        }
#endif // !defined(_ELPP_DISABLE_PERFORMANCE_TRACKING)
    }
    virtual ~Trackable(void) {
#if !defined(_ELPP_DISABLE_PERFORMANCE_TRACKING)
        if (m_enabled) {
            base::threading::lock_guard lock(mutex());
            if (m_scopedLog) {
                base::utils::DateTime::gettimeofday(&m_endTime);
                _ELPP_WRITE_LOG(m_loggerId, m_level) << "Executed [" << m_blockName << "] in [" << *this << "]";
            }
        }
#endif // !defined(_ELPP_DISABLE_PERFORMANCE_TRACKING)
    }
    /// @brief A checkpoint for current trackable block.
    void checkpoint(const char* id = nullptr, const char* file = __FILE__, unsigned long int line = __LINE__, const char* func = "") {
#if !defined(_ELPP_DISABLE_PERFORMANCE_TRACKING)
        if (m_enabled) {
            base::threading::lock_guard lock(mutex());
            base::utils::DateTime::gettimeofday(&m_endTime);
            std::stringstream ss;
            ss << "Performance checkpoint";
            if (id != nullptr) {
                ss << " [" << id << "]";
            }
            ss << " for block [" << m_blockName << "] : [" << *this;
#   if !defined(_ELPP_PERFORMANCE_DISABLE_COMPARE_CHECKPOINTS)
            if (m_hasChecked) {
                ss << " (["
                   << base::utils::DateTime::formatTime(base::utils::DateTime::getTimeDifference(m_endTime, m_lastCheckpointTime,
                                  m_timestampUnit), m_timestampUnit) << "]"
                    << " from ";
                if (m_lastCheckpointId == nullptr) {
                    ss << "last checkpoint";
                } else {
                    ss << "checkpoint '" << m_lastCheckpointId << "'";
                }
                ss << ")]";
            } else {
                ss << "]";
            }
#   else
         ss << "]";
#   endif // defined(_ELPP_PERFORMANCE_DISABLE_COMPARE_CHECKPOINTS)
            base::utils::DateTime::gettimeofday(&m_lastCheckpointTime);
            m_hasChecked = true;
            m_lastCheckpointId = id;
            el::base::Writer(m_loggerId, m_level, file, line, func) << ss;
        }
#else
        _ELPP_UNUSED(id)
#endif // !defined(_ELPP_DISABLE_PERFORMANCE_TRACKING)
    }
private:
    const char* m_blockName;
    base::TimestampUnit m_timestampUnit;
    const char* m_loggerId;
    bool m_scopedLog;
    el::Level m_level;
    struct timeval m_startTime, m_endTime, m_lastCheckpointTime;
    bool m_hasChecked;
    const char* m_lastCheckpointId;
    bool m_enabled;
    Trackable(void);

    friend std::ostream& operator<<(std::ostream& os, const Trackable& trackable) {
        os << base::utils::DateTime::formatTime(base::utils::DateTime::getTimeDifference(trackable.m_endTime,
                trackable.m_startTime, trackable.m_timestampUnit), trackable.m_timestampUnit);
        return os;
    }
};
/// @brief Contains some internal debugging tools like crash handler and stack tracer
namespace debug {
class StackTrace : private base::NoCopy {
public:
    static const std::size_t kMaxStack = 64;
    static const std::size_t kStackStart = 2; // We want to skip c'tor and StackTrace::generateNew()
    class StackTraceEntry {
    public:
        StackTraceEntry(std::size_t index, const char* loc, const char* demang, const char* hex, const char* addr) {
            m_index = index;
            m_location = std::string(loc);
            m_demangled = std::string(demang);
            m_hex = std::string(hex);
            m_addr = std::string(addr);
        }
        StackTraceEntry(std::size_t index, char* loc) {
            m_index = index;
            m_location = std::string(loc);
        }
        std::size_t m_index;
        std::string m_location;
        std::string m_demangled;
        std::string m_hex;
        std::string m_addr;
        friend std::ostream& operator<<(std::ostream& ss, const StackTraceEntry& si) {
           ss << "[" << si.m_index << "] " << si.m_location << (si.m_demangled.empty() ? "" : ":") << si.m_demangled
                   << (si.m_hex.empty() ? "" : "+") << si.m_hex << si.m_addr;
           return ss;
        }
    private:
        StackTraceEntry(void);
    };

    StackTrace(void) {
        generateNew();
    }

    ~StackTrace(void) {
    }

    inline std::vector<StackTraceEntry>& getLatestStack(void) {
        return m_stack;
    }

    friend inline std::ostream& operator<<(std::ostream& os, const StackTrace& st) {
       std::vector<StackTraceEntry>::const_iterator it = st.m_stack.begin();
       while (it != st.m_stack.end()) {
           os << "    " << *it++ << "\n";
       }
       return os;
    }
private:
    std::vector<StackTraceEntry> m_stack;

    void generateNew(void) {
#if _ELPP_STACKTRACE
        m_stack.clear();
        void* stack[kMaxStack];
        std::size_t size = backtrace(stack, kMaxStack);
        char** strings = backtrace_symbols (stack, size);
        if (size > kStackStart) { // Skip StackTrace c'tor and generateNew
            for (std::size_t i = kStackStart; i < size; ++i) {
                char* mangName = nullptr;
                char* hex = nullptr;
                char* addr = nullptr;
                for (char* c = strings[i]; *c; ++c) {
                    switch (*c) {
                    case '(':
                        mangName = c;
                        break;
                    case '+':
                        hex = c;
                        break;
                    case ')':
                        addr = c;
                        break;
                    }
                }
                // Perform demangling if parsed properly
                if (mangName != nullptr && hex != nullptr && addr != nullptr && mangName < hex) {
                    *mangName++ = '\0';
                    *hex++ = '\0';
                    *addr++ = '\0';
                    int status = 0;
                    char* demangName = abi::__cxa_demangle(mangName, 0, 0, &status);
                    // if demangling is successful, output the demangled function name
                    if (status == 0) {
                        // Success (see http://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.3/a01696.html)
                        StackTraceEntry entry(i - 1, strings[i], demangName, hex, addr);
                        m_stack.push_back(entry);
                    }
                    else {
                        // Not successful - we will use mangled name
                        StackTraceEntry entry(i - 1, strings[i], mangName, hex, addr);
                        m_stack.push_back(entry);
                    }
                    free(demangName);
                } else {
                    StackTraceEntry entry(i - 1, strings[i]);
                    m_stack.push_back(entry);
                }
            }
        }
        free(strings);
#else
        ELPP_INTERNAL_INFO("Stacktrace generation not supported for selected compiler");
#endif // _ELPP_STACKTRACE
    }
};
/// @brief Logs reason of crash from sig
static void logCrashReason(int sig, bool stackTraceIfAvailable, const Level& level, const char* logger) {
    std::stringstream ss;
    ss << "CRASH HANDLED; ";
    bool foundReason = false;
    for (int i = 0; i < base::consts::kMaxCrashSignals; ++i) {
        if (base::consts::kCrashSignals[i].numb == sig) {
            ss << "Application has crashed due to [" <<
                  base::consts::kCrashSignals[i].name <<
                  "] signal";
            if (base::elStorage->hasFlag(el::LoggingFlag::LogDetailedCrashReason)) {
                ss << std::endl <<
                      "    " << base::consts::kCrashSignals[i].brief << std::endl <<
                      "    " << base::consts::kCrashSignals[i].detail;
                }
            foundReason = true;
        }
    }
    if (!foundReason) {
        ss << "Application has crashed due to unknown signal [" << sig << "]";
    }
#if _ELPP_STACKTRACE
    if (stackTraceIfAvailable) {
        ss << std::endl << "    ======= Backtrace: =========" << std::endl << base::debug::StackTrace();
    }
#else
    _ELPP_UNUSED(stackTraceIfAvailable)
#endif // _ELPP_STACKTRACE
    _ELPP_WRITE_LOG(logger, level) << ss.str();
}
/// @brief Aborts application due to crash signal
static void crashAbort(int sig) {
#if defined(_ELPP_COMPILER_MSVC) && defined(_M_IX86) && defined(_DEBUG)
    // Ignore msvc critical error dialog - break instead (on debug mode)
    _ELPP_UNUSED(sig)
    _asm int 3
#else
    exit(sig);
#endif
}
/// @brief Default application crash handler
///
/// @detail This function writes log using 'default' logger, prints stack trace for GCC based compilers and exits program.
static void defaultCrashHandler(int sig) {
    logCrashReason(sig, true, Level::Fatal, base::consts::kDefaultLoggerId);
    crashAbort(sig);
}
/// @brief Handles unexpected crashes
class CrashHandler : private base::NoCopy {
public:
    typedef void (*Handler)(int);

    CrashHandler(bool useDefault) {
        if (useDefault) {
            setHandler(defaultCrashHandler);
        }
    }
    CrashHandler(const Handler& cHandler) {
        setHandler(cHandler);
    }
    void setHandler(const Handler& cHandler) {
        m_handler = cHandler;
#if defined(_ELPP_HANDLE_SIGABRT)
            int i = 0; // SIGABRT is at base::consts::kCrashSignals[0]
#else
            int i = 1;
#endif // defined(_ELPP_HANDLE_SIGABRT)
        for (; i < base::consts::kMaxCrashSignals; ++i) {
            m_handler = signal(base::consts::kCrashSignals[i].numb, cHandler);
        }
    }
private:
    Handler m_handler;
};
} // namespace debug
} // namespace base
extern base::debug::CrashHandler elCrashHandler;
#define MAKE_LOGGABLE(ClassType, ClassInstance, OutputStreamInstance) \
    std::ostream& operator<<(std::ostream& OutputStreamInstance, const ClassType& ClassInstance)

/// @brief Base of Easylogging++ friendly class
///
/// @detail After inheriting this class publicly, implement pure-virtual function `void log(std::ostream&) const`
class Loggable {
public:
    virtual void log(std::ostream&) const = 0;
private:
    friend inline std::ostream& operator<<(std::ostream& os, const Loggable& loggable) {
        loggable.log(os);
        return os;
    }
};
/// @brief Static helpers for developers
class Helpers : private base::StaticClass {
public:
    /// @brief Sets application arguments and figures out whats active for logging and whats not.
    static inline void setArgs(int argc, char** argv) {
        base::elStorage->setApplicationArguments(argc, argv);
    }
    /// @copydoc setArgs(int argc, char** argv)
    static inline void setArgs(int argc, const char** argv) {
        base::elStorage->setApplicationArguments(argc, const_cast<char**>(argv));
    }
    /// @brief Adds logging flag used internally.
    /// @see el::LoggingFlag
    static inline void addFlag(const el::LoggingFlag& flag) {
        base::elStorage->addFlag(flag);
    }
    /// @brief Removes logging flag used internally.
    /// @see el::LoggingFlag
    static inline void removeFlag(const el::LoggingFlag& flag) {
        base::elStorage->removeFlag(flag);
    }
    /// @brief Determines whether or not certain flag is active
    /// @see el::LoggingFlag
    static inline bool hasFlag(const el::LoggingFlag& flag) {
        return base::elStorage->hasFlag(flag);
    }
    /// @brief Overrides default crash handler and installs custom handler.
    /// @param crashHandler A functor with no return type that takes single int argument.
    ///        Handler is a typedef with specification: void (*Handler)(int)
    static inline void setCrashHandler(const el::base::debug::CrashHandler::Handler& crashHandler) {
        el::elCrashHandler.setHandler(crashHandler);
    }
    /// @brief Abort due to crash with signal in parameter
    /// @param sig Crash signal
    static inline void crashAbort(int sig) {
        el::base::debug::crashAbort(sig);
    }
    /// @brief Logs reason of crash as per sig
    /// @param sig Crash signal
    /// @param stackTraceIfAvailable Includes stack trace if available
    /// @param level Logging level
    /// @param logger Logger to use for logging
    static void logCrashReason(int sig, bool stackTraceIfAvailable = false, const Level& level = Level::Fatal, const char* logger = base::consts::kDefaultLoggerId) {
        el::base::debug::logCrashReason(sig, stackTraceIfAvailable, level, logger);
    }
    /// @brief Installs pre rollout handler, this handler is triggered when log file is about to be rolled out (can be useful for backing up)
    static void installPreRollOutHandler(const base::PreRollOutHandler& handler) {
        base::elStorage->setPreRollOutHandler(handler);
    }
    /// @brief Converts template to std::string - useful for loggable classes to log containers within log(std::ostream&) const
    template <typename T>
    static inline std::string convertTemplateToStdString(const T& templ) {
        base::elStorage->registeredLoggers()->get(el::base::consts::kInternalHelperLoggerId, true);
        el::base::Writer w(el::base::consts::kInternalHelperLoggerId, el::Level::Unknown, "", 0, "", 0, true);
        w << templ;
        return w.m_logger->stream().str();
    }
    /// @brief Returns command line arguments (pointer) provided to easylogging++
    static inline const el::base::utils::CommandLineArgs* commandLineArgs(void) {
        return base::elStorage->commandLineArgs();
    }
};
/// @brief Static helpers to deal with loggers and their configurations
class Loggers : private base::StaticClass {
public:
    /// @brief Gets existing or registers new logger
    static inline Logger* getLogger(const std::string& identity, bool registerIfNotAvailable = true) {
        return base::elStorage->registeredLoggers()->get(identity, registerIfNotAvailable);
    }
    /// @brief Whether or not logger with id is registered
    static inline bool hasLogger(const std::string& identity) {
        return base::elStorage->registeredLoggers()->has(identity);
    }
    /// @brief Reconfigures specified logger with new configurations
    static inline Logger* reconfigureLogger(Logger* logger, const Configurations& configurations) {
        if (!logger) return nullptr;
        logger->configure(configurations);
        return logger;
    }
    /// @brief Reconfigures logger with new configurations after looking it up using identity
    static inline Logger* reconfigureLogger(const std::string& identity, Configurations& configurations) {
        Logger* logger = Loggers::getLogger(identity);
        Loggers::reconfigureLogger(logger, configurations);
        return logger;
    }
    /// @brief Reconfigures all the existing loggers with new configurations
    static inline void reconfigureAllLoggers(Configurations& configurations) {
        for (base::RegisteredLoggers::iterator it = base::elStorage->registeredLoggers()->begin();
                it != base::elStorage->registeredLoggers()->end(); ++it) {
            Loggers::reconfigureLogger(it->second, configurations);
        }
    }
    /// @brief Reconfigures single configuration for all the loggers
    static inline void reconfigureAllLoggers(const ConfigurationType& configurationType, const std::string& value) {
        reconfigureAllLoggers(Level::Global, configurationType, value);
    }
    ///@brief Reconfigures single configuration for all the loggers for specified level
    static inline void reconfigureAllLoggers(const Level& level, const ConfigurationType& configurationType, const std::string& value) {
        for (base::RegisteredLoggers::iterator it = base::elStorage->registeredLoggers()->begin();
                it != base::elStorage->registeredLoggers()->end(); ++it) {
            Logger* logger = it->second;
            logger->refConfigurations().set(level, configurationType, value);
            logger->reconfigure();
        }
    }
    /// @brief Sets default configurations. This configuration is used for future (and conditionally for existing) loggers
    static inline void setDefaultConfigurations(Configurations& configurations, bool reconfigureExistingLoggers = false) {
        base::elStorage->registeredLoggers()->setDefaultConfigurations(configurations);
        if (reconfigureExistingLoggers) {
            Loggers::reconfigureAllLoggers(configurations);
        }
    }
    /// @brief Populates all logger IDs in current repository.
    /// @param [out] targetList List of fill up.
    static inline std::vector<std::string>& populateAllLoggerIds(std::vector<std::string>& targetList) {
        targetList.clear();
        for (base::RegisteredLoggers::iterator it = base::elStorage->registeredLoggers()->list().begin();
                it != base::elStorage->registeredLoggers()->list().end(); ++it) {
            targetList.push_back(it->first);
        }
        return targetList;
    }
    /// @brief Sets configurations from global configuration file.
    static void configureFromGlobal(const char* globalConfigurationFilePath) {
        std::ifstream gcfStream(globalConfigurationFilePath, std::ifstream::in);
        ELPP_ASSERT(gcfStream.is_open(), "Unable to open global configuration file [" << globalConfigurationFilePath << "] for parsing.");
        std::string line = std::string();
        std::stringstream ss;
        Logger* logger = nullptr;
        auto configure = [&](void) {
            ELPP_INTERNAL_INFO("Configuring logger: '" << logger->id() << "' with configurations \n" << ss.str() << "\n--------------");
            Configurations c;
            c.parseFromText(ss.str());
            logger->configure(c);
        };
        while (gcfStream.good()) {
           std::getline(gcfStream, line);
           ELPP_INTERNAL_INFO("Parsing line: " << line);
           base::utils::Str::trim(line);
           if (Configurations::Parser::isComment(line)) continue;
           Configurations::Parser::ignoreComments(line);
           base::utils::Str::trim(line);
           if (line.size() > 2 && base::utils::Str::startsWith(line, base::consts::kConfigurationLoggerId)) {
               if (!ss.str().empty() && logger != nullptr) {
                   configure();
               }
               ss.str("");
               line = line.substr(2);
               base::utils::Str::trim(line);
               if (line.size() > 1) {
                   ELPP_INTERNAL_INFO("Getting logger: '" << line << "'");
                   logger = getLogger(line);
               }
            } else {
               ss << line << "\n";
            }
        }
        if (!ss.str().empty() && logger != nullptr) {
            configure();
        }
    }
    /// @brief Configures loggers using command line arg. Ensure you have already set command line args, see Helpers::setArgs(..)
    /// @return False if invalid argument or argument with no value provided, true if attempted to configure logger. If true is returned
    ///         that does not mean it has been configured successfully, it only means that it has attempeted to configure logger using configuration
    ///         file provided in argument
    static inline bool configureFromArg(const char* argKey) {
#if defined(_ELPP_DISABLE_CONFIGURATION_FROM_PROGRAM_ARGS)
        _ELPP_UNUSED(argKey);
#else
        if (!Helpers::commandLineArgs()->hasParamWithValue(argKey)) {
            ELPP_INTERNAL_ERROR("Unable to configure from argKey [" << argKey << "]. Argument value not found in program arguments: " << *Helpers::commandLineArgs(), false);
            return false;
        }
        configureFromGlobal(Helpers::commandLineArgs()->getParamValue(argKey));
#endif // defined(_ELPP_DISABLE_CONFIGURATION_FROM_PROGRAM_ARGS)
        return true;
    }
};
class VersionInfo : private base::StaticClass {
public:
    /// @brief Minimal formatted displayable information
    static inline const std::string formattedInfo(void) {
        std::stringstream ss;
        ss << "Easylogging++ v" << version() << " (" << releaseDate() << ")";
        ss << std::endl;
        ss << supportEmail();
        ss << std::endl;
        ss << website();
        ss << std::endl;
        ss << copyright();
        return ss.str();
    }

    /// @brief Current version number
    static inline const std::string version(void) { return std::string("9.20"); }

    /// @brief Release date of current version
    static inline const std::string releaseDate(void) { return std::string("27-09-2013 1800hrs"); }

    /// @brief Original author and maintainer
    static inline const std::string author(void) { return std::string("Majid Khan"); }

    /// @brief Support email
    static inline const std::string supportEmail(void) { return std::string("support@easylogging.org"); }

    /// @brief Web link
    static inline const std::string website(void) { return std::string("http://easylogging.org/"); }

    /// @brief Link to source code
    static inline const std::string sourceCodeLink(void) { return std::string("https://github.com/easylogging/easyloggingpp"); }

    /// @brief Copyright information
    static inline const std::string copyright(void) { return std::string("Copyright (c) 2013 Majid Khan"); }

    /// @brief Full licence
    static const std::string licence(void) {
        std::stringstream ss;
        ss << "The MIT License (MIT)" << std::endl;
        ss << copyright() << std::endl;
        ss << website() << std::endl;
        ss << "   Permission is hereby granted, free of charge, to any person obtaining" << std::endl;
        ss << "   a copy of this software and associated documentation files (the" << std::endl;
        ss << "   \"Software\"), to deal in the Software without restriction, including" << std::endl;
        ss << "   without limitation the rights to use, copy, modify, merge, publish," << std::endl;
        ss << "   distribute, sublicense, and/or sell copies of the Software, and to" << std::endl;
        ss << "   permit persons to whom the Software is furnished to do so, subject to" << std::endl;
        ss << "   the following conditions:" << std::endl;
        ss << std::endl;
        ss << "   The above copyright notice and this permission notice shall be" << std::endl;
        ss << "   included in all copies or substantial portions of the Software." << std::endl;
        ss << std::endl;
        ss << "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND," << std::endl;
        ss << "EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF" << std::endl;
        ss << "MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND" << std::endl;
        ss << "NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE" << std::endl;
        ss << "LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION" << std::endl;
        ss << "OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION" << std::endl;
        ss << "WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE" << std::endl;
        return ss.str();
    }
};
} // namespace el
#undef VLOG_IS_ON
/// @brief Determines whether verbose logging is on for specified level current file.
#define VLOG_IS_ON(verboseLevel) (el::base::elStorage->vRegistry()->allowed(verboseLevel, __FILE__, el::base::elStorage->flags()))
#undef TIMED_BLOCK
#undef TIMED_FUNC
#undef _ELPP_MIN_UNIT
#if defined(_ELPP_PERFORMANCE_MICROSECONDS)
#   define _ELPP_MIN_UNIT el::base::TimestampUnit::Microsecond
#else
#   define _ELPP_MIN_UNIT el::base::TimestampUnit::Millisecond
#endif // (defined(_ELPP_PERFORMANCE_MICROSECONDS))
/// @brief Performance tracked block. Performance gets written when goes out of scope using
///        'performance' logger.
///
/// @detail Please note in order to check the performance at a certain time you can use obj.checkpoint();
/// @see el::base::Trackable
/// @see el::base::Trackable::checkpoint
// Note: Do not surround this definition with null macro because of obj instance
#define TIMED_BLOCK(obj, blockname) el::base::Trackable obj(blockname, _ELPP_MIN_UNIT)
/// @brief Performance tracked function. Performance gets written when goes out of scope using
///        'performance' logger.
///
/// @detail Please note in order to check the performance at a certain time you can use obj.checkpoint();
/// @see el::base::Trackable
/// @see el::base::Trackable::checkpoint
#define TIMED_FUNC(obj) TIMED_BLOCK(obj, _ELPP_FUNC)
#undef PERFORMANCE_CHECKPOINT
#undef PERFORMANCE_CHECKPOINT_WITH_ID
#define PERFORMANCE_CHECKPOINT(obj) obj.checkpoint(nullptr, __FILE__, __LINE__, _ELPP_FUNC)
#define PERFORMANCE_CHECKPOINT_WITH_ID(obj, id) obj.checkpoint(id, __FILE__, __LINE__, _ELPP_FUNC)
#undef ELPP_COUNTER
#undef ELPP_COUNTER_POS
/// @brief Gets hit counter for file/line
#define ELPP_COUNTER (el::base::elStorage->hitCounters()->getCounter(__FILE__, __LINE__))
/// @brief Gets hit counter position for file/line, -1 if not registered yet
#define ELPP_COUNTER_POS (ELPP_COUNTER == nullptr ? -1 : ELPP_COUNTER->hitCounts())
// Undef levels to support LOG(LEVEL)
#undef INFO
#undef WARNING
#undef DEBUG
#undef ERROR
#undef FATAL
#undef TRACE
#undef VERBOSE
// Undef existing
#undef CINFO
#undef CWARNING
#undef CDEBUG
#undef CFATAL
#undef CERROR
#undef CTRACE
#undef CVERBOSE
#undef CINFO_IF
#undef CWARNING_IF
#undef CDEBUG_IF
#undef CERROR_IF
#undef CFATAL_IF
#undef CTRACE_IF
#undef CVERBOSE_IF
#undef CINFO_EVERY_N
#undef CWARNING_EVERY_N
#undef CDEBUG_EVERY_N
#undef CERROR_EVERY_N
#undef CFATAL_EVERY_N
#undef CTRACE_EVERY_N
#undef CVERBOSE_EVERY_N
// Normal logs
#if _ELPP_INFO_LOG
#   define CINFO(loggerId) _ELPP_WRITE_LOG(loggerId, el::Level::Info)
#else
#   define CINFO(loggerId) el::base::NullWriter()
#endif // _ELPP_INFO_LOG
#if _ELPP_WARNING_LOG
#   define CWARNING(loggerId) _ELPP_WRITE_LOG(loggerId, el::Level::Warning)
#else
#   define CWARNING(loggerId) el::base::NullWriter()
#endif // _ELPP_WARNING_LOG
#if _ELPP_DEBUG_LOG
#   define CDEBUG(loggerId) _ELPP_WRITE_LOG(loggerId, el::Level::Debug)
#else
#   define CDEBUG(loggerId) el::base::NullWriter()
#endif // _ELPP_DEBUG_LOG
#if _ELPP_ERROR_LOG
#   define CERROR(loggerId) _ELPP_WRITE_LOG(loggerId, el::Level::Error)
#else
#   define CERROR(loggerId) el::base::NullWriter()
#endif // _ELPP_ERROR_LOG
#if _ELPP_FATAL_LOG
#   define CFATAL(loggerId) _ELPP_WRITE_LOG(loggerId, el::Level::Fatal)
#else
#   define CFATAL(loggerId) el::base::NullWriter()
#endif // _ELPP_FATAL_LOG
#if _ELPP_TRACE_LOG
#   define CTRACE(loggerId) _ELPP_WRITE_LOG(loggerId, el::Level::Trace)
#else
#   define CTRACE(loggerId) el::base::NullWriter()
#endif // _ELPP_TRACE_LOG
#if _ELPP_VERBOSE_LOG
#   define CVERBOSE(vlevel, loggerId) if (VLOG_IS_ON(vlevel)) el::base::Writer(loggerId, \
       el::Level::Verbose, __FILE__, __LINE__, _ELPP_FUNC, vlevel)
#else
#   define CVERBOSE(vlevel, loggerId) el::base::NullWriter()
#endif // _ELPP_VERBOSE_LOG
// Conditional logs
#if _ELPP_INFO_LOG
#   define CINFO_IF(condition_, loggerId) _ELPP_WRITE_LOG_IF((condition_), loggerId, el::Level::Info)
#else
#   define CINFO_IF(condition_, loggerId) el::base::NullWriter()
#endif // _ELPP_INFO_LOG
#if _ELPP_WARNING_LOG
#   define CWARNING_IF(condition_, loggerId) _ELPP_WRITE_LOG_IF((condition_), loggerId, el::Level::Warning)
#else
#   define CWARNING_IF(condition_, loggerId) el::base::NullWriter()
#endif // _ELPP_WARNING_LOG
#if _ELPP_DEBUG_LOG
#   define CDEBUG_IF(condition_, loggerId) _ELPP_WRITE_LOG_IF((condition_), loggerId, el::Level::Debug)
#else
#   define CDEBUG_IF(condition_, loggerId) el::base::NullWriter()
#endif // _ELPP_DEBUG_LOG
#if _ELPP_ERROR_LOG
#   define CERROR_IF(condition_, loggerId) _ELPP_WRITE_LOG_IF((condition_), loggerId, el::Level::Error)
#else
#   define CERROR_IF(condition_, loggerId) el::base::NullWriter()
#endif // _ELPP_ERROR_LOG
#if _ELPP_FATAL_LOG
#   define CFATAL_IF(condition_, loggerId) _ELPP_WRITE_LOG_IF((condition_), loggerId, el::Level::Fatal)
#else
#   define CFATAL_IF(condition_, loggerId) el::base::NullWriter()
#endif // _ELPP_FATAL_LOG
#if _ELPP_TRACE_LOG
#   define CTRACE_IF(condition_, loggerId) _ELPP_WRITE_LOG_IF((condition_), loggerId, el::Level::Trace)
#else
#   define CTRACE_IF(condition_, loggerId) el::base::NullWriter()
#endif // _ELPP_TRACE_LOG
#if _ELPP_VERBOSE_LOG
#   define CVERBOSE_IF(condition_, vlevel, loggerId) if (VLOG_IS_ON(vlevel) && (condition_)) el::base::Writer(loggerId, \
       el::Level::Verbose, __FILE__, __LINE__, _ELPP_FUNC, vlevel)
#else
#   define CVERBOSE_IF(condition_, vlevel, loggerId) el::base::NullWriter()
#endif // _ELPP_VERBOSE_LOG
// Interval logs
#if _ELPP_INFO_LOG
#   define CINFO_EVERY_N(occasion, loggerId) _ELPP_WRITE_LOG_EVERY_N(occasion, loggerId, el::Level::Info)
#else
#   define CINFO_EVERY_N(occasion, loggerId) el::base::NullWriter()
#endif // _ELPP_INFO_LOG
#if _ELPP_WARNING_LOG
#   define CWARNING_EVERY_N(occasion, loggerId) _ELPP_WRITE_LOG_EVERY_N(occasion, loggerId, el::Level::Warning)
#else
#   define CWARNING_EVERY_N(occasion, loggerId) el::base::NullWriter()
#endif // _ELPP_WARNING_LOG
#if _ELPP_DEBUG_LOG
#   define CDEBUG_EVERY_N(occasion, loggerId) _ELPP_WRITE_LOG_EVERY_N(occasion, loggerId, el::Level::Debug)
#else
#   define CDEBUG_EVERY_N(occasion, loggerId) el::base::NullWriter()
#endif // _ELPP_DEBUG_LOG
#if _ELPP_ERROR_LOG
#   define CERROR_EVERY_N(occasion, loggerId) _ELPP_WRITE_LOG_EVERY_N(occasion, loggerId, el::Level::Error)
#else
#   define CERROR_EVERY_N(occasion, loggerId) el::base::NullWriter()
#endif // _ELPP_ERROR_LOG
#if _ELPP_FATAL_LOG
#   define CFATAL_EVERY_N(occasion, loggerId) _ELPP_WRITE_LOG_EVERY_N(occasion, loggerId, el::Level::Fatal)
#else
#   define CFATAL_EVERY_N(occasion, loggerId) el::base::NullWriter()
#endif // _ELPP_FATAL_LOG
#if _ELPP_TRACE_LOG
#   define CTRACE_EVERY_N(occasion, loggerId) _ELPP_WRITE_LOG_EVERY_N(occasion, loggerId, el::Level::Trace)
#else
#   define CTRACE_EVERY_N(occasion, loggerId) el::base::NullWriter()
#endif // _ELPP_TRACE_LOG
#if _ELPP_VERBOSE_LOG
#   define CVERBOSE_EVERY_N(occasion, vlevel, loggerId) VLOG_IF(el::base::elStorage->validateCounter(__FILE__, __LINE__, occasion), vlevel)
#else
#   define CVERBOSE_EVERY_N(occasion, vlevel, loggerId) el::base::NullWriter()
#endif // _ELPP_VERBOSE_LOG
//
// Custom Loggers - Requires (level, loggerId)
//
// undef existing
#undef CLOG
#undef CLOG_VERBOSE
#undef CVLOG
#undef CLOG_IF
#undef CLOG_VERBOSE_IF
#undef CVLOG_IF
#undef CLOG_EVERY_N
#undef CLOG_VERBOSE_EVERY_N
#undef CVLOG_EVERY_N
// Normal logs
#define CLOG(LEVEL, loggerId) C##LEVEL(loggerId)
#define CVLOG(vlevel, loggerId) CVERBOSE(vlevel, loggerId)
// Conditional logs
#define CLOG_IF(condition, LEVEL, loggerId) C##LEVEL##_IF(condition, loggerId)
#define CVLOG_IF(condition, vlevel, loggerId) CVERBOSE_IF(condition, vlevel, loggerId)
// Interval logs
#define CLOG_EVERY_N(n, LEVEL, loggerId) C##LEVEL##_EVERY_N(n, loggerId)
#define CVLOG_EVERY_N(n, vlevel, loggerId) CVERBOSE_EVERY_N(n, vlevel, loggerId)
//
// Default Loggers macro using CLOG(), CLOG_VERBOSE() and CVLOG() macros
//
// undef existing
#undef LOG
#undef VLOG
#undef LOG_IF
#undef VLOG_IF
#undef LOG_EVERY_N
#undef VLOG_EVERY_N
// Normal logs
#define LOG(LEVEL) CLOG(LEVEL, el::base::consts::kDefaultLoggerId)
#define VLOG(vlevel) CVLOG(vlevel, el::base::consts::kDefaultLoggerId)
// Conditional logs
#define LOG_IF(condition, LEVEL) CLOG_IF(condition, LEVEL, el::base::consts::kDefaultLoggerId)
#define VLOG_IF(condition, vlevel) CVLOG_IF(condition, vlevel, el::base::consts::kDefaultLoggerId)
// Interval logs
#define LOG_EVERY_N(n, LEVEL) CLOG_EVERY_N(n, LEVEL, el::base::consts::kDefaultLoggerId)
#define VLOG_EVERY_N(n, vlevel) CVLOG_EVERY_N(n, vlevel, el::base::consts::kDefaultLoggerId)
//
// Custom Debug Only Loggers - Requires (level, loggerId)
//
// undef existing
#undef DCLOG
#undef DCVLOG
#undef DCLOG_IF
#undef DCVLOG_IF
#undef DCLOG_EVERY_N
#undef DCVLOG_EVERY_N
// Normal logs
#define DCLOG(LEVEL, loggerId) if (_ELPP_DEBUG_LOG) CLOG(LEVEL, loggerId)
#define DCLOG_VERBOSE(vlevel, loggerId) if (_ELPP_DEBUG_LOG) CLOG_VERBOSE(vlevel, loggerId)
#define DCVLOG(vlevel, loggerId) if (_ELPP_DEBUG_LOG) CVLOG(vlevel, loggerId)
// Conditional logs
#define DCLOG_IF(condition, LEVEL, loggerId) if (_ELPP_DEBUG_LOG) CLOG_IF(condition, LEVEL, loggerId)
#define DCVLOG_IF(condition, vlevel, loggerId) if (_ELPP_DEBUG_LOG) CVLOG_IF(condition, vlevel, loggerId)
// Interval logs
#define DCLOG_EVERY_N(n, LEVEL, loggerId) if (_ELPP_DEBUG_LOG) CLOG_EVERY_N(n, LEVEL, loggerId)
#define DCVLOG_EVERY_N(n, vlevel, loggerId) if (_ELPP_DEBUG_LOG) CVLOG_EVERY_N(n, vlevel, loggerId)
//
// Default Debug Only Loggers macro using CLOG(), CLOG_VERBOSE() and CVLOG() macros
//
// undef existing
#undef DLOG
#undef DVLOG
#undef DLOG_IF
#undef DVLOG_IF
#undef DLOG_EVERY_N
#undef DVLOG_EVERY_N
// Normal logs
#define DLOG(LEVEL) DCLOG(LEVEL, el::base::consts::kDefaultLoggerId)
#define DVLOG(vlevel) DCVLOG(vlevel, el::base::consts::kDefaultLoggerId)
// Conditional logs
#define DLOG_IF(condition, LEVEL) DCLOG_IF(condition, LEVEL, el::base::consts::kDefaultLoggerId)
#define DVLOG_IF(condition, vlevel) DCVLOG_IF(condition, vlevel, el::base::consts::kDefaultLoggerId)
// Interval logs
#define DLOG_EVERY_N(n, LEVEL) DCLOG_EVERY_N(n, LEVEL, el::base::consts::kDefaultLoggerId)
#define DVLOG_EVERY_N(n, vlevel) DCVLOG_EVERY_N(n, vlevel, el::base::consts::kDefaultLoggerId)
// Check macros
#undef CHECK
#undef CHECK_EQ
#undef CHECK_NE
#undef CHECK_NOTNULL
#undef CHECK_STRCASEEQ
#undef CHECK_STRCASENE
#define CHECK(condition) LOG_IF(!(condition), FATAL) << "Check failed: [" << #condition << "] "
#define CHECK_EQ(a, b) CHECK(a == b)
#define CHECK_NE(a, b) CHECK(a != b)
namespace el {
namespace base {
namespace utils {
template <typename T>
static T* CheckNotNull(T* ptr, const char* name) {
    LOG_IF(ptr == nullptr, FATAL) << "Check failed: [" << name << " != nullptr]";
    return ptr;
}
} // namespace utils
} // namespace base
} // namespace el
#define CHECK_NOTNULL(ptr) el::base::utils::CheckNotNull(ptr, #ptr)
#define CHECK_STREQ(str1, str2) LOG_IF(!el::base::utils::Str::cStringEq(str1, str2), FATAL) \
                        << "Check failed: [" << #str1 << " == " << #str2 << "] "
#define CHECK_STRNE(str1, str2) LOG_IF(el::base::utils::Str::cStringEq(str1, str2), FATAL) \
                        << "Check failed: [" << #str1 << " != " << #str2 << "] "
#define CHECK_STRCASEEQ(str1, str2) LOG_IF(!el::base::utils::Str::cStringCaseEq(str1, str2), FATAL) \
                        << "Check failed: [" << #str1 << " == " << #str2 << "] "
#define CHECK_STRCASENE(str1, str2) LOG_IF(el::base::utils::Str::cStringCaseEq(str1, str2), FATAL) \
                        << "Check failed: [" << #str1 << " != " << #str2 << "] "
#undef DCHECK
#undef DCHECK_EQ
#undef DCHECK_NE
#undef DCHECK_NOTNULL
#undef DCHECK_STRCASEEQ
#undef DCHECK_STRCASENE
#define DCHECK(condition) if (_ELPP_DEBUG_LOG) CHECK(condition)
#define DCHECK_EQ(a, b) if (_ELPP_DEBUG_LOG) CHECK_EQ(a, b)
#define DCHECK_NE(a, b) if (_ELPP_DEBUG_LOG) CHECK_NE(a, b)
#define DCHECK_NULLPTR(ptr) if (_ELPP_DEBUG_LOG) CHECK_NOTNULL(ptr)
#define DCHECK_STREQ(str1, str2) if (_ELPP_DEBUG_LOG) CHECK_STREQ(str1, str2)
#define DCHECK_STRNE(str1, str2) if (_ELPP_DEBUG_LOG) CHECK_STRNE(str1, str2)
#define DCHECK_STRCASEEQ(str1, str2) if (_ELPP_DEBUG_LOG) CHECK_STRCASEEQ(str1, str2)
#define DCHECK_STRCASENE(str1, str2) if (_ELPP_DEBUG_LOG) CHECK_STRCASENE(str1, str2)
#if defined(_ELPP_DISABLE_DEFAULT_CRASH_HANDLING)
#   define _ELPP_USE_DEF_CRASH_HANDLER false
#else
#   define _ELPP_USE_DEF_CRASH_HANDLER true
#endif // defined(_ELPP_DISABLE_DEFAULT_CRASH_HANDLING)
#define _INITIALIZE_EASYLOGGINGPP \
    namespace el {                \
        namespace base {          \
            std::unique_ptr<base::Storage> elStorage(new base::Storage());       \
        }                                                                        \
        base::debug::CrashHandler elCrashHandler(_ELPP_USE_DEF_CRASH_HANDLER);   \
    }
#define _START_EASYLOGGINGPP(argc, argv) el::Helpers::setArgs(argc, argv)
// For minimal backward compatibility
namespace easyloggingpp = el;
#endif // EASYLOGGINGPP_H
