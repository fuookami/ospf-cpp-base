﻿#pragma once

#include <ospf/functional/result.hpp>
#include <ospf/serialization/csv/table.hpp>
#include <istream>
#include <ostream>

namespace ospf
{
    inline namespace serialization
    {
        namespace csv
        {
            template<typename CharT>
            struct CharTrait;

            template<>
            struct CharTrait<char>
            {
                static constexpr const std::string_view default_seperator{ "," };
                static constexpr const std::string_view line_breaker{ "\n" };

                OSPF_BASE_API static std::string catch_regex(const std::string_view seperator) noexcept;
                OSPF_BASE_API static std::ostream& write(std::ostream& os, const std::string& cell, const std::string_view seperator) noexcept;
                OSPF_BASE_API static std::ostream& write(std::ostream& os, const std::optional<std::string>& cell, const std::string_view seperator) noexcept;
                OSPF_BASE_API static std::ostream& write(std::ostream& os, const std::string_view cell, const std::string_view seperator) noexcept;
                OSPF_BASE_API static std::ostream& write(std::ostream& os, const std::optional<std::string_view> cell, const std::string_view seperator) noexcept;
            };

            // todo: impl for different character

            template<typename T, typename CharT>
            inline Try<> write(std::basic_ostream<CharT>& os, const T& table, const std::basic_string_view<CharT> seperator = CharTrait<CharT>::default_seperator) noexcept
            {
                if (table.header().empty())
                {
                    return OSPFError{ OSPFErrCode::DataEmpty };
                }

                const auto column = table.column();
                for (usize j{ 0_uz }; j != column; ++j)
                {
                    CharTrait<CharT>::write(os, table.header()[j].name(), seperator);
                    if (j != (column - 1_uz))
                    {
                        os << seperator;
                    }
                }
                os << CharTrait<CharT>::line_breaker;

                for (const auto& row : table.rows())
                {
                    for (usize j{ 0_uz }; j != column; ++j)
                    {
                        CharTrait<CharT>::write(os, row[j], seperator);
                        if (j != (column - 1_uz))
                        {
                            os << seperator;
                        }
                    }
                }
                os << CharTrait<CharT>::line_breaker;

                return ospf::succeed;
            }

            template<typename CharT>
            inline Result<CSVTable<CharT>> read(std::basic_istream<CharT>& is, const std::basic_string_view<CharT> seperator = CharTrait<CharT>::default_seperator) noexcept
            {
                std::basic_string<CharT> line;
                if (!std::getline(is, line))
                {
                    is.setstate(std::ios_base::failbit);
                    return OSPFError{ OSPFErrCode::DataEmpty };
                }

                const auto regex_matcher = CharTrait<CharT>::catch_regex(seperator);
                std::vector<std::string> header{};
                auto headers = regex_split(line, regex_matcher);
                for (usize j{ 0_uz }; j != headers.size(); ++j)
                {
                    header.push_back(std::move(headers[j]));
                }

                CSVTable table{ std::move(header) };
                while (std::getline(is, line))
                {
                    if (line.empty())
                    {
                        continue;
                    }

                    auto this_row = regex_split(line, regex_matcher);
                    table.insert_row(table.row(), [&this_row](const usize col)
                        {
                            return std::move(this_row[col]);
                        });
                }
                return std::move(table);
            }

            template<usize col, typename CharT>
            inline Result<ORMCSVTable<col, CharT>> read(std::basic_istream<CharT>& is, const std::basic_string_view<CharT> seperator = CharTrait<CharT>::default_seperator) noexcept
            {
                std::basic_string<CharT> line;
                if (!std::getline(is, line))
                {
                    is.setstate(std::ios_base::failbit);
                    return OSPFError{ OSPFErrCode::DataEmpty };
                }

                const auto regex_matcher = CharTrait<CharT>::catch_regex(seperator);
                std::array<std::string, col> header{};
                auto headers = regex_split(line, regex_matcher);
                if (headers.size() != col)
                {
                    return OSPFError{ OSPFErrCode::DeserializationFail, "unmatched header size" };
                }
                for (usize j{ 0_uz }; j != col; ++j)
                {
                    header[j] = std::move(headers[j]);
                }

                ORMCSVTable<col> table{ std::move(header) };
                while (std::getline(is, line))
                {
                    if (line.empty())
                    {
                        continue;
                    }

                    auto this_row = regex_split(line, regex_matcher);
                    table.insert_row(table.row(), [&this_row](const usize j)
                        {
                            return std::move(this_row[j]);
                        });
                }
                
                return std::move(table);
            }
        };
    };
};
