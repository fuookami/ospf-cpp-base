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
                    using Either = ospf::Either<dummy_index::DummyIndex, MapPlaceHolder>;

                private:
                    Either _either;
                };
            };
        };
    };
};
