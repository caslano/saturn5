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
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
*/