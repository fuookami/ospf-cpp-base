#pragma once

#include <ospf/string.hpp>
#include <ospf/meta_programming/name_transfer/frontend.hpp>
#include <ospf/meta_programming/name_transfer/backend.hpp>
#include <ospf/memory/pointer.hpp>
#include <shared_mutex>

namespace ospf
{
    inline namespace meta_programming
    {
        template<NamingSystem frontend, NamingSystem backend, typename CharT = char>
        class NameTransfer
        {
        public:
            static constexpr const NamingSystem from = frontend;
            static constexpr const NamingSystem to = backend;
            using Frontend = name_transfer::Frontend<frontend, CharT>;
            using Backend = name_transfer::Backend<backend, CharT>;

        public:
            NameTransfer(void) = default;
            NameTransfer(const NameTransfer& ano) = delete;
            NameTransfer(NameTransfer&& ano) noexcept = default;
            NameTransfer& operator=(const NameTransfer& rhs) = delete;
            NameTransfer& operator=(const NameTransfer&& rhs) = delete;
            ~NameTransfer(void) noexcept = default;

        public:
            OSPF_BASE_API static const NameTransfer& instance(void) noexcept
            {
                static const NameTransfer* const _instance{ make_unique<NameTransfer>() };
                return *_instance;
            }

        public:
            OSPF_BASE_API const std::basic_string_view<CharT> operator()(const std::basic_string_view<CharT> name) const noexcept
            {
                static constexpr const Frontend transfer_frontend{};
                static constexpr const Backend transfer_backend{};

                auto it = _cache.find(name);
#ifdef OSPF_MULTI_THREAD
                _mutex.lock_shared();
                if (it == _cache.cend())
                {
                    _mutex.unlock_shared();
                    _mutex.lock();
                    it = _cache.find(name);
                    if (it == _cache.cend())
                    {
                        const auto il = transfer_frontend(name);
                        it = _cache.insert(std::make_pair(std::string{ name }, transfer_backend(std::span{ il }))).first;
                    }
                    const auto& ret = it->second;
                    _mutex.unlock();
                    return ret;
                }
                else
                {
                    const auto& ret = it->second;
                    _mutex.unlock_shared();
                    return ret;
                };
#else
                if (it == _cache.cend())
                {
                    const auto il = transfer_frontend(name);
                    it = _cache.insert(std::make_pair(std::string{ name }, transfer_backend(std::span{ il }))).first;
                }
                return it->second;
#endif
            }

            inline const std::basic_string_view<CharT> reverse(const std::basic_string_view<CharT> name) const noexcept
            {
                static const auto& reversed_transfer = NameTransfer<backend, frontend, CharT>::instance();
                return reversed_transfer(name);
            }

        private:
#ifdef OSPF_MULTI_THREAD
            mutable std::shared_mutex _mutex;
#endif
            mutable StringHashMap<std::basic_string<CharT>, std::basic_string<CharT>> _cache;
        };

        extern template class NameTransfer<NamingSystem::Underscore, NamingSystem::Camelcase, char>;
        extern template class NameTransfer<NamingSystem::Underscore, NamingSystem::Pascalcase, char>;
        extern template class NameTransfer<NamingSystem::Underscore, NamingSystem::UpperUnderscore, char>;

        extern template class NameTransfer<NamingSystem::Camelcase, NamingSystem::Underscore, char>;
        extern template class NameTransfer<NamingSystem::Camelcase, NamingSystem::Pascalcase, char>;
        extern template class NameTransfer<NamingSystem::Camelcase, NamingSystem::UpperUnderscore, char>;

        extern template class NameTransfer<NamingSystem::Pascalcase, NamingSystem::Underscore, char>;
        extern template class NameTransfer<NamingSystem::Pascalcase, NamingSystem::Camelcase, char>;
        extern template class NameTransfer<NamingSystem::Pascalcase, NamingSystem::UpperUnderscore, char>;

        extern template class NameTransfer<NamingSystem::UpperUnderscore, NamingSystem::Underscore, char>;
        extern template class NameTransfer<NamingSystem::UpperUnderscore, NamingSystem::Camelcase, char>;
        extern template class NameTransfer<NamingSystem::UpperUnderscore, NamingSystem::Pascalcase, char>;
    };
};
