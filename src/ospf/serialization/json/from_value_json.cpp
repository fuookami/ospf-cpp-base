#include <ospf/serialization/json/from_value.hpp>

namespace ospf::serialization::json
{
    std::optional<bool> to_bool(const rapidjson::Value& value) noexcept
    {
        if (!value.IsBool())
        {
            return std::nullopt;
        }
        return value.GetBool();
    }

    std::optional<u8> to_u8(const rapidjson::Value& value) noexcept
    {
        if (!value.IsUint())
        {
            return std::nullopt;
        }
        return static_cast<u8>(value.GetUint());
    }

    std::optional<i8> to_i8(const rapidjson::Value& value) noexcept
    {
        if (!value.IsInt())
        {
            return std::nullopt;
        }
        return static_cast<i8>(value.GetInt());
    }

    std::optional<u16> to_u16(const rapidjson::Value& value) noexcept
    {
        if (!value.IsUint())
        {
            return std::nullopt;
        }
        return static_cast<u16>(value.GetUint());
    }

    std::optional<i16> to_i16(const rapidjson::Value& value) noexcept
    {
        if (!value.IsInt())
        {
            return std::nullopt;
        }
        return static_cast<i16>(value.GetInt());
    }

    std::optional<u32> to_u32(const rapidjson::Value& value) noexcept
    {
        if (!value.IsUint())
        {
            return std::nullopt;
        }
        return value.GetUint();
    }

    std::optional<i32> to_i32(const rapidjson::Value& value) noexcept
    {
        if (!value.IsInt())
        {
            return std::nullopt;
        }
        return value.GetInt();
    }

    std::optional<u64> to_u64(const rapidjson::Value& value) noexcept
    {
        if (!value.IsUint64())
        {
            return std::nullopt;
        }
        return value.GetUint64();
    }

    std::optional<i64> to_i64(const rapidjson::Value& value) noexcept
    {
        if (!value.IsInt64())
        {
            return std::nullopt;
        }
        return value.GetInt64();
    }

    std::optional<f32> to_f32(const rapidjson::Value& value) noexcept
    {
        if (!value.IsLosslessFloat())
        {
            return std::nullopt;
        }
        return value.GetFloat();
    }

    std::optional<f64> to_f64(const rapidjson::Value& value) noexcept
    {
        if (!value.IsLosslessDouble())
        {
            return std::nullopt;
        }
        return value.GetDouble();
    }

    std::optional<std::string> to_string(const rapidjson::Value& value) noexcept
    {
        if (!value.IsString())
        {
            return std::nullopt;
        }
        return std::string{ value.GetString() };
    }
};
