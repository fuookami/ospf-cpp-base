#pragma once

#include <ospf/basic_definition.hpp>

namespace ospf
{
    inline namespace meta_programming
    {
        enum class NamingSystem : u8
        {
            Underscore,                 // play_station
            Camelcase,                  // playStation
            Pascalcase,                 // PlayStation
            UpperUnderscore             // PLAY_STATION
        };

        static constexpr const auto default_naming_system = NamingSystem::Underscore;
    };
};
