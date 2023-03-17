﻿#pragma once

#include <ospf/string.hpp>
#include <ospf/meta_programming/name_transfer/frontend.hpp>
#include <ospf/meta_programming/name_transfer/backend.hpp>
#include <ospf/memory/pointer.hpp>
#include <shared_mutex>

namespace ospf
{
    inline namespace meta_programming
    {
        template<NamingSystem frontend, NamingSystem backend, CharType CharT = char>
        class NameTransfer
        {
        public:
            static constexpr const NamingSystem from = frontend;
            static constexpr const NamingSystem to = backend;
            using Frontend = name_transfer::Frontend<frontend, CharT>;
            using Backend = name_transfer::Backend<backend, CharT>;
            using StringType = std::basic_string<CharT>;
            using StringViewType = std::basic_string_view<CharT>;

        public:
            NameTransfer(void) = default;
            NameTransfer(const NameTransfer& ano) = delete;
            NameTransfer(NameTransfer&& ano) noexcept = default;
            NameTransfer& operator=(const NameTransfer& rhs) = delete;
            NameTransfer& operator=(const NameTransfer&& rhs) = delete;
            ~NameTransfer(void) noexcept = default;

        public:
            inline static const NameTransfer& instance(void) noexcept
            {
                static const NameTransfer* const _instance = new NameTransfer{};
                return *_instance;
            }

        public:
            inline const StringViewType operator()(const std::string_view name) const noexcept
            {
                static constexpr const Frontend transfer_frontend{};
                static constexpr const Backend transfer_backend{};

                auto it = _cache1.find(name);
#ifdef OSPF_MULTI_THREAD
                _mutex.lock_shared();
                if (it == _cache1.cend())
                {
                    _mutex.unlock_shared();
                    _mutex.lock();
                    it = _cache1.find(name);
                    if (it == _cache1.cend())
                    {
                        std::string str{ name };
                        const auto il = transfer_frontend(boost::locale::conv::to_utf<CharT>(str, std::locale{}));
                        it = _cache1.insert(std::make_pair(std::move(str), transfer_backend(std::span<const StringViewType>{ il }))).first;
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
                }
#else
                if (it == _cache1.cend())
                {
                    std::string str{ name };
                    const auto il = transfer_frontend(boost::locale::conv::to_utf<CharT>(str, std::locale{}));
                    it = _cache1.insert(std::makie_pair(std::move(str), transfer_backend(std::span<const StringViewType>{ il }))).first;
                }
                return it->second;
#endif
            }

            inline const StringViewType operator()(const StringViewType name) const noexcept
            {
                static constexpr const Frontend transfer_frontend{};
                static constexpr const Backend transfer_backend{};

                auto it = _cache2.find(name);
#ifdef OSPF_MULTI_THREAD
                _mutex.lock_shared();
                if (it == _cache2.cend())
                {
                    _mutex.unlock_shared();
                    _mutex.lock();
                    it = _cache2.find(name);
                    if (it == _cache2.cend())
                    {
                        const auto il = transfer_frontend(name);
                        it = _cache2.insert(std::make_pair(StringType{ name }, transfer_backend(std::span<const StringViewType>{ il }))).first;
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
                if (it == _cache2.cend())
                {
                    const auto il = transfer_frontend(name);
                    it = _cache2.insert(std::make_pair(StringType{ name }, transfer_backend(std::span<const StringViewType>{ il }))).first;
                }
                return it->second;
#endif
            }

            inline const StringViewType reverse(const std::string_view name) const noexcept
            {
                static const auto& reversed_transfer = NameTransfer<backend, frontend, CharT>::instance();
                return reversed_transfer(name);
            }

            inline const StringViewType reverse(const StringViewType name) const noexcept
            {
                static const auto& reversed_transfer = NameTransfer<backend, frontend, CharT>::instance();
                return reversed_transfer(name);
            }

        private:
#ifdef OSPF_MULTI_THREAD
            mutable std::shared_mutex _mutex;
#endif
            mutable StringHashMap<std::string, std::basic_string<CharT>> _cache1;
            mutable StringHashMap<std::basic_string<CharT>, std::basic_string<CharT>> _cache2;
        };

        template<NamingSystem frontend, NamingSystem backend>
        class NameTransfer<frontend, backend, char>
        {
        public:
            static constexpr const NamingSystem from = frontend;
            static constexpr const NamingSystem to = backend;
            using Frontend = name_transfer::Frontend<frontend, char>;
            using Backend = name_transfer::Backend<backend, char>;
            using StringType = std::string;
            using StringViewType = std::string_view;

        public:
            NameTransfer(void) = default;
            NameTransfer(const NameTransfer& ano) = delete;
            NameTransfer(NameTransfer&& ano) noexcept = default;
            NameTransfer& operator=(const NameTransfer& rhs) = delete;
            NameTransfer& operator=(const NameTransfer&& rhs) = delete;
            ~NameTransfer(void) noexcept = default;

        public:
            inline static const NameTransfer& instance(void) noexcept
            {
                static const NameTransfer* const _instance = new NameTransfer{};
                return *_instance;
            }

        public:
            inline const StringViewType operator()(const StringViewType name) const noexcept
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
                        it = _cache.insert(std::make_pair(StringType{ name }, transfer_backend(std::span<const StringViewType>{ il }))).first;
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
                    it = _cache.insert(std::make_pair(StringType{ name }, transfer_backend(std::span<const StringViewType>{ il }))).first;
                }
                return it->second;
#endif
            }

            inline const StringViewType reverse(const StringViewType name) const noexcept
            {
                static const auto& reversed_transfer = NameTransfer<backend, frontend, char>::instance();
                return reversed_transfer(name);
            }

        private:
#ifdef OSPF_MULTI_THREAD
            mutable std::shared_mutex _mutex;
#endif
            mutable StringHashMap<std::string, std::string> _cache;
        };

        extern template class NameTransfer<NamingSystem::Underscore, NamingSystem::Camelcase, char>;
        extern template class NameTransfer<NamingSystem::Underscore, NamingSystem::Pascalcase, char>;
        extern template class NameTransfer<NamingSystem::Underscore, NamingSystem::UpperUnderscore, char>;
        extern template class NameTransfer<NamingSystem::Underscore, NamingSystem::Camelcase, wchar>;
        extern template class NameTransfer<NamingSystem::Underscore, NamingSystem::Pascalcase, wchar>;
        extern template class NameTransfer<NamingSystem::Underscore, NamingSystem::UpperUnderscore, wchar>;

        extern template class NameTransfer<NamingSystem::Camelcase, NamingSystem::Underscore, char>;
        extern template class NameTransfer<NamingSystem::Camelcase, NamingSystem::Pascalcase, char>;
        extern template class NameTransfer<NamingSystem::Camelcase, NamingSystem::UpperUnderscore, char>;
        extern template class NameTransfer<NamingSystem::Camelcase, NamingSystem::Underscore, wchar>;
        extern template class NameTransfer<NamingSystem::Camelcase, NamingSystem::Pascalcase, wchar>;
        extern template class NameTransfer<NamingSystem::Camelcase, NamingSystem::UpperUnderscore, wchar>;

        extern template class NameTransfer<NamingSystem::Pascalcase, NamingSystem::Underscore, char>;
        extern template class NameTransfer<NamingSystem::Pascalcase, NamingSystem::Camelcase, char>;
        extern template class NameTransfer<NamingSystem::Pascalcase, NamingSystem::UpperUnderscore, char>;
        extern template class NameTransfer<NamingSystem::Pascalcase, NamingSystem::Underscore, wchar>;
        extern template class NameTransfer<NamingSystem::Pascalcase, NamingSystem::Camelcase, wchar>;
        extern template class NameTransfer<NamingSystem::Pascalcase, NamingSystem::UpperUnderscore, wchar>;

        extern template class NameTransfer<NamingSystem::UpperUnderscore, NamingSystem::Underscore, char>;
        extern template class NameTransfer<NamingSystem::UpperUnderscore, NamingSystem::Camelcase, char>;
        extern template class NameTransfer<NamingSystem::UpperUnderscore, NamingSystem::Pascalcase, char>;
        extern template class NameTransfer<NamingSystem::UpperUnderscore, NamingSystem::Underscore, wchar>;
        extern template class NameTransfer<NamingSystem::UpperUnderscore, NamingSystem::Camelcase, wchar>;
        extern template class NameTransfer<NamingSystem::UpperUnderscore, NamingSystem::Pascalcase, wchar>;
    };
};
