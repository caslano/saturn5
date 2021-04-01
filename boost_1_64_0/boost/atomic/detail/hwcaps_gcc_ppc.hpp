/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/hwcaps_gcc_ppc.hpp
 *
 * This header defines hardware capabilities macros for PowerPC
 */

#ifndef BOOST_ATOMIC_DETAIL_HWCAPS_GCC_PPC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_HWCAPS_GCC_PPC_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(__POWERPC__) || defined(__PPC__)

#if defined(_ARCH_PWR8)
// Power8 and later architectures have 8 and 16-bit instructions
#define BOOST_ATOMIC_DETAIL_PPC_HAS_LBARX_STBCX
#define BOOST_ATOMIC_DETAIL_PPC_HAS_LHARX_STHCX
#endif

#if defined(__powerpc64__) || defined(__PPC64__)
// Power7 and later architectures in 64-bit mode have 64-bit instructions
#define BOOST_ATOMIC_DETAIL_PPC_HAS_LDARX_STDCX
#if defined(_ARCH_PWR8)
// Power8 also has 128-bit instructions
#define BOOST_ATOMIC_DETAIL_PPC_HAS_LQARX_STQCX
#endif
#endif

#endif // defined(__POWERPC__) || defined(__PPC__)

#endif // BOOST_ATOMIC_DETAIL_HWCAPS_GCC_PPC_HPP_INCLUDED_

/* hwcaps_gcc_ppc.hpp
O6VCmKBiaHTnYkFOv/ZTbVQXNovmer/BR+VJhdGrMOEpVzNByurkeXSkFmPY9cd/sDnqprEaoJGqHu1gwb5Bjza/Tby8ffyO4DTFRzhDLjmZEnr2VKqs2gq0Ak8yXxClw2LsKICdTr5e3pApsEcZR2jn297D7Nm/Fu2SPpmegAB3daYvo0089qVO7A53efRu3NYoEEjbekFgkuH55UTjVd41Hp7Ol2dBtuO8ckgsCzWTZyuKm+sUo3/EQ0bZn2s7fd4ECKtATvZBhBhMAHRGi9osfbse2jvUGw0xerNPd1FS6ksYHIciY2rRZkUdahK6IPV01qjahYdSTVAP/dtQjQ/cS8SA0vlJc8XPPi7XuTAFeLqZkqNH8u+9DFOI8m1BGoaZsFRjlACJ1/LAHADoC2SFWjvCUkl2yqx1ahAnemcKPcAPcsggXuldGsB+GhKeoSYIgzoceTgtvwDSN8FwZltyERJUtCmH0yem9SNGPJoOkKHYDHPDaJg5yjOx4Fl1agAc6WMRtOTfiiIfoML3ruaFoP09N0ZWeIr97TGyDF0NrxMNyARfGlYELQ==
*/