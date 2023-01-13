#pragma once

#include <ospf/concepts/copy_faster.hpp>
#include <type_traits>

namespace ospf
{
    template<typename T>
    struct TypeFamily
    {
        using Self = std::decay_t<T>;

        using ArrayType = Self[];
        using CArrayType = const Self[];

        using PtrType = std::add_pointer_t<Self>;
        using CPtrType = std::add_pointer_t<std::add_const_t<Self>>;

        using LRefType = std::add_lvalue_reference_t<Self>;
        using CLRefType = std::add_lvalue_reference_t<std::add_const_t<Self>>;
        using RRefType = std::add_rvalue_reference_t<Self>;

        using ArgLRefType = LRefType;
        using ArgCLRefType = CLRefType;
        using ArgRRefType = RRefType;

        using RetType = Self;
    };

    template<>
    struct TypeFamily<void>
    {
        using Self = void;

        using ArrayType = void*;
        using CArrayType = void*;

        using PtrType = void*;
        using CPtrType = void*;

        using LRefType = Self;
        using CLRefType = Self;
        using RRefType = Self;

        using ArgLRefType = Self;
        using ArgCLRefType = Self;
        using ArgRRefType = Self;

        using RetType = Self;
    };

    template<CopyFaster T>
    struct TypeFamily<T>
    {
        using Self = std::decay_t<T>;

        using ArrayType = Self[];
        using CArrayType = const Self[];

        using PtrType = std::add_pointer_t<Self>;
        using CPtrType = std::add_pointer_t<std::add_const_t<Self>>;

        using LRefType = std::add_lvalue_reference_t<Self>;
        using CLRefType = std::add_lvalue_reference_t<std::add_const_t<Self>>;
        using RRefType = std::add_rvalue_reference_t<Self>;

        using ArgLRefType = std::add_lvalue_reference_t<Self>;
        using ArgCLRefType = std::add_const_t<Self>;
        using ArgRRefType = std::add_const_t<Self>;

        using RetType = std::add_const_t<T>;
    };

    template<typename T>
    using OriginType = typename TypeFamily<T>::Self;

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

    template<typename T>
    using ArgLRefType = typename TypeFamily<T>::ArgLRefType;
    template<typename T>
    using ArgCLRefType = typename TypeFamily<T>::ArgCLRefType;
    template<typename T>
    using ArgRRefType = typename TypeFamily<T>::ArgRRefType;

    template<typename T>
    using RetType = typename TypeFamily<T>::RetType;
};
