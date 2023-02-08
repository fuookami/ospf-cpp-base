#pragma once

namespace ospf
{
    inline namespace serialization
    {
        template<typename T>
        struct SerializationNullableTrait
        {
            static constexpr const bool value = false;
        };

        template<typename T>
        static constexpr const bool serialization_nullable = SerializationNullableTrait<T>::value;

        template<typename T>
        concept SerializationNullable = serialization_nullable<T>;

        // todo: impl for types
    };
};
