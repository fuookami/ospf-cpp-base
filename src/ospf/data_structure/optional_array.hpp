#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/concepts/with_default.hpp>
#include <ospf/literal_constant.hpp>
#include <ospf/memory/reference.hpp>
#include <ospf/meta_programming/iterator.hpp>

namespace ospf
{
    inline namespace data_structure
    {
        namespace optional_array
        {
            template<
                typename T,
                usize len,
                template<typename T, usize l> class C
            >
            class StaticOptionalArray;

            template<
                typename T,
                template<typename T> class C
            >
            class DynamicOptionalArray;

            template<typename T, typename C>
            class OptionalArrayConstIterator
                : public RandomIteratorImpl<std::optional<OriginType<T>>, typename OriginType<C>::const_iterator, OptionalArrayConstIterator<T, C>>
            {
                template<
                    typename T,
                    usize len,
                    template<typename T, usize l> class C
                >
                friend class StaticOptionalArray;

                template<
                    typename T,
                    template<typename T> class C
                >
                friend class DynamicOptionalArray;

            public:
                using ValueType = std::optional<OriginType<T>>;
                using ContainerType = OriginType<C>;
                using IterType = typename ContainerType::const_iterator;

            private:
                using Base = RandomIteratorImpl<ValueType, IterType, OptionalArrayConstIterator<T, C>>;

            public:
                constexpr OptionalArrayConstIterator(const IterType iter)
                    : Base(iter) {}
                constexpr OptionalArrayConstIterator(const OptionalArrayConstIterator& ano) = default;
                constexpr OptionalArrayConstIterator(OptionalArrayConstIterator&& ano) noexcept = default;
                constexpr OptionalArrayConstIterator& operator=(const OptionalArrayConstIterator& rhs) = default;
                constexpr OptionalArrayConstIterator& operator=(OptionalArrayConstIterator&& rhs) noexcept = default;
                constexpr ~OptionalArrayConstIterator(void) noexcept = default;

            public:
                inline constexpr const bool has_value(void) const
                {
                    return this->_iter->has_value();
                }

            OSPF_CRTP_PERMISSION:
                inline static constexpr const ValueType& OSPF_CRTP_FUNCTION(get)(const IterType iter) noexcept
                {
                    return *iter;
                }

                inline static constexpr const OptionalArrayConstIterator OSPF_CRTP_FUNCTION(construct)(const IterType iter) noexcept
                {
                    return OptionalArrayConstIterator{ iter };
                }
            };

            template<typename T, typename C>
            class OptionalArrayIterator
                : public RandomIteratorImpl<std::optional<OriginType<T>>, typename OriginType<C>::iterator, OptionalArrayIterator<T, C>>
            {
                template<
                    typename T,
                    usize len,
                    template<typename T, usize l> class C
                >
                friend class StaticOptionalArray;

                template<
                    typename T,
                    template<typename T> class C
                >
                friend class DynamicOptionalArray;

            public:
                using ValueType = std::optional<OriginType<T>>;
                using ContainerType = OriginType<C>;
                using IterType = typename ContainerType::iterator;

            private:
                using Base = RandomIteratorImpl<ValueType, IterType, OptionalArrayIterator<T, C>>;

            public:
                constexpr OptionalArrayIterator(const IterType iter)
                    : Base(iter) {}
                constexpr OptionalArrayIterator(const OptionalArrayIterator& ano) = default;
                constexpr OptionalArrayIterator(OptionalArrayIterator&& ano) noexcept = default;
                constexpr OptionalArrayIterator& operator=(const OptionalArrayIterator& rhs) = default;
                constexpr OptionalArrayIterator& operator=(OptionalArrayIterator&& rhs) noexcept = default;
                constexpr ~OptionalArrayIterator(void) noexcept = default;

            public:
                inline constexpr const bool has_value(void) const
                {
                    return this->_iter->has_value();
                }

            public:
                inline operator const OptionalArrayConstIterator<T, C>(void) const noexcept
                {
                    return OptionalArrayConstIterator<T, C>{ this->_iter };
                }

            OSPF_CRTP_PERMISSION:
                inline static constexpr ValueType& OSPF_CRTP_FUNCTION(get)(const IterType iter) noexcept
                {
                    return *iter;
                }

                inline static constexpr const OptionalArrayIterator OSPF_CRTP_FUNCTION(construct)(const IterType iter) noexcept
                {
                    return OptionalArrayIterator{ iter };
                }
            };

            template<typename T, typename C>
            class OptionalArrayConstReverseIterator
                : public RandomIteratorImpl<std::optional<OriginType<T>>, typename OriginType<C>::const_reverse_iterator, OptionalArrayConstReverseIterator<T, C>>
            {
                template<
                    typename T,
                    usize len,
                    template<typename T, usize l> class C
                >
                friend class StaticOptionalArray;

                template<
                    typename T,
                    template<typename T> class C
                >
                friend class DynamicOptionalArray;

            public:
                using ValueType = std::optional<OriginType<T>>;
                using ContainerType = OriginType<C>;
                using IterType = typename ContainerType::const_reverse_iterator;

            private:
                using Base = RandomIteratorImpl<ValueType, IterType, OptionalArrayConstReverseIterator<T, C>>;

            public:
                constexpr OptionalArrayConstReverseIterator(const IterType iter)
                    : Base(iter) {}
                constexpr OptionalArrayConstReverseIterator(const OptionalArrayConstReverseIterator& ano) = default;
                constexpr OptionalArrayConstReverseIterator(OptionalArrayConstReverseIterator&& ano) noexcept = default;
                constexpr OptionalArrayConstReverseIterator& operator=(const OptionalArrayConstReverseIterator& rhs) = default;
                constexpr OptionalArrayConstReverseIterator& operator=(OptionalArrayConstReverseIterator&& rhs) noexcept = default;
                constexpr ~OptionalArrayConstReverseIterator(void) noexcept = default;

            public:
                inline constexpr const bool has_value(void) const
                {
                    return this->_iter->has_value();
                }

            OSPF_CRTP_PERMISSION:
                inline static constexpr const ValueType& OSPF_CRTP_FUNCTION(get)(const IterType iter) noexcept
                {
                    return *iter;
                }

                inline static constexpr const OptionalArrayConstReverseIterator OSPF_CRTP_FUNCTION(construct)(const IterType iter) noexcept
                {
                    return OptionalArrayConstReverseIterator{ iter };
                }
            };

            template<typename T, typename C>
            class OptionalArrayReverseIterator
                : public RandomIteratorImpl<std::optional<OriginType<T>>, typename OriginType<C>::reverse_iterator, OptionalArrayReverseIterator<T, C>>
            {
                template<
                    typename T,
                    usize len,
                    template<typename T, usize l> class C
                >
                friend class StaticOptionalArray;

                template<
                    typename T,
                    template<typename T> class C
                >
                friend class DynamicOptionalArray;

            public:
                using ValueType = std::optional<OriginType<T>>;
                using ContainerType = OriginType<C>;
                using IterType = typename ContainerType::reverse_iterator;

            private:
                using Base = RandomIteratorImpl<ValueType, IterType, OptionalArrayReverseIterator<T, C>>;

            public:
                constexpr OptionalArrayReverseIterator(const IterType iter)
                    : Base(iter) {}
                constexpr OptionalArrayReverseIterator(const OptionalArrayReverseIterator& ano) = default;
                constexpr OptionalArrayReverseIterator(OptionalArrayReverseIterator&& ano) noexcept = default;
                constexpr OptionalArrayReverseIterator& operator=(const OptionalArrayReverseIterator& rhs) = default;
                constexpr OptionalArrayReverseIterator& operator=(OptionalArrayReverseIterator&& rhs) noexcept = default;
                constexpr ~OptionalArrayReverseIterator(void) noexcept = default;

            public:
                inline constexpr const bool has_value(void) const
                {
                    return this->_iter->has_value();
                }

            OSPF_CRTP_PERMISSION:
                inline static constexpr ValueType& OSPF_CRTP_FUNCTION(get)(const IterType iter) noexcept
                {
                    return *iter;
                }

                inline static constexpr const OptionalArrayConstReverseIterator OSPF_CRTP_FUNCTION(construct)(const IterType iter) noexcept
                {
                    return OptionalArrayConstReverseIterator{ iter };
                }
            };

            template<typename T, typename C>
            class OptionalArrayConstUncheckedIterator
                : public RandomIteratorImpl<OriginType<T>, typename OriginType<C>::const_iterator, OptionalArrayConstUncheckedIterator<T, C>>
            {
                template<
                    typename T,
                    usize len,
                    template<typename T, usize l> class C
                >
                friend class StaticOptionalArray;

                template<
                    typename T,
                    template<typename T> class C
                >
                friend class DynamicOptionalArray;

            public:
                using ValueType = OriginType<T>;
                using ContainerType = OriginType<C>;
                using IterType = typename ContainerType::const_iterator;

            private:
                using Base = RandomIteratorImpl<ValueType, IterType, OptionalArrayConstUncheckedIterator<T, C>>;

            public:
                constexpr OptionalArrayConstUncheckedIterator(const IterType iter)
                    : Base(iter) {}
                constexpr OptionalArrayConstUncheckedIterator(const OptionalArrayConstUncheckedIterator& ano) = default;
                constexpr OptionalArrayConstUncheckedIterator(OptionalArrayConstUncheckedIterator&& ano) noexcept = default;
                constexpr OptionalArrayConstUncheckedIterator& operator=(const OptionalArrayConstUncheckedIterator& rhs) = default;
                constexpr OptionalArrayConstUncheckedIterator& operator=(OptionalArrayConstUncheckedIterator&& rhs) noexcept = default;
                constexpr ~OptionalArrayConstUncheckedIterator(void) noexcept = default;

            public:
                inline constexpr const bool has_value(void) const
                {
                    return this->_iter->has_value();
                }

            OSPF_CRTP_PERMISSION:
                inline static constexpr const ValueType& OSPF_CRTP_FUNCTION(get)(const IterType iter) noexcept
                {
                    return **iter;
                }

                inline static constexpr const OptionalArrayConstUncheckedIterator OSPF_CRTP_FUNCTION(construct)(const IterType iter) noexcept
                {
                    return OptionalArrayConstUncheckedIterator{ iter };
                }
            };

            template<typename T, typename C>
            class OptionalArrayUncheckedIterator
                : public RandomIteratorImpl<OriginType<T>, typename OriginType<C>::iterator, OptionalArrayUncheckedIterator<T, C>>
            {
                template<
                    typename T,
                    usize len,
                    template<typename T, usize l> class C
                >
                friend class StaticOptionalArray;

                template<
                    typename T,
                    template<typename T> class C
                >
                friend class DynamicOptionalArray;

            public:
                using ValueType = OriginType<T>;
                using ContainerType = OriginType<C>;
                using IterType = typename ContainerType::iterator;

            private:
                using Base = RandomIteratorImpl<ValueType, IterType, OptionalArrayUncheckedIterator<T, C>>;

            public:
                constexpr OptionalArrayUncheckedIterator(const IterType iter)
                    : Base(iter) {}
                constexpr OptionalArrayUncheckedIterator(const OptionalArrayUncheckedIterator& ano) = default;
                constexpr OptionalArrayUncheckedIterator(OptionalArrayUncheckedIterator&& ano) noexcept = default;
                constexpr OptionalArrayUncheckedIterator& operator=(const OptionalArrayUncheckedIterator& rhs) = default;
                constexpr OptionalArrayUncheckedIterator& operator=(OptionalArrayUncheckedIterator&& rhs) noexcept = default;
                constexpr ~OptionalArrayUncheckedIterator(void) noexcept = default;

            public:
                inline constexpr const bool has_value(void) const
                {
                    return this->_iter->has_value();
                }

            public:
                inline operator const OptionalArrayConstUncheckedIterator<T, C>(void) const noexcept
                {
                    return OptionalArrayConstUncheckedIterator<T, C>{ this->_iter };
                }

            OSPF_CRTP_PERMISSION:
                inline static constexpr ValueType& OSPF_CRTP_FUNCTION(get)(const IterType iter) noexcept
                {
                    return **iter;
                }

                inline static constexpr const OptionalArrayUncheckedIterator OSPF_CRTP_FUNCTION(construct)(const IterType iter) noexcept
                {
                    return OptionalArrayUncheckedIterator{ iter };
                }
            };

            template<typename T, typename C>
            class OptionalArrayConstUncheckedReverseIterator
                : public RandomIteratorImpl<OriginType<T>, typename OriginType<C>::const_reverse_iterator, OptionalArrayConstUncheckedReverseIterator<T, C>>
            {
                template<
                    typename T,
                    usize len,
                    template<typename T, usize l> class C
                >
                friend class StaticOptionalArray;

                template<
                    typename T,
                    template<typename T> class C
                >
                friend class DynamicOptionalArray;

            public:
                using ValueType = OriginType<T>;
                using ContainerType = OriginType<C>;
                using IterType = typename ContainerType::const_reverse_iterator;

            private:
                using Base = RandomIteratorImpl<ValueType, IterType, OptionalArrayConstUncheckedReverseIterator<T, C>>;

            public:
                constexpr OptionalArrayConstUncheckedReverseIterator(const IterType iter)
                    : Base(iter) {}
                constexpr OptionalArrayConstUncheckedReverseIterator(const OptionalArrayConstUncheckedReverseIterator& ano) = default;
                constexpr OptionalArrayConstUncheckedReverseIterator(OptionalArrayConstUncheckedReverseIterator&& ano) noexcept = default;
                constexpr OptionalArrayConstUncheckedReverseIterator& operator=(const OptionalArrayConstUncheckedReverseIterator& rhs) = default;
                constexpr OptionalArrayConstUncheckedReverseIterator& operator=(OptionalArrayConstUncheckedReverseIterator&& rhs) noexcept = default;
                constexpr ~OptionalArrayConstUncheckedReverseIterator(void) noexcept = default;

            public:
                inline constexpr const bool has_value(void) const
                {
                    return this->_iter->has_value();
                }

            OSPF_CRTP_PERMISSION:
                inline static constexpr const ValueType& OSPF_CRTP_FUNCTION(get)(const IterType iter) noexcept
                {
                    return **iter;
                }

                inline static constexpr const OptionalArrayConstUncheckedReverseIterator OSPF_CRTP_FUNCTION(construct)(const IterType iter) noexcept
                {
                    return OptionalArrayConstUncheckedReverseIterator{ iter };
                }
            };

            template<typename T, typename C>
            class OptionalArrayUncheckedReverseIterator
                : public RandomIteratorImpl<OriginType<T>, typename OriginType<C>::reverse_iterator, OptionalArrayUncheckedReverseIterator<T, C>>
            {
                template<
                    typename T,
                    usize len,
                    template<typename T, usize l> class C
                >
                friend class StaticOptionalArray;

                template<
                    typename T,
                    template<typename T> class C
                >
                friend class DynamicOptionalArray;

            public:
                using ValueType = OriginType<T>;
                using ContainerType = OriginType<C>;
                using IterType = typename ContainerType::reverse_iterator;

            private:
                using Base = RandomIteratorImpl<ValueType, IterType, OptionalArrayUncheckedReverseIterator<T, C>>;

            public:
                constexpr OptionalArrayUncheckedReverseIterator(const IterType iter)
                    : Base(iter) {}
                constexpr OptionalArrayUncheckedReverseIterator(const OptionalArrayUncheckedReverseIterator& ano) = default;
                constexpr OptionalArrayUncheckedReverseIterator(OptionalArrayUncheckedReverseIterator&& ano) noexcept = default;
                constexpr OptionalArrayUncheckedReverseIterator& operator=(const OptionalArrayUncheckedReverseIterator& rhs) = default;
                constexpr OptionalArrayUncheckedReverseIterator& operator=(OptionalArrayUncheckedReverseIterator&& rhs) noexcept = default;
                constexpr ~OptionalArrayUncheckedReverseIterator(void) noexcept = default;

            public:
                inline constexpr const bool has_value(void) const
                {
                    return this->_iter->has_value();
                }

            OSPF_CRTP_PERMISSION:
                inline static constexpr ValueType& OSPF_CRTP_FUNCTION(get)(const IterType iter) noexcept
                {
                    return **iter;
                }

                inline static constexpr const OptionalArrayUncheckedReverseIterator OSPF_CRTP_FUNCTION(construct)(const IterType iter) noexcept
                {
                    return OptionalArrayUncheckedReverseIterator{ iter };
                }
            };

            template<typename T, typename C>
            struct OptionalArrayAccessPolicy;

            template<
                typename T,
                usize len,
                template<typename U, usize l> class C
            >
            struct OptionalArrayAccessPolicy<T, C<std::optional<OriginType<T>>, len>>
            {
            public:
                using ValueType = OriginType<T>;
                using OptType = std::optional<ValueType>;
                using ContainerType = C<OptType, len>;
                using IterType = OptionalArrayIterator<ValueType, ContainerType>;
                using ConstIterType = OptionalArrayConstIterator<ValueType, ContainerType>;
                using ReverseIterType = OptionalArrayReverseIterator<ValueType, ContainerType>;
                using ConstReverseIterType = OptionalArrayConstReverseIterator<ValueType, ContainerType>;
                using UncheckedIterType = OptionalArrayUncheckedIterator<ValueType, ContainerType>;
                using ConstUncheckedIterType = OptionalArrayConstUncheckedIterator<ValueType, ContainerType>;
                using UncheckedReverseIterType = OptionalArrayUncheckedReverseIterator<ValueType, ContainerType>;
                using ConstUncheckedReverseIterType = OptionalArrayConstUncheckedReverseIterator<ValueType, ContainerType>;

            public:
                inline static constexpr const usize size(const ContainerType& array) noexcept
                {
                    return len;
                }

                inline static constexpr OptType& get(ContainerType& array, const usize i)
                {
                    return array.at(i);
                }

                inline static constexpr const OptType& get(const ContainerType& array, const usize i)
                {
                    return array.at(i);
                }

                inline static constexpr OptType& get_uncheked(ContainerType& array, const usize i)
                {
                    return array[i];
                }

                inline static constexpr const OptType& get_uncheked(const ContainerType& array, const usize i)
                {
                    return array[i];
                }

            public:
                inline static constexpr const IterType begin(ContainerType& array) noexcept
                {
                    return IterType{ array.begin() };
                }

                inline static constexpr const ConstIterType cbegin(const ContainerType& array) noexcept
                {
                    return ConstIterType{ array.begin() };
                }

                inline static constexpr const UncheckedIterType begin_unchecked(ContainerType& array) noexcept
                {
                    return UncheckedIterType{ array.begin() };
                }

                inline static constexpr const ConstUncheckedIterType cbegin_unchecked(const ContainerType& array) noexcept
                {
                    return ConstUncheckedIterType{ array.begin() };
                }

            public:
                inline static constexpr const IterType end(ContainerType& array) noexcept
                {
                    return IterType{ array.end() };
                }

                inline static constexpr const ConstIterType cend(const ContainerType& array) noexcept
                {
                    return ConstIterType{ array.end() };
                }

                inline static constexpr const UncheckedIterType end_unchecked(ContainerType& array) noexcept
                {
                    return UncheckedIterType{ array.end() };
                }

                inline static constexpr const ConstUncheckedIterType cend_unchecked(const ContainerType& array) noexcept
                {
                    return ConstUncheckedIterType{ array.end() };
                }

            public:
                inline static constexpr const ReverseIterType rbegin(ContainerType& array) noexcept
                {
                    return ReverseIterType{ array.rbegin() };
                }

                inline static constexpr const ConstReverseIterType crbegin(const ContainerType& array) noexcept
                {
                    return ConstReverseIterType{ array.rbegin() };
                }

                inline static constexpr const UncheckedReverseIterType rbegin_unchecked(ContainerType& array) noexcept
                {
                    return UncheckedReverseIterType{ array.rbegin() };
                }

                inline static constexpr const ConstUncheckedReverseIterType crbegin_unchecked(const ContainerType& array) noexcept
                {
                    return ConstUncheckedReverseIterType{ array.rbegin() };
                }

            public:
                inline static constexpr const ReverseIterType rend(ContainerType& array) noexcept
                {
                    return ReverseIterType{ array.rend() };
                }

                inline static constexpr const ConstReverseIterType crend(const ContainerType& array) noexcept
                {
                    return ConstReverseIterType{ array.rend() };
                }

                inline static constexpr const UncheckedReverseIterType rend_unchecked(ContainerType& array) noexcept
                {
                    return UncheckedReverseIterType{ array.rend() };
                }

                inline static constexpr const ConstUncheckedReverseIterType crend_unchecked(const ContainerType& array) noexcept
                {
                    return ConstUncheckedReverseIterType{ array.rend() };
                }
            };

            template<
                typename T,
                template<typename U> class C
            >
            struct OptionalArrayAccessPolicy<T, C<std::optional<OriginType<T>>>>
            {
            public:
                using ValueType = OriginType<T>;
                using OptType = std::optional<ValueType>;
                using ContainerType = C<OptType>;
                using IterType = OptionalArrayIterator<ValueType, ContainerType>;
                using ConstIterType = OptionalArrayConstIterator<ValueType, ContainerType>;
                using ReverseIterType = OptionalArrayReverseIterator<ValueType, ContainerType>;
                using ConstReverseIterType = OptionalArrayConstReverseIterator<ValueType, ContainerType>;
                using UncheckedIterType = OptionalArrayUncheckedIterator<ValueType, ContainerType>;
                using ConstUncheckedIterType = OptionalArrayConstUncheckedIterator<ValueType, ContainerType>;
                using UncheckedReverseIterType = OptionalArrayUncheckedReverseIterator<ValueType, ContainerType>;
                using ConstUncheckedReverseIterType = OptionalArrayConstUncheckedReverseIterator<ValueType, ContainerType>;

            protected:
                OptionalArrayAccessPolicy(void) = default;
            public:
                OptionalArrayAccessPolicy(const OptionalArrayAccessPolicy& ano) = default;
                OptionalArrayAccessPolicy(OptionalArrayAccessPolicy&& ano) noexcept = default;
                OptionalArrayAccessPolicy& operator=(const OptionalArrayAccessPolicy& rhs) = default;
                OptionalArrayAccessPolicy& operator=(OptionalArrayAccessPolicy&& rhs) noexcept = default;
                ~OptionalArrayAccessPolicy(void) = default;

            public:
                inline static constexpr const usize size(const ContainerType& array) noexcept
                {
                    return array.size();
                }

            public:
                inline static constexpr OptType& get(ContainerType& array, const usize i)
                {
                    return array.at(i);
                }

                inline static constexpr const OptType& get(const ContainerType& array, const usize i)
                {
                    return array.at(i);
                }

                inline static constexpr OptType& get_uncheked(ContainerType& array, const usize i)
                {
                    return array[i];
                }

                inline static constexpr const OptType& get_uncheked(const ContainerType& array, const usize i)
                {
                    return array[i];
                }

            public:
                inline static constexpr const IterType begin(ContainerType& array) noexcept
                {
                    return IterType{ array.begin() };
                }

                inline static constexpr const ConstIterType cbegin(const ContainerType& array) noexcept
                {
                    return ConstIterType{ array.begin() };
                }

                inline static constexpr const UncheckedIterType begin_unchecked(ContainerType& array) noexcept
                {
                    return UncheckedIterType{ array.begin() };
                }

                inline static constexpr const ConstUncheckedIterType cbegin_unchecked(const ContainerType& array) noexcept
                {
                    return ConstUncheckedIterType{ array.begin() };
                }

            public:
                inline static constexpr const IterType end(ContainerType& array) noexcept
                {
                    return IterType{ array.end() };
                }

                inline static constexpr const ConstIterType cend(const ContainerType& array) noexcept
                {
                    return ConstIterType{ array.end() };
                }

                inline static constexpr const UncheckedIterType end_unchecked(ContainerType& array) noexcept
                {
                    return UncheckedIterType{ array.end() };
                }

                inline static constexpr const ConstUncheckedIterType cend_unchecked(const ContainerType& array) noexcept
                {
                    return ConstUncheckedIterType{ array.end() };
                }

            public:
                inline static constexpr const ReverseIterType rbegin(ContainerType& array) noexcept
                {
                    return ReverseIterType{ array.rbegin() };
                }

                inline static constexpr const ConstReverseIterType crbegin(const ContainerType& array) noexcept
                {
                    return ConstReverseIterType{ array.rbegin() };
                }

                inline static constexpr const UncheckedReverseIterType rbegin_unchecked(ContainerType& array) noexcept
                {
                    return UncheckedReverseIterType{ array.rbegin() };
                }

                inline static constexpr const ConstUncheckedReverseIterType crbegin_unchecked(const ContainerType& array) noexcept
                {
                    return ConstUncheckedReverseIterType{ array.rbegin() };
                }

            public:
                inline static constexpr const ReverseIterType rend(ContainerType& array) noexcept
                {
                    return ReverseIterType{ array.rend() };
                }

                inline static constexpr const ConstReverseIterType crend(const ContainerType& array) noexcept
                {
                    return ConstReverseIterType{ array.rend() };
                }

                inline static constexpr const UncheckedReverseIterType rend_unchecked(ContainerType& array) noexcept
                {
                    return UncheckedReverseIterType{ array.rend() };
                }

                inline static constexpr const ConstUncheckedReverseIterType crend_unchecked(const ContainerType& array) noexcept
                {
                    return ConstUncheckedReverseIterType{ array.rend() };
                }
            };

            template<typename T, typename C, typename Self>
            class OptionalArrayImpl
            {
                OSPF_CRTP_IMPL

            public:
                using ValueType = OriginType<T>;
                using ContainerType = OriginType<C>;
                using AccessPolicyType = OptionalArrayAccessPolicy<ValueType, ContainerType>;
                using OptType = typename AccessPolicyType::OptType;
                using IterType = typename AccessPolicyType::IterType;
                using ConstIterType = typename AccessPolicyType::ConstIterType;
                using ReverseIterType = typename AccessPolicyType::ReverseIterType;
                using ConstReverseIterType = typename AccessPolicyType::ConstReverseIterType;
                using UncheckedIterType = typename AccessPolicyType::UncheckedIterType;
                using ConstUncheckedIterType = typename AccessPolicyType::ConstUncheckedIterType;
                using UncheckedReverseIterType = typename AccessPolicyType::UncheckedReverseIterType;
                using ConstUncheckedReverseIterType = typename AccessPolicyType::ConstUncheckedReverseIterType;

            protected:
                constexpr OptionalArrayImpl(void) = default;
            public:
                constexpr OptionalArrayImpl(const OptionalArrayImpl& ano) = default;
                constexpr OptionalArrayImpl(OptionalArrayImpl&& ano) noexcept = default;
                constexpr OptionalArrayImpl& operator=(const OptionalArrayImpl& rhs) = default;
                constexpr OptionalArrayImpl& operator=(OptionalArrayImpl&& rhs) noexcept = default;
                constexpr ~OptionalArrayImpl(void) noexcept = default;

            public:
                inline constexpr const bool has_value(const usize i) const
                {
                    return at(i).has_value();
                }

                inline void set(const usize i, CLRefType<ValueType> value)
                {
                    AccessPolicyType::get(container())[i] = OptType{ value };
                }

                template<typename = void>
                    requires ReferenceFaster<ValueType> && std::movable<ValueType>
                inline void set(const usize i, RRefType<ValueType> value)
                {
                    AccessPolicyType::get(container())[i] = OptType{ move<ValueType>(value) };
                }

            public:
                inline constexpr OptType& at(const usize i)
                {
                    return AccessPolicyType::get(container())[i];
                }

                inline constexpr const OptType& at(const usize i) const
                {
                    return AccessPolicyType::get(const_container())[i];
                }

                inline constexpr OptType& operator[](const usize i)
                {
                    return AccessPolicyType::get_unchecked(container())[i];
                }

                inline constexpr const OptType& operator[](const usize i)
                {
                    return AccessPolicyType::get_unchecked(const_container())[i];
                }

            public:
                inline constexpr OptType& front(void)
                {
                    return at(0_uz);
                }

                inline constexpr const OptType& front(void) const
                {
                    return at(0_uz);
                }

                inline constexpr OptType& back(void)
                {
                    return at(size() - 1_uz);
                }

                inline constexpr const OptType& back(void) const
                {
                    return at(size() - 1_uz);
                }

            public:
                inline constexpr const IterType begin(void) noexcept
                {
                    return AccessPolicyType::begin(container());
                }

                inline constexpr const ConstIterType begin(void) const noexcept
                {
                    return AccessPolicyType::cbegin(const_container());
                }

                inline constexpr const ConstIterType cbegin(void) const noexcept
                {
                    return AccessPolicyType::cbegin(const_container());
                }

                inline constexpr const UncheckedIterType begin_unchecked(void) noexcept
                {
                    return AccessPolicyType::begin_unchecked(container());
                }

                inline constexpr const ConstUncheckedIterType begin_unchecked(void) const noexcept
                {
                    return AccessPolicyType::cbegin_unchecked(const_container());
                }

                inline constexpr const ConstUncheckedIterType cbegin_unchecked(void) const noexcept
                {
                    return AccessPolicyType::cbegin_unchecked(const_container());
                }

            public:
                inline constexpr const IterType end(void) noexcept
                {
                    return AccessPolicyType::end(container());
                }

                inline constexpr const ConstIterType end(void) const noexcept
                {
                    return AccessPolicyType::cend(const_container());
                }

                inline constexpr const ConstIterType cend(void) const noexcept
                {
                    return AccessPolicyType::cend(const_container());
                }

                inline constexpr const UncheckedIterType end_unchecked(void) noexcept
                {
                    return AccessPolicyType::end_unchecked(container());
                }

                inline constexpr const ConstUncheckedIterType end_unchecked(void) const noexcept
                {
                    return AccessPolicyType::cend_unchecked(const_container());
                }

                inline constexpr const ConstUncheckedIterType cend_unchecked(void) const noexcept
                {
                    return AccessPolicyType::cend_unchecked(const_container());
                }

            public:
                inline constexpr const ReverseIterType rbegin(void) noexcept
                {
                    return AccessPolicyType::rbegin(container());
                }

                inline constexpr const ConstReverseIterType rbegin(void) const noexcept
                {
                    return AccessPolicyType::crbegin(const_container());
                }

                inline constexpr const ConstReverseIterType crbegin(void) const noexcept
                {
                    return AccessPolicyType::crbegin(const_container());
                }

                inline constexpr const UncheckedReverseIterType rbegin_unchecked(void) noexcept
                {
                    return AccessPolicyType::rbegin_unchecked(container());
                }

                inline constexpr const ConstUncheckedReverseIterType rbegin_unchecked(void) const noexcept
                {
                    return AccessPolicyType::crbegin_unchecked(const_container());
                }

                inline constexpr const ConstUncheckedReverseIterType crbegin_unchecked(void) const noexcept
                {
                    return AccessPolicyType::crbegin_unchecked(const_container());
                }

            public:
                inline constexpr const ReverseIterType rend(void) noexcept
                {
                    return AccessPolicyType::rend(container());
                }

                inline constexpr const ConstReverseIterType rend(void) const noexcept
                {
                    return AccessPolicyType::crend(const_container());
                }

                inline constexpr const ConstReverseIterType crend(void) const noexcept
                {
                    return AccessPolicyType::crend(const_container());
                }

                inline constexpr const UncheckedReverseIterType rend_unchecked(void) noexcept
                {
                    return AccessPolicyType::rend_unchecked(container());
                }

                inline constexpr const ConstUncheckedReverseIterType rend_unchecked(void) const noexcept
                {
                    return AccessPolicyType::crend_unchecked(const_container());
                }

                inline constexpr const ConstUncheckedReverseIterType crend_unchecked(void) const noexcept
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
                inline void swap(OptionalArrayImpl<T, C, Self>& ano) noexcept
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
            };

            template<typename T, typename C, typename Self>
            class OptionalArrayUncheckedAccessorImpl
            {
                using Impl = OptionalArrayImpl<T, C, Self>;

            public:
                using ValueType = typename Impl::ValueType;
                using ContainerType = typename Impl::ContainerType;
                using typename Impl::OptType;
                using typename Impl::IterType;
                using typename Impl::ConstIterType;
                using typename Impl::ReverseIterType;
                using typename Impl::ConstReverseIterType;
                using typename Impl::UncheckedIterType;
                using typename Impl::ConstUncheckedIterType;
                using typename Impl::UncheckedReverseIterType;
                using typename Impl::ConstUncheckedReverseIterType;

            public:
                constexpr OptionalArrayUncheckedAccessorImpl(const Impl& impl)
                    : _impl(impl) {}
                constexpr OptionalArrayUncheckedAccessorImpl(const OptionalArrayUncheckedAccessorImpl& ano) = default;
                constexpr OptionalArrayUncheckedAccessorImpl(OptionalArrayUncheckedAccessorImpl&& ano) noexcept = default;
                constexpr OptionalArrayUncheckedAccessorImpl& operator=(const OptionalArrayUncheckedAccessorImpl& rhs) = default;
                constexpr OptionalArrayUncheckedAccessorImpl& operator=(OptionalArrayUncheckedAccessorImpl&& rhs) noexcept = default;
                constexpr ~OptionalArrayUncheckedAccessorImpl(void) noexcept = default;

            public:
                inline constexpr const bool has_value(const usize i) const
                {
                    return _impl.has_value(i);
                }

            public:
                inline constexpr OptType& at(const usize i)
                {
                    return *_impl.at(i);
                }

                inline constexpr const OptType& at(const usize i) const
                {
                    return *_impl.at(i);
                }

                inline constexpr OptType& operator[](const usize i)
                {
                    return *_impl[i];
                }

                inline constexpr const OptType& operator[](const usize i)
                {
                    return *_impl[i];
                }

            public:
                inline constexpr OptType& front(void)
                {
                    return *_impl.front();
                }

                inline constexpr const OptType& front(void) const
                {
                    return *_impl.front();
                }

                inline constexpr OptType& back(void)
                {
                    return *_impl.back();
                }

                inline constexpr const OptType& back(void) const
                {
                    return *_impl.back();
                }

            public:
                inline constexpr const UncheckedIterType begin(void) noexcept
                {
                    return _impl.begin_unchecked();
                }

                inline constexpr const ConstUncheckedIterType begin(void) const noexcept
                {
                    return _impl.begin_unchecked();
                }

                inline constexpr const ConstUncheckedIterType cbegin(void) const noexcept
                {
                    return _impl.cbegin_unchecked();
                }

            public:
                inline constexpr const UncheckedIterType end(void) noexcept
                {
                    return _impl.end_unchecked();
                }

                inline constexpr const ConstUncheckedIterType end(void) const noexcept
                {
                    return _impl.end_unchecked();
                }

                inline constexpr const ConstUncheckedIterType cend(void) const noexcept
                {
                    return _impl.cend_unchecked();
                }

            public:
                inline constexpr const UncheckedReverseIterType rbegin(void) noexcept
                {
                    return _impl.rbegin_unchecked();
                }

                inline constexpr const ConstUncheckedReverseIterType rbegin(void) const noexcept
                {
                    return _impl.rbegin_unchecked();
                }

                inline constexpr const ConstUncheckedReverseIterType crbegin(void) const noexcept
                {
                    return _impl.crbegin_unchecked();
                }

            public:
                inline constexpr const UncheckedReverseIterType rend(void) noexcept
                {
                    return _impl.rend_unchecked();
                }

                inline constexpr const ConstUncheckedReverseIterType rend(void) const noexcept
                {
                    return _impl.rend_unchecked();
                }

                inline constexpr const ConstUncheckedReverseIterType crend(void) const noexcept
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
                template<typename T, usize l> class C
            >
            class StaticOptionalArray
                : public OptionalArrayImpl<T, C<std::optional<OriginType<T>>, len>, StaticOptionalArray<T, len, C>>
            {
                using Impl = OptionalArrayImpl<T, C<std::optional<OriginType<T>>, len>, StaticOptionalArray<T, len, C>>;
                using UncheckedAccessorImpl = OptionalArrayUncheckedAccessorImpl<T, C<std::optional<T>, len>, StaticOptionalArray<T, len, C>>;

            public:
                using typename Impl::ValueType;
                using typename Impl::OptType;
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
                StaticOptionalArray(void) = default;

                StaticOptionalArray(ContainerType container)
                    : _container(move<ContainerType>(container)) {}

                StaticOptionalArray(std::initializer_list<ValueType> eles)
                {
                    for (auto i{ 0_uz }, j{ (std::min)(len, eles.size) }; i != j; ++i)
                    {
                        _container[i] = OptType{ move<ValueType>(eles[i]) };
                    }
                }

                StaticOptionalArray(std::initializer_list<OptType> eles)
                    : _container(std::move(eles)) {}

            public:
                constexpr StaticOptionalArray(const StaticOptionalArray& ano) = default;
                constexpr StaticOptionalArray(StaticOptionalArray&& ano) noexcept = default;
                constexpr StaticOptionalArray& operator=(const StaticOptionalArray& rhs) = default;
                constexpr StaticOptionalArray& operator=(StaticOptionalArray&& rhs) noexcept = default;
                constexpr ~StaticOptionalArray(void) = default;

            public:
                inline constexpr UncheckedAccessorImpl unchecked(void) const noexcept
                {
                    return UncheckedAccessorImpl{ dynamic_cast<const Impl&>(*this) };
                }

                template<typename = void>
                    requires requires (ContainerType& container) { { container.data() } -> DecaySameAs<PtrType<OptType>>; }
                inline constexpr const PtrType<OptType> data(void) noexcept
                {
                    return _container.data();
                }

                template<typename = void>
                    requires requires (const ContainerType& container) { { container.data() } -> DecaySameAs<CPtrType<OptType>>; }
                inline constexpr const CPtrType<OptType> data(void) const noexcept
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

                inline constexpr void fill(const std::nullopt_t _ = std::nullopt) noexcept
                {
                    _container.fill(OptType{ std::nullopt });
                }

                inline constexpr void fill(CLRefType<ValueType> value) noexcept
                {
                    _container.fill(OptType{ value });
                }

                template<typename = void>
                    requires ReferenceFaster<ValueType> && std::movable<ValueType>
                inline void fill(RRefType<ValueType> value) noexcept
                {
                    _container.fill(OptType{ move<ValueType>(value) });
                }

            public:
                inline constexpr const bool operator==(const StaticOptionalArray& rhs) const noexcept
                {
                    return _container == rhs._container;
                }

                inline constexpr const bool operator!=(const StaticOptionalArray& rhs) const noexcept
                {
                    return _container != rhs._container;
                }

            public:
                inline constexpr const bool operator<(const StaticOptionalArray& rhs) const noexcept
                {
                    return _container < rhs._container;
                }

                inline constexpr const bool operator<=(const StaticOptionalArray& rhs) const noexcept
                {
                    return _container <= rhs._container;
                }

                inline constexpr const bool operator>(const StaticOptionalArray& rhs) const noexcept
                {
                    return _container > rhs._container;
                }

                inline constexpr const bool operator>=(const StaticOptionalArray& rhs) const noexcept
                {
                    return _container >= rhs._container;
                }

            public:
                inline constexpr decltype(auto) operator<=>(const StaticOptionalArray& rhs) const noexcept
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
                template<typename T> class C
            >
            class DynamicOptionalArray
                : public OptionalArrayImpl<T, C<std::optional<OriginType<T>>>, DynamicOptionalArray<T, C>>
            {
                using Impl = OptionalArrayImpl<T, C<std::optional<OriginType<T>>>, DynamicOptionalArray<T, C>>;
                using UncheckedAccessorImpl = OptionalArrayUncheckedAccessorImpl<T, C<std::optional<OriginType<T>>>, DynamicOptionalArray<T, C>>;

            public:
                using typename Impl::ValueType;
                using typename Impl::OptType;
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
                constexpr DynamicOptionalArray(void) = default;

                constexpr explicit DynamicOptionalArray(const usize length)
                    : _container(length) {}

                constexpr DynamicOptionalArray(const usize length, CLRefType<ValueType> value)
                    : _container(length, OptType{ value }) {}

                template<typename = void>
                    requires ReferenceFaster<ValueType> && std::movable<ValueType>
                DynamicOptionalArray(const usize length, RRefType<ValueType> value)
                    : _container(length, OptType{ move<ValueType>(value) }) {}

                template<std::input_iterator It>
                constexpr DynamicOptionalArray(const It first, const It last)
                    : _container(first, last) {}

                constexpr DynamicOptionalArray(std::initializer_list<ValueType> eles)
                    : _container(eles.size())
                {
                    for (auto i{ 0_uz }; i != eles.size(); ++i)
                    {
                        _container[i] = move<ValueType>(eles[i]);
                    }
                }

                constexpr DynamicOptionalArray(std::initializer_list<OptType> eles)
                    : _container(std::move(eles)) {}

            public:
                constexpr DynamicOptionalArray(const DynamicOptionalArray& ano) = default;
                constexpr DynamicOptionalArray(DynamicOptionalArray&& ano) noexcept = default;
                constexpr DynamicOptionalArray& operator=(const DynamicOptionalArray& rhs) = default;
                constexpr DynamicOptionalArray& operator=(DynamicOptionalArray&& rhs) noexcept = default;
                constexpr ~DynamicOptionalArray(void) = default;

            public:
                inline constexpr void assign(const usize length, const std::nullopt_t _ = std::nullopt)
                {
                    _container.assign(length, OptType{ std::nullopt });
                }

                inline constexpr void assign(const usize length, CLRefType<ValueType> value)
                {
                    _container.assign(length, OptType{ value });
                }

                inline constexpr void assign(const usize length, RRefType<ValueType> value)
                {
                    _container.assign(length, OptType{ move<ValueType>(value) });
                }

                template<std::input_iterator It>
                inline constexpr void assign(const It first, const It last)
                {
                    _container.assign(first, last);
                }

                inline constexpr void assign(std::initializer_list<ValueType> eles)
                {
                    _container.assign(eles.size());
                    for (auto i{ 0_uz }; i != eles.size(); ++i)
                    {
                        _container[i] = move<ValueType>(eles[i]);
                    }
                }

                inline constexpr void assign(std::initializer_list<OptType> eles)
                {
                    _container.assign(std::move(eles));
                }

            public:
                inline constexpr UncheckedAccessorImpl unchecked(void) const noexcept
                {
                    return UncheckedAccessorImpl{ dynamic_cast<const Impl&>(*this) };
                }

                template<typename = void>
                    requires requires (ContainerType& container) { { container.data() } -> DecaySameAs<PtrType<OptType>>; }
                inline constexpr const PtrType<OptType> data(void) noexcept
                {
                    return _container.data();
                }

                template<typename = void>
                    requires requires (const ContainerType& container) { { container.data() } -> DecaySameAs<CPtrType<OptType>>; }
                inline constexpr const CPtrType<OptType> data(void) const noexcept
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

                inline constexpr const IterType insert(const ConstIterType pos, CLRefType<ValueType> value)
                {
                    return IterType{ _container.insert(pos._iter, value) };
                }

                template<typename = void>
                    requires ReferenceFaster<ValueType> && std::movable<ValueType>
                inline constexpr const IterType insert(const ConstIterType pos, RRefType<ValueType> value)
                {
                    return IterType{ _container.insert(pos._iter, move<ValueType>(value)) };
                }

                inline constexpr const UncheckedIterType insert(const ConstUncheckedIterType pos, CLRefType<ValueType> value)
                {
                    return UncheckedIterType{ _container.insert(pos._iter, value) };
                }

                template<typename = void>
                    requires ReferenceFaster<ValueType>&& std::movable<ValueType>
                inline constexpr const UncheckedIterType insert(const ConstUncheckedIterType pos, RRefType<ValueType> value)
                {
                    return UncheckedIterType{ _container.insert(pos._iter, move<ValueType>(value)) };
                }

                template<std::input_iterator It>
                inline constexpr const IterType insert(const ConstIterType pos, const It first, const It last)
                {
                    return IterType{ _container.insert(pos._iter, first, last) };
                }

                template<std::input_iterator It>
                inline constexpr const UncheckedIterType insert(const ConstUncheckedIterType pos, const It first, const It last)
                {
                    return UncheckedIterType{ _container.insert(pos._iter, first, last) };
                }

                inline constexpr const IterType insert(const ConstIterType pos, std::initializer_list<ValueType> eles)
                {
                    auto it = pos._iter;
                    for (auto i{ 0_uz }; i != eles.size(); ++i)
                    {
                        it = _container.insert(it, move<ValueType>(eles[i]));
                    }
                    return IterType{ it };
                }

                inline constexpr const UncheckedIterType insert(const ConstUncheckedIterType pos, std::initializer_list<ValueType> eles)
                {
                    auto it = pos._iter;
                    for (auto i{ 0_uz }; i != eles.size(); ++i)
                    {
                        it = _container.insert(it, move<ValueType>(eles[i]));
                    }
                    return UncheckedIterType{ it };
                }

                inline constexpr const IterType insert(const ConstIterType pos, std::initializer_list<OptType> eles)
                {
                    return IterType{ _container.insert(pos, std::move(eles)) };
                }

                inline constexpr const UncheckedIterType insert(const ConstUncheckedIterType pos, std::initializer_list<OptType> eles)
                {
                    return UncheckedIterType{ _container.insert(pos, std::move(eles)) };
                }

                template<typename... Args>
                    requires std::constructible_from<ValueType, Args...>
                inline const IterType emplace(const ConstIterType pos, Args&&... args)
                {
                    return IterType{ _container.emplace(pos._iter, std::forward<Args>(args)...) };
                }

                template<typename... Args>
                    requires std::constructible_from<ValueType, Args...>
                inline const UncheckedIterType emplace(const ConstUncheckedIterType pos, Args&&... args)
                {
                    return UncheckedIterType{ _container.emplace(pos._iter, std::forward<Args>(args)...) };
                }

                inline const IterType erase(const ConstIterType pos)
                {
                    return IterType{ _container.erase(pos) };
                }

                inline const UncheckedIterType erase(const ConstUncheckedIterType pos)
                {
                    return UncheckedIterType{ _container.erase(pos) };
                }

                inline const IterType erase(const ConstIterType first, const ConstIterType last)
                {
                    return IterType{ _container.erase(first, last) };
                }

                inline const UncheckedIterType erase(const ConstUncheckedIterType first, const ConstUncheckedIterType last)
                {
                    return UncheckedIterType{ _container.erase(first, last) };
                }

                inline void push_back(const std::nullopt_t _)
                {
                    _container.push_back(std::nullopt);
                }

                inline void push_back(CLRefType<ValueType> value)
                {
                    _container.push_back(OptType{ value });
                }

                template<typename = void>
                    requires ReferenceFaster<ValueType> && std::movable<ValueType>
                inline void push_back(RRefType<ValueType> value)
                {
                    _container.push_back(OptType{ move<ValueType>(value) });
                }

                template<typename... Args>
                    requires std::constructible_from<ValueType, Args...>
                inline ValueType& emplace_back(Args&&... args)
                {
                    return *_container.emplace_back(OptType{ ValueType{ std::forward<Args>(args)... } });
                }

                inline RetType<OptType> pop_back(void)
                {
                    auto back = move<OptType>(this->back());
                    _container.pop_back();
                    return back;
                }

                inline void push_front(const std::nullopt_t _)
                {
                    _container.insert(_container.begin(), std::nullopt);
                }

                template<typename = void>
                    requires requires (ContainerType& container) { container.push_front(std::nullopt); }
                inline void push_front(const std::nullopt_t _)
                {
                    _container.push_front(std::nullopt);
                }

                inline void push_front(CLRefType<ValueType> value)
                {
                    _container.insert(_container.begin(), OptType{ value });
                }

                template<typename = void>
                    requires requires (ContainerType& container) { container.push_front(std::declval<OptType>()); }
                inline void push_front(CLRefType<ValueType> value)
                {
                    _container.push_front(OptType{ value });
                }

                template<typename = void>
                    requires ReferenceFaster<ValueType>&& std::movable<ValueType>
                inline void push_front(RRefType<ValueType> value)
                {
                    _container.insert(_container.begin(), OptType{ move<ValueType>(value) });
                }

                template<typename = void>
                    requires ReferenceFaster<ValueType> && std::movable<ValueType> 
                        && requires (ContainerType& container) { container.push_front(std::declval<OptType>()); }
                inline void push_front(RRefType<ValueType> value)
                {
                    _container.push_front(OptType{ move<ValueType>(value) });
                }

                template<typename... Args>
                    requires std::constructible_from<ValueType, Args...>
                inline ValueType& emplace_front(Args&&... args)
                {
                    return **_container.insert(_container.begin(), OptType{ ValueType{ std::forward<Args>(args)... } });
                }

                template<typename... Args>
                    requires std::constructible_from<ValueType, Args...>
                        && requires (ContainerType& container) { container.emplace_front(std::declval<OptType>()); }
                inline ValueType& emplace_front(Args&&... args)
                {
                    return *_container.emplace_front(OptType{ ValueType{ std::forward<Args>(args)... } });
                }

                inline RetType<OptType> pop_front(void)
                {
                    auto value = move<OptType>(this->front());
                    _container.erase(_container.begin());
                    return value;
                }

                template<typename = void>
                    requires requires (ContainerType& container) { container.pop_front(); }
                inline RetType<OptType> pop_front(void)
                {
                    auto value = move<OptType>(this->front());
                    _container.pop_front();
                    return value;
                }
                
                inline void resize(const usize length)
                {
                    resize(length, std::nullopt);
                }

                inline void resize(const usize length, CLRefType<ValueType> value)
                {
                    resize(length, OptType{ value });
                }

                template<typename = void>
                    requires ReferenceFaster<ValueType> && std::movable<ValueType>
                inline void resize(const usize length, RRefType<ValueType> value)
                {
                    resize(length, OptType{ move<ValueType>(value) });
                }

                inline void resize(const usize length, const OptType& value)
                {
                    resize(length, value);
                }

            public:
                inline constexpr const bool operator==(const DynamicOptionalArray& rhs) const noexcept
                {
                    return _container == rhs._container;
                }

                inline constexpr const bool operator!=(const DynamicOptionalArray& rhs) const noexcept
                {
                    return _container != rhs._container;
                }

            public:
                inline constexpr const bool operator<(const DynamicOptionalArray& rhs) const noexcept
                {
                    return _container < rhs._container;
                }

                inline constexpr const bool operator<=(const DynamicOptionalArray& rhs) const noexcept
                {
                    return _container <= rhs._container;
                }

                inline constexpr const bool operator>(const DynamicOptionalArray& rhs) const noexcept
                {
                    return _container > rhs._container;
                }

                inline constexpr const bool operator>=(const DynamicOptionalArray& rhs) const noexcept
                {
                    return _container >= rhs._container;
                }

            public:
                inline constexpr decltype(auto) operator<=>(const DynamicOptionalArray& rhs) const noexcept
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

        template<
            typename T, 
            usize len,
            template<typename T, usize l> class C = std::array
        >
        using OptArray = optional_array::StaticOptionalArray<OriginType<T>, len, C>;

        template<
            typename T,
            template<typename T> class C = std::vector
        >
        using DynOptArray = optional_array::DynamicOptionalArray<OriginType<T>, C>;
    };
};

namespace std
{
    template<typename T, typename C, typename Self>
    inline void swap(ospf::data_structure::optional_array::OptionalArrayImpl<T, C, Self>& lhs, ospf::data_structure::optional_array::OptionalArrayImpl<T, C, Self>& rhs) noexcept
    {
        lhs.swap(rhs);
    }
};
