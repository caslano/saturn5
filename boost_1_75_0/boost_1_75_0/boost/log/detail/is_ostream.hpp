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
GfmGwUjjKC1ju6qAlyejjR9fz+CaCoPZoGF2WAyXgzb69gaGW7BQV7GYw+OngH7pRAa3qCpKDaVzAT86GWeMhTEMbijVlwn8mjYJPHJAZ6pzrxJtoNieBltvfvcHs8MfsMEpSsMa4KuHsDhj+iDTLRpSJTpCgKcTc4HznifkKTY1wy09D7J1fJMgNkOisPVRFsrU+auAYC0F+B4F8rzkDarJMhMJldPO9ALUo5DZRO4/hnqgPIC1pkP2XzhD0EWZFqC2etnaEnh8K30U2balCz7krHktG+OjrUbrMpi9chhbd7/4jKoeQwonq3zXna2dkhB/4QThCJrJl11TUe5LB8AeRCJCeJ0y0KYJvwCEuAkjEXfGAY3VhaoEzuqA006A/EzcJ0UAju+xx5MBlXwO4yQANyoQv8MqJQp4B5ML9iThjJO1B/zgZFBeT1JuN3aVg4IY8yFO83lo068foLPekq6Gnaz+06FbrHk7jNkno2HOQPq3SmvDpGe+eHKZbtXM9np5+XAOZmEOI0FbmcP0AUz/Zi8V41wGMnwb0+2sfbriUK70WLTFc7M9BmyM4wISb/8MzGvkA3cNE9jCPn4+4n5wcw1PjyNZC/z+4MJvgtJ3M+gbrX4/LTszMgduqxwy9dEbUW7xftSeBMCahzU4uaUik9M54FPbGramoRGRVsbk/8g/CGmZoGZr7GzEXXEfXSsxGHwMnaD60ihl
*/