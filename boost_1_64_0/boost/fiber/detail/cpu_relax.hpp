
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
ga4ifTZHHX68pBsE0szJYjSylROGieevxpUtTDfbn93b04guR1FVxGMI5X5wqS8makxyJJ9b/EUT27JVrVU/V6Jr3hiscUXXE9/FCfDlu0Lyha9SYcXqQVeNyGIUqeD4M5b47OC/Y6B6cB/sLeilj1iMwjBpdSouln7fEgsWWac70hr+4x0/0ULgUtgVhAcJ+VB+cEGuS7H0DTFBYAhadbLl2nS9U5HGwtleLA0qXAsahdJ/D7jnNGBcaot0vuMYwdZCERLNhBKN+3wHxhU8gJK/+7oQJEb7+43IfpK41d3xMPgN+AkIJNjwB8RZtcbJWix3l49IRShytZFcbTqFLfDI/d//KEHB5cw1KLU3K57FHkJ6ImTKH0t+f7Sz5FZ7U1JzuaezdtFyoRjpp2T8FEE+4bLpaYvGy5rcrRfjgs6CHzj7SYz9WPYWxq4ot2HxcGcNbE9y3nF133FCYKZNWojBwd8LOI/5zLXQSE6GRnISbyRvO8Ymon9V0KmsqCTHvvqk9aVBZIxmTJUmy3cqOiO2XNKl4Nf1JcfLNgalk+0zrU9UVvMp2tF1wORUTTI53SFVtSYvLAv/0Mw6fHsz3K8wcRcUhvvJrC6ydS4aTos0Dos07Rqc61AU6bmjrEhRhDhfr4u134Tb4ymBCUjgIUogTkmgFSdA9/nKi+S8IuzWlhaZuD4iYoepxT1YI0jgPVY2WZ9lrm9jNKoLIXPoT/MtAclSggdh0vz4FyivqoYkZy76tMedOd1LcuIbz4n48XSWO/ETci+drSl+MErQm6DZrDQ4swkIzZxpUAjMjLvOJeD3s7hkN5l7WxbbjXBIysTkxC+2XEV2XDoJ5XKnWcAfCMTPo0B2bMMSOAJxBauHoz2vDjQesXpYfMw5GYsu9a2mkNS8/CMDcoDQZXztnSyZGqlR+i+tfV2Kx539wQW0K7/j9icFoOXWxiZZmy9Yk4b1NUbyVZeCeO4JkisMnERllMKceo8tko1tMYS+NetMDyJ48VN8I6GJoytEJKS6hJ9ZollBBYNlKFh/YgHE2dARWg1n7CR/yLG8ziU4sVSIlb3/VVDZ+0Flz+WV/daDdJRwHysXrWT+ZPTTiWSFyTdh8mto8snK5NUHaPJgIz/t04QyCatNSA7rQLq93hUWMuFp4OIj1TqdSwdHELwc/Q9jJU/ANhzquCQieIlhQxJuAhK5CUi/sz1xLEhkMOoHpygNdMfDIGlhIJbVpcccN3MGaN4udSndFZ7SEidNqE5AqyEtLrfRUo36dy+LeW5/r3TUbH+tivaXt8hWqUZM47OtAOmtzqWO+QdZYwAwgb3xaKcHkfXjqj1AiKd+rbxmQ16FijjnCq6I07kivrCfNVo5Mob802IQYt5CwyVANtwdl2T/8UI121PzCElVRTQdk2JzsELeHFjtPwfIa3cUSSC33SgUqNWQJBnKa5+9Wd7+QDbfsRx4IwIFhkTAoUTChsHs4ul0bI0G/+BKbAGfTZ5BF66l8sPvR2R8d0W+Ja0fKmUfCRl6YvzkJip9fgATO7UdeDveiXxIa4onKSC1s5pbm8AsQSpE9/+vNC6e60N9e836YGMGzByaiefhePUgeru4iqIUz+Vvs39uluvN18wEKuqXjdUtqq/kBXuX0hf61oL7KAPbRMjHM4NN/AiUyjsYY+VcMR3lPQRul6GJsDc7jTbNpV9h89qvsFfVMITYr4j9R/oVntvzB0/VbM8T6fwc4ldskLXfifYGfnKkLsJHSOkqRkrAXfvdqQhP5cFUGPY3E+jZQpqAj2fYWwuOfiLiHcO+IPqQnB0BTOB5skmQdHvld5ibSzOWqNaMTSt0conoJWAzlvAPNWMu01E=
*/