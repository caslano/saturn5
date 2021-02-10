// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2001, 2002 Peter Dimov and Multi Media Ltd.
// Copyright (c) 2007, 2014 Peter Dimov
// Copyright (c) Beman Dawes 2011
// Copyright (c) 2015 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_ASSERT_HPP
#define BOOST_GEOMETRY_CORE_ASSERT_HPP

#include <boost/assert.hpp>

#undef BOOST_GEOMETRY_ASSERT
#undef BOOST_GEOMETRY_ASSERT_MSG

#if defined(BOOST_GEOMETRY_ENABLE_ASSERT_HANDLER) || ( defined(BOOST_GEOMETRY_ENABLE_ASSERT_DEBUG_HANDLER) && !defined(NDEBUG) )

#include <boost/config.hpp> // for BOOST_LIKELY
#include <boost/current_function.hpp>

namespace boost { namespace geometry
{
    void assertion_failed(char const * expr, char const * function, char const * file, long line); // user defined
    void assertion_failed_msg(char const * expr, char const * msg, char const * function, char const * file, long line); // user defined
}} // namespace boost::geometry

#define BOOST_GEOMETRY_ASSERT(expr) (BOOST_LIKELY(!!(expr))? ((void)0): ::boost::geometry::assertion_failed(#expr, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__))
#define BOOST_GEOMETRY_ASSERT_MSG(expr, msg) (BOOST_LIKELY(!!(expr))? ((void)0): ::boost::geometry::assertion_failed_msg(#expr, msg, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__))

#else

#define BOOST_GEOMETRY_ASSERT(expr) BOOST_ASSERT(expr)
#define BOOST_GEOMETRY_ASSERT_MSG(expr, msg) BOOST_ASSERT_MSG(expr, msg)

#endif

#endif // BOOST_GEOMETRY_CORE_EXCEPTION_HPP

/* assert.hpp
g8gjNLPlXiWQWnWRvAe2ED+F4JsoAZuUa4EFjz+9zh++yK8fih4jhSSY0yCInFapZKaKkjWx/+CHO8X8QnLK+GP/BB9SwnTHB5VyWrmA4jpCyna+RLWCm/XHXsz4qxip7HAlU3zaO29oq8jINWPH6bf2VtjnWam01vmWR3+hGvDAPOHPwq1kYGujqcWPZ143ePm7g+tvDwpXtzJuhRLiV6lCKK01mOrrfhWdUdUz6/pfNXrzovCs2qt6iVW7Qdyi1iitbHLbJLUQVQTF5svVq/Wqldb/mv8rAybF/wJQSwMECgAAAAgALWdKUoGdxR7aDAAAeC4AABoACQBjdXJsLW1hc3Rlci9saWIvbWVtZGVidWcuY1VUBQABtkgkYM1a+3PbNhL+3X/F2h23oo9+NtNprTY915ZTTRU5J8vN5ZoMByJBiw1fR5BWnWv+99tdgE/Jtpz6enUbkcRjd/Hth8UC5P7O0/1twA48+OfwPwf/8Mo9XmXJr9LNV7d2nN9B/4e93uL1ISX7UHf53bHg4S6/Q4+7OEbLt3TvOA8peku20c8+9Xzr0C2WYDfqeZqkt1lwPc+hd2rB4TfffA27cHRwdGDDmYgDGcJlLuOZzK5t+Nbjkr/PxW+/7Sn53AaZgwj3jKjpPFCgEj9f
*/