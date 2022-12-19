#include <ospf/meta_programming/name_transfer.hpp>

namespace ospf::meta_programming
{
    template class NameTransfer<NamingSystem::Underscore, NamingSystem::Camelcase>;
    template class NameTransfer<NamingSystem::Underscore, NamingSystem::Pascalcase>;
    template class NameTransfer<NamingSystem::Underscore, NamingSystem::UpperUnderscore>;

    template class NameTransfer<NamingSystem::Camelcase, NamingSystem::Underscore>;
    template class NameTransfer<NamingSystem::Camelcase, NamingSystem::Pascalcase>;
    template class NameTransfer<NamingSystem::Camelcase, NamingSystem::UpperUnderscore>;

    template class NameTransfer<NamingSystem::Pascalcase, NamingSystem::Underscore>;
    template class NameTransfer<NamingSystem::Pascalcase, NamingSystem::Camelcase>;
    template class NameTransfer<NamingSystem::Pascalcase, NamingSystem::UpperUnderscore>;

    template class NameTransfer<NamingSystem::UpperUnderscore, NamingSystem::Underscore>;
    template class NameTransfer<NamingSystem::UpperUnderscore, NamingSystem::Camelcase>;
    template class NameTransfer<NamingSystem::UpperUnderscore, NamingSystem::Pascalcase>;
};
