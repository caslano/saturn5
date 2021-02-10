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
B1RFCFfZ7op+SK37xHpdvj6bqPBPuSI5/EvxcQdBQicxCU0m8RahZfuY0sfVdMGdhH9kjw+oPRayfOZSW4yPVjSXb+RP753BLqzDOg7ruR9vGmJtZuuBvXfnpxuWw/w9+AlQSwMECgAAAAgALWdKUlkwNC49AwAAUQcAACIACQBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL2FsdHN2Yy5jVVQFAAG2SCRgrVRtb9s2EP6uX3FzMcAKVCvNvqyNG9Rw2iVoERuxuiJAAIEWTxFXmtRIyi9Y+t93J8mNs3bIBpRBTPF49zz3yvTox60IjuDJlbf/OS3aW4u5s39gEb6vnef30P2R1S3tT5Gk8GByn8fwtMk9DFuTvGcZ83eeP0V0y77xT8qWtzl/koTM2HJq651Td1WA4TSGFy9f/grP4eT45DiBc2EUalgENEt0dwmMZSt5U4ntduTxLAEMIPSoh8oq5cHbMmyEQ6BvrQo0HiUIDxJ94dSSDspAqBBKpRGms/nN5dVvCWwqVVQMsrMN+Mo2WkIl1ggOC1TrDqMWLoAtyZzApfKBAJugrBkRN0JAt/KMwfRCewtiLZQWSyISAaoQav8qTYvGafI+lbbwabEPf1SF1ddIbsiJldiBrQMEC43HBFgzgZWV
*/