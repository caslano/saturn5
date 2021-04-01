/*
 *             Copyright Andrey Semashev 2018.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   allocator_traits.hpp
 * \author Andrey Semashev
 * \date   03.01.2018
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_ALLOCATOR_TRAITS_HPP_INCLUDED_
#define BOOST_LOG_ALLOCATOR_TRAITS_HPP_INCLUDED_

#include <memory>
#include <boost/log/detail/config.hpp>
#if defined(BOOST_NO_CXX11_ALLOCATOR)
#include <boost/container/allocator_traits.hpp>
#endif
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

// A portable name for allocator traits
#if !defined(BOOST_NO_CXX11_ALLOCATOR)
using std::allocator_traits;
#else
using boost::container::allocator_traits;
#endif

/*!
 * \brief A standalone trait to rebind an allocator to another type.
 *
 * The important difference from <tt>std::allocator_traits&lt;Alloc&gt;::rebind_alloc&lt;U&gt;</tt> is that this
 * trait does not require template aliases and thus is compatible with C++03. There is
 * <tt>boost::container::allocator_traits&lt;Alloc&gt;::portable_rebind_alloc&lt;U&gt;</tt>, but it is not present in <tt>std::allocator_traits</tt>.
 * It will also attempt to instantiate the allocator type to test if it provides the nested <tt>rebind</tt> template. We don't want
 * that to happen because it prohibits using <tt>std::allocator&lt;void&gt;</tt> in C++17 and later, which deprecated
 * this allocator specialization. This standalone trait does not use the nested <tt>rebind</tt> template in this case.
 */
template< typename Allocator, typename U >
struct rebind_alloc
{
#if !defined(BOOST_NO_CXX11_ALLOCATOR)
    typedef typename std::allocator_traits< Allocator >::BOOST_NESTED_TEMPLATE rebind_alloc< U > type;
#else
    typedef typename boost::container::allocator_traits< Allocator >::BOOST_NESTED_TEMPLATE portable_rebind_alloc< U >::type type;
#endif
};

template< typename U >
struct rebind_alloc< std::allocator< void >, U >
{
    typedef std::allocator< U > type;
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ALLOCATOR_TRAITS_HPP_INCLUDED_

/* allocator_traits.hpp
yedULrsmAXeV/OQw2YIQ6ytNftw39Zbf5PGbd3o1y7Ugt0a+xH7L28P3qdCr7VK07NeT6d+maTraO5xT/0IrUn7IDCoC+bMM/HK/dm67ZuofijTpzH0ZgVvjTteY8z2UbbggdiY4WqKzioTmJQhcIAeGC9ATZsG8fePJFtHnTkd1GsACYib5nU6URbyDHCeE0XnBYz01u/uhgr9sPlG5w1HYMuahvf0vvIq0YCAkSzhO0JzcMosJ7XLVMDCVOdq7+o81cP3vvAblUmTjMKmA5DPx8fy9kjXj9h9yIY6QY2id5zBKE0wJYftCCVwBHUe6ZdfNyJ/yDToLBMabpN7J/zcyZQqf+zhg4L0dPnQpnuwWbOsJGE/h+PQqb3Qifr/Q55kwIWwpFCjhh362I/VAQo7To+p4FRM5GYLLZjWih+JUwvSAuEo15p4j/EgXYux8/l7EkNxHcDrxC0NEzD8lNPu0GY/wPOkuEPQ5tECb4ud0YKu8URd5qtGRX626/cjsgKZMddkg7h68Bmm771Mnjd5EhUuJKao85lIZ9WelGdbK2LmUtb1bj8cPjA==
*/