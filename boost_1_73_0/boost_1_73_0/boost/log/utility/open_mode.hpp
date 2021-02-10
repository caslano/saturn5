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
zmbDyWIJ0y8wnCyj2Nfx5Iy2XpKZBdw2Fh2ZW5B1oySKnefbtSzpSl2oIBA63hjFHPrQDKpOkkjtYVuilbo0rMh7ayMF9AuKoX2TJn8ehbj1zJQl8yCUN56rPRhtNq8iwn+ohKhycJIkOWWHxppVLBirkXatR7sQ6Eq5UCbnamR0KVfQX7VPf4vGtiN4WeOaK+g7T4fiZWjrRxcrV+TeVubJvJ2VP/DRn95A5i3XjmoJfXqKeXFLCfWvS+FKsVhud0LyWR/axYMOdR5pWZJ0UdP5iH+9cpdH5E9QSwMECgAAAAgALWdKUqbc7/vJBwAA2RMAAB0ACQBjdXJsLW1hc3Rlci9zcmMvdG9vbF9zZGVjbHMuaFVUBQABtkgkYK1Y62/byBH/7r9iYH9gItBWkrZArzYOVWXlLJwsuZaMa4AAxIociXumdnncpWVd0/+9M7tL6mHrDLRhHiKpmd+8H6szuVAZLuBm0Lse3Cf9h/tRMptMRsn0etAfTZObkzP6Wir8A4pu5/tdJ9CBN6/E/Uvook/HcVfpXzG1r1MnyTfwf4jrK32+JaQLW5ZvyXt4m+UbvHMsSZByxfdJ8pagr6wb/9dlzq8J39IbYmPOvi43lVzmFt7138PHH374K5zDpw+fPsRwLZTEAqYW
*/