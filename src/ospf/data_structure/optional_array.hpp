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
                usize l,
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
                    usize l,
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
                inline constexpr const bool has_value(void) const noexcept
                {
                    return this->_iter->has_value();
                }

            OSPF_CRTP_PERMISSION:
                inline static constexpr const ValueType& OSPF_CRTP_FUNCTION(get)(const IterType iter) noexcept
                {
                    return *iter;
                }

                inline static constexpr RetType<OptionalArrayConstIterator> OSPF_CRTP_FUNCTION(construct)(const IterType iter) noexcept
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
                    usize l,
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
                inline constexpr const bool has_value(void) const noexcept
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

                inline static constexpr RetType<OptionalArrayIterator> OSPF_CRTP_FUNCTION(construct)(const IterType iter) noexcept
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
                    usize l,
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
                inline constexpr const bool has_value(void) const noexcept
                {
                    return this->_iter->has_value();
                }

            OSPF_CRTP_PERMISSION:
                inline static constexpr const ValueType& OSPF_CRTP_FUNCTION(get)(const IterType iter) noexcept
                {
                    return *iter;
                }

                inline static constexpr RetType<OptionalArrayConstReverseIterator> OSPF_CRTP_FUNCTION(construct)(const IterType iter) noexcept
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
                    usize l,
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
                inline constexpr const bool has_value(void) const noexcept
                {
                    return this->_iter->has_value();
                }

            OSPF_CRTP_PERMISSION:
                inline static constexpr ValueType& OSPF_CRTP_FUNCTION(get)(const IterType iter) noexcept
                {
                    return *iter;
                }

                inline static constexpr RetType<OptionalArrayConstReverseIterator> OSPF_CRTP_FUNCTION(construct)(const IterType iter) noexcept
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
                    usize l,
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
                inline constexpr const bool has_value(void) const noexcept
                {
                    return this->_iter->has_value();
                }

            OSPF_CRTP_PERMISSION:
                inline static constexpr const ValueType& OSPF_CRTP_FUNCTION(get)(const IterType iter) noexcept
                {
                    return **iter;
                }

                inline static constexpr RetType<OptionalArrayConstUncheckedIterator> OSPF_CRTP_FUNCTION(construct)(const IterType iter) noexcept
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
                    usize l,
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
                inline constexpr const bool has_value(void) const noexcept
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

                inline static constexpr RetType<OptionalArrayUncheckedIterator> OSPF_CRTP_FUNCTION(construct)(const IterType iter) noexcept
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
                    usize l,
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
                inline constexpr const bool has_value(void) const noexcept
                {
                    return this->_iter->has_value();
                }

            OSPF_CRTP_PERMISSION:
                inline static constexpr const ValueType& OSPF_CRTP_FUNCTION(get)(const IterType iter) noexcept
                {
                    return **iter;
                }

                inline static constexpr RetType<OptionalArrayConstUncheckedReverseIterator> OSPF_CRTP_FUNCTION(construct)(const IterType iter) noexcept
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
                    usize l,
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
                inline constexpr const bool has_value(void) const noexcept
                {
                    return this->_iter->has_value();
                }

            OSPF_CRTP_PERMISSION:
                inline static constexpr ValueType& OSPF_CRTP_FUNCTION(get)(const IterType iter) noexcept
                {
                    return **iter;
                }

                inline static constexpr RetType<OptionalArrayUncheckedReverseIterator> OSPF_CRTP_FUNCTION(construct)(const IterType iter) noexcept
                {
                    return OptionalArrayUncheckedReverseIterator{ iter };
                }
            };

            template<typename T, typename C>
            class OptionalArrayAccessPolicy;

            template<
                typename T,
                template<typename U> class C
            >
            class OptionalArrayAccessPolicy<T, C<T>>
            {
            public:
                using ValueType = OriginType<T>;
                using ContainerType = C<T>;
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
                inline static constexpr std::optional<ValueType>& get(ContainerType& array, const usize i)
                {
                    return array.at(i);
                }

                inline static constexpr const std::optional<ValueType>& get(const ContainerType& array, const usize i)
                {
                    return array.at(i);
                }

                inline static constexpr std::optional<ValueType>& get_uncheked(ContainerType& array, const usize i)
                {
                    return array[i];
                }

                inline static constexpr const std::optional<ValueType>& get_uncheked(const ContainerType& array, const usize i)
                {
                    return array[i];
                }

            public:
                inline constexpr decltype(auto) begin(ContainerType& array) noexcept
                {
                    return IterType{ array.begin() };
                }

                inline constexpr decltype(auto) cbegin(const ContainerType& array) noexcept
                {
                    return ConstIterType{ array.cbegin() };
                }

                inline constexpr decltype(auto) begin_unchecked(ContainerType& array) noexcept
                {
                    return UncheckedIterType{ array.begin() };
                }

                inline constexpr decltype(auto) cbegin_unchecked(const ContainerType& array) noexcept
                {
                    return ConstUncheckedIterType{ array.cbegin() };
                }

            public:
                inline constexpr decltype(auto) end(ContainerType& array) noexcept
                {
                    return IterType{ array.end() };
                }

                inline constexpr decltype(auto) cend(const ContainerType& array) noexcept
                {
                    return ConstIterType{ array.cend() };
                }

                inline constexpr decltype(auto) end_unchecked(ContainerType& array) noexcept
                {
                    return UncheckedIterType{ array.end() };
                }

                inline constexpr decltype(auto) cend_unchecked(const ContainerType& array) noexcept
                {
                    return ConstUncheckedIterType{ array.cend() };
                }

            public:
                inline constexpr decltype(auto) rbegin(ContainerType& array) noexcept
                {
                    return ReverseIterType{ array.rbegin() };
                }

                inline constexpr decltype(auto) crbegin(const ContainerType& array) noexcept
                {
                    return ConstReverseIterType{ array.crbegin() };
                }

                inline constexpr decltype(auto) rbegin_unchecked(ContainerType& array) noexcept
                {
                    return UncheckedReverseIterType{ array.rbegin() };
                }

                inline constexpr decltype(auto) crbegin_unchecked(const ContainerType& array) noexcept
                {
                    return ConstUncheckedReverseIterType{ array.crbegin() };
                }

            public:
                inline constexpr decltype(auto) rend(ContainerType& array) noexcept
                {
                    return ReverseIterType{ array.rend() };
                }

                inline constexpr decltype(auto) crend(const ContainerType& array) noexcept
                {
                    return ConstReverseIterType{ array.crend() };
                }

                inline constexpr decltype(auto) rend_unchecked(ContainerType& array) noexcept
                {
                    return UncheckedReverseIterType{ array.rend() };
                }

                inline constexpr decltype(auto) crend_unchecked(const ContainerType& array) noexcept
                {
                    return ConstUncheckedReverseIterType{ array.crend() };
                }
            };

            template<
                typename T,
                usize l,
                template<typename U, usize l> class C
            >
            class OptionalArrayAccessPolicy<T, C<T, l>>
            {
            public:
                using ValueType = OriginType<T>;
                using ContainerType = C<T, l>;
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
                    return l;
                }

                inline static constexpr std::optional<ValueType>& get(ContainerType& array, const usize i)
                {
                    return array.at(i);
                }

                inline static constexpr const std::optional<ValueType>& get(const ContainerType& array, const usize i)
                {
                    return array.at(i);
                }

                inline static constexpr std::optional<ValueType>& get_uncheked(ContainerType& array, const usize i)
                {
                    return array[i];
                }

                inline static constexpr const std::optional<ValueType>& get_uncheked(const ContainerType& array, const usize i)
                {
                    return array[i];
                }

            public:
                inline constexpr decltype(auto) begin(ContainerType& array) noexcept
                {
                    return IterType{ array.begin() };
                }

                inline constexpr decltype(auto) cbegin(const ContainerType& array) noexcept
                {
                    return ConstIterType{ array.begin() };
                }

                inline constexpr decltype(auto) begin_unchecked(ContainerType& array) noexcept
                {
                    return UncheckedIterType{ array.begin() };
                }

                inline constexpr decltype(auto) cbegin_unchecked(const ContainerType& array) noexcept
                {
                    return ConstUncheckedIterType{ array.begin() };
                }

            public:
                inline constexpr decltype(auto) end(ContainerType& array) noexcept
                {
                    return IterType{ array.end() };
                }

                inline constexpr decltype(auto) cend(const ContainerType& array) noexcept
                {
                    return ConstIterType{ array.end() };
                }

                inline constexpr decltype(auto) end_unchecked(ContainerType& array) noexcept
                {
                    return UncheckedIterType{ array.end() };
                }

                inline constexpr decltype(auto) cend_unchecked(const ContainerType& array) noexcept
                {
                    return ConstUncheckedIterType{ array.end() };
                }

            public:
                inline constexpr decltype(auto) rbegin(ContainerType& array) noexcept
                {
                    return ReverseIterType{ array.rbegin() };
                }

                inline constexpr decltype(auto) crbegin(const ContainerType& array) noexcept
                {
                    return ConstReverseIterType{ array.rbegin() };
                }

                inline constexpr decltype(auto) rbegin_unchecked(ContainerType& array) noexcept
                {
                    return UncheckedReverseIterType{ array.rbegin() };
                }

                inline constexpr decltype(auto) crbegin_unchecked(const ContainerType& array) noexcept
                {
                    return ConstUncheckedReverseIterType{ array.rbegin() };
                }

            public:
                inline constexpr decltype(auto) rend(ContainerType& array) noexcept
                {
                    return ReverseIterType{ array.rend() };
                }

                inline constexpr decltype(auto) crend(const ContainerType& array) noexcept
                {
                    return ConstReverseIterType{ array.rend() };
                }

                inline constexpr decltype(auto) rend_unchecked(ContainerType& array) noexcept
                {
                    return UncheckedReverseIterType{ array.rend() };
                }

                inline constexpr decltype(auto) crend_unchecked(const ContainerType& array) noexcept
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
                using ContainerType = C;
                using AccessPolicyType = OptionalArrayAccessPolicy<T, C>;
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
                    AccessPolicyType::get(container())[i] = std::optional<ValueType>{ value };
                }

                template<typename = void>
                    requires ReferenceFaster<ValueType> && std::movable<ValueType>
                inline void set(const usize i, RRefType<ValueType> value)
                {
                    AccessPolicyType::get(container())[i] = std::optional<ValueType>{ move<ValueType>(value) };
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
                usize l,
                template<typename T, usize l> class C
            >
            class StaticOptionalArray
                : public OptionalArrayImpl<T, C<std::optional<T>, l>, StaticOptionalArray<T, l, C>>
            {
                using Impl = OptionalArrayImpl<T, C<std::optional<T>, l>, StaticOptionalArray<T, l, C>>;

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
                StaticOptionalArray(void) = default;

                StaticOptionalArray(ContainerType container)
                    : _container(move<ContainerType>(container)) {}

                StaticOptionalArray(std::initializer_list<ValueType> eles)
                {
                    for (auto i{ 0_uz }, j{ (std::min)(l, eles.size) }; i != j; ++i)
                    {
                        _container[i] = std::optional<ValueType>{ move<ValueType>(eles[i]) };
                    }
                }

                StaticOptionalArray(std::initializer_list<std::optional<ValueType>> eles)
                    : _container(std::move(eles)) {}

            public:
                constexpr StaticOptionalArray(const StaticOptionalArray& ano) = default;
                constexpr StaticOptionalArray(StaticOptionalArray&& ano) noexcept = default;
                constexpr StaticOptionalArray& operator=(const StaticOptionalArray& rhs) = default;
                constexpr StaticOptionalArray& operator=(StaticOptionalArray&& rhs) noexcept = default;
                constexpr ~StaticOptionalArray(void) = default;

            public:
                template<typename = void>
                    requires requires (ContainerType& container) { { container.data() } -> DecaySameAs<PtrType<T>>; }
                inline constexpr const PtrType<T> data(void) noexcept
                {
                    return _container.data();
                }

                template<typename = void>
                    requires requires (const ContainerType& container) { { container.data() } -> DecaySameAs<CPtrType<T>>; }
                inline constexpr const CPtrType<T> data(void) const noexcept
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
                    _container.fill(std::nullopt);
                }

                inline constexpr void fill(CLRefType<ValueType> value) noexcept
                {
                    _container.fill(std::optional<ValueType>(value));
                }

                template<typename = void>
                    requires ReferenceFaster<ValueType> && std::movable<ValueType>
                inline void fill(RRefType<ValueType> value) noexcept
                {
                    _container.fill(std::optional<ValueType>(move<ValueType>(value)));
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
                : public OptionalArrayImpl<T, C<std::optional<T>>, DynamicOptionalArray<T, C>>
            {
                using Impl = OptionalArrayImpl<T, C<std::optional<T>>, DynamicOptionalArray<T, C>>;

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
                constexpr DynamicOptionalArray(void) = default;

                constexpr explicit DynamicOptionalArray(const usize length)
                    : _container(length) {}

                constexpr DynamicOptionalArray(const usize length, CLRefType<ValueType> value)
                    : _container(length, std::optional<ValueType>{ value }) {}

                template<typename = void>
                    requires ReferenceFaster<ValueType> && std::movable<ValueType>
                DynamicOptionalArray(const usize length, RRefType<ValueType> value)
                    : _container(length, std::optional<ValueType>{ move<ValueType>(value) }) {}

                template<typename It>
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

                constexpr DynamicOptionalArray(std::initializer_list<std::optional<ValueType>> eles)
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
                    _container.assign(length, std::nullopt);
                }

                inline constexpr void assign(const usize length, CLRefType<ValueType> value)
                {
                    _container.assign(length, std::optional<ValueType>{ value });
                }

                inline constexpr void assign(const usize length, RRefType<ValueType> value)
                {
                    _container.assign(length, std::optional<ValueType>{ move<ValueType>(value) });
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

                inline constexpr void assign(std::initializer_list<std::optional<ValueType>> eles)
                {
                    _container.assign(std::move(eles));
                }

            public:
                template<typename = void>
                    requires requires (ContainerType& container) { { container.data() } -> DecaySameAs<PtrType<T>>; }
                inline constexpr const PtrType<T> data(void) noexcept
                {
                    return _container.data();
                }

                template<typename = void>
                    requires requires (const ContainerType& container) { { container.data() } -> DecaySameAs<CPtrType<T>>; }
                inline constexpr const CPtrType<T> data(void) const noexcept
                {
                    return _container.data();
                }

            public:
                inline constexpr const usize max_size(void) const noexcept
                {
                    return _container.max_size();
                }

                template<typename = void>
                    requires requires (const ContainerType& container) { container.reserve(std::declval<usize>()); }
                inline constexpr void reserve(const usize new_capacity) const noexcept
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
                    requires requires (const ContainerType& container) { container.shrink_to_fit(); }
                inline void shrink_to_fit(void)
                {
                    _container.shrink_to_fit();
                }

            public:
                inline constexpr void clear(void) noexcept
                {
                    _container.clear();
                }

                inline constexpr decltype(auto) insert(const ConstIterType pos, CLRefType<ValueType> value)
                {
                    return IterType{ _container.insert(pos._iter, value) };
                }

                template<typename = void>
                    requires ReferenceFaster<ValueType> && std::movable<ValueType>
                inline constexpr decltype(auto) insert(const ConstIterType pos, RRefType<ValueType> value)
                {
                    return IterType{ _container.insert(pos._iter, move<ValueType>(value)) };
                }

                inline constexpr decltype(auto) insert(const ConstUncheckedIterType pos, CLRefType<ValueType> value)
                {
                    return UncheckedIterType{ _container.insert(pos._iter, value) };
                }

                template<typename = void>
                    requires ReferenceFaster<ValueType>&& std::movable<ValueType>
                inline constexpr decltype(auto) insert(const ConstUncheckedIterType pos, RRefType<ValueType> value)
                {
                    return UncheckedIterType{ _container.insert(pos._iter, move<ValueType>(value)) };
                }

                template<std::input_iterator It>
                inline constexpr decltype(auto) insert(const ConstIterType pos, const It first, const It last)
                {
                    return IterType{ _container.insert(pos._iter, first, last) };
                }

                template<std::input_iterator It>
                inline constexpr decltype(auto) insert(const ConstUncheckedIterType pos, const It first, const It last)
                {
                    return UncheckedIterType{ _container.insert(pos._iter, first, last) };
                }

                inline constexpr decltype(auto) insert(const ConstIterType pos, std::initializer_list<ValueType> eles)
                {
                    auto it = pos._iter;
                    for (auto i{ 0_uz }; i != eles.size(); ++i)
                    {
                        it = _container.insert(it, move<ValueType>(eles[i]));
                    }
                    return IterType{ it };
                }

                inline constexpr decltype(auto) insert(const ConstUncheckedIterType pos, std::initializer_list<ValueType> eles)
                {
                    auto it = pos._iter;
                    for (auto i{ 0_uz }; i != eles.size(); ++i)
                    {
                        it = _container.insert(it, move<ValueType>(eles[i]));
                    }
                    return UncheckedIterType{ it };
                }

                inline constexpr decltype(auto) insert(const ConstIterType pos, std::initializer_list<std::optional<ValueType>> eles)
                {
                    return IterType{ _container.insert(pos, std::move(eles)) };
                }

                inline constexpr decltype(auto) insert(const ConstUncheckedIterType pos, std::initializer_list<std::optional<ValueType>> eles)
                {
                    return UncheckedIterType{ _container.insert(pos, std::move(eles)) };
                }

                template<typename... Args>
                    requires std::constructible_from<ValueType, Args...>
                inline decltype(auto) emplace(const ConstIterType pos, Args&&... args)
                {
                    return IterType{ _container.emplace(pos._iter, std::forward<Args>(args)...) };
                }

                template<typename... Args>
                    requires std::constructible_from<ValueType, Args...>
                inline decltype(auto) emplace(const ConstUncheckedIterType pos, Args&&... args)
                {
                    return UncheckedIterType{ _container.emplace(pos._iter, std::forward<Args>(args)...) };
                }

                inline decltype(auto) erase(const ConstIterType pos)
                {
                    return IterType{ _container.erase(pos) };
                }

                inline decltype(auto) erase(const ConstUncheckedIterType pos)
                {
                    return UncheckedIterType{ _container.erase(pos) };
                }

                inline decltype(auto) erase(const ConstIterType first, const ConstIterType last)
                {
                    return IterType{ _container.erase(first, last) };
                }

                inline decltype(auto) erase(const ConstUncheckedIterType first, const ConstUncheckedIterType last)
                {
                    return UncheckedIterType{ _container.erase(first, last) };
                }

                inline void push_back(const std::nullopt_t _)
                {
                    _container.push_back(std::nullopt);
                }

                inline void push_back(CLRefType<ValueType> value)
                {
                    _container.push_back(std::optional<ValueType>{ value });
                }

                template<typename = void>
                    requires ReferenceFaster<ValueType> && std::movable<ValueType>
                inline void push_back(RRefType<ValueType> value)
                {
                    _container.push_back(std::optional<ValueType>{ move<ValueType>(value) });
                }

                template<typename... Args>
                    requires std::constructible_from<ValueType, Args...>
                inline ValueType& emplace_back(Args&&... args)
                {
                    return *_container.emplace_back(std::optional<ValueType>{ ValueType{ std::forward<Args>(args)... } });
                }

                inline RetType<std::optional<ValueType>> pop_back(void)
                {
                    auto back = move<std::optional<ValueType>>(this->back());
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
                    _container.insert(_container.begin(), std::optional<ValueType>{ value });
                }

                template<typename = void>
                    requires requires (ContainerType& container) { container.push_front(std::declval<std::optional<ValueType>>()); }
                inline void push_front(CLRefType<ValueType> value)
                {
                    _container.push_front(std::optional<ValueType>{ value });
                }

                template<typename = void>
                    requires ReferenceFaster<ValueType>&& std::movable<ValueType>
                inline void push_front(RRefType<ValueType> value)
                {
                    _container.insert(_container.begin(), std::optional<ValueType>{ move<ValueType>(value) });
                }

                template<typename = void>
                    requires ReferenceFaster<ValueType> && std::movable<ValueType> 
                        && requires (ContainerType& container) { container.push_front(std::declval<std::optional<ValueType>>()); }
                inline void push_front(RRefType<ValueType> value)
                {
                    _container.push_front(std::optional<ValueType>{ move<ValueType>(value) });
                }

                template<typename... Args>
                    requires std::constructible_from<ValueType, Args...>
                inline ValueType& emplace_front(Args&&... args)
                {
                    return **_container.insert(_container.begin(), std::optional<ValueType>{ ValueType{ std::forward<Args>(args)... } });
                }

                template<typename... Args>
                    requires std::constructible_from<ValueType, Args...>
                        && requires (ContainerType& container) { container.emplace_front(std::declval<std::optional<ValueType>>()); }
                inline ValueType& emplace_front(Args&&... args)
                {
                    return *_container.emplace_front(std::optional<ValueType>{ ValueType{ std::forward<Args>(args)... } });
                }

                inline RetType<std::optional<ValueType>> pop_front(void)
                {
                    auto value = move<std::optional<ValueType>>(this->front());
                    _container.erase(_container.begin());
                    return value;
                }

                template<typename = void>
                    requires requires (ContainerType& container) { container.pop_front(); }
                inline RetType<std::optional<ValueType>> pop_front(void)
                {
                    auto value = move<std::optional<ValueType>>(this->front());
                    _container.pop_front();
                    return value;
                }

                // todo: posh_front, emplace_front, pop_front
                
                inline void resize(const usize length)
                {
                    resize(length, std::nullopt);
                }

                inline void resize(const usize length, CLRefType<ValueType> value)
                {
                    resize(length, std::optional<ValueType>{ value });
                }

                template<typename = void>
                    requires ReferenceFaster<ValueType> && std::movable<ValueType>
                inline void resize(const usize length, RRefType<ValueType> value)
                {
                    resize(length, std::optional<ValueType>{ move<ValueType>(value) });
                }

                inline void resize(const usize length, const std::optional<ValueType>& value)
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
            usize l,
            template<typename T, usize l> class C = std::array
        >
        using OptionalArray = optional_array::StaticOptionalArray<OriginType<T>, l, C>;

        template<
            typename T,
            template<typename T> class C = std::vector
        >
        using DynOptionalArray = optional_array::DynamicOptionalArray<OriginType<T>, C>;
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
