#pragma once

#include <ospf/memory/reference.hpp>
#include <span>

namespace ospf
{
    inline namespace serialization
    {
        template<typename T>
        struct SerializationWritableTrait
        {
            static constexpr const bool value = true;
        };

        template<typename T>
        static constexpr const bool serialization_writable = SerializationWritableTrait<T>::value;

        template<typename T>
        concept SerializationWritable = serialization_writable<T>;

        template<typename T, reference::ReferenceCategory cat>
        struct SerializationWritableTrait<reference::Ref<T, cat>>
        {
            static constexpr const bool value = false;
        };

        template<typename T, usize len>
        struct SerializationWritableTrait<std::span<T, len>>
        {
            static constexpr const bool value = false;
        };
    };
};
