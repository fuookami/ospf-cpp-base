#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/concepts/with_default.hpp>
#include <ospf/literal_constant.hpp>
#include <ospf/memory/pointer.hpp>
#include <ospf/memory/reference.hpp>
#include <ospf/meta_programming/iterator.hpp>

namespace ospf
{
    inline namespace data_structure
    {
        namespace pointer_array
        {
            template<
                typename T,
                usize len,
                pointer::PointerCategory cat,
                template<typename T, usize l> class C
            >
            class StaticPointerArray;

            template<
                typename T,
                pointer::PointerCategory cat,
                template<typename T> class C
            >
            class DynamicPointerArray;

            template<typename T, pointer::PointerCategory cat, typename C>
            class PointerArrayConstIterator
                : public RandomIteratorImpl<pointer::Ptr<OriginType<T>, cat>, typename OriginType<C>::const_iterator, PointerArrayConstIterator<T, cat, C>>
            {
                template<
                    typename T,
                    usize len,
                    pointer::PointerCategory cat,
                    template<typename T, usize l> class C
                >
                friend class StaticPointerArray;

                template<
                    typename T,
                    pointer::PointerCategory cat,
                    template<typename T> class C
                >
                friend class DynamicPointerArray;

            public:
                using ValueType = pointer::Ptr<OriginType<T>, cat>;
                using ContainerType = OriginType<C>;
                using IterType = typename ContainerType::const_iterator;

            private:
                using Base = RandomIteratorImpl<ValueType, IterType, PointerArrayConstIterator<T, cat, C>>;

            public:
                constexpr PointerArrayConstIterator(const IterType iter)
                    : Base(iter) {}
                constexpr PointerArrayConstIterator(const PointerArrayConstIterator& ano) = default;
                constexpr PointerArrayConstIterator(PointerArrayConstIterator&& ano) noexcept = default;
                constexpr PointerArrayConstIterator& operator=(const PointerArrayConstIterator& rhs) = default;
                constexpr PointerArrayConstIterator& operator=(PointerArrayConstIterator&& rhs) noexcept = default;
                constexpr ~PointerArrayConstIterator(void) noexcept = default;

            public:
                inline constexpr const bool null(void) const
                {
                    return *this->_iter == nullptr;
                }

            OSPF_CRTP_PERMISSION:
                inline static constexpr const ValueType& OSPF_CRTP_FUNCTION(get)(const IterType iter) noexcept
                {
                    return *iter;
                }

                inline static constexpr RetType<PointerArrayConstIterator> OSPF_CRTP_FUNCTION(construct)(const IterType iter) noexcept
                {
                    return PointerArrayConstIterator{ iter };
                }
            };

            template<typename T, pointer::PointerCategory cat, typename C>
            class PointerArrayIterator
                : public RandomIteratorImpl<pointer::Ptr<OriginType<T>, cat>, typename OriginType<C>::iterator, PointerArrayIterator<T, cat, C>>
            {
                template<
                    typename T,
                    usize len,
                    pointer::PointerCategory cat,
                    template<typename T, usize l> class C
                >
                friend class StaticPointerArray;

                template<
                    typename T,
                    pointer::PointerCategory cat,
                    template<typename T> class C
                >
                friend class DynamicPointerArray;

            public:
                using ValueType = pointer::Ptr<OriginType<T>, cat>;
                using ContainerType = OriginType<C>;
                using IterType = typename ContainerType::iterator;

            private:
                using Base = RandomIteratorImpl<ValueType, IterType, PointerArrayIterator<T, cat, C>>;

            public:
                constexpr PointerArrayIterator(const IterType iter)
                    : Base(iter) {}
                constexpr PointerArrayIterator(const PointerArrayIterator& ano) = default;
                constexpr PointerArrayIterator(PointerArrayIterator&& ano) noexcept = default;
                constexpr PointerArrayIterator& operator=(const PointerArrayIterator& ano) = default;
                constexpr PointerArrayIterator& operator=(PointerArrayIterator&& ano) noexcept = default;
                constexpr ~PointerArrayIterator(void) noexcept = default;

            public:
                inline constexpr const bool null(void) const
                {
                    return *this->_iter == nullptr;
                }

            public:
                inline operator const PointerArrayConstIterator<T, cat, C>(void) const noexcept
                {
                    return PointerArrayConstIterator<T, cat, C>{ this->_iter };
                }

            OSPF_CRTP_PERMISSION:
                inline static constexpr ValueType& OSPF_CRTP_FUNCTION(get)(const IterType iter) noexcept
                {
                    return *iter;
                }

                inline static constexpr RetType<PointerArrayIterator> OSPF_CRTP_FUNCTION(construct)(const IterType iter) noexcept
                {
                    return PointerArrayIterator{ iter };
                }
            };

            template<typename T, pointer::PointerCategory cat, typename C>
            class PointerArrayConstReverseIterator
                : public RandomIteratorImpl<pointer::Ptr<OriginType<T>, cat>, typename OriginType<C>::const_reverse_iterator, PointerArrayConstReverseIterator<T, cat, C>>
            {
                template<
                    typename T,
                    usize len,
                    pointer::PointerCategory cat,
                    template<typename T, usize l> class C
                >
                friend class StaticPointerArray;

                template<
                    typename T,
                    pointer::PointerCategory cat,
                    template<typename T> class C
                >
                friend class DynamicPointerArray;

            public:
                using ValueType = pointer::Ptr<OriginType<T>, cat>;
                using ContainerType = OriginType<C>;
                using IterType = typename ContainerType::const_reverse_iterator;

            private:
                using Base = RandomIteratorImpl<ValueType, IterType, PointerArrayConstReverseIterator<T, cat, C>>;

            public:
                constexpr PointerArrayConstReverseIterator(const IterType iter)
                    : Base(iter) {}
                constexpr PointerArrayConstReverseIterator(const PointerArrayConstReverseIterator& ano) = default;
                constexpr PointerArrayConstReverseIterator(PointerArrayConstReverseIterator&& ano) noexcept = default;
                constexpr PointerArrayConstReverseIterator& operator=(const PointerArrayConstReverseIterator& rhs) = default;
                constexpr PointerArrayConstReverseIterator& operator=(PointerArrayConstReverseIterator&& rhs) noexcept = default;
                constexpr ~PointerArrayConstReverseIterator(void) = default;

            public:
                inline constexpr const bool null(void) const
                {
                    return *this->_iter == nullptr;
                }

            OSPF_CRTP_PERMISSION:
                inline static constexpr const ValueType& OSPF_CRTP_FUNCTION(get)(const IterType iter) noexcept
                {
                    return *iter;
                }

                inline static constexpr const RetType<PointerArrayConstReverseIterator> OSPF_CRTP_FUNCTION(construct)(const IterType iter) noexcept
                {
                    return PointerArrayConstReverseIterator{ iter };
                }
            };

            template<typename T, pointer::PointerCategory cat, typename C>
            class PointerArrayReverseIterator
                : public RandomIteratorImpl<pointer::Ptr<OriginType<T>, cat>, typename OriginType<C>::reverse_iterator, PointerArrayReverseIterator<T, cat, C>>
            {
                template<
                    typename T,
                    usize len,
                    pointer::PointerCategory cat,
                    template<typename T, usize l> class C
                >
                friend class StaticPointerArray;

                template<
                    typename T,
                    pointer::PointerCategory cat,
                    template<typename T> class C
                >
                friend class DynamicPointerArray;

            public:
                using ValueType = pointer::Ptr<OriginType<T>, cat>;
                using ContainerType = OriginType<C>;
                using IterType = typename ContainerType::reverse_iterator;

            private:
                using Base = RandomIteratorImpl<ValueType, IterType, PointerArrayReverseIterator<T, cat, C>>;

            public:
                constexpr PointerArrayReverseIterator(const IterType iter)
                    : Base(iter) {}
                constexpr PointerArrayReverseIterator(const PointerArrayReverseIterator& ano) = default;
                constexpr PointerArrayReverseIterator(PointerArrayReverseIterator&& ano) noexcept = default;
                constexpr PointerArrayReverseIterator& operator=(const PointerArrayReverseIterator& rhs) = default;
                constexpr PointerArrayReverseIterator& operator=(PointerArrayReverseIterator&& rhs) noexcept = default;
                constexpr ~PointerArrayReverseIterator(void) noexcept = default;

            public:
                inline constexpr const bool null(void) const
                {
                    return *this->_iter == nullptr;
                }

            OSPF_CRTP_PERMISSION:
                inline static constexpr const ValueType& OSPF_CRTP_FUNCTION(get)(const IterType iter) noexcept
                {
                    return *iter;
                }

                inline static constexpr const RetType<PointerArrayReverseIterator> OSPF_CRTP_FUNCTION(construct)(const IterType iter) noexcept
                {
                    return PointerArrayReverseIterator{ iter };
                }
            };

            template<typename T, pointer::PointerCategory cat, typename C>
            class PointerArrayConstUncheckedIterator
                : public RandomIteratorImpl<OriginType<T>, typename OriginType<C>::const_iterator, PointerArrayConstUncheckedIterator<T, cat, C>>
            {
                template<
                    typename T,
                    usize len,
                    pointer::PointerCategory cat,
                    template<typename T, usize l> class C
                >
                friend class StaticPointerArray;

                template<
                    typename T,
                    pointer::PointerCategory cat,
                    template<typename T> class C
                >
                friend class DynamicPointerArray;

            public:
                using ValueType = pointer::Ptr<OriginType<T>, cat>;
                using ContainerType = OriginType<C>;
                using IterType = typename ContainerType::const_iterator;

            private:
                using Base = RandomIteratorImpl<ValueType, IterType, PointerArrayConstUncheckedIterator<T, cat, C>>;

            public:
                constexpr PointerArrayConstUncheckedIterator(const IterType iter)
                    : Base(iter) {}
                constexpr PointerArrayConstUncheckedIterator(const PointerArrayConstUncheckedIterator& ano) = default;
                constexpr PointerArrayConstUncheckedIterator(PointerArrayConstUncheckedIterator&& ano) noexcept = default;
                constexpr PointerArrayConstUncheckedIterator& operator=(const PointerArrayConstUncheckedIterator& rhs) = default;
                constexpr PointerArrayConstUncheckedIterator& operator=(PointerArrayConstUncheckedIterator&& rhs) noexcept = default;
                constexpr ~PointerArrayConstUncheckedIterator(void) = default;

            public:
                inline constexpr const bool null(void) const
                {
                    return *this->_iter == nullptr;
                }

            OSPF_CRTP_PERMISSION:
                inline static constexpr const ValueType& OSPF_CRTP_FUNCTION(get)(const IterType iter) noexcept
                {
                    return **iter;
                }

                inline static constexpr RetType<PointerArrayConstUncheckedIterator> OSPF_CRTP_FUNCTION(construct)(const IterType iter) noexcept
                {
                    return PointerArrayConstUncheckedIterator{ iter };
                }
            };

            template<typename T, pointer::PointerCategory cat, typename C>
            class PointerArrayUncheckedIterator
                : public RandomIteratorImpl<OriginType<T>, typename OriginType<C>::iterator, PointerArrayUncheckedIterator<T, cat, C>>
            {
                template<
                    typename T,
                    usize len,
                    pointer::PointerCategory cat,
                    template<typename T, usize l> class C
                >
                friend class StaticPointerArray;

                template<
                    typename T,
                    pointer::PointerCategory cat,
                    template<typename T> class C
                >
                friend class DynamicPointerArray;

            public:
                using ValueType = pointer::Ptr<OriginType<T>, cat>;
                using ContainerType = OriginType<C>;
                using IterType = typename ContainerType::iterator;

            private:
                using Base = RandomIteratorImpl<ValueType, IterType, PointerArrayUncheckedIterator<T, cat, C>>;

            public:
                constexpr PointerArrayUncheckedIterator(const IterType iter)
                    : Base(iter) {}
                constexpr PointerArrayUncheckedIterator(const PointerArrayUncheckedIterator& ano) = default;
                constexpr PointerArrayUncheckedIterator(PointerArrayUncheckedIterator&& ano) noexcept = default;
                constexpr PointerArrayUncheckedIterator& operator=(const PointerArrayUncheckedIterator& rhs) = default;
                constexpr PointerArrayUncheckedIterator& operator=(PointerArrayUncheckedIterator&& rhs) noexcept = default;
                constexpr ~PointerArrayUncheckedIterator(void) = default;

            public:
                inline constexpr const bool null(void) const
                {
                    return *this->_iter == nullptr;
                }

            OSPF_CRTP_PERMISSION:
                inline static constexpr const ValueType& OSPF_CRTP_FUNCTION(get)(const IterType iter) noexcept
                {
                    return **iter;
                }

                inline static constexpr RetType<PointerArrayUncheckedIterator> OSPF_CRTP_FUNCTION(construct)(const IterType iter) noexcept
                {
                    return PointerArrayUncheckedIterator{ iter };
                }
            };

            template<typename T, pointer::PointerCategory cat, typename C>
            class PointerArrayConstUncheckedReverseIterator
                : public RandomIteratorImpl<OriginType<T>, typename OriginType<C>::const_reverse_iterator, PointerArrayConstUncheckedReverseIterator<T, cat, C>>
            {
                template<
                    typename T,
                    usize len,
                    pointer::PointerCategory cat,
                    template<typename T, usize l> class C
                >
                friend class StaticPointerArray;

                template<
                    typename T,
                    pointer::PointerCategory cat,
                    template<typename T> class C
                >
                friend class DynamicPointerArray;

            public:
                using ValueType = pointer::Ptr<OriginType<T>, cat>;
                using ContainerType = OriginType<C>;
                using IterType = typename ContainerType::const_reverse_iterator;

            private:
                using Base = RandomIteratorImpl<ValueType, IterType, PointerArrayConstUncheckedReverseIterator<T, cat, C>>;

            public:
                constexpr PointerArrayConstUncheckedReverseIterator(const IterType iter)
                    : Base(iter) {}
                constexpr PointerArrayConstUncheckedReverseIterator(const PointerArrayConstUncheckedReverseIterator& ano) = default;
                constexpr PointerArrayConstUncheckedReverseIterator(PointerArrayConstUncheckedReverseIterator&& ano) noexcept = default;
                constexpr PointerArrayConstUncheckedReverseIterator& operator=(const PointerArrayConstUncheckedReverseIterator& rhs) = default;
                constexpr PointerArrayConstUncheckedReverseIterator& operator=(PointerArrayConstUncheckedReverseIterator&& rhs) noexcept = default;
                constexpr ~PointerArrayConstUncheckedReverseIterator(void) = default;

            public:
                inline constexpr const bool null(void) const
                {
                    return *this->_iter == nullptr;
                }

            OSPF_CRTP_PERMISSION:
                inline static constexpr const ValueType& OSPF_CRTP_FUNCTION(get)(const IterType iter) noexcept
                {
                    return **iter;
                }

                inline static constexpr RetType<PointerArrayConstUncheckedReverseIterator> OSPF_CRTP_FUNCTION(construct)(const IterType iter) noexcept
                {
                    return PointerArrayConstUncheckedReverseIterator{ iter };
                }
            };

            template<typename T, pointer::PointerCategory cat, typename C>
            class PointerArrayUncheckedReverseIterator
                : public RandomIteratorImpl<OriginType<T>, typename OriginType<C>::reverse_iterator, PointerArrayUncheckedReverseIterator<T, cat, C>>
            {
                template<
                    typename T,
                    usize len,
                    pointer::PointerCategory cat,
                    template<typename T, usize l> class C
                >
                friend class StaticPointerArray;

                template<
                    typename T,
                    pointer::PointerCategory cat,
                    template<typename T> class C
                >
                friend class DynamicPointerArray;

            public:
                using ValueType = pointer::Ptr<OriginType<T>, cat>;
                using ContainerType = OriginType<C>;
                using IterType = typename ContainerType::reverse_iterator;

            private:
                using Base = RandomIteratorImpl<ValueType, IterType, PointerArrayUncheckedReverseIterator<T, cat, C>>;

            public:
                constexpr PointerArrayUncheckedReverseIterator(const IterType iter)
                    : Base(iter) {}
                constexpr PointerArrayUncheckedReverseIterator(const PointerArrayUncheckedReverseIterator& ano) = default;
                constexpr PointerArrayUncheckedReverseIterator(PointerArrayUncheckedReverseIterator&& ano) noexcept = default;
                constexpr PointerArrayUncheckedReverseIterator& operator=(const PointerArrayUncheckedReverseIterator& rhs) = default;
                constexpr PointerArrayUncheckedReverseIterator& operator=(PointerArrayUncheckedReverseIterator&& rhs) noexcept = default;
                constexpr ~PointerArrayUncheckedReverseIterator(void) = default;

            public:
                inline constexpr const bool null(void) const
                {
                    return *this->_iter == nullptr;
                }

            OSPF_CRTP_PERMISSION:
                inline static constexpr const ValueType& OSPF_CRTP_FUNCTION(get)(const IterType iter) noexcept
                {
                    return **iter;
                }

                inline static constexpr RetType<PointerArrayUncheckedReverseIterator> OSPF_CRTP_FUNCTION(construct)(const IterType iter) noexcept
                {
                    return PointerArrayUncheckedReverseIterator{ iter };
                }
            };

            template<typename T, typename C>
            class PointerArrayAccessPolicy;

            template<
                typename T,
                usize len,
                pointer::PointerCategory cat,
                template<typename U, usize l> class C
            >
            class PointerArrayAccessPolicy<T, C<pointer::Ptr<OriginType<T>, cat>, len>>
            {
            public:
                using ValueType = OriginType<T>;
                using ContainerType = C<pointer::Ptr<ValueType, cat>, len>;
                using IterType = PointerArrayIterator<ValueType, cat, ContainerType>;
                using ConstIterType = PointerArrayConstIterator<ValueType, cat, ContainerType>;
                using ReverseIterType = PointerArrayReverseIterator<ValueType, cat, ContainerType>;
                using ConstReverseIterType = PointerArrayConstReverseIterator<ValueType, cat, ContainerType>;
                using UncheckedIterType = PointerArrayUncheckedIterator<ValueType, cat, ContainerType>;
                using ConstUncheckedIterType = PointerArrayConstUncheckedIterator<ValueType, cat, ContainerType>;
                using UncheckedReverseIterType = PointerArrayUncheckedReverseIterator<ValueType, cat, ContainerType>;
                using ConstUncheckedReverseIterType = PointerArrayConstUncheckedReverseIterator<ValueType, cat, ContainerType>;

            public:
                inline static constexpr const usize size(const ContainerType& array) noexcept
                {
                    return len;
                }

                inline static constexpr pointer::Ptr<ValueType, cat>& get(ContainerType& array, const usize i)
                {
                    return array.at(i);
                }

                inline static constexpr const pointer::Ptr<ValueType, cat>& get(const ContainerType& array, const usize i)
                {
                    return array.at(i);
                }

                inline static constexpr pointer::Ptr<ValueType, cat>& get_unchecked(ContainerType& array, const usize i)
                {
                    return array[i];
                }

                inline static constexpr const pointer::Ptr<ValueType, cat>& get_unchecked(const ContainerType& array, const usize i)
                {
                    return array[i];
                }

            public:
                inline static constexpr decltype(auto) begin(ContainerType& array) noexcept
                {
                    return IterType{ array.begin() };
                }

                inline static constexpr decltype(auto) cbegin(const ContainerType& array) noexcept
                {
                    return ConstIterType{ array.begin() };
                }

                inline static constexpr decltype(auto) begin_unchecked(ContainerType& array) noexcept
                {
                    return UncheckedIterType{ array.begin() };
                }

                inline static constexpr decltype(auto) cbegin_unchecked(const ContainerType& array) noexcept
                {
                    return ConstUncheckedIterType{ array.begin() };
                }

            public:
                inline static constexpr decltype(auto) end(ContainerType& array) noexcept
                {
                    return IterType{ array.end() };
                }

                inline static constexpr decltype(auto) cend(const ContainerType& array) noexcept
                {
                    return ConstIterType{ array.end() };
                }

                inline static constexpr decltype(auto) end_unchecked(ContainerType& array) noexcept
                {
                    return UncheckedIterType{ array.end() };
                }

                inline static constexpr decltype(auto) cend_unchecked(const ContainerType& array) noexcept
                {
                    return ConstUncheckedIterType{ array.end() };
                }

            public:
                inline static constexpr decltype(auto) rbegin(ContainerType& array) noexcept
                {
                    return ReverseIterType{ array.rbegin() };
                }

                inline static constexpr decltype(auto) crbegin(const ContainerType& array) noexcept
                {
                    return ConstReverseIterType{ array.rbegin() };
                }

                inline static constexpr decltype(auto) rbegin_unchecked(ContainerType& array) noexcept
                {
                    return UncheckedReverseIterType{ array.rbegin() };
                }

                inline static constexpr decltype(auto) crbegin_unchecked(const ContainerType& array) noexcept
                {
                    return ConstUncheckedReverseIterType{ array.rbegin() };
                }

            public:
                inline static constexpr decltype(auto) rend(ContainerType& array) noexcept
                {
                    return ReverseIterType{ array.rend() };
                }

                inline static constexpr decltype(auto) crend(const ContainerType& array) noexcept
                {
                    return ConstReverseIterType{ array.rend() };
                }

                inline static constexpr decltype(auto) rend_unchecked(ContainerType& array) noexcept
                {
                    return UncheckedReverseIterType{ array.rend() };
                }

                inline static constexpr decltype(auto) crend_unchecked(const ContainerType& array) noexcept
                {
                    return ConstUncheckedReverseIterType{ array.rend() };
                }
            };

            template<
                typename T,
                pointer::PointerCategory cat,
                template<typename U> class C
            >
            class PointerArrayAccessPolicy<T, C<pointer::Ptr<OriginType<T>, cat>>>
            {
            public:
                using ValueType = OriginType<T>;
                using ContainerType = C<pointer::Ptr<ValueType, cat>>;
                using IterType = PointerArrayIterator<ValueType, cat, ContainerType>;
                using ConstIterType = PointerArrayConstIterator<ValueType, cat, ContainerType>;
                using ReverseIterType = PointerArrayReverseIterator<ValueType, cat, ContainerType>;
                using ConstReverseIterType = PointerArrayConstReverseIterator<ValueType, cat, ContainerType>;
                using UncheckedIterType = PointerArrayUncheckedIterator<ValueType, cat, ContainerType>;
                using ConstUncheckedIterType = PointerArrayConstUncheckedIterator<ValueType, cat, ContainerType>;
                using UncheckedReverseIterType = PointerArrayUncheckedReverseIterator<ValueType, cat, ContainerType>;
                using ConstUncheckedReverseIterType = PointerArrayConstUncheckedReverseIterator<ValueType, cat, ContainerType>;

            public:
                inline static constexpr const usize size(const ContainerType& array) noexcept
                {
                    return l;
                }

                inline static constexpr pointer::Ptr<ValueType, cat>& get(ContainerType& array, const usize i)
                {
                    return array.at(i);
                }

                inline static constexpr const pointer::Ptr<ValueType, cat>& get(const ContainerType& array, const usize i)
                {
                    return array.at(i);
                }

                inline static constexpr pointer::Ptr<ValueType, cat>& get_unchecked(ContainerType& array, const usize i)
                {
                    return array[i];
                }

                inline static constexpr const pointer::Ptr<ValueType, cat>& get_unchecked(const ContainerType& array, const usize i)
                {
                    return array[i];
                }

            public:
                inline static constexpr decltype(auto) begin(ContainerType& array) noexcept
                {
                    return IterType{ array.begin() };
                }

                inline static constexpr decltype(auto) cbegin(const ContainerType& array) noexcept
                {
                    return ConstIterType{ array.begin() };
                }

                inline static constexpr decltype(auto) begin_unchecked(ContainerType& array) noexcept
                {
                    return UncheckedIterType{ array.begin() };
                }

                inline static constexpr decltype(auto) cbegin_unchecked(const ContainerType& array) noexcept
                {
                    return ConstUncheckedIterType{ array.begin() };
                }

            public:
                inline static constexpr decltype(auto) end(ContainerType& array) noexcept
                {
                    return IterType{ array.end() };
                }

                inline static constexpr decltype(auto) cend(const ContainerType& array) noexcept
                {
                    return ConstIterType{ array.end() };
                }

                inline static constexpr decltype(auto) end_unchecked(ContainerType& array) noexcept
                {
                    return UncheckedIterType{ array.end() };
                }

                inline static constexpr decltype(auto) cend_unchecked(const ContainerType& array) noexcept
                {
                    return ConstUncheckedIterType{ array.end() };
                }

            public:
                inline static constexpr decltype(auto) rbegin(ContainerType& array) noexcept
                {
                    return ReverseIterType{ array.rbegin() };
                }

                inline static constexpr decltype(auto) crbegin(const ContainerType& array) noexcept
                {
                    return ConstReverseIterType{ array.rbegin() };
                }

                inline static constexpr decltype(auto) rbegin_unchecked(ContainerType& array) noexcept
                {
                    return UncheckedReverseIterType{ array.rbegin() };
                }

                inline static constexpr decltype(auto) crbegin_unchecked(const ContainerType& array) noexcept
                {
                    return ConstUncheckedReverseIterType{ array.rbegin() };
                }

            public:
                inline static constexpr decltype(auto) rend(ContainerType& array) noexcept
                {
                    return ReverseIterType{ array.rend() };
                }

                inline static constexpr decltype(auto) crend(const ContainerType& array) noexcept
                {
                    return ConstReverseIterType{ array.rend() };
                }

                inline static constexpr decltype(auto) rend_unchecked(ContainerType& array) noexcept
                {
                    return UncheckedReverseIterType{ array.rend() };
                }

                inline static constexpr decltype(auto) crend_unchecked(const ContainerType& array) noexcept
                {
                    return ConstUncheckedReverseIterType{ array.rend() };
                }
            };

            template<typename T, typename C, typename Self>
            class PointerArrayImpl
            {
                OSPF_CRTP_IMPL

            public:
                using ValueType = OriginType<T>;
                using ContainerType = OriginType<C>;
                using AccessPolicyType = PointerArrayAccessPolicy<ValueType, ContainerType>;
                using IterType = typename AccessPolicyType::IterType;
                using ConstIterType = typename AccessPolicyType::ConstIterType;
                using ReverseIterType = typename AccessPolicyType::ReverseIterType;
                using ConstReverseIterType = typename AccessPolicyType::ConstReverseIterType;
                using UncheckedIterType = typename AccessPolicyType::UncheckedIterType;
                using ConstUncheckedIterType = typename AccessPolicyType::ConstUncheckedIterType;
                using UncheckedReverseIterType = typename AccessPolicyType::UncheckedReverseIterType;
                using ConstUncheckedReverseIterType = typename AccessPolicyType::ConstUncheckedReverseIterType;

            protected:
                constexpr PointerArrayImpl(void) = default;
            public:
                constexpr PointerArrayImpl(const PointerArrayImpl& ano) = default;
                constexpr PointerArrayImpl(PointerArrayImpl&& ano) noexcept = default;
                constexpr PointerArrayImpl& operator=(const PointerArrayImpl& rhs) = default;
                constexpr PointerArrayImpl& operator=(PointerArrayImpl&& rhs) noexcept = default;
                constexpr ~PointerArrayImpl(void) noexcept = default;

            public:
                inline constexpr const bool null(const usize i) const
                {
                    return at(i) == nullptr;
                }

            public:
                inline constexpr decltype(auto) at(const usize i)
                {
                    return AccessPolicyType::get(container())[i];
                }

                inline constexpr decltype(auto) at(const usize i) const
                {
                    return AccessPolicyType::get(const_container())[i];
                }

                inline constexpr decltype(auto) operator[](const usize i)
                {
                    return AccessPolicyType::get_unchecked(container())[i];
                }

                inline constexpr decltype(auto) operator[](const usize i)
                {
                    return AccessPolicyType::get_unchecked(const_container())[i];
                }

            public:
                inline constexpr decltype(auto) front(void)
                {
                    return at(0_uz);
                }

                inline constexpr decltype(auto) front(void) const
                {
                    return at(0_uz);
                }

                inline constexpr decltype(auto) back(void)
                {
                    return at(size() - 1_uz);
                }

                inline constexpr decltype(auto) back(void) const
                {
                    return at(size() - 1_uz);
                }

            public:
                inline constexpr decltype(auto) begin(void) noexcept
                {
                    return AccessPolicyType::begin(container());
                }

                inline constexpr decltype(auto) begin(void) const noexcept
                {
                    return AccessPolicyType::cbegin(const_container());
                }

                inline constexpr decltype(auto) cbegin(void) const noexcept
                {
                    return AccessPolicyType::cbegin(const_container());
                }

                inline constexpr decltype(auto) begin_unchecked(void) noexcept
                {
                    return AccessPolicyType::begin_unchecked(container());
                }

                inline constexpr decltype(auto) begin_unchecked(void) const noexcept
                {
                    return AccessPolicyType::cbegin_unchecked(const_container());
                }

                inline constexpr decltype(auto) cbegin_unchecked(void) const noexcept
                {
                    return AccessPolicyType::cbegin_unchecked(const_container());
                }

            public:
                inline constexpr decltype(auto) end(void) noexcept
                {
                    return AccessPolicyType::end(container());
                }

                inline constexpr decltype(auto) end(void) const noexcept
                {
                    return AccessPolicyType::cend(const_container());
                }

                inline constexpr decltype(auto) cend(void) const noexcept
                {
                    return AccessPolicyType::cend(const_container());
                }

                inline constexpr decltype(auto) end_unchecked(void) noexcept
                {
                    return AccessPolicyType::end_unchecked(container());
                }

                inline constexpr decltype(auto) end_unchecked(void) const noexcept
                {
                    return AccessPolicyType::cend_unchecked(const_container());
                }

                inline constexpr decltype(auto) cend_unchecked(void) const noexcept
                {
                    return AccessPolicyType::cend_unchecked(const_container());
                }

            public:
                inline constexpr decltype(auto) rbegin(void) noexcept
                {
                    return AccessPolicyType::rbegin(container());
                }

                inline constexpr decltype(auto) rbegin(void) const noexcept
                {
                    return AccessPolicyType::crbegin(const_container());
                }

                inline constexpr decltype(auto) crbegin(void) const noexcept
                {
                    return AccessPolicyType::crbegin(const_container());
                }

                inline constexpr decltype(auto) rbegin_unchecked(void) noexcept
                {
                    return AccessPolicyType::rbegin_unchecked(container());
                }

                inline constexpr decltype(auto) rbegin_unchecked(void) const noexcept
                {
                    return AccessPolicyType::crbegin_unchecked(const_container());
                }

                inline constexpr decltype(auto) crbegin_unchecked(void) const noexcept
                {
                    return AccessPolicyType::crbegin_unchecked(const_container());
                }

            public:
                inline constexpr decltype(auto) rend(void) noexcept
                {
                    return AccessPolicyType::rend(container());
                }

                inline constexpr decltype(auto) rend(void) const noexcept
                {
                    return AccessPolicyType::crend(const_container());
                }

                inline constexpr decltype(auto) crend(void) const noexcept
                {
                    return AccessPolicyType::crend(const_container());
                }

                inline constexpr decltype(auto) rend_unchecked(void) noexcept
                {
                    return AccessPolicyType::rend_unchecked(container());
                }

                inline constexpr decltype(auto) rend_unchecked(void) const noexcept
                {
                    return AccessPolicyType::crend_unchecked(const_container());
                }

                inline constexpr decltype(auto) crend_unchecked(void) const noexcept
                {
                    return AccessPolicyType::crend_unchecked(const_container());
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
                inline void swap(PointerArrayImpl<T, C, Self>& ano) noexcept
                {
                    std::swap(container(), ano.container());
                }

            protected:
                inline ContainerType& container(void) noexcept
                {
                    return Trait::get_container(self());
                }

                inline const ContainerType& const_container(void) const noexcept
                {
                    return Trait::get_const_container(self());
                }

            private:
                struct Trait : public Self
                {
                    inline static ContainerType& get_container(Self& self) noexcept
                    {
                        static const auto get_impl = &Self::OSPF_CRTP_FUNCTION(get_container);
                        return (self.*get_impl)();
                    }

                    inline static const ContainerType& get_const_container(const Self& self) noexcept
                    {
                        static const auto get_impl = &Self::OSPF_CRTP_FUNCTION(get_const_container);
                        return (self.*get_impl)();
                    }
                };

                template<typename T, typename C, typename Self>
                class PointerArrayUncheckedAccessorImpl
                {
                    using Impl = PointerArrayImpl<T, C, Self>;

                public:
                    using ValueType = typename Impl::ValueType;
                    using ContainerType = typename Impl::ContainerType;
                    using typename Impl::IterType;
                    using typename Impl::ConstIterType;
                    using typename Impl::ReverseIterType;
                    using typename Impl::ConstReverseIterType;
                    using typename Impl::UncheckedIterType;
                    using typename Impl::ConstUncheckedIterType;
                    using typename Impl::UncheckedReverseIterType;
                    using typename Impl::ConstUncheckedReverseIterType;

                public:
                    constexpr PointerArrayUncheckedAccessorImpl(const Impl& impl)
                        : _impl(impl) {}
                    constexpr PointerArrayUncheckedAccessorImpl(const PointerArrayUncheckedAccessorImpl& ano) = default;
                    constexpr PointerArrayUncheckedAccessorImpl(PointerArrayUncheckedAccessorImpl&& ano) noexcept = default;
                    constexpr PointerArrayUncheckedAccessorImpl& operator=(const PointerArrayUncheckedAccessorImpl& rhs) = default;
                    constexpr PointerArrayUncheckedAccessorImpl& operator=(PointerArrayUncheckedAccessorImpl&& rhs) noexcept = default;
                    constexpr ~PointerArrayUncheckedAccessorImpl(void) noexcept = default;

                public:
                    inline constexpr const bool null(const usize i) const
                    {
                        return _impl.null(i);
                    }

                public:
                    inline constexpr decltype(auto) at(const usize i)
                    {
                        return *_impl.at(i);
                    }

                    inline constexpr decltype(auto) at(const usize i) const
                    {
                        return *_impl.at(i);
                    }

                    inline constexpr decltype(auto) operator[](const usize i)
                    {
                        return *_impl[i];
                    }

                    inline constexpr decltype(auto) operator[](const usize i)
                    {
                        return *_impl[i];
                    }

                public:
                    inline constexpr decltype(auto) front(void)
                    {
                        return *_impl.front();
                    }

                    inline constexpr decltype(auto) front(void) const
                    {
                        return *_impl.front();
                    }

                    inline constexpr decltype(auto) back(void)
                    {
                        return *_impl.back();
                    }

                    inline constexpr decltype(auto) back(void) const
                    {
                        return *_impl.back();
                    }

                public:
                    inline constexpr decltype(auto) begin(void) noexcept
                    {
                        return _impl.begin_unchecked();
                    }

                    inline constexpr decltype(auto) begin(void) const noexcept
                    {
                        return _impl.begin_unchecked();
                    }

                    inline constexpr decltype(auto) cbegin(void) const noexcept
                    {
                        return _impl.cbegin_unchecked();
                    }

                public:
                    inline constexpr decltype(auto) end(void) noexcept
                    {
                        return _impl.end_unchecked();
                    }

                    inline constexpr decltype(auto) end(void) const noexcept
                    {
                        return _impl.end_unchecked();
                    }

                    inline constexpr decltype(auto) cend(void) const noexcept
                    {
                        return _impl.cend_unchecked();
                    }

                public:
                    inline constexpr decltype(auto) rbegin(void) noexcept
                    {
                        return _impl.rbegin_unchecked();
                    }

                    inline constexpr decltype(auto) rbegin(void) const noexcept
                    {
                        return _impl.rbegin_unchecked();
                    }

                    inline constexpr decltype(auto) crbegin(void) const noexcept
                    {
                        return _impl.crbegin_unchecked();
                    }

                public:
                    inline constexpr decltype(auto) rend(void) noexcept
                    {
                        return _impl.rend_unchecked();
                    }

                    inline constexpr decltype(auto) rend(void) const noexcept
                    {
                        return _impl.rend_unchecked();
                    }

                    inline constexpr decltype(auto) crend(void) const noexcept
                    {
                        return _impl.crend_unchecked();
                    }

                public:
                    inline constexpr const bool empty(void) const noexcept
                    {
                        return _impl.empty();
                    }

                    inline constexpr const usize size(void) const noexcept
                    {
                        return _impl.size();
                    }

                private:
                    Ref<Impl> _impl;
                };

                template<
                    typename T, 
                    usize len,
                    memory::pointer::PointerCategory cat,
                    template<typename T, usize l> class C
                >
                class StaticPointerArray
                    : public PointerArrayImpl<T, C<pointer::Ptr<OriginType<T>, cat>, len>, StaticPointerArray<T, len, cat, C>>
                {
                    using Impl = PointerArrayImpl<T, C<pointer::Ptr<OriginType<T>, cat>, len>, StaticPointerArray<T, len, cat, C>>;
                    using UncheckedAccessorImpl = PointerArrayUncheckedAccessorImpl<T, C<pointer::Ptr<OriginType<T>, cat>, len>, StaticPointerArray<T, len, cat, C>>;

                public:
                    using typename Impl::ValueType;
                    using typename Impl::ContainerType;
                    using typename Impl::IterType;
                    using typename Impl::ConstIterType;
                    using typename Impl::ReverseIterType;
                    using typename Impl::ConstReverseIterType;
                    using typename Impl::UncheckedIterType;
                    using typename Impl::ConstUncheckedIterType;
                    using typename Impl::UncheckedReverseIterType;
                    using typename Impl::ConstUncheckedReverseIterType;

                public:
                    StaticPointerArray(void) = default;

                    StaticPointerArray(ContainerType container)
                        : _container(move<ContainerType>(container)) {}

                    StaticPointerArray(std::initializer_list<PtrType<ValueType>> ptrs)
                    {
                        for (auto i{ 0_uz }, j{ (std::min)(l, ptrs.size) }; i != j; ++i)
                        {
                            _container[i] = pointer::Ptr<ValueType, cat>{ move<ValueType>(ptrs[i]) };
                        }
                    }

                    StaticPointerArray(std::initializer_list<CPtrType<ValueType>> ptrs)
                    {
                        for (auto i{ 0_uz }, j{ (std::min)(l, ptrs.size) }; i != j; ++i)
                        {
                            _container[i] = pointer::Ptr<ValueType, cat>{ move<ValueType>(ptrs[i]) };
                        }
                    }

                    StaticPointerArray(std::initializer_list<pointer::Ptr<ValueType, cat>> ptrs)
                        : _container(std::move(ptrs)) {}

                public:
                    constexpr StaticPointerArray(const StaticPointerArray& ano) = default;
                    constexpr StaticPointerArray(StaticPointerArray&& ano) noexcept = default;
                    constexpr StaticPointerArray& operator=(const StaticPointerArray& rhs) = default;
                    constexpr StaticPointerArray& operator=(StaticPointerArray&& rhs) noexcept = default;
                    constexpr ~StaticPointerArray(void) = default;

                public:
                    inline constexpr RetType<UncheckedAccessorImpl> unchecked(void) const noexcept
                    {
                        return UncheckedAccessorImpl{ dynamic_cast<const Impl&>(*this) };
                    }

                    template<typename = void>
                        requires requires (ContainerType& container) { { container.data() } -> DecaySameAs<PtrType<pointer::Ptr<ValueType, cat>>>; }
                    inline constexpr const PtrType<pointer::Ptr<ValueType, cat>> data(void) noexcept
                    {
                        return _container.data();
                    }

                    template<typename = void>
                        requires requires (const ContainerType& container) { { container.data() } -> DecaySameAs<CPtrType<pointer::Ptr<ValueType, cat>>>; }
                    inline constexpr const CPtrType<pointer::Ptr<ValueType, cat>> data(void) const noexcept
                    {
                        return _container.data();
                    }

                public:
                    inline constexpr const usize max_size(void) const noexcept
                    {
                        return _container.max_size();
                    }

                public:
                    inline constexpr void clear(void) noexcept
                    {
                        _container.fill();
                    }

                    inline constexpr void fill(const std::nullptr_t _ = nullptr) noexcept
                    {
                        _container.fill(pointer::Ptr<ValueType, cat>{ nullptr });
                    }

                    inline constexpr void fill(const PtrType<ValueType> ptr) noexcept
                    {
                        _container.fill(pointer::Ptr<ValueType, cat>{ ptr });
                    }

                    inline constexpr void fill(const CPtrType<ValueType> ptr) noexcept
                    {
                        _container.fill(pointer::Ptr<ValueType, cat>{ ptr });
                    }

                public:
                    inline constexpr const bool operator==(const StaticPointerArray& rhs) const noexcept
                    {
                        return _container == rhs._container;
                    }

                    inline constexpr const bool operator!=(const StaticPointerArray& rhs) const noexcept
                    {
                        return _container != rhs._container;
                    }

                public:
                    inline constexpr const bool operator<(const StaticPointerArray& rhs) const noexcept
                    {
                        return _container < rhs._container;
                    }

                    inline constexpr const bool operator<=(const StaticPointerArray& rhs) const noexcept
                    {
                        return _container <= rhs._container;
                    }

                    inline constexpr const bool operator>(const StaticPointerArray& rhs) const noexcept
                    {
                        return _container > rhs._container;
                    }

                    inline constexpr const bool operator>=(const StaticPointerArray& rhs) const noexcept
                    {
                        return _container >= rhs._container;
                    }

                public:
                    inline constexpr decltype(auto) operator<=>(const StaticPointerArray& rhs) const noexcept
                    {
                        return _container <=> rhs._container;
                    }

                OSPF_CRTP_PERMISSION:
                    inline ContainerType& OSPF_CRTP_FUNCTION(get_container)(void) noexcept
                    {
                        return _container;
                    }

                    inline const ContainerType& OSPF_CRTP_FUNCTION(get_const_container)(void) const noexcept
                    {
                        return _container;
                    }

                private:
                    ContainerType _container;
                };

                template<
                    typename T,
                    pointer::PointerCategory cat,
                    template<typename T> class C
                >
                class DynamicPointerArray
                    : public PointerArrayImpl<T, C<pointer::Ptr<OriginType<T>, cat>>, DynamicPointerArray<T, cat, C>>
                {
                    using Impl = PointerArrayImpl<T, C<pointer::Ptr<OriginType<T>, cat>>, DynamicPointerArray<T, cat, C>>;
                    using UncheckedAccessorImpl = PointerArrayUncheckedAccessorImpl<T, C<pointer::Ptr<OriginType<T>, cat>>, DynamicPointerArray<T, cat, C>>;

                public:
                    using typename Impl::ValueType;
                    using typename Impl::ContainerType;
                    using typename Impl::IterType;
                    using typename Impl::ConstIterType;
                    using typename Impl::ReverseIterType;
                    using typename Impl::ConstReverseIterType;
                    using typename Impl::UncheckedIterType;
                    using typename Impl::ConstUncheckedIterType;
                    using typename Impl::UncheckedReverseIterType;
                    using typename Impl::ConstUncheckedReverseIterType;

                public:
                    constexpr DynamicPointerArray(void) = default;

                    constexpr explicit DynamicPointerArray(const usize length)
                        : _container(length) {}

                    constexpr DynamicPointerArray(const usize length, const PtrType<ValueType> ptr)
                        : _container(length, pointer::Ptr<ValueType, cat>{ ptr }) {}

                    constexpr DynamicPointerArray(const usize length, const CPtrType<ValueType> ptr)
                        : _container(length, pointer::Ptr<ValueType, cat>{ ptr }) {}

                    template<std::input_iterator It>
                    constexpr DynamicPointerArray(const It first, const It last)
                        : _container(first, last) {}

                    constexpr DynamicPointerArray(std::initializer_list<PtrType<ValueType>> ptrs)
                        : _container(ptrs.size())
                    {
                        for (auto i{ 0_uz }; i != ptrs.size(); ++i)
                        {
                            _container[i] = pointer::Ptr<ValueType, cat>{ ptrs[i] };
                        }
                    }

                    constexpr DynamicPointerArray(std::initializer_list<CPtrType<ValueType>> ptrs)
                        : _container(ptrs.size())
                    {
                        for (auto i{ 0_uz }; i != ptrs.size(); ++i)
                        {
                            _container[i] = pointer::Ptr<ValueType, cat>{ ptrs[i] };
                        }
                    }

                    constexpr DynamicPointerArray(std::initializer_list<pointer::Ptr<ValueType, cat>> ptrs)
                        : _container(std::move(ptrs)) {}

                public:
                    constexpr DynamicPointerArray(const DynamicPointerArray& ano) = default;
                    constexpr DynamicPointerArray(DynamicPointerArray&& ano) noexcept = default;
                    constexpr DynamicPointerArray& operator=(const DynamicPointerArray& rhs) = default;
                    constexpr DynamicPointerArray& operator=(DynamicPointerArray&& rhs) noexcept = default;
                    constexpr ~DynamicPointerArray(void) = default;

                public:
                    // todo: assign

                public:
                    // todo: unchecked, data

                public:
                    // todo: max_size, reserve, capacity, shrink_to_fit

                public:
                    // todo: clear, insert, emplace, erase
                    // todo: push_back, emplace_back, pop_back
                    // todo: push_front, emplace_front, pop_front
                    // todo: resize


                public:
                    inline constexpr const bool operator==(const DynamicPointerArray& rhs) const noexcept
                    {
                        return _container == rhs._container;
                    }

                    inline constexpr const bool operator!=(const DynamicPointerArray& rhs) const noexcept
                    {
                        return _container != rhs._container;
                    }

                public:
                    inline constexpr const bool operator<(const DynamicPointerArray& rhs) const noexcept
                    {
                        return _container < rhs._container;
                    }

                    inline constexpr const bool operator<=(const DynamicPointerArray& rhs) const noexcept
                    {
                        return _container <= rhs._container;
                    }

                    inline constexpr const bool operator>(const DynamicPointerArray& rhs) const noexcept
                    {
                        return _container > rhs._container;
                    }

                    inline constexpr const bool operator>=(const DynamicPointerArray& rhs) const noexcept
                    {
                        return _container >= rhs._container;
                    }

                public:
                    inline constexpr decltype(auto) operator<=>(const DynamicPointerArray& rhs) const noexcept
                    {
                        return _container <=> rhs._container;
                    }

                OSPF_CRTP_PERMISSION:
                    inline ContainerType& OSPF_CRTP_FUNCTION(get_container)(void) noexcept
                    {
                        return _container;
                    }

                    inline const ContainerType& OSPF_CRTP_FUNCTION(get_const_container)(void) const noexcept
                    {
                        return _container;
                    }

                private:
                    ContainerType _container;
                };
            };
        };

        template<
            typename T,
            usize l,
            pointer::PointerCategory cat = pointer::PointerCategory::Raw,
            template<typename T, usize l> class C = std::array
        >
        using PtrArray = pointer_array::StaticPointerArray<T, l, cat, C>;

        template<typename T,
            usize l,
            template<typename T, usize l> class C = std::array
        >
        using SharedArray = pointer_array::StaticPointerArray<T, l, pointer::PointerCategory::Shared, C>;

        template<typename T,
            usize l,
            template<typename T, usize l> class C = std::array
        >
        using UniqueArray = pointer_array::StaticPointerArray<T, l, pointer::PointerCategory::Unique, C>;

        template<
            typename T,
            pointer::PointerCategory cat = pointer::PointerCategory::Raw,
            template<typename T> class C = std::vector
        >
        using DynPtrArray = pointer_array::DynamicPointerArray<T, cat, C>;

        template<
            typename T,
            template<typename T> class C = std::vector
        >
        using DynSharedArray = pointer_array::DynamicPointerArray<T, pointer::PointerCategory::Shared, C>;

        template<
            typename T,
            template<typename T> class C = std::vector
        >
        using DynUniqueArray = pointer_array::DynamicPointerArray<T, pointer::PointerCategory::Unique, C>;
    };
};

namespace std
{
    template<typename T, typename C, typename Self>
    inline void swap(ospf::data_structure::pointer_array::PointerArrayImpl<T, C, Self>& lhs, ospf::data_structure::pointer_array::PointerArrayImpl<T, C, Self>& rhs) noexcept
    {
        lhs.swap(rhs);
    }
};
 