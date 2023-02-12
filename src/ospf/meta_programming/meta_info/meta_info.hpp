﻿#pragma once

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

        };

        template<typename T>
        concept WithMetaInfo = requires
        {
            { meta_info::MetaInfo<T>{} } -> DecayNotSameAs<void>;
        };

        namespace meta_info
        {
            template<WithMetaInfo T, bool v = false>
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
            class FieldList
                : public SequenceTuple<Fs...>
            {
            public:
                constexpr FieldList(Fs... args)
                    : SequenceTuple<Fs...>(args...) {}
                constexpr FieldList(const FieldList& ano) = default;
                constexpr FieldList(FieldList&& ano) noexcept = default;
                constexpr FieldList& operator=(const FieldList& rhs) = default;
                constexpr FieldList& operator=(FieldList&& rhs) noexcept = default;
                constexpr ~FieldList(void) noexcept = default;
            };

            template<typename... As>
            class AttrList
                : public SequenceTuple<As...>
            {
            public:
                constexpr AttrList(As... args)
                    : SequenceTuple<As...>(args...) {}
                constexpr AttrList(const AttrList& ano) = default;
                constexpr AttrList(AttrList&& ano) = default;
                constexpr AttrList& operator=(const AttrList& rhs) = default;
                constexpr AttrList& operator=(AttrList&& rhs) = default;
                constexpr ~AttrList(void) = default;
            };

            template<typename... Bs>
            class BaseList
                : public SequenceTuple<Bs...>
            {
            public:
                constexpr BaseList(Bs... args)
                    : SequenceTuple<Bs...>(args...) {}
                constexpr BaseList(const BaseList& ano) = default;
                constexpr BaseList(BaseList&& ano) noexcept = default;
                constexpr BaseList& operator=(const BaseList& rhs) = default;
                constexpr BaseList& operator=(BaseList&& rhs) noexcept = default;
                constexpr ~BaseList(void) noexcept = default;
            };

#ifndef OSPF_META_ITEM
#define OSPF_META_ITEM(Item, Name, Mem) Item<decltype(&ParentType::Mem)>{ Name, &ParentType::Mem }
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

                inline constexpr const usize size(void) const noexcept
                {
                    return virtual_bases().accumulate(0_uz, [](const auto lhs, const auto& type)
                        {
                            return lhs + type.size();
                        }) + non_virtual_size();
                }

                inline constexpr decltype(auto) virtual_bases(void) const noexcept
                {
                    return bases.accumulate(SequenceTuple{}, [](const auto& lhs, const auto& rhs)
                        {
                            constexpr const auto this_virtual_bases = rhs.info.virtual_bases();
                            const auto ret = this_virtual_bases.accumulate(lhs, [](const auto lhs, const auto rhs) 
                                {
                                    return lhs.insert(rhs);
                                });
                            if constexpr (rhs.is_virtual)
                            {
                                return ret.insert(rhs.info);
                            }
                            else
                            {
                                return ret;
                            }
                        });
                }

                inline constexpr decltype(auto) fields(void) const noexcept
                {
                    return Trait::field_list(self());
                }

                inline constexpr decltype(auto) attributes(void) const noexcept
                {
                    return Trait::attribute_list(self());
                }

            public:
                template<typename Func>
                inline constexpr void for_each(ParentType& obj, const Func& func) const noexcept
                {
                    virtual_bases().for_each([&obj, &func](const auto& type)
                        {
                            type.fields().for_each([&obj, &func](const auto& field)
                                {
                                    func(obj, field);
                                });
                            type.attributes().for_each([&obj, &func](const auto& attribute)
                                {
                                    func(obj, attribute);
                                });
                        });
                    for_each_non_virtual(obj, func);
                }

                template<typename Func>
                inline constexpr void for_each(const ParentType& obj, const Func& func) const noexcept
                {
                    virtual_bases().for_each([&obj, &func](const auto& type)
                        {
                            type.fields().for_each([&obj, &func](const auto& field)
                                {
                                    func(obj, field);
                                });
                            type.attributes().for_each([&obj, &func](const auto& attribute)
                                {
                                    func(obj, attribute);
                                });
                        });
                    for_each_non_virtual(obj, func);
                }

                template<typename Func>
                inline constexpr void for_each(const Func& func) const noexcept
                {
                    virtual_bases().for_each([&func](const auto& type)
                        {
                            type.fields().for_each([&func](const auto& field)
                                {
                                    func(field);
                                });
                            type.attributes().for_each([&func](const auto& attribute)
                                {
                                    func(attribute);
                                });
                        });
                    for_each_non_virtual(func);
                }
                
            private:
                inline constexpr const usize non_virtual_size(void) const noexcept
                {
                    return bases.accumulate(0_uz, [](const auto lhs, const auto& type) 
                        {
                            if constexpr (!type.is_virtual)
                            {
                                return lhs + type.info.non_virtual_size();
                            }
                            else
                            {
                                return lhs;
                            }
                        }) + fields().size() + attributes().size();
                }

                template<typename Func>
                inline constexpr void for_each_non_virtual(ParentType& obj, const Func& func) const noexcept
                {
                    bases.for_each([&obj, &func](const auto& type)
                        {
                            if constexpr (!type.is_virtual)
                            {
                                type.info.for_each_non_virtual(obj, func);
                            }
                        });
                    fields().for_each([&obj, &func](const auto& field)
                        {
                            func(obj, field);
                        });
                    attributes().for_each([&obj, &func](const auto& attribute)
                        {
                            func(obj, attribute);
                        });
                }

                template<typename Func>
                inline constexpr void for_each_non_virtual(const ParentType& obj, const Func& func) const noexcept
                {
                    bases.for_each([&obj, &func](const auto& type)
                        {
                            if constexpr (!type.is_virtual)
                            {
                                type.info.for_each_non_virtual(obj, func);
                            }
                        });
                    fields().for_each([&obj, &func](const auto& field)
                        {
                            func(obj, field);
                        });
                    attributes().for_each([&obj, &func](const auto& attribute)
                        {
                            func(obj, attribute);
                        });
                }

                template<typename Func>
                inline constexpr void for_each_non_virtual(const Func& func) const noexcept
                {
                    bases.for_each([&func](const auto& type)
                        {
                            if constexpr (!type.is_virtual)
                            {
                                type.info.for_each_non_virtual(func);
                            }
                        });
                    fields().for_each([&func](const auto& field)
                        {
                            func(field);
                        });
                    attributes().for_each([&func](const auto& attribute)
                        {
                            func(attribute);
                        });
                }

            private:
                struct Trait : public Self
                {
                    inline static constexpr decltype(auto) field_list(const Self& self) noexcept
                    {
                        const auto get_impl = &Self::OSPF_CRTP_FUNCTION(get_field_list);
                        return (self.*get_impl)();
                    }

                    inline static constexpr decltype(auto) attribute_list(const Self& self) noexcept
                    {
                        const auto get_impl = &Self::OSPF_CRTP_FUNCTION(get_attribute_list);
                        return (self.*get_impl)();
                    }
                };
            };
        };
    };
};
