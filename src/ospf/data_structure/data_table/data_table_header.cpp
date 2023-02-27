#include <ospf/data_structure/data_table/header.hpp>

namespace ospf::data_structure::data_table
{
    std::string to_string(const DataTableHeader<char>& header) noexcept
    {
        if (header._type.has_value())
        {
            return std::visit([&header](const auto& type) -> std::string
                {
                    if constexpr (DecaySameAs<decltype(type), std::type_index>)
                    {
                        return std::format("{}({})", header.name(), type_name(type));
                    }
                    else if constexpr (DecaySameAs<decltype(type), std::set<std::type_index>>)
                    {
                        if (type.empty())
                        {
                            return header._name;
                        }
                        else if (type.size() == 1_uz)
                        {
                            return std::format("{}({})", header.name(), type_name(*type.begin()));
                        }
                        else
                        {
                            return std::format("{}({}...)", header.name(), type_name(*type.begin()));
                        }
                    }
                    else
                    {
                        return "";
                    }
                }, * header._type);
        }
        else
        {
            return "";
        }
    }

    std::wstring to_string(const DataTableHeader<wchar>& header) noexcept
    {
        if (header._type.has_value())
        {
            return std::visit([&header](const auto& type) -> std::wstring
                {
                    if constexpr (DecaySameAs<decltype(type), std::type_index>)
                    {
                        return std::format(L"{}({})", header.name(), boost::locale::conv::to_utf<wchar>(type_name(type).data(), std::locale{}));
                    }
                    else if constexpr (DecaySameAs<decltype(type), std::set<std::type_index>>)
                    {
                        if (type.empty())
                        {
                            return header._name;
                        }
                        else if (type.size() == 1_uz)
                        {
                            return std::format(L"{}({})", header.name(), boost::locale::conv::to_utf<wchar>(type_name(*type.begin()).data(), std::locale{}));
                        }
                        else
                        {
                            return std::format(L"{}({}...)", header.name(), boost::locale::conv::to_utf<wchar>(type_name(*type.begin()).data(), std::locale{}));
                        }
                    }
                    else
                    {
                        return L"";
                    }
                }, *header._type);
        }
        else
        {
            return L"";
        }
    }
};
