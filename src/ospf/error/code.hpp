#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/concepts.hpp>
#include <ospf/literal_constant.hpp>
#include <magic_enum.hpp>
#include <format>

namespace ospf
{
    inline namespace error
    {
        enum class OSPFErrCode : u64
        {
            None = 0x00_u64,

            NotAFile = 0x100_u64,
            NotADirectory = 0x101_u64,
            FileNotFound = 0x102_u64,
            DirectoryUnusable = 0x103_u64,
            FileExtensionNotMatched = 0x104_u64,
            DataNotFound = 0x105_u64,
            DataEmpty = 0x106_u64,
            EnumVisitorEmpty = 0x107_u64,
            UniqueBoxLocked = 0x108_u64,
            UniqueRefLocked = 0x109_u64,
            SerializationFail = 0x10a_u64,
            DeserializationFail = 0x10b_u64,

            LackOfPipelines = 0x1000_u64,
            SolverNotFound = 0x1001_u64,
            OREngineEnvironmentLost = 0x1002_u64,
            OREngineConnectionOvertime = 0x1003_u64,
            OREngineModelingException = 0x1004_u64,
            OREngineSolvingException = 0x1005_u64,
            OREngineTerminated = 0x1006_u64,
            ORModelNoSolution = 0x1007_u64,
            ORModelUnbounded = 0x1008_u64,
            ORSolutionInvalid = 0x1009_u64,

            ApplicationFail = 0x10000_u64,
            ApplicationError = 0x10001_u64,
            ApplicationException = 0x10002_u64,
            ApplicationStop = 0x10003_u64,

            Other = ((std::numeric_limits<u64>::max)()) - 1,
            Unknown = ((std::numeric_limits<u64>::max)())
        };
    };
};

template<class CharT>
struct std::formatter<ospf::OSPFErrCode, CharT>: std::formatter<std::string_view, CharT> {
    template<class FormatContext>
    auto format(const ospf::OSPFErrCode code, FormatContext& fc) {
        return std::formatter<std::string_view, CharT>::format(magic_enum::enum_name<ospf::OSPFErrCode>(code), fc);
    }
};

template<>
struct ospf::DefaultValue<ospf::OSPFErrCode>
{
    static constexpr const OSPFErrCode value = OSPFErrCode::None;
};
