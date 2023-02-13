#include <ospf/string/hasher.hpp>

namespace ospf::string
{
    template class StringHasher<char>;
    template class StringHasher<wchar>;
};
