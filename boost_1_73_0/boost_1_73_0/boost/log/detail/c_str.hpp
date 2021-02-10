/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   c_str.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * This header is the Boost.Log library implementation, see the library documentation
 * at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_C_STR_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_C_STR_HPP_INCLUDED_

#include <string>
#include <boost/core/enable_if.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/is_character_type.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

template< typename T >
inline typename boost::enable_if_c< is_character_type< T >::value, const T* >::type c_str(const T* str) BOOST_NOEXCEPT
{
    return str;
}

template< typename T, typename TraitsT, typename AllocatorT >
inline typename boost::enable_if_c< is_character_type< T >::value, const T* >::type c_str(std::basic_string< T, TraitsT, AllocatorT > const& str) BOOST_NOEXCEPT
{
    return str.c_str();
}

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_C_STR_HPP_INCLUDED_

/* c_str.hpp
R1wh8bvx13lc4h0M/Y6jWx3XhnZuB/995W31aXCIrlMX+uVourNEFb+Jq/MTA+ztoBrwQo1/s3yO0zSPGiRUcpg7XW0QV2AXJmx6E5J1gCs6Xcc40cnp8S+/0rOby15O+MXwdUChiFQA5zaEUxaK4ARYg5m41RHRffRphLJQdy3JeEcZ04AJnpz4u/g2uqRWvSXxJPacbVsAQNJ27bh+9Y+LN1xiYNTg040M+TRvYCIY8nirdmC/LVdJUUh2mOM1lcS32arvGicHWp3Wv3bOmWoj+rh3zgFqzdcj+5a96fwS4P59eNg9XGd//aVvhv4237BtQ+l6gXaZ7DR42d3vnB3Orx819HBI3Fydx3753vqd7zOJChMkQdDXiF+3VQ/qOQdvrvXhnmd5DqL8V178KvVg3H6TjSjG2u7hAewzsEdgjJQh/mRz518Yczrd39vZevqvdW+1H8wuzOj9SYq79w/edPeOj14GB/tvjl/2Do725tfTs44QgZ4zfELAoMgk6clHkHR25BLl4aCHzl2TzsOwKBXnbAq/vjOFh51eHyhsTpyUNXR2d0myKA+mcvGqe94jobnWqoOodfoVrGGsWa3VeIHedD3a3kZb2O7KsomRAtByq+CeR5GIH9FBv/GCoLS8iRa6oCguLpjR
*/