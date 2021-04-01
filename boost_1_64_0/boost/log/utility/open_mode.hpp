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
q5yXHzEvi0O6440qp2nduLZH56+DnKq1oggfArTxvoRa5yS972tEHl0D0/QCzi7U0ifCsHP3HkVMXoiErq6lkdoWftY/ttdjl0U574mEOfYf28Nj6TF//osM2J5Vlq1YXxxj46Fbqpxhzm459x9DMjdaB5gJrTuMR2R5qn9owLkvLkJ3h2to5RCbfL0LOHiPK5za1pxjU4i0POQiFgc9KHbd4pZ3fBzsteDe7cryOPyMGYN/3yqUP06a9cBM3R7HoYrrVwIXrwkOfv7Qebj9CL/Dg2fEtmoUEkv6zUFZQKSBx/iF6ZC3dL7C0G7JHX4ICb/xA7MBNfdt/T4WAeI9wno2GqnvMsHkQj1ncmztAJseC2Gkc9JHD81L2OF774U4SSie3PvoloEYU7ZWbJSuRw5Q3DB/x6cN/MhXkiem5RIY8ow4rkI3oTWheLDrkasLtdrPgwwynhB2cq4rHy6iRvAVh7QfPU6PoBLfk4lqDgvGW39S5YwnSVhQJzDtXo+a0IlT7NqCane9MEpXLl36YgQGFgRK3ia5dykYYd0LYzSXTsPBWT9VlIuDCw==
*/