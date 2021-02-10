/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   is_ostream.hpp
 * \author Andrey Semashev
 * \date   05.07.2015
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html. In this file
 *         internal configuration macros are defined.
 */

#ifndef BOOST_LOG_DETAIL_IS_OSTREAM_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_IS_OSTREAM_HPP_INCLUDED_

#include <iosfwd>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/has_left_shift.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/utility/formatting_ostream_fwd.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

template< typename T >
struct is_ostream
{
    static BOOST_CONSTEXPR_OR_CONST bool value = is_base_of< std::ios_base, T >::value && has_left_shift< T, int >::value;
};

template< typename CharT, typename TraitsT, typename AllocatorT >
struct is_ostream< basic_formatting_ostream< CharT, TraitsT, AllocatorT > >
{
    static BOOST_CONSTEXPR_OR_CONST bool value = true;
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_IS_OSTREAM_HPP_INCLUDED_

/* is_ostream.hpp
c8lOoYJhz4T+LSfjiBxXsMkR7Nnl+Vpo1hnxfbaMrAVYinytzYE6S2//iqolA2SLACmzJ59Prary7L45k946I28JSQ3mGfjxdfK4rCt5MMfwzanZ/U68iqCfsmgnY5+nzpysdNyfLXRvCO4S7s92R07BnMbtQYe5WZLCI0GdbfYXIUlwV72EIQYOM+FLLiN3jep7ZALX2vFVLPcRGG9Hz56tteTPMX4fgkjBDW8HYCPJsYGynDfYqzNknpnjKZnyGj6CQw8MkfordhCEKt7lYGoCGHog+YkveByHcXndrDUoCiNCdBZ3Yn9lIg3RloqBStqYJxQN3J4PQnTTagdTEeIzx084erpahkvHDG2s11jI7LywzpR6TTQBa0+w4c+IGeihXQMKUq/YMvNTj3IoLnoX3V2MjRqNi2gs4VpIbOLL34MsjSzHdcMsSIs2RVs+JItCdGCzHV3R8QTaT1EPpSBgwBkkpcVOZRxUj0cMlSzayEedcm13r9h7HPrHLeoQcaz1eYR0W4bwEQuZNyOuQTcc5m57XMz8XuUpwCxCeuAH0V/Do03j0Gedd2cglpx5mT3rxhA52iRAa2jYtt+20BpgGC1CZz+cMVxHa0FZw4YCFWLwqKTwCCi0L8Brb7U2CF6svGfhAQ+vumBN
*/