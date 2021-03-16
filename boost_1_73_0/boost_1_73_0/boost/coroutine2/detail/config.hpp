
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
Hd34XSM6ZA/SzLlcm8zR59tcQeIEV63vYSByFK46wXjlEk9TtJ4nQiGPC6tvGaT14zZ5xI4F8NJpi9LJSpLGHXpaD4olTKnRgZAYIIN+zZCVmWIreqS4MIq7wgt4yVRsCZ6AixsC9AiMGKVyAf25FwGZLt5WGxNQQx5YVUEpowBuVPRvh5nOZv3ZY8sDisGujQoeJezDeAaSwadz6ZnJx0W5l/YDJIhyg35Ml7RAwIyXGKMES4YTjpQMiugv/Xg=
*/