#include <ospf/serialization/bytes/header.hpp>

namespace ospf::serialization::bytes
{
    const bool ospf::serialization::bytes::SubHeader::operator==(const SubHeader& rhs) const noexcept
    {
        // todo
        return true;
    }

    const bool ospf::serialization::bytes::SubHeader::operator!=(const SubHeader& rhs) const noexcept
    {
        // todo
        return true;
    }

    Try<> Header::fit(const StringHashMap<std::string_view, Shared<SubHeader>> fields) const noexcept
    {
        for (const auto& [key, _] : _fields)
        {
            if (!fields.contains(key))
            {
                // todo
            }
        }
        for (const auto& [key, field] : fields)
        {
            if (!_fields.contains(key))
            {
                // todo
            }
            if (*field != *_fields.at(key))
            {
                // todo
            }
        }
        return succeed;
    }
};
