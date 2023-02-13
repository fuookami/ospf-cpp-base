#include <ospf/meta_programming/name_transfer/backend.hpp>

namespace ospf::meta_programming::name_transfer
{
    template struct Backend<NamingSystem::Underscore, char>;
    template struct Backend<NamingSystem::Underscore, wchar>;

    template struct Backend<NamingSystem::Camelcase, char>;
    template struct Backend<NamingSystem::Camelcase, wchar>;

    template struct Backend<NamingSystem::Pascalcase, char>;
    template struct Backend<NamingSystem::Pascalcase, wchar>;

    template struct Backend<NamingSystem::UpperUnderscore, char>;
    template struct Backend<NamingSystem::UpperUnderscore, wchar>;
};
