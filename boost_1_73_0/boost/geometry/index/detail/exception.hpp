// Boost.Geometry Index
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_EXCEPTION_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_EXCEPTION_HPP

#include <boost/core/no_exceptions_support.hpp>

#ifndef BOOST_NO_EXCEPTIONS
#include <stdexcept>
#include <boost/throw_exception.hpp>
#else
#include <cstdlib>
#include <boost/geometry/index/detail/assert.hpp>
#endif

namespace boost { namespace geometry { namespace index { namespace detail {

#ifndef BOOST_NO_EXCEPTIONS

inline void throw_runtime_error(const char * str)
{
    BOOST_THROW_EXCEPTION(std::runtime_error(str));
}

inline void throw_logic_error(const char * str)
{
    BOOST_THROW_EXCEPTION(std::logic_error(str));
}

inline void throw_invalid_argument(const char * str)
{
    BOOST_THROW_EXCEPTION(std::invalid_argument(str));
}

inline void throw_length_error(const char * str)
{
    BOOST_THROW_EXCEPTION(std::length_error(str));
}

inline void throw_out_of_range(const char * str)
{
    BOOST_THROW_EXCEPTION(std::out_of_range(str));
}

#else

inline void throw_runtime_error(const char * str)
{
    BOOST_GEOMETRY_INDEX_ASSERT(!"runtime_error thrown", str);
    std::abort();
}

inline void throw_logic_error(const char * str)
{
    BOOST_GEOMETRY_INDEX_ASSERT(!"logic_error thrown", str);
    std::abort();
}

inline void throw_invalid_argument(const char * str)
{
    BOOST_GEOMETRY_INDEX_ASSERT(!"invalid_argument thrown", str);
    std::abort();
}

inline void throw_length_error(const char * str)
{
    BOOST_GEOMETRY_INDEX_ASSERT(!"length_error thrown", str);
    std::abort();
}

inline void throw_out_of_range(const char * str)
{
    BOOST_GEOMETRY_INDEX_ASSERT(!"out_of_range thrown", str);
    std::abort();
}

#endif

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_EXCEPTION_HPP

/* exception.hpp
UfwM566MC5laa3C+ZSifN263yyXuI5i9sBt/7c3NtwOKWS7r84L5ArMQNrOCQ1n2L0o8r5RObci+DlZR2Lr08/58RuiJfSvM9euGyzyPYI7Cyr0v+oZ7Eyav+X7RR45bCPMWlmRddRn7OpitsAc163J+R2Ay1nX9D3NvZsHk/CbZfunIXgomc2LZp9B47hVYpMyloNwxfFbrhZotbF+qrf6OEybXYeWFjW1Zd2FOwqLs195k
*/