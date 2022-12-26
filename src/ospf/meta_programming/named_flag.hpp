#pragma once

#include <type_traits>

namespace ospf
{
    inline namespace meta_programming
    {
        template<typename T>
        concept FlagType = requires (T value)
        {
            requires (std::is_enum_v<T>);
            T::Off;
            T::On;
        };

        template<typename T>
        concept TernaryFlagType = FlagType<T> && requires (T value)
        {
            T::Half;
        };

        namespace named_flag
        {
            struct OnArgType
            {
                constexpr OnArgType(void) noexcept = default;
                OnArgType(const OnArgType& ano) = delete;
                OnArgType(OnArgType&& ano) = delete;
                OnArgType& operator=(const OnArgType& rhs) = delete;
                OnArgType& operator=(OnArgType&& rhs) = delete;
                ~OnArgType(void) noexcept = default;

                template<typename ArgType_>
                inline constexpr operator ArgType_(void) const noexcept
                {
                    return ArgType_::On;
                }
            };

            struct HalfArgType
            {
                constexpr HalfArgType(void) noexcept = default;
                HalfArgType(const HalfArgType& ano) = delete;
                HalfArgType(HalfArgType&& ano) = delete;
                HalfArgType& operator=(const HalfArgType& rhs) = delete;
                HalfArgType& operator=(HalfArgType&& rhs) = delete;
                ~HalfArgType(void) noexcept = default;

                template<typename ArgType_>
                inline constexpr operator ArgType_(void) const noexcept
                {
                    return ArgType_::Half;
                }
            };

            struct OffArgType
            {
                constexpr OffArgType(void) noexcept = default;
                OffArgType(const OffArgType& ano) = delete;
                OffArgType(OffArgType&& ano) = delete;
                OffArgType& operator=(const OffArgType& rhs) = delete;
                OffArgType& operator=(OffArgType&& rhs) = delete;
                ~OffArgType(void) noexcept = default;

                template<typename ArgType_>
                inline constexpr operator ArgType_(void) const noexcept
                {
                    return ArgType_::Off;
                }
            };
        };

        static constexpr named_flag::OffArgType off = named_flag::OffArgType();
        static constexpr named_flag::HalfArgType half = named_flag::HalfArgType();
        static constexpr named_flag::OnArgType on = named_flag::OnArgType();

        template<FlagType T_>
        inline constexpr const bool to_bool(const T_ value)
        {
            return value == T_::On;
        }
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
