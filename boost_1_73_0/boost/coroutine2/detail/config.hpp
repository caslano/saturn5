
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_DETAIL_CONFIG_H
#define BOOST_COROUTINES2_DETAIL_CONFIG_H

#include <boost/config.hpp>
#include <boost/context/detail/config.hpp>
#include <boost/detail/workaround.hpp>

#ifdef BOOST_COROUTINES2_DECL
# undef BOOST_COROUTINES2_DECL
#endif

#if (defined(BOOST_ALL_DYN_LINK) || defined(BOOST_COROUTINES2_DYN_LINK) ) && ! defined(BOOST_COROUTINES2_STATIC_LINK)
# if defined(BOOST_COROUTINES2_SOURCE)
#  define BOOST_COROUTINES2_DECL BOOST_SYMBOL_EXPORT
# else
#  define BOOST_COROUTINES2_DECL BOOST_SYMBOL_IMPORT
# endif
#endif

#if ! defined(BOOST_COROUTINES2_DECL)
# define BOOST_COROUTINES2_DECL
#endif

#endif // BOOST_COROUTINES2_DETAIL_CONFIG_H

/* config.hpp
KruC3Iorr7IB45VTycD4yaasacHTCaxJJqWqPErvNFf+pBQzF+Mvc+Ivb5JLGSzALMWsPiwuUxI/4kf8iB/xI37Ej/jxnz5+yfn/ktK84sLcnNL9pf/vsIaVsvgrfkXfVeLfT+T7CXrXnfekn7dmYH+9B/2734HiR/yIH/EjfsSP+BE/4kf8iB/x47/h+CXf/4tLikW51P56/+/T0DK6pbaoTH8rzUdLTP8M3h9fMDLZsyZG
*/