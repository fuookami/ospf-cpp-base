#pragma once

#include <ospf/serialization/csv/io.hpp>
#include <ospf/serialization/csv/from_value.hpp>
#include <ospf/serialization/nullable.hpp>
#include <ospf/meta_programming/type_info.hpp>
#include <ospf/string/hasher.hpp>

namespace ospf
{
    inline namespace serialization
    {
        namespace csv
        {
            template<WithMetaInfo T>
            class Deserializer
            {
                using NameTransfer = std::function<const std::string_view(const std::string_view)>;
                using ColumnMap = StringHashMap<std::string_view, usize>;
                using ValueType = OriginType<T>;
                using RowType = ORMRowType<ValueType>;
                using RowViewType = ORMRowViewType<ValueType>;

            public:
                Deserializer(void) = default;
                Deserializer(NameTransfer transfer)
                    : _transfer(std::move(transfer)) {}
                Deserializer(const Deserializer& serializer) = default;
                Deserializer(Deserializer&& serializer) noexcept = default;
                Deserializer& operator=(const Deserializer& rhs) = default;
                Deserializer& operator=(Deserializer&& rhs) noexcept = default;
                ~Deserializer(void) = default;

            public:
                template<typename = void>
                    requires std::default_initializable<ValueType>
                inline std::vector<ValueType> operator()(const CSVTable& table) const noexcept
                {
                    static const meta_info::MetaInfo<ValueType> info{};
                    OSPF_TRY_GET(column_map, parse_header(info, table.header()));
                    std::vector<ValueType> ret;
                    for (const auto& row : table.rows())
                    {
                        ValueType obj{};
                        OSPF_TRY_EXEC(deserialize(obj, info, row, column_map));
                        ret.push_back(std::move(obj));
                    }
                    return ret;
                }

                template<typename = void>
                    requires std::copy_constructible<ValueType>
                inline std::vector<ValueType> operator()(const CSVTable& table, const ValueType& origin_obj) const noexcept
                {
                    static const meta_info::MetaInfo<ValueType> info{};
                    OSPF_TRY_GET(column_map, parse_header(info, table.header()));
                    std::vector<ValueType> ret;
                    for (const auto& row : table.rows())
                    {
                        ValueType obj{ origin_obj };
                        OSPF_TRY_EXEC(deserialize(obj, info, row, column_map));
                        ret.push_back(std::move(obj));
                    }
                    return ret;
                }

                template<typename = void>
                    requires std::default_initializable<ValueType>
                inline std::vector<ValueType> operator()(const CSVViewTable& table) const noexcept
                {
                    static const meta_info::MetaInfo<ValueType> info{};
                    OSPF_TRY_GET(column_map, parse_header(info, table.header()));
                    std::vector<ValueType> ret;
                    for (const auto& row : table.rows())
                    {
                        ValueType obj{};
                        OSPF_TRY_EXEC(deserialize(obj, info, row, column_map));
                        ret.push_back(std::move(obj));
                    }
                    return ret;
                }

                template<typename = void>
                    requires std::copy_constructible<ValueType>
                inline std::vector<ValueType> operator()(const CSVViewTable& table, const ValueType& origin_obj) const noexcept
                {
                    static const meta_info::MetaInfo<ValueType> info{};
                    OSPF_TRY_GET(column_map, parse_header(info, table.header()));
                    std::vector<ValueType> ret;
                    for (const auto& row : table.rows())
                    {
                        ValueType obj{ origin_obj };
                        OSPF_TRY_EXEC(deserialize(obj, info, row, column_map));
                        ret.push_back(std::move(obj));
                    }
                    return ret;
                }

                template<typename = void>
                    requires std::default_initializable<ValueType>
                inline std::vector<ValueType> operator()(const ORMTableType<ValueType>& table) const noexcept
                {
                    static const meta_info::MetaInfo<ValueType> info{};
                    OSPF_TRY_GET(column_map, parse_header(info, table.header()));
                    std::vector<ValueType> ret;
                    for (const auto& row : table.rows())
                    {
                        ValueType obj{};
                        OSPF_TRY_EXEC(deserialize(obj, info, row, column_map));
                        ret.push_back(std::move(obj));
                    }
                    return ret;
                }

                template<typename = void>
                    requires std::copy_constructible<ValueType>
                inline std::vector<ValueType> operator()(const ORMTableType<ValueType>& table, const ValueType& origin_obj) const noexcept
                {
                    static const meta_info::MetaInfo<ValueType> info{};
                    OSPF_TRY_GET(column_map, parse_header(info, table.header()));
                    std::vector<ValueType> ret;
                    for (const auto& row : table.rows())
                    {
                        ValueType obj{ origin_obj };
                        OSPF_TRY_EXEC(deserialize(obj, info, row, column_map));
                        ret.push_back(std::move(obj));
                    }
                    return ret;
                }

                template<typename = void>
                    requires std::default_initializable<ValueType>
                inline std::vector<ValueType> operator()(const ORMViewTableType<ValueType>& table) const noexcept
                {
                    static const meta_info::MetaInfo<ValueType> info{};
                    OSPF_TRY_GET(column_map, parse_header(info, table.header()));
                    std::vector<ValueType> ret;
                    for (const auto& row : table.rows())
                    {
                        ValueType obj{};
                        OSPF_TRY_EXEC(deserialize(obj, info, row, column_map));
                        ret.push_back(std::move(obj));
                    }
                    return ret;
                }

                template<typename = void>
                    requires std::copy_constructible<ValueType>
                inline std::vector<ValueType> operator()(const ORMViewTableType<ValueType>& table, const ValueType& origin_obj) const noexcept
                {
                    static const meta_info::MetaInfo<ValueType> info{};
                    OSPF_TRY_GET(column_map, parse_header(info, table.header()));
                    std::vector<ValueType> ret;
                    for (const auto& row : table.rows())
                    {
                        ValueType obj{ origin_obj };
                        OSPF_TRY_EXEC(deserialize(obj, info, row, column_map));
                        ret.push_back(std::move(obj));
                    }
                    return ret;
                }

            private:
                template<usize len>
                inline Result<ColumnMap> parse_header(const meta_info::MetaInfo<T>& info, const std::span<const data_table::DataTableHeader, len> header) const noexcept
                {
                    ColumnMap column_map;
                    std::optional<OSPFError> err;
                    info.for_each([this, header, &column_map, &err](const auto& field) 
                        {
                            if (err.has_value())
                            {
                                return;
                            }

                            const auto key = this->_tansfer.has_value() ? (*this->_transfer)(field.key()) : field.key();
                            const auto it = std::find_if(header.begin(), header.end(), [key](const data_table::DataTableHeader& header)
                                {
                                    return header.name() == key;
                                });
                            if (it == header.end() && !serialization_nullable<ValueType>)
                            {
                                err = OSPFError{ OSPFErrCode::DeserializationFail, std::format("lost non-nullable column \"{}\" for type \"{}\"", field.key(), TypeInfo<ValueType>::name()) };
                                return
                            }
                            column_map.insert({ field.key(), it - header.begin() });
                        });
                    if (err.has_value())
                    {
                        return std::move(err).value();
                    }
                    else
                    {
                        return std::move(column_map);
                    }
                }

                template<typename S, usize len>
                inline Try<> deserialize(T& obj, const meta_info::MetaInfo<T>& info, const std::span<const std::optional<S>, len> row, const ColumnMap& column_map) const noexcept
                {
                    std::optional<OSPFError> err;
                    info.for_each(obj, [this, row, &column_map, err](auto& obj, const auto& field)
                        {
                            static_assert(DeserializableFromCSV<OriginType<decltype(field.value(obj))>>);
                            if constexpr (!field.writable())
                            {
                                return;
                            }
                            else
                            {
                                if (err.has_value())
                                {
                                    return;
                                }

                                const auto key = this->_tansfer.has_value() ? (*this->_transfer)(field.key()) : field.key();
                                const FromCSVValue<OriginType<decltype(field.value(obj))>> deserializer{};
                                auto value = deserializer(*row[column_map.at(key)]);
                                if (value.failed())
                                {
                                    err = OSPFError{ OSPFErrCode::SerializationFail, std::format("failed deserializing field \"{}\" for type {}, {}", field.key(), TypeInfo<ValueType>::name(), value.err().message()) };
                                }
                                else
                                {
                                    field.value(obj) = std::move(value).unwrap();
                                }
                            }
                        });
                    if (err.has_value())
                    {
                        return std::move(err).value();
                    }
                    else
                    {
                        return succeed;
                    }
                }

                template<typename S, usize len>
                inline Try<> deserialize(T& obj, const meta_info::MetaInfo<T>& info, const std::span<const S, len> row, const ColumnMap& column_map) const noexcept
                {
                    std::optional<OSPFError> err;
                    info.for_each(obj, [this, row, &column_map, err](auto& obj, const auto& field)
                        {
                            if constexpr (!field.writable())
                            {
                                return;
                            }
                            else
                            {
                                if (err.has_value())
                                {
                                    return;
                                }

                                const auto key = this->_tansfer.has_value() ? (*this->_transfer)(field.key()) : field.key();
                                const FromCSVValue<OriginType<decltype(field.value(obj))>> deserializer{};
                                auto value = deserializer(row[column_map.at(key)]);
                                if (value.failed())
                                {
                                    err = OSPFError{ OSPFErrCode::SerializationFail, std::format("failed deserializing field \"{}\" for type {}, {}", field.key(), TypeInfo<ValueType>::name(), value.err().message()) };
                                }
                                else
                                {
                                    field.value(obj) = std::move(value).unwrap();
                                }
                            }
                        });
                    if (err.has_value())
                    {
                        return std::move(err).value();
                    }
                    else
                    {
                        return succeed;
                    }
                }

            private:
                std::optional<NameTransfer> _transfer;
            };

            // todo: deserialize from file / deserialize from string
        };
    };
};
