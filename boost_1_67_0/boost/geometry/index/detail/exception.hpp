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
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
*/