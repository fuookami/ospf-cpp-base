#pragma once

#include <ospf/concepts/base.hpp>
#include <type_traits>

namespace ospf
{
    inline namespace meta_programming
    {
        template<typename T>
        concept FlagType = requires (T value)
        {
            requires (std::is_enum_v<T>);
            { T::On } -> DecaySameAs<T>;
            { T::Off } -> DecaySameAs<T>;
        };

        template<typename T>
        concept TernaryFlagType = FlagType<T> && requires (T value)
        {
            { T::Half } -> DecaySameAs<T>;
        };

        namespace named_flag
        {
            struct OnArgType
            {
                constexpr OnArgType(void) noexcept = default;
                constexpr OnArgType(const OnArgType& ano) noexcept = default;
                constexpr OnArgType(OnArgType&& ano) noexcept = default;
                constexpr OnArgType& operator=(const OnArgType& rhs) noexcept = default;
                constexpr OnArgType& operator=(OnArgType&& rhs) noexcept = default;
                constexpr ~OnArgType(void) noexcept = default;

                template<FlagType T>
                inline constexpr operator T(void) const noexcept
                {
                    return T::On;
                }
            };

            struct OffArgType
            {
                constexpr OffArgType(void) noexcept = default;
                constexpr OffArgType(const OffArgType& ano) noexcept = default;
                constexpr OffArgType(OffArgType&& ano) noexcept = default;
                constexpr OffArgType& operator=(const OffArgType& rhs) noexcept = default;
                constexpr OffArgType& operator=(OffArgType&& rhs) noexcept = default;
                constexpr ~OffArgType(void) noexcept = default;

                template<TernaryFlagType T>
                inline constexpr operator T(void) const noexcept
                {
                    return T::Off;
                }
            };

            struct HalfArgType
            {
                constexpr HalfArgType(void) noexcept = default;
                constexpr HalfArgType(const HalfArgType& ano) noexcept = default;
                constexpr HalfArgType(HalfArgType&& ano) noexcept = default;
                constexpr HalfArgType& operator=(const HalfArgType& rhs) noexcept = default;
                constexpr HalfArgType& operator=(HalfArgType&& rhs) noexcept = default;
                constexpr ~HalfArgType(void) noexcept = default;

                template<TernaryFlagType T>
                inline constexpr operator T(void) const noexcept
                {
                    return T::Half;
                }
            };
        };

        static constexpr named_flag::OnArgType on = named_flag::OnArgType();
        static constexpr named_flag::OffArgType off = named_flag::OffArgType();
        static constexpr named_flag::HalfArgType half = named_flag::HalfArgType();
    };
};

#ifndef OSPF_NAMED_FLAG_IMPL_TEMPLATE
#define OSPF_NAMED_FLAG_IMPL_TEMPLATE(Name) \
template<>\
inline constexpr ::ospf::meta_programming::named_flag::OnArgType::operator Name(void) const noexcept\
{\
return Name::On; \
}\
template<>\
inline constexpr ::ospf::meta_programming::named_flag::OffArgType::operator Name(void) const noexcept\
{\
return Name::Off; \
}
#endif

#ifndef OSPF_NAMED_TERNARY_FLAG_IMPL_TEMPLATE
#define OSPF_NAMED_TERNARY_FLAG_IMPL_TEMPLATE(Name) \
OSPF_NAMED_FLAG_IMPL_TEMPLATE(Name)\
template<>\
inline constexpr ::ospf::meta_programming::named_flag::HalfArgType::operator Name(void) const noexcept\
{\
return Name::Half; \
}
#endif

#ifndef OSPF_NAMED_FLAG_TEMPLATE
#define OSPF_NAMED_FLAG_TEMPLATE(Name) enum class Name\
{\
    Off,\
    On\
};\
OSPF_NAMED_FLAG_IMPL_TEMPLATE(Name)
#endif

#ifndef OSPF_NAMED_TERNARY_FLAG_TEMPLATE
#define OSPF_NAMED_TERNARY_FLAG_TEMPLATE(Name) enum class Name\
{\
    Off,\
    Half,\
    On\
};\
OSPF_NAMED_TERNARY_FLAG_IMPL_TEMPLATE(Name)
#endif

template<ospf::FlagType T>
inline constexpr const bool to_bool(const T value)
{
    return value == T::On;
}

template<ospf::FlagType T>
inline constexpr const bool operator==(const T value, const ospf::named_flag::OnArgType _) noexcept
{
    return value == T::On;
}

template<ospf::FlagType T>
inline constexpr const bool operator!=(const T value, const ospf::named_flag::OnArgType _) noexcept
{
    return value != T::On;
}

template<ospf::FlagType T>
inline constexpr const bool operator==(const T value, const ospf::named_flag::OffArgType _) noexcept
{
    return value == T::Off;
}

template<ospf::FlagType T>
inline constexpr const bool operator!=(const T value, const ospf::named_flag::OffArgType _) noexcept
{
    return value != T::Off;
}

template<ospf::TernaryFlagType T>
inline constexpr const bool operator==(const T value, const ospf::named_flag::HalfArgType _) noexcept
{
    return value == T::Half;
}

template<ospf::TernaryFlagType T>
inline constexpr const bool operator!=(const T value, const ospf::named_flag::HalfArgType _) noexcept
{
    return value != T::Half;
}
