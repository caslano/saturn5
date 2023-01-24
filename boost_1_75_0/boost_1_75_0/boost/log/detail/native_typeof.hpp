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
Va/m5dg1F+W4+a25XcrRyebM/Wc8QkHYGZMc5Yj/whOmHHIj8n3uYo9AZ6ka789c7BHOvrSzsdcz7oCnmp9XFRfjfQx9X83KkVGOvdqPXmPHZYsc9lVUgtm9NVbRl4xxAeJ3HvR4VrL4SQUYL08/ZfCVuUzVXrtdsPtuZXvaF+s9NUE4k6kVbF9nDfbRYVfB9vvKoCdfzW1xjO5amN+DNHAdKnYeuQ/bkZSlsN2ua6STF3avmK0DeJ9oKjyeEHHAaDnZOUzZBNqmICWauTHc1grY9y7WzMVdbDr6F7ocVPlBtODdsioT5MfTw/iFHiNMZfiekwl9csBEZaCuUTin2mxCHTL2M/vp2lp27Q0TPXAnjUznvIfJsyAJi/w82u+Q8crLqiA7VFqtwawrgSczFZyYAZ9cijnAfkyCXUIjlOoNRh3w7aXQzw3S1Es0xrJSHSIINGIqEOfL+dI4FQtLLYYLVBVaIU7SbOwJ3DVVGsdoKJ1vLuMZbaVxDhmwX/d4ulDWCp1podFs4bilxZBz3w8JwJcE7+cCf2oB8He0B/F6q8MJ7xYcfxg8IE/9OojnnqjQV53z2d09GZ3JAr5UNpWCT0/3sa0SoJShvNagD66WBRhPxQW0PwItDnhbGfSAF69g+14+sxt8CHijAf2X+6m3VrBol+D2mZHG/p5gv8TOFBnfmlCut7QeOJ5y+i3QJxLV4PsXLub3MIPn
*/