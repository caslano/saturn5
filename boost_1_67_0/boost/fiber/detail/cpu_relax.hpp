
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
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
*/