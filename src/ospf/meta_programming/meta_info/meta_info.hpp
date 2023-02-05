#pragma once

#include <ospf/functional/sequence_tuple.hpp>
#include <ospf/meta_programming/meta_info/meta_item.hpp>

namespace ospf
{
    inline namespace meta_programming
    {
        namespace meta_info
        {
            template<typename T>
            class MetaInfo;

            template<typename T>
            concept WithMetaInfo = requires
            {
                { MetaInfo<T>{} } -> DecayNotSameAs<void>;
            };

            template<typename T, bool v = false>
                requires WithMetaInfo<T>
            struct BaseType
            {
                static constexpr const auto info = MetaInfo<T>{};
                static constexpr const auto is_virtual = v;

                template<typename U>
                    requires std::derived_from<U, T>
                inline static constexpr T& from(U& obj) noexcept
                {
                    return static_cast<T&>(obj);
                }

                template<typename U>
                    requires std::derived_from<U, T>
                inline static constexpr const T& from(const U& obj) noexcept
                {
                    return static_cast<const T&>(obj);
                }
            };

            template<typename... Fs>
            using FieldList = SequenceTuple<Fs...>;

            template<typename... As>
            using AttributeList = SequenceTuple<As...>;

            template<typename... Bs>
            using BaseList = SequenceTuple<Bs...>;

#ifndef OSPF_META_ITEM
#define OSPF_META_ITEM(Item, Name, Mem) Item<decltype(&Type::Mem)>{ Name, &Type::Mem }
#endif

#ifndef OSPF_META_NAMED_FIELD
#define OSPF_META_NAMED_FIELD(Name, Mem) OSPF_META_ITEM(FieldItem, Name, Mem)
#endif

#ifndef OSPF_META_FIELD
#define OSPF_META_FIELD(Mem) OSPF_META_NAMED_FIELD(BOOST_STRINGIZE(Mem), Mem)
#endif

#ifndef OSPF_META_NAMED_ATTRIBUTE
#define OSPF_META_NAMED_ATTRIBUTE(Name, Mem) OSPF_META_ITEM(AttributeItem, Name, Mem)
#endif

#ifndef OSPF_META_ATTRIBUTE
#define OSPF_META_ATTRIBUTE(Mem) OSPF_META_NAMED_ATTRIBUTE(BOOST_STRINGIZE(Mem), Mem)
#endif

            template<typename T, typename Self, typename... Bs>
            class MetaInfoImpl
            {
                OSPF_CRTP_IMPL

            public:
                using ParentType = OriginType<T>;

                template<typename P>
                using FieldItem = meta_info::FieldItem<ParentType, P>;
                template<typename P>
                using AttributeItem = meta_info::AttributeItem<ParentType, P>;

                static constexpr const BaseList bases = { Bs{}... };

            protected:
                constexpr MetaInfoImpl(void) = default;
            public:
                constexpr MetaInfoImpl(const MetaInfoImpl& ano) = default;
                constexpr MetaInfoImpl(MetaInfoImpl&& ano) noexcept = default;
                constexpr MetaInfoImpl& operator=(const MetaInfoImpl& rhs) = default;
                constexpr MetaInfoImpl& operator=(MetaInfoImpl&& rhs) noexcept = default;
                constexpr ~MetaInfoImpl(void) = default;

            public:
                inline constexpr const bool plane(void) const noexcept
                {
                    return bases.empty();
                }

                // todo
            };
        };
    };
};
