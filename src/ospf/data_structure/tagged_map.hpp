#pragma once

#include <ospf/concepts/with_tag.hpp>
#include <ospf/memory/reference.hpp>

namespace ospf
{
    inline namespace data_structure
    {
        namespace tagged_map
        {
            template<typename T>
                requires WithTag<T>
            struct DefaultTagExtractor
            {
                inline decltype(auto) operator()(CLRefType<T> ele) const noexcept
                {
                    return TagValue<T>::value(ele);
                }
            };

            template<
                typename T,
                template<typename V> class E,
                template<typename K, typename V> class C
            >
                requires NotSameAs<std::invoke_result_t<E<T>, T>, void>
            class TaggedMap;

            template<
                typename T,
                template<typename V> class E,
                template<typename K, typename V> class C
            >
                requires NotSameAs<std::invoke_result_t<E<T>, T>, void>
            class TaggedMapConstIterator
            {
                friend class TaggedMap<T, E, C>;

            public:
                using KeyExtratorType = E<T>;
                using KeyType = OriginType<std::invoke_result_t<KeyExtratorType, T>>;
                using ValueType = OriginType<T>;
                using MapType = C<KeyType, ValueType>;
                using IterType = typename MapType::const_iterator;
                
            public:
                TaggedMapConstIterator(const IterType it)
                    : _iter(it) {}
                TaggedMapConstIterator(const TaggedMapConstIterator& ano) = default;
                TaggedMapConstIterator(TaggedMapConstIterator&& ano) noexcept = default;
                TaggedMapConstIterator& operator=(const TaggedMapConstIterator& rhs) = default;
                TaggedMapConstIterator& operator=(TaggedMapConstIterator&& rhs) noexcept = default;
                ~TaggedMapConstIterator(void) noexcept = default;

            public:
                inline const T& operator*(void) const noexcept
                {
                    return _iter->second;
                }

                inline const CPtrType<T> operator->(void) const noexcept
                {
                    return &_iter->second;
                }

                inline TaggedMapConstIterator& operator++(void) noexcept
                {
                    ++_iter;
                    return *this;
                }

                inline TaggedMapConstIterator& operator++(int) noexcept
                {
                    TaggedMapConstIterator ret{ *this };
                    ++_iter;
                    return *this;
                }

                inline TaggedMapConstIterator& operator--(void) noexcept
                {
                    --_iter;
                    return *this;
                }

                inline TaggedMapConstIterator& operator--(int) noexcept
                {
                    TaggedMapConstIterator ret{ *this };
                    --_iter;
                    return *this;
                }

                inline const bool operator==(const TaggedMapConstIterator& rhs) const noexcept
                {
                    return _iter == rhs._iter;
                }

                inline const bool operator!=(const TaggedMapConstIterator& rhs) const noexcept
                {
                    return _iter != rhs._iter;
                }

            private:
                IterType _iter;
            };

            template<
                typename T,
                template<typename V> class E,
                template<typename K, typename V> class C
            >
                requires NotSameAs<std::invoke_result_t<E<T>, T>, void>
            class TaggedMapIterator
            {
                friend class TaggedMap<T, E, C>;

            public:
                using KeyExtratorType = E<T>;
                using KeyType = OriginType<std::invoke_result_t<KeyExtratorType, T>>;
                using ValueType = OriginType<T>;
                using MapType = C<KeyType, ValueType>;
                using IterType = typename MapType::iterator;

            public:
                TaggedMapIterator(const IterType it)
                    : _iter(it) {}
                TaggedMapIterator(const TaggedMapIterator& ano) = default;
                TaggedMapIterator(TaggedMapIterator&& ano) noexcept = default;
                TaggedMapIterator& operator=(const TaggedMapIterator& rhs) = default;
                TaggedMapIterator& operator=(TaggedMapIterator&& rhs) noexcept = default;
                ~TaggedMapIterator(void) noexcept = default;

            public:
                inline ValueType& operator*(void) const noexcept
                {
                    return _iter->second;
                }

                inline const PtrType<ValueType> const operator->(void) const noexcept
                {
                    return &_iter->second;
                }

                inline operator TaggedMapConstIterator<T, E, C>(void) const noexcept
                {
                    return TaggedMapConstIterator<T, E, C>{ static_cast<typename MapType::const_iterator>(_iter) };
                }

                inline TaggedMapIterator& operator++(void) noexcept
                {
                    ++_iter;
                    return *this;
                }

                inline TaggedMapIterator& operator++(int) noexcept
                {
                    TaggedMapIterator ret{ *this };
                    ++_iter;
                    return *this;
                }

                inline TaggedMapIterator& operator--(void) noexcept
                {
                    --_iter;
                    return *this;
                }

                inline TaggedMapIterator& operator--(int) noexcept
                {
                    TaggedMapIterator ret{ *this };
                    --_iter;
                    return *this;
                }

                inline const bool operator==(const TaggedMapIterator& rhs) const noexcept
                {
                    return _iter == rhs._iter;
                }

                inline const bool operator!=(const TaggedMapIterator& rhs) const noexcept
                {
                    return _iter != rhs._iter;
                }

                inline const bool operator==(const TaggedMapConstIterator<T, E, C>& rhs) const noexcept
                {
                    return static_cast<TaggedMapConstIterator<T, E, C>>(*this) == rhs;
                }

                inline const bool operator!=(const TaggedMapConstIterator<T, E, C>& rhs) const noexcept
                {
                    return static_cast<TaggedMapConstIterator<T, E, C>>(*this) != rhs;
                }

            private:
                IterType _iter;
            };

            template<
                typename T,
                template<typename V> class E,
                template<typename K, typename V> class C
            >
                requires NotSameAs<std::invoke_result_t<E<T>, T>, void>
            class TaggedMapEntry
            {
            public:
                using SelfType = TaggedMap<T, E, C>;
                using ValueType = typename SelfType::ValueType;
                using IteratorType = typename SelfType::IteratorType;

            public:
                TaggedMapEntry(const SelfType& map)
                    : _iter(std::nullopt), _map(map) {}
                TaggedMapEntry(const IteratorType iter, const SelfType& map)
                    : _iter(iter), _map(map) {}

            public:
                TaggedMapEntry(const TaggedMapEntry& ano) = delete;
                TaggedMapEntry(TaggedMapEntry&& ano) noexcept = default;
                TaggedMapEntry& operator=(const TaggedMapEntry& rhs) = delete;
                TaggedMapEntry& operator=(TaggedMapEntry&& rhs) = delete;
                ~TaggedMapEntry(void) noexcept = default;

            public:
                inline ValueType& operator*(void) noexcept
                {
                    return _iter.value()->second;
                }

                inline const PtrType<ValueType> const operator->(void) noexcept
                {
                    return &_iter.value()->second;
                }

                inline const ValueType& operator*(void) const noexcept
                {
                    return _iter.value()->second;
                }

                inline const CPtrType<ValueType> const operator->(void) const noexcept
                {
                    return &_iter.value()->second;
                }

                inline operator ValueType&(void)
                {
                    return *_iter;
                }

                inline operator const ValueType&(void) const
                {
                    return *_iter;
                }

            public:
                inline TaggedMapEntry<T, E, C>& or_insert(CLRefType<ValueType> value)
                {
                    const auto [iter, succeeded] = _map->insert(value);
                    if (succeeded)
                    {
                        _iter = iter;
                    }
                    return *this;
                }

                template<typename = void>
                    requires ReferenceFaster<ValueType> && std::movable<ValueType>
                inline TaggedMapEntry<T, E, C>& or_insert(RRefType<ValueType> value)
                {
                    const auto [iter, succeeded] = _map->insert(move<ValueType>(value));
                    if (succeeded)
                    {
                        _iter = iter;
                    }
                    return *this;
                }

                template<typename U>
                    requires std::is_convertible_v<U, ValueType>
                inline TaggedMapEntry<T, E, C>& or_insert(CLRefType<U> value)
                {
                    const auto [iter, succeeded] = _map->insert(ValueType{ value });
                    if (succeeded)
                    {
                        _iter = iter;
                    }
                    return *this;
                }

                template<typename U>
                    requires ReferenceFaster<U> && std::is_convertible_v<U, ValueType> && std::movable<U>
                inline TaggedMapEntry<T, E, C>& or_insert(RRefType<U> value)
                {
                    const auto [iter, succeeded] = _map->insert(ValueType{ move<U>(value) });
                    if (succeeded)
                    {
                        _iter = iter;
                    }
                    return *this;
                }

            private:
                std::optional<IteratorType> _iter;
                Ref<SelfType> _map;
            };

            template<
                typename T,
                template<typename V> class E,
                template<typename K, typename V> class C
            >
                requires NotSameAs<std::invoke_result_t<E<T>, T>, void>
            class TaggedMap
            {
            public:
                using KeyExtratorType = E<T>;
                using KeyType = OriginType<std::invoke_result_t<KeyExtratorType, T>>;
                using ValueType = OriginType<T>;
                using MapType = C<KeyType, ValueType>;
                using ConstIteratorType = TaggedMapConstIterator<T, E, C>;
                using IteratorType = TaggedMapIterator<T, E, C>;
                using EntryType = TaggedMapEntry<T, E, C>;

            public:
                TaggedMap(KeyExtratorType key_extractor = KeyExtratorType{})
                    : _key_extractor(move<KeyExtratorType>(key_extractor)) {}

                template<typename It>
                TaggedMap(const It first, const It last, KeyExtratorType key_extractor = KeyExtratorType{})
                    : TaggedMap(move<KeyExtratorType>(key_extractor))
                {
                    _map.insert(first, last);
                }

                TaggedMap(std::initializer_list<ValueType> eles, KeyExtratorType key_extractor = KeyExtratorType{})
                    : TaggedMap(move<KeyExtratorType>(key_extractor))
                {
                    _map.insert(std::move(eles));
                }

                template<typename U>
                    requires std::is_convertible_v<U, ValueType>
                TaggedMap(std::initializer_list<U> eles, KeyExtratorType key_extractor = KeyExtratorType{})
                    : TaggedMap(move<KeyExtratorType>(key_extractor))
                {
                    _map.insert(std::move(eles));
                }

            public:
                TaggedMap(const TaggedMap& ano) = default;
                TaggedMap(TaggedMap&& ano) noexcept = default;
                TaggedMap& operator=(const TaggedMap& rsh) = default;
                TaggedMap& operator=(TaggedMap&& rhs) noexcept = default;
                ~TaggedMap(void) = default;

            public:
                inline decltype(auto) begin(void) noexcept
                {
                    return IteratorType{ _map.begin() };
                }

                inline decltype(auto) begin(void) const noexcept
                {
                    return ConstIteratorType{ _map.begin() };
                }

                inline decltype(auto) cbegin(void) const noexcept
                {
                    return ConstIteratorType{ _map.cbegin() };
                }

                inline decltype(auto) end(void) noexcept
                {
                    return IteratorType{ _map.end() };
                }

                inline decltype(auto) end(void) const noexcept
                {
                    return ConstIteratorType{ _map.end() };
                }

                inline decltype(auto) cend(void) const noexcept
                {
                    return ConstIteratorType{ _map.cend() };
                }

            public:
                inline const bool empty(void) const noexcept
                {
                    return _map.empty();
                }

                inline const usize size(void) const noexcept
                {
                    return _map.size();
                }

                inline const usize max_size(void) const noexcept
                {
                    return _map.max_size();
                }

            public:
                inline void clear(void) noexcept
                {
                    return _map.clear();
                }

                inline decltype(auto) insert(CLRefType<ValueType> value)
                {
                    const auto [iter, succeeded] = _map.insert(std::make_pair(_key_extractor(value), value));
                    return std::make_pair(IteratorType{ iter }, succeeded);
                }

                template<typename = void>
                    requires ReferenceFaster<ValueType> && std::movable<ValueType>
                inline decltype(auto) insert(RRefType<ValueType> value)
                {
                    const auto [iter, succeeded] = _map.insert(std::make_pair(_key_extractor(value), move<ValueType>(value)));
                    return std::make_pair(IteratorType{ iter }, succeeded);
                }

                template<typename U>
                    requires std::is_convertible_v<U, ValueType>
                inline decltype(auto) insert(CLRefType<U> value)
                {
                    return insert(ValueType{ value });
                }

                template<typename U>
                    requires ReferenceFaster<U> && std::is_convertible_v<U, ValueType> && std::movable<U>
                inline decltype(auto) insert(RRefType<U> value)
                {
                    return insert(ValueType{ move<U>(value) });
                }

                template<typename It>
                inline void insert(It first, const It last)
                {
                    while (first != last)
                    {
                        insert(*first);
                        ++first;
                    }
                }

                inline void insert(std::initializer_list<ValueType> eles)
                {
                    for (auto& ele : eles)
                    {
                        insert(move<ValueType>(ele));
                    }
                }

                template<typename U>
                    requires std::is_convertible_v<U, ValueType>
                inline void insert(std::initializer_list<U> eles)
                {
                    for (auto& ele : eles)
                    {
                        insert(ValueType{ move<U>(ele) });
                    }
                }

                inline decltype(auto) insert_or_assign(CLRefType<ValueType> value)
                {
                    const auto [iter, succeeded] = _map.insert_or_assign(_key_extractor(value), value);
                    return std::make_pair(IteratorType{ iter }, succeeded);
                }

                template<typename = void>
                    requires ReferenceFaster<ValueType> && std::movable<ValueType>
                inline decltype(auto) insert_or_assign(RRefType<ValueType> value)
                {
                    const auto [iter, succeeded] = _map.insert_or_assign(_key_extractor(value), move<ValueType>(value));
                    return std::make_pair(IteratorType{ iter }, succeeded);
                }

                template<typename U>
                    requires std::is_convertible_v<U, ValueType>
                inline decltype(auto) insert_or_assign(CLRefType<U> value)
                {
                    return insert_or_assign(ValueType{ value });
                }

                template<typename U>
                    requires ReferenceFaster<U> && std::is_convertible_v<U, ValueType> && std::movable<U>
                inline decltype(auto) insert_or_assign(RRefType<U> value)
                {
                    return insert_or_assign(ValueType{ move<U>(value) });
                }
                
                inline decltype(auto) erase(const IteratorType iter)
                {
                    return IteratorType{ _map.erase(iter._iter) };
                }

                inline decltype(auto) erase(const ConstIteratorType iter)
                {
                    return IteratorType{ _map.erase(iter._iter) };
                }

                inline decltype(auto) erase(const ConstIteratorType first, const ConstIteratorType last)
                {
                    return IteratorType{ _map.erase(first._iter, last._iter) };
                }

                inline const usize erase(CLRefType<KeyType> key)
                {
                    return static_cast<usize>(_map.erase(key));
                }

                inline const usize erase(CLRefType<ValueType> value)
                {
                    return erase(_key_extractor(value));
                }

                template<typename K>
                inline const usize erase(CLRefType<K> key)
                {
                    return static_cast<usize>(_map.erase(key));
                }

                void swap(TaggedMap& other) noexcept
                {
                    std::swap(_key_extractor, other._key_extractor);
                    std::swap(_map, other._map);
                }

                void merge(const TaggedMap& other)
                {
                    _map.merge(other._map);
                }

                void merge(TaggedMap&& other)
                {
                    _map.merge(std::move(other._map));
                }

                template<template<typename K, typename V> class C2>
                void merge(const TaggedMap<T, E, C2>& other)
                {
                    _map.merge(other._map);
                }

                template<template<typename K, typename V> class C2>
                void merge(TaggedMap<T, E, C2>&& other)
                {
                    _map.merge(std::move(other._map));
                }

            public:
                inline decltype(auto) at(CLRefType<KeyType> key)
                {
                    return _map.at(key);
                }

                inline decltype(auto) at(CLRefType<KeyType> key) const
                {
                    return _map.at(key);
                }

                inline decltype(auto) operator[](CLRefType<KeyType> key)
                {
                    return _map.at(key);
                }

                inline decltype(auto) operator[](CLRefType<KeyType> key) const
                {
                    return _map.at(key);
                }

                inline decltype(auto) find(CLRefType<KeyType> key) noexcept
                {
                    return IteratorType{ _map.find(key) };
                }

                inline decltype(auto) find(CLRefType<KeyType> key) const noexcept
                {
                    return ConstIteratorType{ _map.find(key) };
                }

                inline decltype(auto) find(CLRefType<ValueType> value) noexcept
                {
                    return find(_key_extractor(value));
                }

                inline decltype(auto) find(CLRefType<ValueType> value) const noexcept
                {
                    return find(_key_extractor(value));
                }

                template<typename K>
                inline decltype(auto) find(CLRefType<K> key) noexcept
                {
                    return IteratorType{ _map.find(key) };
                }

                template<typename K>
                inline decltype(auto) find(CLRefType<K> key) const noexcept
                {
                    return ConstIteratorType{ _map.find(key) };
                }

                inline decltype(auto) entry(CLRefType<KeyType> key) noexcept
                {
                    const auto iter = find(key);
                    return iter == end() ? EntryType{ *this } : EntryType{ iter, *this };
                }

                template<typename K>
                inline decltype(auto) entry(CLRefType<K> key) noexcept
                {
                    const auto iter = find(key);
                    return iter == end() ? EntryType{ *this } : EntryType{ iter, *this };
                }

                inline decltype(auto) contains(CLRefType<KeyType> key) const noexcept
                {
                    return _map.contains(key);
                }

                inline decltype(auto) contains(CLRefType<ValueType> value) const noexcept
                {
                    return contains(_key_extractor(value));
                }

                template<typename K>
                inline decltype(auto) contains(CLRefType<K> key) const noexcept
                {
                    return _map.contains(key);
                }

                inline decltype(auto) equal_range(CLRefType<KeyType> key)
                {
                    const auto [bg_it, ed_it] = _map.equal_range(key);
                    return std::make_pair(IteratorType{ bg_it }, IteratorType{ ed_it });
                }

                inline decltype(auto) equal_range(CLRefType<KeyType> key) const
                {
                    const auto [bg_it, ed_it] = _map.equal_range(key);
                    return std::make_pair(ConstIteratorType{ bg_it }, ConstIteratorType{ ed_it });
                }

                template<typename K>
                inline decltype(auto) equal_range(CLRefType<K> key)
                {
                    const auto [bg_it, ed_it] = _map.equal_range(key);
                    return std::make_pair(IteratorType{ bg_it }, IteratorType{ ed_it });
                }

                template<typename K>
                inline decltype(auto) equal_range(CLRefType<K> key) const
                {
                    const auto [bg_it, ed_it] = _map.equal_range(key);
                    return std::make_pair(ConstIteratorType{ bg_it }, ConstIteratorType{ ed_it });
                }

            private:
                KeyExtratorType _key_extractor;
                MapType _map;
            };
        };

        template<
            typename T, 
            template<typename V> class E = tagged_map::DefaultTagExtractor,
            template<typename K, typename V> class C = std::unordered_map
        >
        using TaggedMap = tagged_map::TaggedMap<OriginType<T>, E, C>;

        template<
            typename T,
            template<typename V> class E = tagged_map::DefaultTagExtractor,
            template<typename K, typename V> class C = std::unordered_multimap
        >
        using TaggedMultiMap = tagged_map::TaggedMap<OriginType<T>, E, C>;
    };
};
