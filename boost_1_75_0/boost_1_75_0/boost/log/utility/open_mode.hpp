/*
 *              Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   open_mode.hpp
 * \author Andrey Semashev
 * \date   01.01.2016
 *
 * The header defines resource opening modes.
 */

#ifndef BOOST_LOG_UTILITY_OPEN_MODE_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_OPEN_MODE_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace open_mode {

//! Create a new resource; fail if exists already
struct create_only_tag {} const create_only = create_only_tag();
//! Opens an existing resource; fail if not exist
struct open_only_tag {} const open_only = open_only_tag();
//! Creates a new resource or opens an existing one
struct open_or_create_tag {} const open_or_create = open_or_create_tag();

} // namespace open_mode

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_OPEN_MODE_HPP_INCLUDED_

/* open_mode.hpp
lc3c/Q8qjjAK6nwfRTSeUvVUVgyUvBaOzPkELqPG4UVUDwbS1kC+kGoCIxPadQcac+seo96TrlgPSltjrrQWRU7Tze/WikpcXKadCx6GqiI2myNyFptCNt2IwaAsyztDlpwbhFqXzSTB3czzliinJedFtwnz8S5d+tkWOg5Sru1/ULkNULfzTWKMJPWyc/FyhFAE8bfzWFQDgbld6zOPA98FQT5NnJjbopJuLPVCNwZgi9RbGpWDCwORCPH7nBazTtG3zCs3BzT47WTix40PSgqTO5fyAxcN9mU82/pk4ice7rc/oMSnRJnAgVyBGxp/0JQk5Y/Hk9SWIFllbv6M/SMyBOrfkgGrHgJXDq4iYW5FTY0lOzo6Gy6lfX19fgAPOn92TKr1PcqR0Jsk0yZ+pEZqxd19BGeX8vmNnUvqOTwT915M97msnsLU1znFEcUAzCnrnOB5Am6LmYxIcvkZnLejJdcBZuR4KnecN4xv/4hAocc+LuaJ8MnDIfKV5oZt84Is0rTOcXXo+OoBfj0yussR+XfU7b9IECarOSoLC/O/8Jzt74s1L843m3a7lzdWMC+uYoEEHd8OHntPBQ018EMB27d6WaHKI/0/pN9eT3VjHtpKZrZ6+Ep08qWjbKQ4y9t4BA1SPdJajmfvb8oFKSvqtzmcde/LmTTifUbjzXx3sOlmpt+zWUjOOZ3lu0065BX0CHEy6pwmTxcc
*/