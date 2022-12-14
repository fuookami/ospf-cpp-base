#include "system_info.hpp"
#include "literal_constant.hpp"
#include <algorithm>
#include <cstdint>

#ifdef OPF_SUPPORT_CPU_INFO
#ifdef BOOST_MSVC
#if BOOST_MSVC > 1400
#include <Intrin.h>
#include <windows.h>
#endif
#elif defined(BOOST_GCC) || defined(BOOST_CLANG)
#include <cpuid.h>
#include <unistd.h>
#endif
#endif

namespace ospf::detail
{
#ifdef OPF_SUPPORT_CPU_INFO
    void get_cpu_id_ex(u32 cpu_info[4], i32 info_type, i32 ecx_value) noexcept
    {
#ifndef OSPF_OS_UNKNOWN
#ifdef BOOST_MSVC
#if defined(_WIN64) || _MSC_VER >= 1600
        __cpuidex(reinterpret_cast<i32*>(cpu_info), info_type, ecx_value);
#else
        if (cpu_info != 0)
        {
            _asm {
                mov edi, cpu_info;
                mov eax, info_type;
                mov ecx, ecx_value;
                cpuid;
                mov[edi], eax;
                mov[edi + 4], ebx;
                mov[edi + 8], ecx;
                mov[edi + 12], edx;
            }
        }

#endif
#elif defined(BOOST_GCC) || defined(BOOST_CLANG)
        __cpuid_count(info_type, ecx_value, cpu_info[0], cpu_info[1], cpu_info[2], cpu_info[3]);
#endif
#endif
    }

    void get_cpu_id(u32 cpu_info[4], i32 info_type) noexcept
    {
#ifndef OSPF_OS_UNKNOWN
#ifdef BOOST_MSVC
#if _MSC_VER >= 1400
        __cpuid(reinterpret_cast<i32*>(cpu_info), info_type);
#else
        get_cpu_id_ex(cpu_info, info_type, 0);
#endif
#elif defined(BOOST_GCC) || defined(BOOST_CLANG)
        __cpuid(info_type, cpu_info[0], cpu_info[1], cpu_info[2], cpu_info[3]);
#endif
#endif
    }

    const CPUInfo::ID get_cpu_id(const u32 cpu_info[4]) noexcept
    {
        CPUInfo::ID cpu_id;
        cpu_id[0] = static_cast<ubyte>(0xFF & (cpu_info[3] >> 24));
        cpu_id[1] = static_cast<ubyte>(0xFF & (cpu_info[3] >> 16));
        cpu_id[2] = static_cast<ubyte>(0xFF & (cpu_info[3] >> 8));
        cpu_id[3] = static_cast<ubyte>(0xFF & (cpu_info[3]));

        cpu_id[4] = static_cast<ubyte>(0xFF & (cpu_info[0] >> 24));
        cpu_id[5] = static_cast<ubyte>(0xFF & (cpu_info[0] >> 16));
        cpu_id[6] = static_cast<ubyte>(0xFF & (cpu_info[0] >> 8));
        cpu_id[7] = static_cast<ubyte>(0xFF & (cpu_info[0]));
        return cpu_id;
    }

    const usize get_cpu_core_number(void) noexcept
    {
        static usize num = 0_uz;
        if (num != 0_uz)
        {
            return num;
        }
#ifdef BOOST_MSVC
        SYSTEM_INFO si;
        GetSystemInfo(&si);
        num = si.dwNumberOfProcessors;
#elif defined(BOOST_GCC) || defined(BOOST_CLANG)
        num = sysconf(_SC_NPROCESSORS_CONF);
#endif
        return num;
    }

    const CPUInfo::ID get_cpu_id(void) noexcept
    {
#ifndef OSPF_OS_UNKNOWN
        u32 cpu_info[4];
        get_cpu_id(cpu_info, 1);
        return get_cpu_id(cpu_info);
#else
        return { static_cast<ubyte>(0) };
#endif
    }

    const CPUInfo get_cpu_info(void) noexcept
    {
        return { get_cpu_core_number(), get_cpu_id() };
    }
#else
    const CPUInfo get_cpu_info(void) noexcept
    {
        return { 1_uz, { static_cast<ubyte>(0xFF) } };
    }
#endif
};
