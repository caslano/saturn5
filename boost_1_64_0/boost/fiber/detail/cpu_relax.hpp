
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
kVFABVz4tCmemQGjiR+rmmGIjFnFuYDuLJNdrjzl/EvdyLBnrqM967Eo8oBAWedfnbL8+2jKMwC1p0+dFn7ZcbnhY/DKcU4LNEJf9AbKDlt8RJiDqpDZJvJh33NdI2wigWvMkAWMVtfNuMXdFqmOnWivSNq8PzGNxbsxidCKwh6uCFUF+zBjPLe0Kb8AP9WrSt19V4SJomR6mvk/LJwxSw3HFtjMuA765RcUI3VzuUfB2EqITi9f+Hl/E5Ry9pYMmTy7/JvhyH9HIuJMO3iTLByyZ/FiLEFN3IY+B8uxX9qSus+AjRZNgbfisLISXvcl+6oSN7c2gNQTtu/nipLKu7593N9gLcKEHUvq96QyYFGiJCaRcAL6eT9iOBosHOsjOnKrfYePu3HQsHQYcrqqFynVkZHcjlETy6B6u0Rt4LeF7hVaWFAik45q6/FWUiZtO3qdB4PyjfLOWeXOmrxbwh9szhCHOvuhQL5s/PoFjsoRVENXYoD5gj09yR9XxTaTW/1D+227Aiv/iyi7rgp1JBUXuuYCIM9L2RdjghoNhtdHb6BZCnqxbZdNvg==
*/