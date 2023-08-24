#include <ospf/meta_programming/name_transfer.hpp>

namespace ospf::meta_programming::name_transfer
{
    template class NameTransferImpl<NamingSystem::Underscore, NamingSystem::Kebab, char>;
    template class NameTransferImpl<NamingSystem::Underscore, NamingSystem::CamelCase, char>;
    template class NameTransferImpl<NamingSystem::Underscore, NamingSystem::PascalCase, char>;
    template class NameTransferImpl<NamingSystem::Underscore, NamingSystem::UpperUnderscore, char>;
    template class NameTransferImpl<NamingSystem::Underscore, NamingSystem::Kebab, wchar>;
    template class NameTransferImpl<NamingSystem::Underscore, NamingSystem::CamelCase, wchar>;
    template class NameTransferImpl<NamingSystem::Underscore, NamingSystem::PascalCase, wchar>;
    template class NameTransferImpl<NamingSystem::Underscore, NamingSystem::UpperUnderscore, wchar>;

    template class NameTransferImpl<NamingSystem::Kebab, NamingSystem::Underscore, char>;
    template class NameTransferImpl<NamingSystem::Kebab, NamingSystem::CamelCase, char>;
    template class NameTransferImpl<NamingSystem::Kebab, NamingSystem::PascalCase, char>;
    template class NameTransferImpl<NamingSystem::Kebab, NamingSystem::UpperUnderscore, char>;
    template class NameTransferImpl<NamingSystem::Kebab, NamingSystem::Underscore, wchar>;
    template class NameTransferImpl<NamingSystem::Kebab, NamingSystem::CamelCase, wchar>;
    template class NameTransferImpl<NamingSystem::Kebab, NamingSystem::PascalCase, wchar>;
    template class NameTransferImpl<NamingSystem::Kebab, NamingSystem::UpperUnderscore, wchar>;

    template class NameTransferImpl<NamingSystem::CamelCase, NamingSystem::Underscore, char>;
    template class NameTransferImpl<NamingSystem::CamelCase, NamingSystem::Kebab, char>;
    template class NameTransferImpl<NamingSystem::CamelCase, NamingSystem::PascalCase, char>;
    template class NameTransferImpl<NamingSystem::CamelCase, NamingSystem::UpperUnderscore, char>;
    template class NameTransferImpl<NamingSystem::CamelCase, NamingSystem::Underscore, wchar>;
    template class NameTransferImpl<NamingSystem::CamelCase, NamingSystem::Kebab, wchar>;
    template class NameTransferImpl<NamingSystem::CamelCase, NamingSystem::PascalCase, wchar>;
    template class NameTransferImpl<NamingSystem::CamelCase, NamingSystem::UpperUnderscore, wchar>;

    template class NameTransferImpl<NamingSystem::PascalCase, NamingSystem::Underscore, char>;
    template class NameTransferImpl<NamingSystem::PascalCase, NamingSystem::Kebab, char>;
    template class NameTransferImpl<NamingSystem::PascalCase, NamingSystem::CamelCase, char>;
    template class NameTransferImpl<NamingSystem::PascalCase, NamingSystem::UpperUnderscore, char>;
    template class NameTransferImpl<NamingSystem::PascalCase, NamingSystem::Underscore, wchar>;
    template class NameTransferImpl<NamingSystem::PascalCase, NamingSystem::Kebab, wchar>;
    template class NameTransferImpl<NamingSystem::PascalCase, NamingSystem::CamelCase, wchar>;
    template class NameTransferImpl<NamingSystem::PascalCase, NamingSystem::UpperUnderscore, wchar>;

    template class NameTransferImpl<NamingSystem::UpperUnderscore, NamingSystem::Underscore, char>;
    template class NameTransferImpl<NamingSystem::UpperUnderscore, NamingSystem::Kebab, char>;
    template class NameTransferImpl<NamingSystem::UpperUnderscore, NamingSystem::CamelCase, char>;
    template class NameTransferImpl<NamingSystem::UpperUnderscore, NamingSystem::PascalCase, char>;
    template class NameTransferImpl<NamingSystem::UpperUnderscore, NamingSystem::Underscore, wchar>;
    template class NameTransferImpl<NamingSystem::UpperUnderscore, NamingSystem::Kebab, wchar>;
    template class NameTransferImpl<NamingSystem::UpperUnderscore, NamingSystem::CamelCase, wchar>;
    template class NameTransferImpl<NamingSystem::UpperUnderscore, NamingSystem::PascalCase, wchar>;
};
