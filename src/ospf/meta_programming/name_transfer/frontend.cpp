#include <ospf/meta_programming/name_transfer/frontend.hpp>

namespace ospf::meta_programming::name_transfer
{
    template struct Frontend<NamingSystem::Underscore, char>;
    template struct Frontend<NamingSystem::Underscore, wchar>;

    template struct Frontend<NamingSystem::Camelcase, char>;
    template struct Frontend<NamingSystem::Camelcase, wchar>;

    template struct Frontend<NamingSystem::Pascalcase, char>;
    template struct Frontend<NamingSystem::Pascalcase, wchar>;

    template struct Frontend<NamingSystem::UpperUnderscore, char>;
    template struct Frontend<NamingSystem::UpperUnderscore, wchar>;
};
