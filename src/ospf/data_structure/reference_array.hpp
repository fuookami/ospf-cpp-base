#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/concepts/with_default.hpp>
#include <ospf/literal_constant.hpp>
#include <ospf/memory/reference.hpp>
#include <ospf/functional/iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>

namespace ospf
{
    inline namespace data_structure
    {
        namespace reference_array
        {
            template<
                typename T,
                usize len,
                reference::ReferenceCategory cat,
                template<typename T, usize l> class C
            >
            class StaticReferenceArray;

            template<
                typename T,
                reference::ReferenceCategory cat,
                template<typename T> class C
            >
            class DynamicReferenceArray;

            template<typename T, reference::ReferenceCategory cat, typename C>
            class ReferenceArrayConstIterator
                : public RandomIteratorImpl<OriginType<T>, typename OriginType<C>::const_iterator, ReferenceArrayConstIterator<T, cat, C>>
            {
                template<
                    typename T,
                    usize len,
                    reference::ReferenceCategory cat,
                    template<typename T, usize l> class C
                >
                friend class StaticReferenceArray;

                template<
                    typename T,
                    reference::ReferenceCategory cat,
                    template<typename T> class C
                >
                friend class DynamicReferenceArray;

            public:
                using ValueType = OriginType<T>;
                using ContainerType = OriginType<C>;
                using IterType = typename ContainerType::const_iterator;

            private:
                using Base = RandomIteratorImpl<ValueType, IterType, ReferenceArrayConstIterator<T, cat, C>>;

            public:
                constexpr ReferenceArrayConstIterator(ArgCLRefType<IterType> iter)
                    : Base(iter) {}
                constexpr ReferenceArrayConstIterator(const ReferenceArrayConstIterator& ano) = default;
                constexpr ReferenceArrayConstIterator(ReferenceArrayConstIterator&& ano) noexcept = default;
                constexpr ReferenceArrayConstIterator& operator=(const ReferenceArrayConstIterator& rhs) = default;
                constexpr ReferenceArrayConstIterator& operator=(ReferenceArrayConstIterator&& rhs) noexcept = default;
                constexpr ~ReferenceArrayConstIterator(void) noexcept = default;

            OSPF_CRTP_PERMISSION:
                inline static constexpr CLRefType<ValueType> OSPF_CRTP_FUNCTION(get)(ArgCLRefType<IterType> iter) noexcept
                {
                    return **iter;
                }

                inline static constexpr const ReferenceArrayConstIterator OSPF_CRTP_FUNCTION(construct)(ArgCLRefType<IterType> iter) noexcept
                {
                    return ReferenceArrayConstIterator{ iter };
                }
            };

            template<typename T, reference::ReferenceCategory cat, typename C>
            class ReferenceArrayIterator
                : public RandomIteratorImpl<OriginType<T>, typename OriginType<C>::iterator, ReferenceArrayIterator<T, cat, C>>
            {
                template<
                    typename T,
                    usize len,
                    reference::ReferenceCategory cat,
                    template<typename T, usize l> class C
                >
                friend class StaticReferenceArray;

                template<
                    typename T,
                    reference::ReferenceCategory cat,
                    template<typename T> class C
                >
                friend class DynamicReferenceArray;

            public:
                using ValueType = OriginType<T>;
                using ContainerType = OriginType<C>;
                using IterType = typename ContainerType::iterator;

            private:
                using Base = RandomIteratorImpl<ValueType, IterType, ReferenceArrayIterator<T, cat, C>>;

            public:
                constexpr ReferenceArrayIterator(ArgCLRefType<IterType> iter)
                    : Base(iter) {}
                constexpr ReferenceArrayIterator(const ReferenceArrayIterator& ano) = default;
                constexpr ReferenceArrayIterator(ReferenceArrayIterator&& ano) noexcept = default;
                constexpr ReferenceArrayIterator& operator=(const ReferenceArrayIterator& rhs) = default;
                constexpr ReferenceArrayIterator& operator=(ReferenceArrayIterator&& rhs) noexcept = default;
                constexpr ~ReferenceArrayIterator(void) noexcept = default;

            public:
                inline constexpr operator const ReferenceArrayConstIterator<T, cat, C>(void) const noexcept
                {
                    return ReferenceArrayConstIterator<T, cat, C>{ this->_iter };
                }

            OSPF_CRTP_PERMISSION:
                inline static constexpr LRefType<ValueType> OSPF_CRTP_FUNCTION(get)(ArgCLRefType<IterType> iter) noexcept
                {
                    return **iter;
                }

                inline static constexpr const ReferenceArrayIterator OSPF_CRTP_FUNCTION(construct)(ArgCLRefType<IterType> iter) noexcept
                {
                    return ReferenceArrayIterator{ iter };
                }
            };

            template<typename T, reference::ReferenceCategory cat, typename C>
            class ReferenceArrayConstReverseIterator
            {
                template<
                    typename T,
                    usize len,
                    reference::ReferenceCategory cat,
                    template<typename T, usize l> class C
                >
                friend class StaticReferenceArray;

                template<
                    typename T,
                    reference::ReferenceCategory cat,
                    template<typename T> class C
                >
                friend class DynamicReferenceArray;

            public:
                using ValueType = OriginType<T>;
                using ContainerType = OriginType<C>;
                using IterType = typename ContainerType::const_reverse_iterator;

            private:
                using Base = RandomIteratorImpl<ValueType, IterType, ReferenceArrayConstReverseIterator<T, cat, C>>;

            public:
                constexpr ReferenceArrayConstReverseIterator(ArgCLRefType<IterType> iter)
                    : Base(iter) {}
                constexpr ReferenceArrayConstReverseIterator(const ReferenceArrayConstReverseIterator& ano) = default;
                constexpr ReferenceArrayConstReverseIterator(ReferenceArrayConstReverseIterator&& ano) noexcept = default;
                constexpr ReferenceArrayConstReverseIterator& operator=(const ReferenceArrayConstReverseIterator& rhs) = default;
                constexpr ReferenceArrayConstReverseIterator& operator=(ReferenceArrayConstReverseIterator&& rhs) noexcept = default;
                constexpr ~ReferenceArrayConstReverseIterator(void) noexcept = default;

            OSPF_CRTP_PERMISSION:
                inline static constexpr CLRefType<ValueType> OSPF_CRTP_FUNCTION(get)(ArgCLRefType<IterType> iter) noexcept
                {
                    return **iter;
                }

                inline static constexpr const ReferenceArrayConstReverseIterator OSPF_CRTP_FUNCTION(construct)(ArgCLRefType<IterType> iter) noexcept
                {
                    return ReferenceArrayConstReverseIterator{ iter };
                }
            };

            template<typename T, reference::ReferenceCategory cat, typename C>
            class ReferenceArrayReverseIterator
            {
                template<
                    typename T,
                    usize len,
                    reference::ReferenceCategory cat,
                    template<typename T, usize l> class C
                >
                friend class StaticReferenceArray;

                template<
                    typename T,
                    reference::ReferenceCategory cat,
                    template<typename T> class C
                >
                friend class DynamicReferenceArray;

            public:
                using ValueType = OriginType<T>;
                using ContainerType = OriginType<C>;
                using IterType = typename ContainerType::reverse_iterator;

            private:
                using Base = RandomIteratorImpl<ValueType, IterType, ReferenceArrayConstReverseIterator<T, cat, C>>;

            public:
                constexpr ReferenceArrayReverseIterator(ArgCLRefType<IterType> iter)
                    : Base(iter) {}
                constexpr ReferenceArrayReverseIterator(const ReferenceArrayReverseIterator& ano) = default;
                constexpr ReferenceArrayReverseIterator(ReferenceArrayReverseIterator&& ano) noexcept = default;
                constexpr ReferenceArrayReverseIterator& operator=(const ReferenceArrayReverseIterator& rhs) = default;
                constexpr ReferenceArrayReverseIterator& operator=(ReferenceArrayReverseIterator&& rhs) noexcept = default;
                constexpr ~ReferenceArrayReverseIterator(void) noexcept = default;

            OSPF_CRTP_PERMISSION:
                inline static constexpr LRefType<ValueType> OSPF_CRTP_FUNCTION(get)(ArgCLRefType<IterType> iter) noexcept
                {
                    return **iter;
                }

                inline static constexpr const ReferenceArrayReverseIterator OSPF_CRTP_FUNCTION(construct)(ArgCLRefType<IterType> iter) noexcept
                {
                    return ReferenceArrayReverseIterator{ iter };
                }
            };

            template<typename T, typename C>
            struct ReferenceArrayAccessPolicy;

            template<
                typename T,
                usize len,
                reference::ReferenceCategory cat,
                template<typename U, usize l> class C
            >
            struct ReferenceArrayAccessPolicy<T, C<reference::Ref<OriginType<T>, cat>, len>>
            {
            public:
                using ValueType = OriginType<T>;
                using ReferenceType = reference::Ref<ValueType, cat>;
                using ContainerType = C<ReferenceType, len>;
                using IterType = ReferenceArrayIterator<ValueType, cat, ContainerType>;
                using ConstIterType = ReferenceArrayConstIterator<ValueType, cat, ContainerType>;
                using ReverseIterType = ReferenceArrayReverseIterator<ValueType, cat, ContainerType>;
                using ConstReverseIterType = ReferenceArrayConstReverseIterator<ValueType, cat, ContainerType>;

            public:
                inline static constexpr const usize size(CLRefType<ContainerType> array) noexcept
                {
                    return len;
                }

                inline static constexpr LRefType<ValueType> get(LRefType<ContainerType> array, const usize i)
                {
                    return *array.at(i);
                }

                inline static constexpr CLRefType<ValueType> get(CLRefType<ContainerType> array, const usize i)
                {
                    return *array.at(i);
                }

                inline static constexpr LRefType<ValueType> get_unchecked(LRefType<ContainerType> array, const usize i)
                {
                    return *array[i];
                }

                inline static constexpr CLRefType<ValueType> get_unchecked(CLRefType<ContainerType> array, const usize i)
                {
                    return *array[i];
                }

            public:
                inline static constexpr RetType<IterType> begin(LRefType<ContainerType> array) noexcept
                {
                    return IterType{ array.begin() };
                }

                inline static constexpr RetType<ConstIterType> cbegin(CLRefType<ContainerType> array) noexcept
                {
                    return ConstIterType{ array.begin() };
                }

            public:
                inline static constexpr RetType<IterType> end(LRefType<ContainerType> array) noexcept
                {
                    return IterType{ array.end() };
                }

                inline static constexpr RetType<ConstIterType> cend(CLRefType<ContainerType> array) noexcept
                {
                    return ConstIterType{ array.end() };
                }

            public:
                inline static constexpr RetType<ReverseIterType> rbegin(LRefType<ContainerType> array) noexcept
                {
                    return ReverseIterType{ array.rbegin() };
                }

                inline static constexpr RetType<ConstReverseIterType> crbegin(CLRefType<ContainerType> array) noexcept
                {
                    return ConstReverseIterType{ array.rbegin() };
                }

            public:
                inline static constexpr RetType<ReverseIterType> rend(LRefType<ContainerType> array) noexcept
                {
                    return ReverseIterType{ array.rend() };
                }

                inline static constexpr RetType<ConstReverseIterType> crend(CLRefType<ContainerType> array) noexcept
                {
                    return ConstReverseIterType{ array.rend() };
                }
            };

            template<
                typename T,
                reference::ReferenceCategory cat,
                template<typename U> class C
            >
            struct ReferenceArrayAccessPolicy<T, C<reference::Ref<OriginType<T>, cat>>>
            {
            public:
                using ValueType = OriginType<T>;
                using ReferenceType = reference::Ref<ValueType, cat>;
                using ContainerType = C<ReferenceType>;
                using IterType = ReferenceArrayIterator<ValueType, cat, ContainerType>;
                using ConstIterType = ReferenceArrayConstIterator<ValueType, cat, ContainerType>;
                using ReverseIterType = ReferenceArrayReverseIterator<ValueType, cat, ContainerType>;
                using ConstReverseIterType = ReferenceArrayConstReverseIterator<ValueType, cat, ContainerType>;

            public:
                inline static constexpr const usize size(CLRefType<ContainerType> array) noexcept
                {
                    return array.size();
                }

                inline static constexpr LRefType<ValueType> get(LRefType<ContainerType> array, const usize i)
                {
                    return *array.at(i);
                }

                inline static constexpr CLRefType<ValueType> get(CLRefType<ContainerType> array, const usize i)
                {
                    return *array.at(i);
                }

                inline static constexpr LRefType<ValueType> get_unchecked(LRefType<ContainerType> array, const usize i)
                {
                    return *array[i];
                }

                inline static constexpr CLRefType<ValueType> get_unchecked(CLRefType<ContainerType> array, const usize i)
                {
                    return *array[i];
                }

            public:
                inline static constexpr RetType<IterType> begin(LRefType<ContainerType> array) noexcept
                {
                    return IterType{ array.begin() };
                }

                inline static constexpr RetType<ConstIterType> cbegin(CLRefType<ContainerType> array) noexcept
                {
                    return ConstIterType{ array.cbegin() };
                }

            public:
                inline static constexpr RetType<IterType> end(LRefType<ContainerType> array) noexcept
                {
                    return IterType{ array.end() };
                }

                inline static constexpr RetType<ConstIterType> cend(CLRefType<ContainerType> array) noexcept
                {
                    return ConstIterType{ array.cend() };
                }

            public:
                inline static constexpr RetType<ReverseIterType> rbegin(LRefType<ContainerType> array) noexcept
                {
                    return ReverseIterType{ array.rbegin() };
                }

                inline static constexpr RetType<ConstReverseIterType> crbegin(CLRefType<ContainerType> array) noexcept
                {
                    return ConstReverseIterType{ array.crbegin() };
                }

            public:
                inline static constexpr RetType<ReverseIterType> rend(LRefType<ContainerType> array) noexcept
                {
                    return ReverseIterType{ array.rend() };
                }

                inline static constexpr RetType<ConstReverseIterType> crend(CLRefType<ContainerType> array) noexcept
                {
                    return ConstReverseIterType{ array.crend() };
                }
            };

            template<typename T, typename C, typename Self>
            class ReferenceArrayImpl
            {
                OSPF_CRTP_IMPL

            public:
                using ValueType = OriginType<T>;
                using ContainerType = OriginType<C>;
                using AccessPolicyType = ReferenceArrayAccessPolicy<ValueType, ContainerType>;
                using ReferenceType = typename AccessPolicyType::ReferenceType;
                using IterType = typename AccessPolicyType::IterType;
                using ConstIterType = typename AccessPolicyType::ConstIterType;
                using ReverseIterType = typename AccessPolicyType::ReverseIterType;
                using ConstReverseIterType = typename AccessPolicyType::ConstReverseIterType;

            protected:
                constexpr ReferenceArrayImpl(void) = default;
            public:
                constexpr ReferenceArrayImpl(const ReferenceArrayImpl& ano) = default;
                constexpr ReferenceArrayImpl(ReferenceArrayImpl&& ano) noexcept = default;
                constexpr ReferenceArrayImpl& operator=(const ReferenceArrayImpl& rhs) = default;
                constexpr ReferenceArrayImpl& operator=(ReferenceArrayImpl&& rhs) noexcept = default;
                constexpr ~ReferenceArrayImpl(void) noexcept = default;

            public:
                inline constexpr LRefType<ValueType> at(const usize i)
                {
                    return AccessPolicyType::get(container(), i);
                }

                inline constexpr CLRefType<ValueType> at(const usize i) const
                {
                    return AccessPolicyType::get(const_container(), i);
                }

                inline constexpr LRefType<ValueType> operator[](const usize i)
                {
                    return AccessPolicyType::get_unchecked(container(), i);
                }

                inline constexpr CLRefType<ValueType> operator[](const usize i) const
                {
                    return AccessPolicyType::get_unchecked(const_container(), i);
                }

            public:
                inline constexpr LRefType<ValueType> front(void)
                {
                    return at(0_uz);
                }

                inline constexpr CLRefType<ValueType> front(void) const
                {
                    return at(0_uz);
                }

                inline constexpr LRefType<ValueType> back(void)
                {
                    return at(size() - 1_uz);
                }

                inline constexpr CLRefType<ValueType> back(void) const
                {
                    return at(size() - 1_uz);
                }

            public:
                inline constexpr RetType<IterType> begin(void) noexcept
                {
                    return AccessPolicyType::begin(container());
                }

                inline constexpr RetType<ConstIterType> begin(void) const noexcept
                {
                    return AccessPolicyType::cbegin(const_container());
                }

                inline constexpr RetType<ConstIterType> cbegin(void) const noexcept
                {
                    return AccessPolicyType::cbegin(const_container());
                }

            public:
                inline constexpr RetType<IterType> end(void) noexcept
                {
                    return AccessPolicyType::end(container());
                }

                inline constexpr RetType<ConstIterType> end(void) const noexcept
                {
                    return AccessPolicyType::cend(const_container());
                }

                inline constexpr RetType<ConstIterType> cend(void) const noexcept
                {
                    return AccessPolicyType::cend(const_container());
                }

            public:
                inline constexpr RetType<ReverseIterType> rbegin(void) noexcept
                {
                    return AccessPolicyType::rbegin(container());
                }

                inline constexpr RetType<ConstReverseIterType> rbegin(void) const noexcept
                {
                    return AccessPolicyType::crbegin(const_container());
                }

                inline constexpr RetType<ConstReverseIterType> crbegin(void) const noexcept
                {
                    return AccessPolicyType::crbegin(const_container());
                }

            public:
                inline constexpr const bool empty(void) const noexcept
                {
                    return size() == 0_uz;
                }

                inline constexpr const usize size(void) const noexcept
                {
                    return AccessPolicyType::size(const_container());
                }

            public:
                inline void swap(ReferenceArrayImpl& ano) noexcept
                {
                    std::swap(container(), ano.container());
                }

            protected:
                inline constexpr LRefType<ContainerType> container(void) noexcept
                {
                    return Trait::get_container(self());
                }

                inline constexpr CLRefType<ContainerType> const_container(void) const noexcept
                {
                    return Trait::get_const_container(self());
                }

            private:
                struct Trait : public Self
                {
                    inline static constexpr LRefType<ContainerType> get_container(Self& self) noexcept
                    {
                        static const auto get_impl = &Self::OSPF_CRTP_FUNCTION(get_container);
                        return (self.*get_impl)();
                    }

                    inline static constexpr CLRefType<ContainerType> get_const_container(const Self& self) noexcept
                    {
                        static const auto get_impl = &Self::OSPF_CRTP_FUNCTION(get_const_container);
                        return (self.*get_impl)();
                    }
                };
            };

            template<
                typename T,
                usize len,
                reference::ReferenceCategory cat,
                template<typename T, usize l> class C
            >
            class StaticReferenceArray
                : public ReferenceArrayImpl<T, C<reference::Ref<OriginType<T>, cat>, len>, StaticReferenceArray<T, len, cat, C>>
            {
                using Impl = ReferenceArrayImpl<T, C<reference::Ref<OriginType<T>, cat>, len>, StaticReferenceArray<T, len, cat, C>>;

            public:
                using typename Impl::ValueType;
                using typename Impl::ReferenceType;
                using typename Impl::ContainerType;
                using typename Impl::IterType;
                using typename Impl::ConstIterType;
                using typename Impl::ReverseIterType;
                using typename Impl::ConstReverseIterType;

            public:
                constexpr StaticReferenceArray(ArgRRefType<ContainerType> container)
                    : _container(move<ContainerType>(container)) {}

            public:
                constexpr StaticReferenceArray(const StaticReferenceArray& ano) = default;
                constexpr StaticReferenceArray(StaticReferenceArray&& ano) noexcept = default;
                constexpr StaticReferenceArray& operator=(const StaticReferenceArray& rhs) = default;
                constexpr StaticReferenceArray& operator=(StaticReferenceArray&& rhs) noexcept = default;
                constexpr ~StaticReferenceArray(void) = default;

            public:
                template<typename = void>
                    requires requires (ContainerType& container) { { container.data() } -> DecaySameAs<PtrType<ReferenceType>>; }
                inline constexpr const PtrType<ReferenceType> data(void) noexcept
                {
                    return _container.data();
                }

                template<typename = void>
                    requires requires (const ContainerType& container) { { container.data() } -> DecaySameAs<CPtrType<ReferenceType>>; }
                inline constexpr const CPtrType<ReferenceType> data(void) const noexcept
                {
                    return _container.data();
                }

            public:
                inline constexpr const usize max_size(void) const noexcept
                {
                    return _container.max_size();
                }

            public:
                template<typename = void>
                    requires std::copy_constructible<ReferenceType>
                inline constexpr void fill(ArgCLRefType<ReferenceType> ref) noexcept
                {
                    _container.fill(ref);
                }

            public:
                inline constexpr const bool operator==(const StaticReferenceArray& rhs) const noexcept
                {
                    return _container == rhs._container;
                }

                inline constexpr const bool operator!=(const StaticReferenceArray& rhs) const noexcept
                {
                    return _container != rhs._container;
                }

            public:
                inline constexpr const bool operator<(const StaticReferenceArray& rhs) const noexcept
                {
                    return _container < rhs._container;
                }

                inline constexpr const bool operator<=(const StaticReferenceArray& rhs) const noexcept
                {
                    return _container <= rhs._container;
                }

                inline constexpr const bool operator>(const StaticReferenceArray& rhs) const noexcept
                {
                    return _container > rhs._container;
                }

                inline constexpr const bool operator>=(const StaticReferenceArray& rhs) const noexcept
                {
                    return _container >= rhs._container;
                }

            public:
                inline constexpr decltype(auto) operator<=>(const StaticReferenceArray& rhs) const noexcept
                {
                    return _container <=> rhs._container;
                }

            OSPF_CRTP_PERMISSION:
                inline constexpr LRefType<ContainerType> OSPF_CRTP_FUNCTION(get_container)(void) noexcept
                {
                    return _container;
                }

                inline constexpr CLRefType<ContainerType> OSPF_CRTP_FUNCTION(get_const_container)(void) const noexcept
                {
                    return _container;
                }

            private:
                ContainerType _container;
            };

            template<
                typename T,
                reference::ReferenceCategory cat,
                template<typename T> class C
            >
            class DynamicReferenceArray
                : public ReferenceArrayImpl<T, C<reference::Ref<OriginType<T>, cat>>, DynamicReferenceArray<T, cat, C>>
            {
                using Impl = ReferenceArrayImpl<T, C<reference::Ref<OriginType<T>, cat>>, DynamicReferenceArray<T, cat, C>>;

            public:
                using typename Impl::ValueType;
                using typename Impl::ReferenceType;
                using typename Impl::ContainerType;
                using typename Impl::IterType;
                using typename Impl::ConstIterType;
                using typename Impl::ReverseIterType;
                using typename Impl::ConstReverseIterType;

            public:
                constexpr DynamicReferenceArray(void) = default;

                template<typename = void>
                    requires std::copy_constructible<ReferenceType>
                constexpr DynamicReferenceArray(const usize length, CLRefType<ValueType> ref)
                    : _container(length, ReferenceType{ ref }) {}

                template<typename = void>
                    requires std::copy_constructible<ReferenceType>
                constexpr DynamicReferenceArray(const usize length, ArgCLRefType<ReferenceType> ref)
                    : _container(length, ref) {}

                template<std::input_iterator It>
                    requires requires (const It it) { { *it } -> std::same_as<LRefType<ValueType>>; }
                constexpr DynamicReferenceArray(It&& first, It&& last)
                    : _container(
                        boost::make_transform_iterator(std::forward<It>(first), [](LRefType<ValueType> ref) { return ReferenceType{ref}; }),
                        boost::make_transform_iterator(std::forward<It>(last), [](LRefType<ValueType> ref) { return ReferenceType{ref}; })
                    ) {}

                template<std::input_iterator It>
                    requires requires (const It it) { { *it } -> std::same_as<CLRefType<ValueType>>; }
                constexpr DynamicReferenceArray(It&& first, It&& last)
                    : _container(
                        boost::make_transform_iterator(std::forward<It>(first), [](CLRefType<ValueType> ref) { return ReferenceType{ref}; }),
                        boost::make_transform_iterator(std::forward<It>(last), [](CLRefType<ValueType> ref) { return ReferenceType{ref}; })
                    ) {}

                template<std::input_iterator It>
                    requires requires (const It it) { { *it } -> DecaySameAs<ReferenceType>; }
                constexpr DynamicReferenceArray(It&& first, It&& last)
                    : _container(std::forward<It>(first), std::forward<It>(last)) {}

                constexpr DynamicReferenceArray(std::initializer_list<ReferenceType> refs)
                    : _container(std::move(refs)) {}

            public:
                constexpr DynamicReferenceArray(const DynamicReferenceArray& ano) = default;
                constexpr DynamicReferenceArray(DynamicReferenceArray&& ano) noexcept = default;
                constexpr DynamicReferenceArray& operator=(const DynamicReferenceArray& rhs) = default;
                constexpr DynamicReferenceArray& operator=(DynamicReferenceArray&& rhs) noexcept = default;
                constexpr ~DynamicReferenceArray(void) noexcept = default;

            public:
                template<typename = void>
                    requires std::copy_constructible<ReferenceType>
                inline constexpr void assign(const usize length, CLRefType<ValueType> ref)
                {
                    _container.assign(length, ReferenceType{ ref });
                }

                template<typename = void>
                    requires std::copy_constructible<ReferenceType>
                inline constexpr void assign(const usize length, ArgCLRefType<ReferenceType> ref)
                {
                    _container.assign(length, ref);
                }

                template<std::input_iterator It>
                    requires requires (const It it) { { *it } -> std::same_as<LRefType<ValueType>>; }
                inline constexpr void assign(It&& first, It&& last)
                {
                    _container.assign(
                        boost::make_transform_iterator(std::forward<It>(first), [](LRefType<ValueType> ref) { return ReferenceType{ ref }; }),
                        boost::make_transform_iterator(std::forward<It>(last), [](LRefType<ValueType> ref) { return ReferenceType{ ref }; })
                    );
                }

                template<std::input_iterator It>
                    requires requires (const It it) { { *it } -> std::same_as<CLRefType<ValueType>>; }
                inline constexpr void assign(It&& first, It&& last)
                {
                    _container.assign(
                        boost::make_transform_iterator(std::forward<It>(first), [](CLRefType<ValueType> ref) { return ReferenceType{ ref }; }),
                        boost::make_transform_iterator(std::forward<It>(last), [](CLRefType<ValueType> ref) { return ReferenceType{ ref }; })
                    );
                }

                template<std::input_iterator It>
                    requires requires (const It it) { { *it } -> DecaySameAs<ReferenceType>; }
                inline constexpr void assign(It&& first, It&& last)
                {
                    _container.assign(std::forward<It>(first), std::forward<It>(last));
                }

                inline constexpr void assign(std::initializer_list<ReferenceType> refs)
                {
                    _container.assign(refs);
                }

                template<
                    usize len,
                    template<typename T, usize l> class C1
                >
                    requires std::copy_constructible<ReferenceType>
                inline constexpr void assign(const StaticReferenceArray<T, len, cat, C1>& refs)
                {
                    assign(refs.cbegin(), refs.cend());
                }

                template<
                    typename U,
                    usize len,
                    template<typename T, usize l> class C1
                >
                    requires std::copy_constructible<ReferenceType> && std::convertible_to<PtrType<U>, PtrType<ValueType>>
                inline constexpr void assign(const StaticReferenceArray<U, len, cat, C1>& refs)
                {
                    assign(
                        boost::make_transform_iterator(refs.cbegin(), [](const Ref<U, cat>& ref) { return ReferenceType{ ref }; }),
                        boost::make_transform_iterator(refs.cend(), [](const Ref<U, cat>& ref) { return ReferenceType{ ref }; })
                    );
                }

                template<
                    template<typename T> class C1
                >
                    requires std::copy_constructible<ReferenceType>
                inline constexpr void assign(const DynamicReferenceArray<T, cat, C1>& refs)
                {
                    assign(refs.cbegin(), refs.cend());
                }

                template<
                    typename U,
                    template<typename T> class C1
                >
                    requires std::copy_constructible<ReferenceType> && std::convertible_to<PtrType<U>, PtrType<ValueType>>
                inline constexpr void assign(const DynamicReferenceArray<U, cat, C1>& refs)
                {
                    assign(
                        boost::make_transform_iterator(refs.cbegin(), [](const Ref<U, cat>& ref) { return ReferenceType{ ref }; }),
                        boost::make_transform_iterator(refs.cend(), [](const Ref<U, cat>& ref) { return ReferenceType{ ref }; })
                    );
                }

                // todo: assign moved dynamic reference array

                template<std::ranges::range R>
                inline constexpr void assign(const R& range)
                {
                    assign(std::ranges::begin(range), std::ranges::end(range));
                }

            public:
                template<typename = void>
                    requires requires (ContainerType& container) { { container.data() } -> DecaySameAs<PtrType<ReferenceType>>; }
                inline constexpr const PtrType<ReferenceType> data(void) noexcept
                {
                    return _container.data();
                }

                template<typename = void>
                    requires requires (const ContainerType& container) { { container.data() } -> DecaySameAs<CPtrType<ReferenceType>>; }
                inline constexpr const CPtrType<ReferenceType> data(void) const noexcept
                {
                    return _container.data();
                }

            public:
                inline constexpr const usize max_size(void) const noexcept
                {
                    return _container.max_size();
                }

                template<typename = void>
                    requires requires (ContainerType& container) { container.reserve(std::declval<usize>()); }
                inline constexpr void reserve(const usize new_capacity)
                {
                    _container.reserve(new_capacity);
                }

                template<typename = void>
                    requires requires (const ContainerType& container) { { container.capacity() } -> DecaySameAs<usize>; }
                inline constexpr const usize capacity(void) const noexcept
                {
                    return _container.capacity();
                }

                template<typename = void>
                    requires requires (ContainerType& container) { container.shrink_to_fit(); }
                inline void shrink_to_fit(void)
                {
                    _container.shrink_to_fit();
                }

            public:
                inline constexpr void clear(void) noexcept
                {
                    _container.clear();
                }

                inline constexpr RetType<IterType> insert(ArgCLRefType<ConstIterType> pos, CLRefType<ValueType> ref)
                {
                    return IterType{ _container.insert(pos._iter, ReferenceType{ ref }) };
                }

                inline constexpr RetType<IterType> insert(ArgCLRefType<ConstIterType> pos, ArgRRefType<ReferenceType> ref)
                {
                    return IterType{ _container.insert(pos._iter, move<ReferenceType>(ref)) };
                }

                template<std::input_iterator It>
                    requires requires (const It it) { { *it } -> std::same_as<LRefType<ValueType>>; }
                inline constexpr RetType<IterType> insert(ArgCLRefType<ConstIterType> pos, It&& first, It&& last)
                {
                    return IterType{ _container.insert(pos._iter, 
                        boost::make_transform_iterator(std::forward<It>(first), [](LRefType<ValueType> ref) { return ReferenceType{ ref }; }),
                        boost::make_transform_iterator(std::forward<It>(last), [](LRefType<ValueType> ref) { return ReferenceType{ref}; })
                    ) };
                }

                template<std::input_iterator It>
                    requires requires (const It it) { { *it } -> std::same_as<CLRefType<ValueType>>; }
                inline constexpr RetType<IterType> insert(ArgCLRefType<ConstIterType> pos, It&& first, It&& last)
                {
                    return IterType{ _container.insert(pos._iter,
                        boost::make_transform_iterator(std::forward<It>(first), [](CLRefType<ValueType> ref) { return ReferenceType{ ref }; }),
                        boost::make_transform_iterator(std::forward<It>(last), [](CLRefType<ValueType> ref) { return ReferenceType{ ref }; })
                    ) };
                }

                template<std::input_iterator It>
                    requires requires (const It it) { { *it } -> DecaySameAs<ReferenceType>; }
                inline constexpr RetType<IterType> insert(ArgCLRefType<ConstIterType> pos, It&& first, It&& last)
                {
                    return IterType{ _container.insert(pos._iter, std::forward<It>(first), std::forward<It>(last)) };
                }

                inline constexpr RetType<IterType> insert(ArgCLRefType<ConstIterType> pos, std::initializer_list<ReferenceType> refs)
                {
                    return IterType{ _container.insert(pos._iter, std::move(refs)) };
                }

                template<
                    usize len,
                    template<typename T, usize l> class C1
                >
                    requires std::copy_constructible<ReferenceType>
                inline constexpr RetType<IterType> insert(ArgCLRefType<ConstIterType> pos, const StaticReferenceArray<T, len, cat, C1>& refs)
                {
                    return insert(refs.cbegin(), refs.cend());
                }

                template<
                    typename U,
                    usize len,
                    template<typename T, usize l> class C1
                >
                    requires std::copy_constructible<ReferenceType> && std::convertible_to<PtrType<U>, PtrType<ValueType>>
                inline constexpr RetType<IterType> insert(ArgCLRefType<ConstIterType> pos, const StaticReferenceArray<U, len, cat, C1>& refs)
                {
                    return insert(
                        boost::make_transform_iterator(refs.cbegin(), [](const Ref<U, cat>& ref) { return ReferenceType{ ref }; }),
                        boost::make_transform_iterator(refs.cend(), [](const Ref<U, cat>& ref) { return ReferenceType{ ref }; })
                    );
                }

                template<
                    template<typename T> class C1
                >
                    requires std::copy_constructible<ReferenceType>
                inline constexpr RetType<IterType> insert(ArgCLRefType<ConstIterType> pos, const DynamicReferenceArray<T, cat, C1>& refs)
                {
                    return insert(refs.cbegin(), refs.cend());
                }

                template<
                    typename U,
                    template<typename T> class C1
                >
                    requires std::copy_constructible<ReferenceType> && std::convertible_to<PtrType<U>, PtrType<ValueType>>
                inline constexpr RetType<IterType> insert(ArgCLRefType<ConstIterType> pos, const DynamicReferenceArray<U, cat, C1>& refs)
                {
                    return insert(
                        boost::make_transform_iterator(refs.cbegin(), [](const Ref<U, cat>& ref) { return ReferenceType{ ref }; }),
                        boost::make_transform_iterator(refs.cend(), [](const Ref<U, cat>& ref) { return ReferenceType{ ref }; })
                    );
                }

                // todo: insert moved dynamic reference array

                template<std::ranges::range R>
                inline constexpr RetType<IterType> insert(ArgCLRefType<ConstIterType> pos, const R& range)
                {
                    return insert(std::ranges::begin(range), std::ranges::end(range));
                }

                inline constexpr RetType<IterType> emplace(ArgCLRefType<ConstIterType> pos, CLRefType<ValueType> ref)
                {
                    return IterType{ _container.emplace(pos._iter, ref) };
                }

                template<typename... Args>
                    requires std::constructible_from<ReferenceType, Args...>
                inline constexpr RetType<IterType> emplace(ArgCLRefType<ConstIterType> pos, Args&&... args)
                {
                    return IterType{ _container.emplace(pos._iter, std::forward<Args>(args)...) };
                }

                inline constexpr RetType<IterType> erase(ArgCLRefType<ConstIterType> pos)
                {
                    return IterType{ _container.erase(pos._iter) };
                }

                inline constexpr RetType<IterType> erase(ArgCLRefType<ConstIterType> first, ArgCLRefType<ConstIterType> last)
                {
                    return IterType{ _container.erase(first._iter, last._iter) };
                }

                inline constexpr void push_back(CLRefType<ValueType> ref)
                {
                    _container.push_back(ReferenceType{ ref });
                }

                inline constexpr void push_back(RRefType<ReferenceType> ref)
                {
                    _container.push_back(move<ReferenceType>(ref));
                }

                template<
                    usize len,
                    template<typename T, usize l> class C1
                >
                    requires std::copy_constructible<ReferenceType>
                inline constexpr void push_back(const StaticReferenceArray<T, len, cat, C1>& refs)
                {
                    insert(this->end(), refs);
                }

                template<
                    typename U,
                    usize len,
                    template<typename T, usize l> class C1
                >
                    requires std::copy_constructible<ReferenceType> && std::convertible_to<PtrType<U>, PtrType<ValueType>>
                inline constexpr void push_back(const StaticReferenceArray<U, len, cat, C1>& refs)
                {
                    insert(this->end(), refs);
                }

                template<
                    template<typename T> class C1
                >
                    requires std::copy_constructible<ReferenceType>
                inline constexpr void push_back(const DynamicReferenceArray<T, cat, C1>& refs)
                {
                    insert(this->end(), refs);
                }

                template<
                    typename U,
                    template<typename T> class C1
                >
                    requires std::copy_constructible<ReferenceType> && std::convertible_to<PtrType<U>, PtrType<ValueType>>
                inline constexpr void push_back(const DynamicReferenceArray<U, cat, C1>& refs)
                {
                    insert(this->end(), refs);
                }

                // todo: push back moved dynamic reference array

                inline constexpr void emplace_back(CLRefType<ValueType> ref)
                {
                    _container.emplace_back(ref);
                }

                template<typename... Args>
                    requires std::constructible_from<ReferenceType, Args...>
                inline constexpr void emplace_back(Args&&... args)
                {
                    _container.emplace_back(std::forward<Args>(args)...);
                }

                inline constexpr RetType<ReferenceType> pop_back(void)
                {
                    auto back = move<ReferenceType>(this->back());
                    _container.pop_back();
                    return back;
                }

                inline constexpr void push_front(CLRefType<ValueType> ref)
                {
                    _container.insert(_container.begin(), ReferenceType{ ref });
                }

                template<typename = void>
                    requires requires (ContainerType& container) { container.push_front(std::declval<ReferenceType>()); }
                inline constexpr void push_front(CLRefType<ValueType> ref)
                {
                    _container.push_front(ReferenceType{ ref });
                }

                inline constexpr void push_front(ArgRRefType<ReferenceType> ref)
                {
                    _container.insert(_container.begin(), move<ReferenceType>(ref));
                }

                template<typename = void>
                    requires requires (ContainerType& container) { container.push_front(std::declval<ReferenceType>()); }
                inline constexpr void push_front(ArgRRefType<ReferenceType> ref)
                {
                    _container.push_front(move<ReferenceType>(ref));
                }

                template<
                    usize len,
                    template<typename T, usize l> class C1
                >
                    requires std::copy_constructible<ReferenceType>
                inline constexpr void push_front(const StaticReferenceArray<T, len, cat, C1>& refs)
                {
                    insert(this->begin(), refs);
                }

                template<
                    typename U,
                    usize len,
                    template<typename T, usize l> class C1
                >
                    requires std::copy_constructible<ReferenceType> && std::convertible_to<PtrType<U>, PtrType<ValueType>>
                inline constexpr void push_front(const StaticReferenceArray<U, len, cat, C1>& refs)
                {
                    insert(this->begin(), refs);
                }

                template<
                    template<typename T> class C1
                >
                    requires std::copy_constructible<ReferenceType>
                inline constexpr void push_front(const DynamicReferenceArray<T, cat, C1>& refs)
                {
                    insert(this->begin(), refs);
                }

                // todo: push front moved dynamic reference array

                template<
                    typename U,
                    template<typename T> class C1
                >
                    requires std::copy_constructible<ReferenceType> && std::convertible_to<PtrType<U>, PtrType<ValueType>>
                inline constexpr void push_front(const DynamicReferenceArray<U, cat, C1>& refs)
                {
                    insert(this->begin(), refs);
                }

                inline constexpr void emplace_front(CLRefType<ValueType> ref)
                {
                    _container.emplace_front(ref);
                }

                template<typename = void>
                    requires requires (ContainerType& container) { container.emplace_front(std::declval<const ValueType&>()); }
                inline constexpr void emplace_front(CLRefType<ValueType> ref)
                {
                    _container.emplace_front(ref);
                }

                template<typename... Args>
                    requires std::constructible_from<ReferenceType, Args...>
                inline constexpr void emplace_front(Args&&... args)
                {
                    _container.emplace_front(std::forward<Args>(args)...);
                }

                template<typename... Args>
                    requires std::constructible_from<ReferenceType, Args...>
                        && requires (ContainerType& container) { container.emplace_front(std::declval<Args>()...); }
                inline constexpr void emplace_front(Args&&... args)
                {
                    _container.emplace_front(std::forward<Args>(args)...);
                }

                inline constexpr RetType<ReferenceType> pop_front(void)
                {
                    auto front = move<ReferenceType>(this->front());
                    _container.pop_front();
                    return front;
                }

                template<typename = void>
                    requires std::copy_constructible<ReferenceType>
                inline constexpr void resize(const usize length, CLRefType<ValueType> ref)
                {
                    _container.resize(length, ReferenceType{ ref });
                }

                template<typename = void>
                    requires std::copy_constructible<ReferenceType>
                inline constexpr void resize(const usize length, ArgCLRefType<ReferenceType> ref)
                {
                    _container.resize(length, ref);
                }

            public:
                inline constexpr const bool operator==(const DynamicReferenceArray& rhs) const noexcept
                {
                    return _container == rhs._container;
                }

                inline constexpr const bool operator!=(const DynamicReferenceArray& rhs) const noexcept
                {
                    return _container != rhs._container;
                }

            public:
                inline constexpr const bool operator<(const DynamicReferenceArray& rhs) const noexcept
                {
                    return _container < rhs._container;
                }

                inline constexpr const bool operator<=(const DynamicReferenceArray& rhs) const noexcept
                {
                    return _container <= rhs._container;
                }

                inline constexpr const bool operator>(const DynamicReferenceArray& rhs) const noexcept
                {
                    return _container > rhs._container;
                }

                inline constexpr const bool operator>=(const DynamicReferenceArray& rhs) const noexcept
                {
                    return _container >= rhs._container;
                }

            public:
                inline constexpr decltype(auto) operator<=>(const DynamicReferenceArray& rhs) const noexcept
                {
                    return _container <=> rhs._container;
                }

            OSPF_CRTP_PERMISSION:
                inline constexpr LRefType<ContainerType> OSPF_CRTP_FUNCTION(get_container)(void) noexcept
                {
                    return _container;
                }

                inline constexpr CLRefType<ContainerType> OSPF_CRTP_FUNCTION(get_const_container)(void) const noexcept
                {
                    return _container;
                }

            private:
                ContainerType _container;
            };

            template<typename T, reference::ReferenceCategory cat>
            struct ReferenceArrayTrait
            {
                template<
                    usize len,
                    template<typename T, usize l> class C
                >
                using StaticType = StaticReferenceArray<T, len, cat, C>;

                template<
                    template<typename T> class C
                >
                using DynamicType = DynamicReferenceArray<T, cat, C>;
            };

            template<typename T, reference::ReferenceCategory cat>
            struct ReferenceArrayTrait<reference::Ref<T, cat>, cat>
                : public ReferenceArrayTrait<T, cat> {};
        };

        template<
            typename T,
            usize len,
            reference::ReferenceCategory cat = reference::ReferenceCategory::Reference,
            template<typename T, usize l> class C = std::array
        >
        using RefArray = typename reference_array::ReferenceArrayTrait<T, cat>::template StaticType<len, C>;

        template<
            typename T,
            usize len,
            template<typename T, usize l> class C = std::array
        >
        using BorrowArray = typename reference_array::ReferenceArrayTrait<T, reference::ReferenceCategory::Borrow>::template StaticType<len, C>;

        template<
            typename T,
            usize len,
            template<typename T, usize l> class C = std::array
        >
        using UniqueBorrowArray = typename reference_array::ReferenceArrayTrait<T, reference::ReferenceCategory::UniqueBorrow>::template StaticType<len, C>;

        template<
            typename T,
            reference::ReferenceCategory cat = reference::ReferenceCategory::Reference,
            template<typename T> class C = std::vector
        >
        using DynRefArray = typename reference_array::ReferenceArrayTrait<T, cat>::template DynamicType<C>;

        template<
            typename T,
            template<typename T> class C = std::vector
        >
        using DynBorrowArray = typename reference_array::ReferenceArrayTrait<T, reference::ReferenceCategory::Borrow>::template DynamicType<C>;

        template<
            typename T,
            template<typename T> class C = std::vector
        >
        using DynUniqueBorrowArray = typename reference_array::ReferenceArrayTrait<T, reference::ReferenceCategory::UniqueBorrow>::template DynamicType<C>;
    };
};

namespace std
{
    template<typename T, typename C, typename Self>
    inline void swap(ospf::reference_array::ReferenceArrayImpl<T, C, Self>& lhs, ospf::reference_array::ReferenceArrayImpl<T, C, Self>& rhs) noexcept
    {
        lhs.swap(rhs);
    }
};
