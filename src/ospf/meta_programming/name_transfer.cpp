#include <ospf/meta_programming/name_transfer.hpp>

namespace ospf::meta_programming
{
    template class NameTransfer<NamingSystem::Underscore, NamingSystem::Camelcase, char>;
    template class NameTransfer<NamingSystem::Underscore, NamingSystem::Pascalcase, char>;
    template class NameTransfer<NamingSystem::Underscore, NamingSystem::UpperUnderscore, char>;
    template class NameTransfer<NamingSystem::Underscore, NamingSystem::Camelcase, wchar>;
    template class NameTransfer<NamingSystem::Underscore, NamingSystem::Pascalcase, wchar>;
    template class NameTransfer<NamingSystem::Underscore, NamingSystem::UpperUnderscore, wchar>;

    template class NameTransfer<NamingSystem::Camelcase, NamingSystem::Underscore, char>;
    template class NameTransfer<NamingSystem::Camelcase, NamingSystem::Pascalcase, char>;
    template class NameTransfer<NamingSystem::Camelcase, NamingSystem::UpperUnderscore, char>;
    template class NameTransfer<NamingSystem::Camelcase, NamingSystem::Underscore, wchar>;
    template class NameTransfer<NamingSystem::Camelcase, NamingSystem::Pascalcase, wchar>;
    template class NameTransfer<NamingSystem::Camelcase, NamingSystem::UpperUnderscore, wchar>;

    template class NameTransfer<NamingSystem::Pascalcase, NamingSystem::Underscore, char>;
    template class NameTransfer<NamingSystem::Pascalcase, NamingSystem::Camelcase, char>;
    template class NameTransfer<NamingSystem::Pascalcase, NamingSystem::UpperUnderscore, char>;
    template class NameTransfer<NamingSystem::Pascalcase, NamingSystem::Underscore, wchar>;
    template class NameTransfer<NamingSystem::Pascalcase, NamingSystem::Camelcase, wchar>;
    template class NameTransfer<NamingSystem::Pascalcase, NamingSystem::UpperUnderscore, wchar>;

    template class NameTransfer<NamingSystem::UpperUnderscore, NamingSystem::Underscore, char>;
    template class NameTransfer<NamingSystem::UpperUnderscore, NamingSystem::Camelcase, char>;
    template class NameTransfer<NamingSystem::UpperUnderscore, NamingSystem::Pascalcase, char>;
    template class NameTransfer<NamingSystem::UpperUnderscore, NamingSystem::Underscore, wchar>;
    template class NameTransfer<NamingSystem::UpperUnderscore, NamingSystem::Camelcase, wchar>;
    template class NameTransfer<NamingSystem::UpperUnderscore, NamingSystem::Pascalcase, wchar>;
};
