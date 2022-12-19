#pragma once

#include <ospf/string.hpp>
#include <ospf/meta_programming/name_transfer/frontend.hpp>
#include <ospf/meta_programming/name_transfer/backend.hpp>
#include <shared_mutex>

namespace ospf
{
    inline namespace meta_programming
    {
        // todo: use memory pool, advanced pointer and advanced reference
        template<NamingSystem frontend, NamingSystem backend>
        class NameTransfer
        {
        public:
            static constexpr const NamingSystem from = frontend;
            static constexpr const NamingSystem to = backend;
            using Frontend = name_transfer::Frontend<frontend>;
            using Backend = name_transfer::Backend<backend>;

        public:
            NameTransfer(void) = default;
            NameTransfer(const NameTransfer& ano) = delete;
            NameTransfer(NameTransfer&& ano) noexcept = default;
            NameTransfer& operator=(const NameTransfer& rhs) = delete;
            NameTransfer& operator=(const NameTransfer&& rhs) = delete;
            ~NameTransfer(void) noexcept = default;

        public:
            OSPF_BASE_API static const NameTransfer<frontend, backend>& instance(void) noexcept
            {
                static const NameTransfer* const _instance = new NameTransfer<frontend, backend>{};
                return *_instance;
            }

        public:
            OSPF_BASE_API const std::string_view operator()(const std::string_view name) const noexcept
            {
                static constexpr const Frontend transfer_frontend{};
                static constexpr const Backend transfer_backend{};

                auto it = m_cache.find(name);
#ifdef OSPF_MULTI_THREAD
                m_mutex.lock_shared();
                if (it == m_cache.cend())
                {
                    m_mutex.unlock_shared();
                    m_mutex.lock();
                    it = m_cache.find(name);
                    if (it == m_cache.cend())
                    {
                        const auto il = transfer_frontend(name);
                        it = m_cache.insert(std::make_pair(std::string{ name }, transfer_backend(std::span{ il }))).first;
                    }
                    const auto& ret = it->second;
                    m_mutex.unlock();
                    return ret;
                }
                else
                {
                    const auto& ret = it->second;
                    m_mutex.unlock_shared();
                    return ret;
                };
#else
                if (it == m_cache.cend())
                {
                    const auto il = transfer_frontend(name);
                    it = m_cache.insert(std::make_pair(std::string{ name }, transfer_backend(std::span{ il }))).first;
                }
                return it->second;
#endif
            }

            OSPF_BASE_API const std::string_view reverse(const std::string_view name) const noexcept
            {
                static const auto& reversed_transfer = NameTransfer<backend, frontend>::instance();
                return reversed_transfer(name);
            }

        private:
#ifdef OSPF_MULTI_THREAD
            mutable std::shared_mutex m_mutex;
#endif
            mutable StringHashMap<std::string, std::string> m_cache;
        };

        extern template class NameTransfer<NamingSystem::Underscore, NamingSystem::Camelcase>;
        extern template class NameTransfer<NamingSystem::Underscore, NamingSystem::Pascalcase>;
        extern template class NameTransfer<NamingSystem::Underscore, NamingSystem::UpperUnderscore>;

        extern template class NameTransfer<NamingSystem::Camelcase, NamingSystem::Underscore>;
        extern template class NameTransfer<NamingSystem::Camelcase, NamingSystem::Pascalcase>;
        extern template class NameTransfer<NamingSystem::Camelcase, NamingSystem::UpperUnderscore>;

        extern template class NameTransfer<NamingSystem::Pascalcase, NamingSystem::Underscore>;
        extern template class NameTransfer<NamingSystem::Pascalcase, NamingSystem::Camelcase>;
        extern template class NameTransfer<NamingSystem::Pascalcase, NamingSystem::UpperUnderscore>;

        extern template class NameTransfer<NamingSystem::UpperUnderscore, NamingSystem::Underscore>;
        extern template class NameTransfer<NamingSystem::UpperUnderscore, NamingSystem::Camelcase>;
        extern template class NameTransfer<NamingSystem::UpperUnderscore, NamingSystem::Pascalcase>;
    };
};
