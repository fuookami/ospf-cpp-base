#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/literal_constant.hpp>
#include <ospf/memory/reference.hpp>
#include <ospf/meta_programming/iterator.hpp>

namespace ospf
{
    inline namespace data_structure
    {
        namespace optional_array
        {
            template<typename T, typename C>
            class OptionalArrayConstIterator
                : public RandomIteratorImpl<std::optional<OriginType<T>>, typename OriginType<C>::const_iterator, OptionalArrayConstIterator<T, C>>
            {
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
                    return OptionalArrayIterator{ array.begin() };
                }

                inline constexpr decltype(auto) cbegin(const ContainerType& array) noexcept
                {
                    return OptionalArrayConstIterator{ array.cbegin() };
                }

                inline constexpr decltype(auto) begin_unchecked(ContainerType& array) noexcept
                {
                    return OptionalArrayUncheckedIterator{ array.begin() };
                }

                inline constexpr decltype(auto) cbegin_unchecked(const ContainerType& array) noexcept
                {
                    return OptionalArrayConstUncheckedIterator{ array.cbegin() };
                }

            public:
                inline constexpr decltype(auto) end(ContainerType& array) noexcept
                {
                    return OptionalArrayIterator{ array.end() };
                }

                inline constexpr decltype(auto) cend(const ContainerType& array) noexcept
                {
                    return OptionalArrayConstIterator{ array.cend() };
                }

                inline constexpr decltype(auto) end_unchecked(ContainerType& array) noexcept
                {
                    return OptionalArrayUncheckedIterator{ array.end() };
                }

                inline constexpr decltype(auto) cend_unchecked(const ContainerType& array) noexcept
                {
                    return OptionalArrayConstUncheckedIterator{ array.cend() };
                }

            public:
                inline constexpr decltype(auto) rbegin(ContainerType& array) noexcept
                {
                    return OptionalArrayReverseIterator{ array.rbegin() };
                }

                inline constexpr decltype(auto) crbegin(const ContainerType& array) noexcept
                {
                    return OptionalArrayConstReverseIterator{ array.crbegin() };
                }

                inline constexpr decltype(auto) rbegin_unchecked(ContainerType& array) noexcept
                {
                    return OptionalArrayUncheckedReverseIterator{ array.rbegin() };
                }

                inline constexpr decltype(auto) crbegin_unchecked(const ContainerType& array) noexcept
                {
                    return OptionalArrayConstUncheckedReverseIterator{ array.crbegin() };
                }

            public:
                inline constexpr decltype(auto) rend(ContainerType& array) noexcept
                {
                    return OptionalArrayReverseIterator{ array.rend() };
                }

                inline constexpr decltype(auto) crend(const ContainerType& array) noexcept
                {
                    return OptionalArrayConstReverseIterator{ array.crend() };
                }

                inline constexpr decltype(auto) rend_unchecked(ContainerType& array) noexcept
                {
                    return OptionalArrayUncheckedReverseIterator{ array.rend() };
                }

                inline constexpr decltype(auto) crend_unchecked(const ContainerType& array) noexcept
                {
                    return OptionalArrayConstUncheckedReverseIterator{ array.crend() };
                }
            };

            template<
                typename T,
                usize length,
                template<typename U, usize len> class C
            >
            class OptionalArrayAccessPolicy<T, C<T, length>>
            {
            public:
                using ValueType = OriginType<T>;
                using ContainerType = C<T, length>;

            public:
                inline static constexpr const usize size(const ContainerType& array) noexcept
                {
                    return length;
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
                    return OptionalArrayIterator{ array.begin() };
                }

                inline constexpr decltype(auto) cbegin(const ContainerType& array) noexcept
                {
                    return OptionalArrayConstIterator{ array.begin() };
                }

                inline constexpr decltype(auto) begin_unchecked(ContainerType& array) noexcept
                {
                    return OptionalArrayUncheckedIterator{ array.begin() };
                }

                inline constexpr decltype(auto) cbegin_unchecked(const ContainerType& array) noexcept
                {
                    return OptionalArrayConstUncheckedIterator{ array.begin() };
                }

            public:
                inline constexpr decltype(auto) end(ContainerType& array) noexcept
                {
                    return OptionalArrayIterator{ array.end() };
                }

                inline constexpr decltype(auto) cend(const ContainerType& array) noexcept
                {
                    return OptionalArrayConstIterator{ array.end() };
                }

                inline constexpr decltype(auto) end_unchecked(ContainerType& array) noexcept
                {
                    return OptionalArrayUncheckedIterator{ array.end() };
                }

                inline constexpr decltype(auto) cend_unchecked(const ContainerType& array) noexcept
                {
                    return OptionalArrayConstUncheckedIterator{ array.end() };
                }

            public:
                inline constexpr decltype(auto) rbegin(ContainerType& array) noexcept
                {
                    return OptionalArrayReverseIterator{ array.rbegin() };
                }

                inline constexpr decltype(auto) crbegin(const ContainerType& array) noexcept
                {
                    return OptionalArrayConstReverseIterator{ array.rbegin() };
                }

                inline constexpr decltype(auto) rbegin_unchecked(ContainerType& array) noexcept
                {
                    return OptionalArrayUncheckedReverseIterator{ array.rbegin() };
                }

                inline constexpr decltype(auto) crbegin_unchecked(const ContainerType& array) noexcept
                {
                    return OptionalArrayConstUncheckedReverseIterator{ array.rbegin() };
                }

            public:
                inline constexpr decltype(auto) rend(ContainerType& array) noexcept
                {
                    return OptionalArrayReverseIterator{ array.rend() };
                }

                inline constexpr decltype(auto) crend(const ContainerType& array) noexcept
                {
                    return OptionalArrayConstReverseIterator{ array.rend() };
                }

                inline constexpr decltype(auto) rend_unchecked(ContainerType& array) noexcept
                {
                    return OptionalArrayUncheckedReverseIterator{ array.rend() };
                }

                inline constexpr decltype(auto) crend_unchecked(const ContainerType& array) noexcept
                {
                    return OptionalArrayConstUncheckedReverseIterator{ array.rend() };
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
        };
    };
};
