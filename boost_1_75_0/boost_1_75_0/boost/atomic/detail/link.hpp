/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2012 Hartmut Kaiser
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/config.hpp
 *
 * This header defines macros for linking with compiled library of Boost.Atomic
 */

#ifndef BOOST_ATOMIC_DETAIL_LINK_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_LINK_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

///////////////////////////////////////////////////////////////////////////////
//  Set up dll import/export options
#if (defined(BOOST_ATOMIC_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)) && \
    !defined(BOOST_ATOMIC_STATIC_LINK)

#if defined(BOOST_ATOMIC_SOURCE)
#define BOOST_ATOMIC_DECL BOOST_SYMBOL_EXPORT
#define BOOST_ATOMIC_BUILD_DLL
#else
#define BOOST_ATOMIC_DECL BOOST_SYMBOL_IMPORT
#endif

#endif // building a shared library

#ifndef BOOST_ATOMIC_DECL
#define BOOST_ATOMIC_DECL
#endif

///////////////////////////////////////////////////////////////////////////////
//  Auto library naming
#if !defined(BOOST_ATOMIC_SOURCE) && !defined(BOOST_ALL_NO_LIB) && \
    !defined(BOOST_ATOMIC_NO_LIB)

#define BOOST_LIB_NAME boost_atomic

// tell the auto-link code to select a dll when required:
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_ATOMIC_DYN_LINK)
#define BOOST_DYN_LINK
#endif

#include <boost/config/auto_link.hpp>

#endif  // auto-linking disabled

#endif

/* link.hpp
JyjFFUFiWu0/2j6GKnbASBc0CtaQjdnOaQzQgbPdw4qGAJh0c2nmOM11UhTXn2Yw3mXjs/q3ejjW5tiV5N8IZZTJr2EkahsE746eh/w5Ayj6o9+UYz7jvSj5qcdYjlZJ+YIep5L1xW8pEPH58nwAMlLCm6xNiBGMexDnTVvnLAelFCbgk82UgtJ7s4qKBD0RHuQ3Dfkcf0lf5CQtXzCJU6cl63OkmbnfbD5MLY7uS03N6SuhTaXJcciptPd8uyo7IpFEVHXttDhj8IM4dRpS+itVm5HOsP4GY0auj+CgVZLQIeq6QNtJu3a642RUymSFrtJD5cNAFSKX2ZG3PGNRAAy4o36o/+Jh7xnJO4EEbaBRVjtlCm6WJUG49DwJkXYjvEi7Y96xUSPv3zLR3kHDFtShRqJJtW9BRqvUZgU8sUO2XxI3C4S6W9o2/lKWZMmiljusgnYcYZhrY4VeX1hSKlYrfhL7Kf00bZlJYco8ceA1J4EVV5DIn+QKvI7fDfK4SZmlOOXCkoFntRPeqUYkb91TSt284slrunnlTUlmmQMTrWS5NGQQ36oNTVSxhgasFIfD9pddG6IsQyZ+mMcOHaCrzVWGqkZqmMMNbA9KNoZifqs+fIxitY1ijHnjcKf1y5Ja8f40XIJ/2UpY1tVTGVMm/PPKmmVP2dTx1KAcwc7e8MZWP53TGmp5x5z/mLa3gGVGITX6M1lkgiw/
*/