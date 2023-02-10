#include <ospf/serialization/csv/io.hpp>

namespace ospf::serialization::csv
{
    std::string CharTrait<char>::catch_regex(const std::string_view seperator) noexcept
    {
        return std::format("\"[\\s\\S]*?\"({}|$)", regex::RegexTrait<char>::to_regex_expr(seperator));
    }

    std::ostream& CharTrait<char>::write(std::ostream& os, const std::string& cell, const std::string_view seperator) noexcept
    {
        if (cell.find(seperator) != std::string_view::npos)
        {
            os << "\"" << cell << "\"";
        }
        else
        {
            os << cell;
        }
        return os;
    }

    std::ostream& CharTrait<char>::write(std::ostream& os, const std::optional<std::string>& cell, const std::string_view seperator) noexcept
    {
        if (cell.has_value())
        {
            if (cell->find(seperator) != std::string_view::npos)
            {
                os << "\"" << *cell << "\"";
            }
            else
            {
                os << *cell;
            }
            return os;
        }
        else
        {
            os << "";
            return os;
        }
    }

    std::ostream& CharTrait<char>::write(std::ostream& os, const std::string_view cell, const std::string_view seperator) noexcept
    {
        if (cell.find(seperator) != std::string_view::npos)
        {
            os << "\"" << cell << "\"";
        }
        else
        {
            os << cell;
        }
        return os;
    }

    std::ostream& CharTrait<char>::write(std::ostream& os, const std::optional<std::string_view> cell, const std::string_view seperator) noexcept
    {
        if (cell.has_value())
        {
            if (cell->find(seperator) != std::string_view::npos)
            {
                os << "\"" << *cell << "\"";
            }
            else
            {
                os << *cell;
            }
            return os;
        }
        else
        {
            os << "";
            return os;
        }
    }
};
