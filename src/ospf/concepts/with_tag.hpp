#pragma once

#include <ospf/type_family.hpp>
#include <ospf/concepts/base.hpp>
#include <ospf/meta_programming/named_type.hpp>

namespace ospf
{
    inline namespace concepts
    {
        template<typename T>
        struct TagValue;

        template<typename T>
        concept WithTag = std::default_initializable<TagValue<T>> 
            && requires(const TagValue<T>& trait, const T& ele)
            {
                { trait.value(ele) } -> DecaySameAs<typename TagValue<T>::Type>;
            };

        template<typename T, typename P>
            requires WithTag<T>
        struct TagValue<NamedType<T, P>>
        {
            using Type = typename TagValue<OriginType<T>>::Type;

            inline constexpr RetType<Type> value(ArgCLRefType<NamedType<T, P>> obj) const noexcept
            {
                static const TagValue<OriginType<T>> extractor{};
                return extractor.value(obj.unwrap());
            }
        };
    };
};
