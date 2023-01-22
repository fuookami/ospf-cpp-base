#pragma once

#include <ospf/data_structure/multi_array/dummy_index.hpp>

namespace ospf
{
    inline namespace data_structure
    {
        inline namespace multi_array
        {
            namespace map_index
            {
                using RangeFull = range_bounds::RangeFull;
                using DummyIndex = dummy_index::DummyIndex;

                struct MapPlaceHolder
                {
                    usize to_dimension;

                    inline constexpr operator const usize(void) const noexcept
                    {
                        return to_dimension;
                    }
                };

                static constexpr const auto _0 = MapPlaceHolder{ 0_uz };
                static constexpr const auto _1 = MapPlaceHolder{ 1_uz };
                static constexpr const auto _2 = MapPlaceHolder{ 2_uz };
                static constexpr const auto _3 = MapPlaceHolder{ 3_uz };
                static constexpr const auto _4 = MapPlaceHolder{ 4_uz };
                static constexpr const auto _5 = MapPlaceHolder{ 5_uz };
                static constexpr const auto _6 = MapPlaceHolder{ 6_uz };
                static constexpr const auto _7 = MapPlaceHolder{ 7_uz };
                static constexpr const auto _8 = MapPlaceHolder{ 8_uz };
                static constexpr const auto _9 = MapPlaceHolder{ 9_uz };
                static constexpr const auto _10 = MapPlaceHolder{ 10_uz };
                static constexpr const auto _11 = MapPlaceHolder{ 11_uz };
                static constexpr const auto _12 = MapPlaceHolder{ 12_uz };
                static constexpr const auto _13 = MapPlaceHolder{ 13_uz };
                static constexpr const auto _14 = MapPlaceHolder{ 14_uz };
                static constexpr const auto _15 = MapPlaceHolder{ 15_uz };
                static constexpr const auto _16 = MapPlaceHolder{ 16_uz };
                static constexpr const auto _17 = MapPlaceHolder{ 17_uz };
                static constexpr const auto _18 = MapPlaceHolder{ 18_uz };
                static constexpr const auto _19 = MapPlaceHolder{ 19_uz };
                static constexpr const auto _20 = MapPlaceHolder{ 20_uz };

                class MapIndex
                {
                    using Either = ospf::Either<DummyIndex, MapPlaceHolder>;

                public:
                    constexpr MapIndex(const usize index)
                        : _either(DummyIndex{ index }) {}

                    constexpr MapIndex(const isize index)
                        : _either(DummyIndex{ index }) {}

                    constexpr MapIndex(const RangeBounds<usize> range)
                        : _either(DummyIndex{ range }) {}

                    constexpr MapIndex(const RangeBounds<isize> range)
                        : _either(DummyIndex{ range }) {}

                    constexpr MapIndex(const std::vector<usize>& array)
                        : _either(DummyIndex{ array }) {}

                    constexpr MapIndex(std::vector<usize>&& array)
                        : _either(DummyIndex{ std::move(array) }) {}

                    constexpr MapIndex(const std::vector<isize>& array)
                        : _either(DummyIndex{ array }) {}

                    constexpr MapIndex(std::vector<isize>&& array)
                        : _either(DummyIndex{ std::move(array) }) {}

                    constexpr MapIndex(const RangeFull _)
                        : _either(DummyIndex{ _ }) {}

                    template<typename T>
                        requires std::constructible_from<DummyIndex, T>
                    constexpr MapIndex(T&& index)
                        : _either(DummyIndex{ std::forward<T>(index) }) {}

                    constexpr MapIndex(const MapPlaceHolder holder)
                        : _either(holder) {}

                public:
                    constexpr MapIndex(const MapIndex& ano) = default;
                    constexpr MapIndex(MapIndex&& ano) noexcept = default;
                    constexpr MapIndex& operator=(const MapIndex& rhs) = default;
                    constexpr MapIndex& operator=(MapIndex&& rhs) noexcept = default;
                    constexpr ~MapIndex(void) noexcept = default;

                public:
                    inline constexpr const bool is_index(void) const noexcept
                    {
                        return _either.is_left();
                    }

                    inline constexpr const bool is_holder(void) const noexcept
                    {
                        return _either.is_right();
                    }

                public:
                    inline constexpr const DummyIndex& index(void) const
                    {
                        return _either.left();
                    }

                    inline constexpr const MapPlaceHolder holder(void) const
                    {
                        return _either.right();
                    }

                private:
                    Either _either;
                };

                template<usize dim, usize to_dim>
                class MapVector
                {
                    using Index = map_index::MapIndex;

                public:
                    constexpr MapVector(std::initializer_list<Index> vector)
                        : _vector(std::move(vector)) {}
                    constexpr MapVector(const MapVector& ano) = default;
                    constexpr MapVector(MapVector&& ano) noexcept = default;
                    constexpr MapVector& operator=(const MapVector& rhs) = default;
                    constexpr MapVector& operator=(MapVector&& rhs) noexcept = default;
                    constexpr ~MapVector(void) noexcept = default;

                public:
                    inline constexpr ArgCLRefType<Index> operator[](const usize i) const
                    {
                        return _vector[i];
                    }

                public:
                    inline constexpr const usize size(void) const noexcept
                    {
                        return _vector.size();
                    }

                private:
                    std::array<Index, dim> _vector;
                };
            };

            template<typename... Args>
            struct IsMapVector
            {
                static constexpr const bool value = false;
            };

            template<typename T>
            struct IsMapVector<T>
            {
                static constexpr const bool value = DummyIndex::Types::template contains<T> || DecaySameAs<T, MapPlaceHolder>;
            };

            template<typename T, typename... Args>
            struct IsMapVector<T, Args...>
            {
                static constexpr const bool value = IsMapVector<T>::value && IsMapVector<Args...>::value;
            };

            template<typename... Args>
            static constexpr const bool is_map_vector = IsMapVector<Args...>::value;

            template<typename... Args>
                requires is_map_vector<Args...>
            inline constexpr decltype(auto) map_vector(Args&&... args) noexcept
            {
                static constexpr const auto dim = VariableTypeList<Args...>::length;
                static constexpr const auto to_dim = VariableTypeList<Args...>::template count<map_index::MapPlaceHolder>;
                return map_index::MapVector<dim, to_dim>{ std::forward<MapIndex>(args)... };
            }
        };
    };
};
