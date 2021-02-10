
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
VF9QUk9YWV9TU0xLRVkuM1VUBQABtkgkYK1VbW+cRhD+zq8YkS/niHBxoiZNm0YlF1KffAZ0cHFOOgntwWK24XYRu9g+Nf3vnVm4+qVW40jBOgO7+8zLM88M/saFpz/scnwyB9+8cvvL8cL7AZR06k9emIcBef4Vhj8EbvD+CFdTuEF9zY/gUaivMLGofPT1lp7z/BHuNhQk/ZsSeJPTI64MyBE/U+2+Exe1gcnsCI7fvPkZnsGL58evPfjApOANpIbLLe8uPHhb2pXfa3Z97Wv+zgNugDX+HYNZLTRoVZkr1nHA50YUXGpeAtNQcl10YosvQoKpOVSi4TCLk/U8+sODq1oU9Whnr3rQteqbEmp2yaHjBReXg5mWdQZUhRbQfim0QZu9EUr66J6D4d1Oj2YoCNZoBeySiYZt0R0zUBvT6l+m06LvGsxkWqpCT4sDFX5tdveyWmM0O7YH1RowCnrNPaDzHuxUKSq6I0W42PbbRujauwkLHcpyqjrQvGlGcwgVXA8pcEhHtjw6CS1GLwzdtJKavF3VanfnINI6Gqr6TqI7pAXPlQqJ96CXJe/seUvEwcvIsqX8GyW7ib0EJTEqcIMU5qkLW6aF9uB8np3EqwzOg+UyiLI1xB8hiNajvdN59AG1IdBrB/y6
*/