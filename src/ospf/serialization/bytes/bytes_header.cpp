#include <ospf/serialization/bytes/header.hpp>

namespace ospf::serialization::bytes
{
    const bool same(const Fields& lhs, const Fields& rhs, const bool recursive) noexcept
    {
        for (const auto& [key, _] : rhs)
        {
            if (!lhs.contains(key))
            {
                return false;
            }
        }
        for (const auto& [key, field] : lhs)
        {
            if (!rhs.contains(key))
            {
                return false;
            }
            if (recursive && !same(field->fields(), rhs.at(key)->fields(), true))
            {
                return false;
            }
            if (!recursive && *field != *rhs.at(key))
            {
                return false;
            }
        }
        return true;
    }

    const bool SubHeader::operator==(const SubHeader& rhs) const noexcept
    {
        return _id == rhs._id
            && _tag == rhs._tag
            && same(_fields, rhs._fields, false);
    }

    const bool SubHeader::operator!=(const SubHeader& rhs) const noexcept
    {
        return _id != rhs._id
            || _tag != rhs._tag
            || !same(_fields, rhs._fields, false);
    }
};
