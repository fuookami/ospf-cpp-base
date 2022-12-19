#pragma once

#include <ospf/concepts.hpp>
#include <type_traits>

namespace ospf
{
    template<typename T>
    struct TypeFamily
    {
        using Self = std::decay_t<T>;

        using RetType = Self;
        using PtrType = std::add_pointer_t<Self>;
        using CPtrType = std::add_pointer_t<std::add_const_t<Self>>;
        using LRefType = std::add_lvalue_reference_t<Self>;
        using CLRefType = std::add_lvalue_reference_t<std::add_const_t<Self>>;
        using RRefType = std::add_rvalue_reference_t<Self>;
    };

    template<>
    struct TypeFamily<void>
    {
        using Self = void;

        using RetType = Self;
        using LRefType = Self;
        using CLRefType = Self;
        using RRefType = Self;
    };

    template<CopyFaster T>
    struct TypeFamily<T>
    {
        using Self = std::decay_t<T>;

        using RetType = std::add_const_t<T>;
        using ArrayType = T[];
        using CArrayType = const T[];
        using PtrType = std::add_pointer_t<Self>;
        using CPtrType = std::add_pointer_t<std::add_const_t<Self>>;
        using LRefType = std::add_lvalue_reference_t<Self>;
        using CLRefType = std::add_const_t<Self>;
        using RRefType = std::add_const_t<Self>;
    };

    template<typename T>
    using OriginType = typename TypeFamily<T>::Self;
    template<typename T>
    using RetType = typename TypeFamily<T>::RetType;
    template<typename T>
    using ArrayType = typename TypeFamily<T>::ArrayType;
    template<typename T>
    using CArrayType = typename TypeFamily<T>::CArrayType;
    template<typename T>
    using PtrType = typename TypeFamily<T>::PtrType;
    template<typename T>
    using CPtrType = typename TypeFamily<T>::CPtrType;
    template<typename T>
    using LRefType = typename TypeFamily<T>::LRefType;
    template<typename T>
    using CLRefType = typename TypeFamily<T>::CLRefType;
    template<typename T>
    using RRefType = typename TypeFamily<T>::RRefType;
};
