#pragma once

#include <ospf/error.hpp>
#include <ospf/log/multi_thread_impl.hpp>
#include <ospf/log/record.hpp>
#include <ospf/meta_programming/crtp.hpp>
#include <ospf/meta_programming/named_flag.hpp>
#include <ospf/meta_programming/variable_type_list.hpp>
#include <ospf/type_family.hpp>

namespace ospf
{
    inline namespace log
    {
        OSPF_NAMED_FLAG(LoggerMultiThread);

        template<CharType CharT = char>
        class LoggerInterface
        {
        public:
            using CharType = CharT;
            using RecoredType = LogRecord<CharT>;
            using StringType = std::basic_string<CharT>;
            using StringViewType = std::basic_string_view<CharT>;

        public:
            LoggerInterface(const LogLevel lowest_level)
                : _lowest_level(lowest_level) {}
            LoggerInterface(const LoggerInterface& ano) = delete;
            LoggerInterface(LoggerInterface&& ano) noexcept = default;
            LoggerInterface& operator=(const LoggerInterface& rhs) = delete;
            LoggerInterface& operator=(LoggerInterface&& rhs) = delete;
            ~LoggerInterface(void) noexcept = default;

        public:
            inline const LogLevel lowest_level(void) const noexcept
            {
                return _lowest_level;
            }

        public:
            inline void log(void) noexcept
            {
                write(StringType{});
            }

            inline void log(StringType message) noexcept
            {
                write(std::move(message));
            }

        public:
            inline void log(const LogLevel level, StringType message) noexcept
            {
                if (level >= _lowest_level)
                {
                    log(recored(level, std::move(message));
                }
            }

            inline void log(const LogLevel level, const StringViewType message) noexcept
            {
                if (level >= _lowest_level)
                {
                    log(recored(level, StringType{ message });
                }
            }

            template<EnumType C>
            inline void log(Error<C, CharT> error) noexcept
            {
                if (LogLevel::Error >= _lowest_level)
                {
                    static const auto fmt = boost::locale::conv::to_utf<CharT>("{}, {}", std::locale{});
                    log(record(LogLevel::Error, std::vformat(fmt, make_format_args<CharT>(error.code(), error.message()))));
                }
            }

        public:
            template<typename... Args>
                requires (VariableTypeList<Args_...>::length != 0_uz)
            inline void log(const StringViewType format, Args&&... args) noexcept
            {
                write(std::vformat(fmt, make_format_args<CharT>(std::forward<Args>(args)...)));
            }

            template<typename... Args>
                requires (VariableTypeList<Args_...>::length != 0_uz)
            inline void log(const LogLevel level, const StringViewType format, Args&&... args) noexcept
            {
                if (level >= _lowest_level)
                {
                    log(record(level, std::vformat(fmt, make_format_args<CharT>(std::forward<Args>(args)...))));
                }
            }

        protected:
            virtual void log(RecoredType record) noexcept
            {
                assert(record.level() >= _lowest_level);
                record.write();
            }

        protected:
            virtual RecoredType record(const LogLevel level, StringType message) noexcept = 0;
            virtual void write(StringType message) noexcept = 0;

        private:
            LogLevel _lowest_level;
        };

        template<LogLevel _lowest_level, CharType CharT = char>
            requires (_lowest_level != LogLevel::Other)
        class StaticLoggerInterface
        {
        public:
            using CharType = CharT;
            using RecoredType = LogRecord<CharT>;
            using StringType = std::basic_string<CharT>;
            using StringViewType = std::basic_string_view<CharT>;

            static constexpr const LogLevel lowest_log_level = _lowest_level;

        public:
            StaticLoggerInterface(void) = default;
            StaticLoggerInterface(const StaticLoggerInterface& ano) = delete;
            StaticLoggerInterface(StaticLoggerInterface&& ano) noexcept = default;
            StaticLoggerInterface& operator=(const StaticLoggerInterface& rhs) = delete;
            StaticLoggerInterface& operator=(StaticLoggerInterface&& rhs) = delete;
            ~StaticLoggerInterface(void) noexcept = default;

        public:
            inline const LogLevel lowest_level(void) const noexcept
            {
                return _lowest_level;
            }

        public:
            inline void log(void) noexcept
            {
                write(StringType{});
            }

            inline void log(StringType message) noexcept
            {
                write(std::move(message));
            }

        public:
            inline void log(const LogLevel level, StringType message) noexcept
            {
                if (level >= _lowest_level)
                {
                    log(recored(level, std::move(message));
                }
            }

            inline void log(const LogLevel level, const StringViewType message) noexcept
            {
                if (level >= _lowest_level)
                {
                    log(recored(level, StringType{ message });
                }
            }

            template<LogLevel level>
            inline void log(StringType message) noexcept
            {
                if constexpr (level >= _lowest_level)
                {
                    log(recored(level, std::move(message));
                }
            }

            template<LogLevel level>
            inline void log(const StringViewType message) noexcept
            {
                if constexpr (level >= _lowest_level)
                {
                    log(recored(level, StringType{ message });
                }
            }

            template<EnumType C>
            inline void log(Error<C, CharT> error) noexcept
            {
                if constexpr (LogLevel::Error >= _lowest_level)
                {
                    static const auto fmt = boost::locale::conv::to_utf<CharT>("{}, {}", std::locale{});
                    log(record(LogLevel::Error, std::vformat(fmt, make_format_args<CharT>(error.code(), error.message()))));
                }
            }

        public:
            template<typename... Args>
                requires (VariableTypeList<Args_...>::length != 0_uz)
            inline void log(const StringViewType format, Args&&... args) noexcept
            {
                write(std::vformat(fmt, make_format_args<CharT>(std::forward<Args>(args)...)));
            }

            template<typename... Args>
                requires (VariableTypeList<Args_...>::length != 0_uz)
            inline void log(const LogLevel level, const StringViewType format, Args&&... args) noexcept
            {
                if (level >= _lowest_level)
                {
                    log(record(level, std::vformat(fmt, make_format_args<CharT>(std::forward<Args>(args)...))));
                }
            }

            template<LogLevel level, typename... Args>
                requires (VariableTypeList<Args_...>::length != 0_uz)
            inline void log(const StringViewType format, Args&&... args) noexcept
            {
                if constexpr (level >= _lowest_level)
                {
                    log(record(level, std::vformat(fmt, make_format_args<CharT>(std::forward<Args>(args)...))));
                }
            }

        protected:
            virtual void log(RecoredType record) noexcept
            {
                assert(record.level() >= _lowest_level);
                record.write();
            }

        protected:
            virtual RecoredType record(const LogLevel level, StringType message) noexcept = 0;
            virtual void write(StringType message) noexcept = 0;
        };

        template<CharType CharT = char>
        using LoggerRefWrapper = std::variant<
            Ref<LoggerInterface<CharT>>,
            Ref<StaticLoggerInterface<LogLevel::Trace, CharT>>,
            Ref<StaticLoggerInterface<LogLevel::Debug, CharT>>,
            Ref<StaticLoggerInterface<LogLevel::Info, CharT>>,
            Ref<StaticLoggerInterface<LogLevel::Warn, CharT>>,
            Ref<StaticLoggerInterface<LogLevel::Error, CharT>>,
            Ref<StaticLoggerInterface<LogLevel::Fatal, CharT>>
        >;

        template<CharType CharT = char>
        using LoggerUniqueWrapper = std::variant<
            Unique<LoggerInterface<CharT>>,
            Unique<StaticLoggerInterface<LogLevel::Trace, CharT>>,
            Unique<StaticLoggerInterface<LogLevel::Debug, CharT>>,
            Unique<StaticLoggerInterface<LogLevel::Info, CharT>>,
            Unique<StaticLoggerInterface<LogLevel::Warn, CharT>>,
            Unique<StaticLoggerInterface<LogLevel::Error, CharT>>,
            Unique<StaticLoggerInterface<LogLevel::Fatal, CharT>>
        >;

        template<typename T, typename... Args>
            requires std::convertible_to<PtrType<T>, PtrType<LoggerInterface<typename T::CharType>>>
        inline LoggerUniqueWrapper<typename T::CharType> make_logger(Args&&... args) noexcept
        {
            auto new_logger = new T{ std::forward<Args>(args)... };
            return LoggerUniqueWrapper<typename T::CharType>{ Unique<LoggerInterface<typename T::CharType>>{ new_logger } };
        }

        template<typename T, typename... Args>
            requires std::convertible_to<PtrType<T>, PtrType<StaticLoggerInterface<T::lowest_log_level, typename T::CharType>>>
        inline LoggerUniqueWrapper<typename T::CharType> make_logger(Args&&... args) noexcept
        {
            auto new_logger = new T{ std::forward<Args>(args)... };
            return LoggerUniqueWrapper<typename T::CharType>{ Unique<StaticLoggerInterface<T::lowest_log_level, typename T::CharType>>{ new_logger } };
        }

        template<CharType CharT>
        inline LoggerRefWrapper<CharT> ref(const LoggerUniqueWrapper<CharT>& logger) noexcept
        {
            return std::visit([](const auto& logger)
                {
                    using LoggerType = OriginType<decltype(*logger)>;
                    return Ref<LoggerType>{ *logger };
                }, logger);
        }

        namespace log_detail
        {
            template<LoggerMultiThread mt, CharType CharT, typename Self>
            class LoggerImpl;

            template<CharType CharT, typename Self>
            class LoggerImpl<on, CharT, Self>
                : public LoggerInterface<CharT>
            {
                OSPF_CRTP_IMPL;
                using Interface = LoggerInterface<CharT>;

            public:
                using typename Interface::RecoredType;
                using typename Interface::StringType;
                using typename Interface::StringViewType;

            protected:
                void log(RecoredType record) noexcept override
                {
                    assert(record.level() >= this->lowest_level());
                    _impl.add(std::move(record));
                }

            private:
                MultiThreadImpl<CharT> _impl;
            };

            template<CharType CharT, typename Self>
            class LoggerImpl<off, CharT, Self>
                : public LoggerInterface<CharT>
            {
                OSPF_CRTP_IMPL;
            };

            template<LogLevel lowest_level, LoggerMultiThread mt, CharType CharT, typename Self>
            class StaticLoggerImpl;

            template<LogLevel lowest_level, CharType CharT, typename Self>
            class StaticLoggerImpl<lowest_level, on, CharT, Self>
                : public StaticLoggerInterface<lowest_level, CharT>
            {
                OSPF_CRTP_IMPL;

            protected:
                void log(RecoredType record) noexcept override
                {
                    assert(record.level() >= this->lowest_level());
                    _impl.add(std::move(record));
                }

            private:
                MultiThreadImpl<CharT> _impl;
            };

            template<LogLevel lowest_level, CharType CharT, typename Self>
            class StaticLoggerImpl<lowest_level, off, CharT, Self>
                : public StaticLoggerInterface<lowest_level, CharT>
            {
                OSPF_CRTP_IMPL;
            };
        };
    };
};
