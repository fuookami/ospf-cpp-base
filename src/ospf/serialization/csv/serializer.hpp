#pragma once

#include <ospf/serialization/csv/io.hpp>
#include <ospf/serialization/csv/to_value.hpp>
#include <ospf/meta_programming/type_info.hpp>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace ospf
{
    inline namespace serialization
    {
        namespace csv
        {
            template<WithMetaInfo T>
            class Serializer
            {
                using NameTransfer = std::function<const std::string_view(const std::string_view)>;
                using ValueType = OriginType<T>;
                using TableType = ORMTableType<ValueType>;
                using HeaderType = ORMHeaderType<ValueType>;
                using RowType = ORMRowType<ValueType>;

            public:
                Serializer(void) = default;
                Serializer(NameTransfer transfer)
                    : _transfer(std::move(transfer)) {}
                Serializer(const Serializer& serializer) = default;
                Serializer(Serializer&& serializer) noexcept = default;
                Serializer& operator=(const Serializer& rhs) = default;
                Serializer& operator=(Serializer&& rhs) noexcept = default;
                ~Serializer(void) = default;

            public:
                template<usize len>
                inline Result<TableType> operator()(const std::span<const ValueType, len> objs) const noexcept
                {
                    static const meta_info::MetaInfo<ValueType> info{};
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
                    static const meta_info::MetaInfo<ValueType> info{};
                    TableType ret{ make_csv_table<ValueType>(_transfer) };
                    OSPF_TRY_GET(row, serialize(info, obj));
                    ret.insert_row(ret.row(), [&row](const usize col) { return std::move(row[col]); });
                    return ret;
                }

            private:
                inline constexpr Result<RowType> serialize(const meta_info::MetaInfo<ValueType>& info, const ValueType& obj) noexcept
                {
                    RowType row;
                    usize i{ 0_uz };
                    std::optional<OSPFError> err;
                    info.for_each(obj, [this, &row, &err](const auto& obj, const auto& field) 
                        {
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

            template<typename T>
            inline Try<> to_file(const std::filesystem::path& path, const T& obj) noexcept
            {
                // todo
            }

            template<typename T, usize len>
            inline Try<> to_file(const std::filesystem::path& path, const std::span<T, len> objs) noexcept
            {
                // todo
            }

            template<typename T>
            inline Result<std::string> to_string(const T& obj) noexcept
            {
                // todo
            }

            template<typename T, usize len>
            inline Result<std::string> to_file(const std::span<T, len> objs) noexcept
            {
                // todo
            }
        };
    };
};
