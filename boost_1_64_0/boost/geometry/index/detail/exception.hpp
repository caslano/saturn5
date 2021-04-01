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
twPvu7uCf78klnRJrrkDualGmarMBv5SMwJb2iUJHCEIgGhfl3GrLLsuj6mct9QBn2+93nlAEkI+9C0001VJ3zXhvR74QYWIj42cPVcrzt9E/vwEUY4WD+sLvspzTIll9kwwek2gJDDn5xKmgIJIklzCLSkZwyaFgaYtb5+2s20FvPHPWMLwX5DpydGAttjs7ilmO+kTT0HdmoU2G8IutRa+LP2j3RqtOji8YrG+O8//unrS/Z71Piv8dtz3yr6I5sOdgOJlnCcN28184R77NlYN0jYTN4lsbs/IGiV3jxOCLj4uJ4oUZJswNsXhJMvo0cbsu1UGqycGIAgy84ynFQqb5G9fNw+IevD8Sp+H67YGZaZ0mwW3T585WV0G96S3J60R5jfcl1LRAj6bjNsoT0QdT/e2kShDYTX2E4NBZWj45VpCVkjbghToUx7thBPIBGvWf6BaM5kgTljvqskSa5pYWkY4JhykKYYx0CXouH33zPiOjo5xH/tafJRGX2MjcP2p3lY6nITPHJR8iLvXG6gJ95O9OUdoGXEUN3hoHekHKG1+v8Z7IKWrAg==
*/