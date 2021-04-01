/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   native_typeof.hpp
 * \author Andrey Semashev
 * \date   08.03.2009
 *
 * This header is the Boost.Log library implementation, see the library documentation
 * at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_NATIVE_TYPEOF_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_NATIVE_TYPEOF_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if !defined(BOOST_NO_CXX11_DECLTYPE)

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

template< typename T >
T get_root_type(T const&);

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#define BOOST_LOG_TYPEOF(x) decltype(::boost::log::aux::get_root_type(x))

#elif defined(__COMO__) && defined(__GNUG__)

#define BOOST_LOG_TYPEOF(x) typeof(x)

#elif defined(__GNUC__) || defined(__MWERKS__)

#define BOOST_LOG_TYPEOF(x) __typeof__(x)

#endif


#if !defined(BOOST_NO_CXX11_AUTO_DECLARATIONS)
#define BOOST_LOG_AUTO(var, expr) auto var = (expr)
#endif

#if !defined(BOOST_LOG_AUTO) && defined(BOOST_LOG_TYPEOF)
#define BOOST_LOG_AUTO(var, expr) BOOST_LOG_TYPEOF((expr)) var = (expr)
#endif

#endif // BOOST_LOG_DETAIL_NATIVE_TYPEOF_HPP_INCLUDED_

/* native_typeof.hpp
9N5Bs+g1mdi7VQb2D9/qMI0hxmldn5D7SJZ3eVjCYMe2gUdAcE8ZdmE+jblCFuqT0C1iYIKnzlPcMrLd3IvQbReZRxCxcSAmwO1Z6VJ96wce18vSrF32c2Ff/0zOR4ZJFcO1ujfaeANnQlkkXfIH40+v9xLYkY0NRYNraIu8phzZ08/4154BCgj60i5ACLAOpQye2Ljz0prlLjhLWsMONZPzzS0M7VhD7tAh7Wl4p3aEOIbf92A2TcdYQAd+wMoElLgP+naj7CFCqotL49cIhdq5pYLEBvZ1uLsAIMqRgUkaT34zW+hza7Eqxg7xtC5uV4WgFS9gnWq0Bfh3e2p4H/1LMpu3Dz8d1JxDSJnRB2X2IaX8TqeqngBu04nrqWAS30mNXp6APBbs42it+QtfftvUNARuVWnT6VanQ4nUMoL9zdREha42OYsKfPq+f81PezbKMPtiENtiHd15XMxl95IxGBmyPxCbIbM4NxpbwZ7JfFkwB9T7H1hZ4mKsm6t9bkhAtJ4DHPaIrlgqNHKEZnAG2kjU//jy32E2yhAwnkRUiiFXWg3pJvV8cw==
*/