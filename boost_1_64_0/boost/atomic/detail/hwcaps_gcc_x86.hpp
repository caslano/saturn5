/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/hwcaps_gcc_x86.hpp
 *
 * This header defines hardware capabilities macros for x86
 */

#ifndef BOOST_ATOMIC_DETAIL_HWCAPS_GCC_X86_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_HWCAPS_GCC_X86_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(__GNUC__)

#if defined(__i386__) &&\
    (\
        defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8) ||\
        defined(__i586__) || defined(__i686__) || defined(__SSE__)\
    )
#define BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG8B 1
#endif

#if defined(__x86_64__) && defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_16)
#define BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B 1
#endif

#if defined(__x86_64__) || defined(__SSE2__)
// Use mfence only if SSE2 is available
#define BOOST_ATOMIC_DETAIL_X86_HAS_MFENCE 1
#endif

#else // defined(__GNUC__)

#if defined(__i386__) && !defined(BOOST_ATOMIC_NO_CMPXCHG8B)
#define BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG8B 1
#endif

#if defined(__x86_64__) && !defined(BOOST_ATOMIC_NO_CMPXCHG16B)
#define BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B 1
#endif

#if !defined(BOOST_ATOMIC_NO_MFENCE)
#define BOOST_ATOMIC_DETAIL_X86_HAS_MFENCE 1
#endif

#endif // defined(__GNUC__)

#endif // BOOST_ATOMIC_DETAIL_HWCAPS_GCC_X86_HPP_INCLUDED_

/* hwcaps_gcc_x86.hpp
9FcUrLb2cT+odNYE1KU4qUvvqvOTSHW00ZX608wsR9I6Qvq+/4KYXBsbut6ocS4O9SDLpR5k+5ej9JXjjpV6F5n/9K205dLAx/Fm33v2q18+mPnSD877Mjm1b79jkbbc+rblyjwMeS7wiwqch9FO2hg7wLNgIhwLO8L5MAmug53hBtgFPgLPhI/DZLgPdrPMczoKe8L3YC/4EUyBH8O+0vZSqu9b6p6p0tUaFku6Bki6BsLJ0gY3DZ4Di+BQuAoOk3QNh3fC8+BT0kb0vLQZvQhHwpfhKJmXNRZuDrMNp8k2voG38o36aOj2nGyPr02ncOvpbddZs/V/q21n+1b8IE5tPEe2NrydJ23b19fW4/kteYw7b1t48yeKt/nafNbzt7Xd58NVTevc9lO+LXT7zzPo9If972/8rbcDfbYt/LYgo4R9+0oibTqR3//W75v8/s8/Td//T1m+/7k81W+OjIufikxO4x3jWcs3Tn6BSo53LF3rpIDxG6Kf6jYemfP+ayM8ptyjXb+B4uFWpTNSuQt1GAkqjmyV+vy5ixca6ts4TdI2svb4svkEylpM6luwUvkbosfbZ8XXfpeMSgk9Ftf7bdE6ScaK1GMcbhokvRxX6dVjc0eqY2ZaI98m38a3yRD1bdL8nX1LGv9iynPPXfHUnnE/vetg5NukId8mGYZcp3COQ/9rjJrL7PtGiYdT5VtlYpjv7hMj/a8Nekf/b+x/3Rfpe61T3+vwyLt25Bf5RX6RX+QX+X1tv2/u+38pH5WnZ/7/jyzf//3l+/8TJBF5G5lsrq/6I+u8lKUFq2o/cwPWMkySvsHXlf4LRl/WSl+EPIFI24CE1c2I020Dyxbn6/BoH9A6XVV4k3AfUu7Dai79SuR5xOffl54k6VN9VekfNIZgYTFSiUhfqITdCd2ZsbwVqT7Iu1IgfMJkHebdW9dTlP5IaQcQm+R4tj6u06q+8QfIurZvyriL7yE9EPN8Nvles13lO+0E5qwZw9vWwTEO+dpbRO9s3Z7S9gmZi63X1PbouTMTtH5/vSdC9L/ZOxPwKqorAM+8l4SQRCQJhIQ1bGGHBEVQUcMiRpYaKypVMYkhmLCENAsgAgZwQXCJLSgqSrRY0LY2rUhpa9u02FattbTVulQrtVVp60Kttmjt8s/JeffNmzcvhGjr16/v6eXPnTn3zl3OvbOdORd58nTLy0txbTPkI9dd6Cryl9IORj70ct28104SmQslfq7JI0+O0ZRtbBbM++TBIj/B9MufMniHld72vdXDhD9mtPstz8z0qOcrtJFum2R8I0s7aP+ZbVJX7T/dZuoT4X/4gH7Xf6pNHnA8/DT91Cxlb9TOdT6os/Rbcu83WyqL/mXpu/dvS7y/nc2RphH8xkWWttE+ka2y+vLvWQTtT80z229MmD5ExqyPMJf4wxIfbPezeHdACD9Hq6uk5eR52UZirW3lNX7gnff8JdJiYV8BlQ86MoXGHsHYAqi+vCl5vMq81NWKyEd6I2ybc6nkc06ETQE1CdscyP7hGsc/t8R7UCdXnqbnws8OF4nciWjfnPTnGGsn0o8PMtaDjeuSAsG+SQlpwa6px6UOTR2Fe/DkLu3poHcMmrINlGOc7S2bV9/NmDtN9jfpt9zYR+j3OK8MbXsm+Sq8JyPsI6D4KHpfA7d7vtdbGWM+avTOR5rHRjN2RAcidP9J/W55IWUfppyL7ud/1av7dVLn5nzV/bDtC7K6XoDq4HyJn2wX2Amxzwcm3UjjW+Uiiefay6xtus22VrWID3I0PCjPgKlL7PFg8pwgsrxDj1qbohqZUpE5yR5pJ1u90Z2n6aTkZJ550U9piflpwXV2WiLbQt8cPpg=
*/