#include <ospf/meta_programming/name_transfer.hpp>

namespace ospf::meta_programming::name_transfer
{
    template class NameTransferImpl<NamingSystem::Underscore, NamingSystem::Camelcase, char>;
    template class NameTransferImpl<NamingSystem::Underscore, NamingSystem::Pascalcase, char>;
    template class NameTransferImpl<NamingSystem::Underscore, NamingSystem::UpperUnderscore, char>;
    template class NameTransferImpl<NamingSystem::Underscore, NamingSystem::Camelcase, wchar>;
    template class NameTransferImpl<NamingSystem::Underscore, NamingSystem::Pascalcase, wchar>;
    template class NameTransferImpl<NamingSystem::Underscore, NamingSystem::UpperUnderscore, wchar>;

    template class NameTransferImpl<NamingSystem::Camelcase, NamingSystem::Underscore, char>;
    template class NameTransferImpl<NamingSystem::Camelcase, NamingSystem::Pascalcase, char>;
    template class NameTransferImpl<NamingSystem::Camelcase, NamingSystem::UpperUnderscore, char>;
    template class NameTransferImpl<NamingSystem::Camelcase, NamingSystem::Underscore, wchar>;
    template class NameTransferImpl<NamingSystem::Camelcase, NamingSystem::Pascalcase, wchar>;
    template class NameTransferImpl<NamingSystem::Camelcase, NamingSystem::UpperUnderscore, wchar>;

    template class NameTransferImpl<NamingSystem::Pascalcase, NamingSystem::Underscore, char>;
    template class NameTransferImpl<NamingSystem::Pascalcase, NamingSystem::Camelcase, char>;
    template class NameTransferImpl<NamingSystem::Pascalcase, NamingSystem::UpperUnderscore, char>;
    template class NameTransferImpl<NamingSystem::Pascalcase, NamingSystem::Underscore, wchar>;
    template class NameTransferImpl<NamingSystem::Pascalcase, NamingSystem::Camelcase, wchar>;
    template class NameTransferImpl<NamingSystem::Pascalcase, NamingSystem::UpperUnderscore, wchar>;

    template class NameTransferImpl<NamingSystem::UpperUnderscore, NamingSystem::Underscore, char>;
    template class NameTransferImpl<NamingSystem::UpperUnderscore, NamingSystem::Camelcase, char>;
    template class NameTransferImpl<NamingSystem::UpperUnderscore, NamingSystem::Pascalcase, char>;
    template class NameTransferImpl<NamingSystem::UpperUnderscore, NamingSystem::Underscore, wchar>;
    template class NameTransferImpl<NamingSystem::UpperUnderscore, NamingSystem::Camelcase, wchar>;
    template class NameTransferImpl<NamingSystem::UpperUnderscore, NamingSystem::Pascalcase, wchar>;
};
