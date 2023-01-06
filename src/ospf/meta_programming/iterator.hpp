#pragma once

#include <ospf/type_family.hpp>
#include <ospf/meta_programming/crtp.hpp>

namespace ospf
{
    inline namespace meta_programming
    {
        inline namespace iterator
        {
            template<typename T, typename I, typename Self>
            class BidirectionalIteratorImpl;

            template<typename T, typename I, typename Self>
            class RandomIteratorImpl;

            template<typename T, typename I, typename Self>
            class ForwardIteratorImpl
            {
                OSPF_CRTP_IMPL

                template<typename T, typename I, typename Self>
                friend class BidirectionalIteratorImpl;

                template<typename T, typename I, typename Self>
                friend class RandomIteratorImpl;

            public:
                using ValueType = OriginType<T>;
                using IterType = OriginType<I>;

                static_assert(std::forward_iterator<IterType>, "Iterator must at least be forward.");

            protected:
                ForwardIteratorImpl(IterType iter)
                    : _iter(iter) {}
            public:
                ForwardIteratorImpl(const ForwardIteratorImpl& ano) = default;
                ForwardIteratorImpl(ForwardIteratorImpl&& ano) noexcept = default;
                ForwardIteratorImpl& operator=(const ForwardIteratorImpl& rhs) = default;
                ForwardIteratorImpl& operator=(ForwardIteratorImpl&& rhs) noexcept = default;
                ~ForwardIteratorImpl(void) noexcept = default;

            public:
                inline const ValueType& operator*(void) const noexcept
                {
                    return Trait::get(_iter);
                }

                inline const CPtrType<ValueType> operator->(void) const noexcept
                {
                    return &Trait::get(_iter);
                }

            public:
                inline decltype(auto) operator++(void) noexcept
                {
                    ++_iter;
                    return self();
                }

                inline decltype(auto) operator++(int) noexcept
                {
                    auto ret = Trait::construct(_iter);
                    ++_iter;
                    return ret;
                }

            public:
                inline void swap(ForwardIteratorImpl& ano) noexcept
                {
                    return std::swap(_iter, ano._iter);
                }

            public:
                inline const bool operator==(const ForwardIteratorImpl& ano) const noexcept
                {
                    return _iter == ano._iter;
                }

                inline const bool operator!=(const ForwardIteratorImpl& ano) const noexcept
                {
                    return _iter != ano._iter;
                }

            private:
                struct Trait : public Self
                {
                    inline static const ValueType& get(const IterType iter) noexcept
                    {
                        static const auto impl = &Self::OSPF_CRTP_FUNCTION(get);
                        return (*impl)(iter);
                    }

                    inline static RetType<Self> construct(const IterType iter) noexcept
                    {
                        static const auto impl = &Self::OSPF_CRTP_FUNCTION(construct);
                        return (*impl)(iter);
                    }
                };

            protected:
                IterType _iter;
            };

            template<typename T, typename I, typename Self>
            class BidirectionalIteratorImpl
                : public ForwardIteratorImpl<T, I, Self>
            {
                using Base = ForwardIteratorImpl<T, I, Self>;
                using typename Base::Trait;

                template<typename T, typename I, typename Self>
                friend class RandomIteratorImpl;

            public:
                using ValueType = OriginType<T>;
                using IterType = OriginType<I>;

                static_assert(std::bidirectional_iterator<IterType>, "Iterator must at least be forward.");

            protected:
                BidirectionalIteratorImpl(IterType iter)
                    : Base(iter) {}
            public:
                BidirectionalIteratorImpl(const BidirectionalIteratorImpl& ano) = default;
                BidirectionalIteratorImpl(BidirectionalIteratorImpl&& ano) noexcept = default;
                BidirectionalIteratorImpl& operator=(const BidirectionalIteratorImpl& rhs) = default;
                BidirectionalIteratorImpl& operator=(BidirectionalIteratorImpl&& rhs) noexcept = default;
                ~BidirectionalIteratorImpl(void) noexcept = default;

            public;
                inline decltype(auto) operator--(void) noexcept
                {
                    --this->_iter;
                    return this->self();
                }

                inline decltype(auto) operator--(int) noexcept
                {
                    auto ret = Trait::construct(this->_iter);
                    --this->_iter;
                    return ret;
                }
            };

            template<typename T, typename I, typename Self>
            class RandomIteratorImpl
                : public BidirectionalIteratorImpl<T, I, Self>
            {
                using Base = BidirectionalIteratorImpl<T, I, Self>;
                using typename Base::Trait;

            public:
                using ValueType = OriginType<T>;
                using IterType = OriginType<I>;

                static_assert(std::random_access_iterator<IterType>, "Iterator must at least be random.");

            protected:
                RandomIteratorImpl(IterType iter)
                    : Base(iter) {}
            public:
                RandomIteratorImpl(const RandomIteratorImpl& ano) = default;
                RandomIteratorImpl(RandomIteratorImpl&& ano) noexcept = default;
                RandomIteratorImpl& operator=(const RandomIteratorImpl& rhs) = default;
                RandomIteratorImpl& operator=(RandomIteratorImpl&& rhs) noexcept = default;
                ~RandomIteratorImpl(void) noexcept = default;

            public:
                inline decltype(auto) operator+(const ptrdiff diff) const noexcept
                {
                    return Trait::construct(this->_iter + diff);
                }

                inline decltype(auto) operator+=(const ptrdiff diff) noexcept
                {
                    this->_iter += diff;
                    return this->self();
                }

                inline decltype(auto) operator-(const ptrdiff diff) const noexcept
                {
                    return Trait::construct(this->_iter - diff);
                }

                inline decltype(auto) operator-=(const ptrdiff diff) noexcept
                {
                    this->_iter -= diff;
                    return this->self();
                }

            public:
                inline const bool operator<(const RandomIteratorImpl& ano) const noexcept
                {
                    return this->_iter < ano._iter;
                }

                inline const bool operator<=(const RandomIteratorImpl& ano) const noexcept
                {
                    return this->_iter <= ano._iter;
                }

                inline const bool operator>(const RandomIteratorImpl& ano) const noexcept
                {
                    return this->_iter > ano._iter;
                }

                inline const bool operator>=(const RandomIteratorImpl& ano) const noexcept
                {
                    return this->_iter >= ano._iter;
                }

                inline decltype(auto) operator<=>(const RandomIteratorImpl& ano) const noexcept
                {
                    return this->_iter <=> ano._iter;
                }
            };
        };
    };
};

namespace std
{
    template<typename T, typename I, typename Self>
    inline void swap(ospf::ForwardIteratorImpl<T, I, Self>& lhs, ospf::ForwardIteratorImpl<T, I, Self>& rhs) noexcept
    {
        return lhs.swap(rhs);
    }
};
