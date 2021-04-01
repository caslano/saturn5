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
xzbh7fYuPewe7LWLlyvQNER08QmuMQx6hu7+XPz6aG0Zjxhk/gZO0oa4bAHLYnDHdv8wytun18PgA0cy9OfLl/FEvanR/McpOpLQ38MJP8hddZN90EUZI7bPZLiiF+bx95enPAZFWxm9rI8H7lVyMNc6VgXaRMRgLmOYnT03g3f8tf24jwxOqLnor2EjONLx6bjX5bWwEEnGwdhJoWEGfk/X8FKnjhsDrtGx5sW3T/Dwd94yUNE0KAEMyz1jVsLz+OVWSo8mNZBgVptBdN1bTo2daUA0kIwKcmIl2mmGLPb7YKT33p02/+NeUgJCnLIyxy2CMYzE0ZL9vdfHdb6YYJUtPxvJM6B8XW37wpzgSDG4bjzExB1UvyCUWGSEcp9jcO79vjYpfs9oQm+A42L6YTHbzK7lxw0IDG5U8MvId2DvkuLD40M609e/Na7+dv0P1xBylxhkS8U+JRDoPCSyiVqDfGDEfFdaH3LDI4cNb3c53cgd069ExI+bZfYAk1fVFoAUp2hQXD+zzLIb32m4w8g1HfDYopRi6ZBvNsBxBk51q/O6sEVoCLQkBQ==
*/