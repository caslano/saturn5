/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/classify.hpp
 *
 * This header contains type traits for type classification.
 */

#ifndef BOOST_ATOMIC_DETAIL_CLASSIFY_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CLASSIFY_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/type_traits/is_integral.hpp>
#include <boost/atomic/detail/type_traits/is_function.hpp>
#include <boost/atomic/detail/type_traits/is_floating_point.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename T, bool IsFunction = atomics::detail::is_function< T >::value >
struct classify_pointer
{
    typedef void* type;
};

template< typename T >
struct classify_pointer< T, true >
{
    typedef void type;
};

template< typename T, bool IsInt = atomics::detail::is_integral< T >::value, bool IsFloat = atomics::detail::is_floating_point< T >::value >
struct classify
{
    typedef void type;
};

template< typename T >
struct classify< T, true, false > { typedef int type; };

#if !defined(BOOST_ATOMIC_NO_FLOATING_POINT)
template< typename T >
struct classify< T, false, true > { typedef float type; };
#endif

template< typename T >
struct classify< T*, false, false > { typedef typename classify_pointer< T >::type type; };

template< >
struct classify< void*, false, false > { typedef void type; };

template< >
struct classify< const void*, false, false > { typedef void type; };

template< >
struct classify< volatile void*, false, false > { typedef void type; };

template< >
struct classify< const volatile void*, false, false > { typedef void type; };

template< typename T, typename U >
struct classify< T U::*, false, false > { typedef void type; };

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_CLASSIFY_HPP_INCLUDED_

/* classify.hpp
OF5p43WMxx1xUSiZ4vXptcpBDjVBF3NkQQ5BWMa6+At4O61WjqqtFs98uMGh9+PgQQmSUJQui8/A3WTztNE6jbnUvoS/XWlLuqjZ6E5/NAyYIj4AmmIGnESIGPQ+ny/W6776G/V1nwr+9N6DncRxtgvpLPluUW9Elq7O0XZRt90GD2PPcoT64pCpYfwno/lB4zQm2D5zQJZuZQgWOy7+HPFyWtBt7sL+Vl62YuUDNMftV8bz7Y4TT8hg6Vbnk+Pga7WdL8t4g77vB3gubNItZ3H02drv9HVvkKxcORtpprMZOEMCYCEi4AGAg6sIiY6EcKv6Xjaa++ez4zna/4SzA2wsOA/SdBfhS+YRVPW7TguHzIiM4l/tzda/v+r0422Vn0fsdG28TNHhEHAYhImecd4EFEefMgWv5YRcjbPzPb0fR6x7Ae4n5pAY+VwfKmVWxR+uVtSuXEM/+BHhWcyfZ+l59wTaLxtSObOYHZt7NnBj8LBL2Qv/INJzJGrPpqOqy5ccUl80xeh47mbs17lYPm5y/XnhPnkEwKudnG8X89BhHFDTWHjeqt//2/PNJ7un2IVK4vTDDOdW97Hut33BYe5NoNxlEQ/54kcGTIbfsvJ82uM20/ILCx0/SRPCN5lopj7LNms107TJYzWnX3e2LVNLj+LMk52iRjA7UWIQN5PKMyP3oIvVstwHIW8BcJlImW5QfXOtNJninjKT
*/