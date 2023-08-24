#include <ospf/meta_programming/name_transfer/frontend.hpp>

namespace ospf::meta_programming::name_transfer
{
    template struct Frontend<NamingSystem::Underscore, char>;
    template struct Frontend<NamingSystem::Underscore, wchar>;

    template struct Frontend<NamingSystem::Kebab, char>;
    template struct Frontend<NamingSystem::Kebab, wchar>;

    template struct Frontend<NamingSystem::CamelCase, char>;
    template struct Frontend<NamingSystem::CamelCase, wchar>;

    template struct Frontend<NamingSystem::PascalCase, char>;
    template struct Frontend<NamingSystem::PascalCase, wchar>;

    template struct Frontend<NamingSystem::UpperUnderscore, char>;
    template struct Frontend<NamingSystem::UpperUnderscore, wchar>;
};
