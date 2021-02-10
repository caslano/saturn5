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
rgN9LX02FI426LvkxYXebOtDI52vKSnzIr6i2DNuz83BsH8+bF4Z7ARtEFqJGHk9rz7HrAQFUdsQXpXBVZxT1KH1bXX618ZJwXzP60FphfYurmnoosBh5QT7cPqct0ldUdJ3BdK7Rhsl3ifsed1Wnn3g9izAQXLoeuisg3fKMzpkYTdAsaaymo3DB5ozFIkUaJ+wQvtJ3521bOKSS5Nxi7iYZQG9Zx/k5Kc2ka2t/KAQa/JzJXT6iYmUrNUc5fidxIBkTsg2mAb0yUDFOQ3Raw3UTUsVAMGlHrf8E+VZ7aAyvALeUUFIBb8bEwC7FXCMLhn0FicUTZ9yOSFZaDSoksgUKI9HgEy1zFpdOWgnY6UiCMN122IQJP1UTM0PJ8jtPdJUy56HuDrZ/Ly7wzViCKgKsWjaVY4BEno3uYNKu6vus7Z+xrIP06UPB6QDQQm/ruEFzA8SxsW3AzcWRGoMlrCwUVbusPE98f9FktlCpwknfjE7p09AsRizjjnzgjj5ZTfirhfZ71LgiIU+9Kh7u2DFL4OE+EEBoek7ENoTFHNcjDvwFNjwvaqmH3h2kkoHnAeV9DtUEVJU7F73avR5oJfwkvuQCqp4VUIqFnv68FRChBSzIecq9GY3Hn2hKiOCb7jvWwv+mM5AnNDL
*/