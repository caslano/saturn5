
//          Copyright Oliver Kowalke 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_CPU_RELAX_H
#define BOOST_FIBERS_DETAIL_CPU_RELAX_H

#include <chrono>
#include <thread>

#include <boost/config.hpp>
#include <boost/predef.h> 

#include <boost/fiber/detail/config.hpp>

#if BOOST_COMP_MSVC || BOOST_COMP_MSVC_EMULATED
# include <windows.h>
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

#if BOOST_ARCH_ARM
# if BOOST_COMP_MSVC
#  define cpu_relax() YieldProcessor();
# elif (defined(__ARM_ARCH_6K__) || \
        defined(__ARM_ARCH_6Z__) || \
        defined(__ARM_ARCH_6ZK__) || \
        defined(__ARM_ARCH_6T2__) || \
        defined(__ARM_ARCH_7__) || \
        defined(__ARM_ARCH_7A__) || \
        defined(__ARM_ARCH_7R__) || \
        defined(__ARM_ARCH_7M__) || \
        defined(__ARM_ARCH_7S__) || \
        defined(__ARM_ARCH_8A__) || \
        defined(__aarch64__))
// http://groups.google.com/a/chromium.org/forum/#!msg/chromium-dev/YGVrZbxYOlU/Vpgy__zeBQAJ
// mnemonic 'yield' is supported from ARMv6k onwards
#  define cpu_relax() asm volatile ("yield" ::: "memory");
# else
#  define cpu_relax() asm volatile ("nop" ::: "memory");
# endif
#elif BOOST_ARCH_MIPS && (__mips_isa_rev > 1)
# define cpu_relax() asm volatile ("pause" ::: "memory");
#elif BOOST_ARCH_PPC
// http://code.metager.de/source/xref/gnu/glibc/sysdeps/powerpc/sys/platform/ppc.h
// http://stackoverflow.com/questions/5425506/equivalent-of-x86-pause-instruction-for-ppc
// mnemonic 'or' shared resource hints
// or 27, 27, 27 This form of 'or' provides a hint that performance
//               will probably be imrpoved if shared resources dedicated
//               to the executing processor are released for use by other
//               processors
// extended mnemonics (available with POWER7)
// yield   ==   or 27, 27, 27
# define cpu_relax() asm volatile ("or 27,27,27" ::: "memory");
#elif BOOST_ARCH_X86
# if BOOST_COMP_MSVC || BOOST_COMP_MSVC_EMULATED
#  define cpu_relax() YieldProcessor();
# else
#  define cpu_relax() asm volatile ("pause" ::: "memory");
# endif
#else
# define cpu_relax() { \
   static constexpr std::chrono::microseconds us0{ 0 }; \
   std::this_thread::sleep_for( us0); \
  }
#endif

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_DETAIL_CPU_RELAX_H

/* cpu_relax.hpp
GdPtBATQF++f7EnET3AyOyMU4Sz/TWIUcpTHgHtyuF8kjCmPT2KcwkPDdLqLpcO0+D+4w6okSYRcmZiYw8+/2zAw2osE/sJJDCHBSkkl8k+HXvDCfWUKB5TKNnuaX3ChYrp66V4WQrh5M2+WiOGIIQSymxFR2k22A0Dm4S2wSlyPFD0JCcx8/DJYK+OvsVcPuZls/BWSqjMnTHzEvnqPteJ+j5fgzfgVWpuC9KdCpT94Tdu21F0pwAqEv3YbPy0D75+aWXYH0BY4LP9zEiGnIYicDqk6ia9OxfPC1MRUB3g04nowDGiSOIvkdlCgXIbNEMnvxwNEi96uhB0itg0i268vcYuGOtEieehrgLr2E+rahzmZifl2d2foXD56q8vls7VukJ6TKcE3XIhFg/R6DXMGaRp4MwZxpETfZIks9lHmIA4xm3kPO6v5oqZ+g/RABRhGg1UV+1Tp86okH+yTw+utSsaKxusQCkgumtYCbJWBY8hmN1uY6JwgC5OZTQuzW+ILA7x6zBTdqmjHOGvKPp9VaNUumbzm65PpHIcLKJbgnQp1CYrmqzibIbmtfyCSAwSiC6CAmObHsdxP0y30fIg/l01AnLV/LGKwggmUms+fU3mpnAlw5qpTsibQ2cs2QbvLMt6qOTvNeU0V+bADx5nBx8vAXMdjzn1NiGO6T4ZJQBdDDANJ1xEGygIMFHodx0C5aLgCOggo6WHo
*/