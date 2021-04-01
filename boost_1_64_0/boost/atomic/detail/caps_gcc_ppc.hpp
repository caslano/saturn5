/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_gcc_ppc.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_GCC_PPC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_GCC_PPC_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/hwcaps_gcc_ppc.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#define BOOST_ATOMIC_INT8_LOCK_FREE 2
#define BOOST_ATOMIC_INT16_LOCK_FREE 2
#define BOOST_ATOMIC_INT32_LOCK_FREE 2
#if defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LDARX_STDCX)
#define BOOST_ATOMIC_INT64_LOCK_FREE 2
#endif
#define BOOST_ATOMIC_POINTER_LOCK_FREE 2

#define BOOST_ATOMIC_THREAD_FENCE 2
#define BOOST_ATOMIC_SIGNAL_FENCE 2

#endif // BOOST_ATOMIC_DETAIL_CAPS_GCC_PPC_HPP_INCLUDED_

/* caps_gcc_ppc.hpp
Km7diBwccCP6BV/vKJULmhRDqaEgkQlR7ZcmwLqHUKSPGEQEmRD2DJOJAbeFxQlztegUTcJsGX+tuQvWAwgD1c4O/xhyeFOm8XG696oMlXz+EKgGqybo6eD+xtnuKZckLHb3IrHU01rbMwD0Ar6++fpAj/BP0t6rqCqu8R+1XRbSV0FCUJta06cblW02iAx5gvxdlVPvSerndn8T57XidPi/a+n/nAkCzjKiITPrajhDWS4cjL/1LuYoSoZBUuDXAxViqT5AAnrevk+01aGNFpNHOijGe4Cyd/3GEYt5vQEKHH74yLNGJiVs1A83sHlaEb11tgrfjOU+Ety7cYBSNBtB7dzxKPhi2zrya+GmRfG/MFBtClG/nSjMbKe8qzNux5mvUi74+UjaKShsNE0Q/xSVg2uD035gxIGgueemUf6tCDT4yeG40WoBEAlrr1vBjF8omLwU8ON585IM9GoUvibGq5Nvbc7KuXD09wrgMhedactqUDjHOefR8QSGUv/PJf9ap0h4dTzC9OE/WmfGlB6CRsOyZk/rnyshfaUkPNqc8Ke+xe+yMeQC7w==
*/