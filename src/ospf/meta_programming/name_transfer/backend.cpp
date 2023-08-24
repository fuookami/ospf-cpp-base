#include <ospf/meta_programming/name_transfer/backend.hpp>

namespace ospf::meta_programming::name_transfer
{
    template struct Backend<NamingSystem::Underscore, char>;
    template struct Backend<NamingSystem::Underscore, wchar>;

    template struct Backend<NamingSystem::Kebab, char>;
    template struct Backend<NamingSystem::Kebab, wchar>;

    template struct Backend<NamingSystem::CamelCase, char>;
    template struct Backend<NamingSystem::CamelCase, wchar>;

    template struct Backend<NamingSystem::PascalCase, char>;
    template struct Backend<NamingSystem::PascalCase, wchar>;

    template struct Backend<NamingSystem::UpperUnderscore, char>;
    template struct Backend<NamingSystem::UpperUnderscore, wchar>;
};
