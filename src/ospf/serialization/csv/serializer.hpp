#pragma once

#include <ospf/serialization/csv/io.hpp>
#include <ospf/serialization/csv/to_value.hpp>
#include <ospf/meta_programming/name_transfer.hpp>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace ospf
{
    inline namespace serialization
    {
        namespace csv
        {
            template<WithMetaInfo T, typename CharT = char>
            class Serializer
            {
            public:
                using NameTransfer = std::function<const std::basic_string_view<CharT>(const std::basic_string_view<CharT>)>;
                using ValueType = OriginType<T>;
                using TableType = ORMTableType<ValueType>;
                using HeaderType = ORMHeaderType<ValueType>;
                using RowType = ORMRowType<ValueType>;

            public:
                Serializer(void) = default;
                Serializer(NameTransfer transfer)
                    : _transfer(std::move(transfer)) {}
                Serializer(const Serializer& ano) = default;
                Serializer(Serializer&& ano) noexcept = default;
                Serializer& operator=(const Serializer& rhs) = default;
                Serializer& operator=(Serializer&& rhs) noexcept = default;
                ~Serializer(void) = default;

            public:
                template<usize len>
                inline Result<TableType> operator()(const std::span<const ValueType, len> objs) const noexcept
                {
                    static constexpr const meta_info::MetaInfo<ValueType> info{};
                    TableType ret{ make_csv_table<ValueType>(_transfer) };
                    for (const auto& obj : objs)
                    {
                        OSPF_TRY_GET(row, serialize(info, obj));
                        ret.insert_row(ret.row(), [&row](const usize col) { return std::move(row[col]); });
                    }
                    return ret;
                }

                inline Result<TableType> operator()(const ValueType& obj) const noexcept
                {
                    static constexpr const meta_info::MetaInfo<ValueType> info{};
                    TableType ret{ make_csv_table<ValueType>(_transfer) };
                    OSPF_TRY_GET(row, serialize(info, obj));
                    ret.insert_row(ret.row(), [&row](const usize col) { return std::move(row[col]); });
                    return ret;
                }

            private:
                inline Result<RowType> serialize(const meta_info::MetaInfo<ValueType>& info, const ValueType& obj) noexcept
                {
                    RowType row;
                    usize i{ 0_uz };
                    std::optional<OSPFError> err;
                    info.for_each(obj, [this, &row, &err](const auto& obj, const auto& field)
                        {
                            // todo: impl concept refer to a type that all fileds are plane
                            static_assert(field.plane());
                            static_assert(SerializableToCSV<OriginType<decltype(field.value(obj))>>);

                            if (err.has_value())
                            {
                                return;
                            }

                            const auto key = this->_transfer.has_value() ? (*this->_transfer)(field.key()) : field.key();
                            const ToCSVValue<OriginType<decltype(field.value(obj))>> serializer{};
                            auto value = serializer(field.value(obj));
                            if (value.failed())
                            {
                                err = OSPFError{ OSPFErrCode::SerializationFail, std::format("failed serializing field \"{}\" for type \"{}\", {}", field.key(), TypeInfo<ValueType>::name(), value.err().message())};
                            }
                            else
                            {
                                row[i] = std::move(value).unwrap();
                                ++i;
                            }
                        });
                    if (err.has_value())
                    {
                        return std::move(err).value();
                    }
                    else
                    {
                        return std::move(row);
                    }
                }

            private:
                std::optional<NameTransfer> _transfer;
            };

            template<typename T, typename CharT = char>
            inline Try<> to_file
            (
                const std::filesystem::path& path, 
                const T& obj, 
                std::optional<typename Serializer<T, CharT>::NameTransfer> transfer = NameTransfer<NamingSystem::Underscore, NamingSystem::UpperUnderscore, CharT>{}, 
                const std::basic_string_view<CharT> seperator = CharTrait<CharT>::default_seprator
            ) noexcept
            {
                if (std::filesystem::is_directory(path))
                {
                    return OSPFError{ OSPFErrCode::NotAFile, std::format("\"{}\" is not a file", path) };
                }

                const auto parent_path = path.parent_path();
                if (!std::filesystem::exists(parent_path))
                {
                    if (!std::filesystem::create_directories(parent_path))
                    {
                        return OSPFError{ OSPFErrCode::DirectoryUnusable, std::format("directory \"{}\" unusable", parent_path) };
                    }
                }

                auto serializer = transfer.has_value() ? Serializer<T, CharT>{ std::move(transfer).value() } : Serializer<T, CharT>{};
                OSPF_TRY_GET(table, serializer(obj));

                std::basic_ofstream<CharT> fout{ path };
                OSPF_TRY_EXEC(write(fout, table, seperator));
                return succeed;
            }

            template<typename T, usize len, typename CharT = char>
            inline Try<> to_file
            (
                const std::filesystem::path& path, 
                const std::span<const T, len> objs, 
                std::optional<typename Serializer<T, CharT>::NameTransfer> transfer = NameTransfer<NamingSystem::Underscore, NamingSystem::UpperUnderscore, CharT>{},
                const std::basic_string_view<CharT> seperator = CharTrait<CharT>::default_seprator
            ) noexcept
            {
                if (std::filesystem::is_directory(path))
                {
                    return OSPFError{ OSPFErrCode::NotAFile, std::format("\"{}\" is not a file", path) };
                }

                const auto parent_path = path.parent_path();
                if (!std::filesystem::exists(parent_path))
                {
                    if (!std::filesystem::create_directories(parent_path))
                    {
                        return OSPFError{ OSPFErrCode::DirectoryUnusable, std::format("directory \"{}\" unusable", parent_path) };
                    }
                }

                auto serializer = transfer.has_value() ? Serializer<T, CharT>{ std::move(transfer).value() } : Serializer<T, CharT>{};
                OSPF_TRY_GET(table, serializer(objs));

                std::basic_ofstream<CharT> fout{ path };
                OSPF_TRY_EXEC(write(fout, table, seperator));
                return succeed;
            }

            template<typename T, typename CharT = char>
            inline Result<std::basic_string<CharT>> to_string
            (
                const T& obj, 
                std::optional<typename Serializer<T, CharT>::NameTransfer> transfer = NameTransfer<NamingSystem::Underscore, NamingSystem::UpperUnderscore, CharT>{},
                const std::basic_string_view<CharT> seperator = CharTrait<CharT>::default_seprator
            ) noexcept
            {
                auto serializer = transfer.has_value() ? Serializer<T, CharT>{ std::move(transfer).value() } : Serializer<T, CharT>{};
                OSPF_TRY_GET(table, serializer(obj));

                std::basic_ostringstream<CharT> sout;
                OSPF_TRY_EXEC(write(sout, table, seperator));
                return sout.str();
            }

            template<typename T, usize len, typename CharT = char>
            inline Result<std::basic_string<CharT>> to_string
            (
                const std::span<const T, len> objs, 
                std::optional<typename Serializer<T, CharT>::NameTransfer> transfer = NameTransfer<NamingSystem::Underscore, NamingSystem::UpperUnderscore, CharT>{},
                const std::basic_string_view<CharT> seperator = CharTrait<CharT>::default_seprator
            ) noexcept
            {
                auto serializer = transfer.has_value() ? Serializer<T, CharT>{ std::move(transfer).value() } : Serializer<T, CharT>{};
                OSPF_TRY_GET(table, serializer(objs));

                std::basic_ostringstream<CharT> sout;
                OSPF_TRY_EXEC(write(sout, table, seperator));
                return sout.str();
            }

            // todo: to bytes
        };
    };
};
