#pragma once

#include <ospf/config.hpp>
#include <ospf/log/interface.hpp>
#include <sstream>

namespace ospf
{
    inline namespace log
    {
        template<
            LoggerMultiThread mt = OSPF_BASE_MULTI_THREAD,
            CharType CharT = char
        >
        class StringLogger
            : public log_detail::LoggerImpl<mt, CharT, FileLogger<mt, CharT>>
        {
        private:
            std::basic_ostringstream<CharT> _sout;
            LogRecord::Writer _writer;
        };

        template<
            LogLevel lowest_level = default_log_level,
            LoggerMultiThread mt = OSPF_BASE_MULTI_THREAD,
            CharType CharT = char
        >
        class StaticStringLogger
            : public log_detail::StaticLoggerImpl<lowest_level, mt, CharT, FileLogger<mt, CharT>>
        {
        private:
            std::basic_ostringstream<CharT> _sout;
            LogRecord::Writer _writer;
        };
    };
};
