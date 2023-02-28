#pragma once

#include <ospf/config.hpp>
#include <ospf/log/interface.hpp>

namespace ospf
{
    inline namespace log
    {
        template<
            LoggerMultiThread mt = OSPF_BASE_MULTI_THREAD,
            CharType CharT = char
        >
        class ConsoleLogger
            : public log_detail::LoggerImpl<mt, CharT, FileLogger<mt, CharT>>
        {
        private:
            Ref<std::basic_ostream<CharT>> _os;
            LogRecord::Writer _writer;
        };

        template<
            LogLevel lowest_level = default_log_level,
            LoggerMultiThread mt = OSPF_BASE_MULTI_THREAD,
            CharType CharT = char
        >
        class StaticConsoleLogger
            : public log_detail::StaticLoggerImpl<lowest_level, mt, CharT, FileLogger<mt, CharT>>
        {
        private:
            Ref<std::basic_ostream<CharT>> _os;
            LogRecord::Writer _writer;
        };
    };
};
