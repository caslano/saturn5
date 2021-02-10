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
qFopTfZlC703apLH2Ogx6wb/8B3VceFc9ShXPA6QNLWqb2eSJeXfk7PbOnNutGc5hwSDyPHd//PdH42rGXzFXbL//M08nW1xhpZUc1WQ2lJ7IsN7OkvP8mleky+dAzhNhoZpcf7l2TPocTqlCG4zmHYDsxwvpuyQgL7xuEI8XYRY7AATLvI9dA7eQoSYyPD2PYkqMPBWaLoFpD34kY+5tGzX+9PR0ZvR2+Hbo+NfdtwAnoZ5H+/EkOQNX2BxIukEseDKhNlP9ug+Jz9sC52a8YV8X4B2XmRYKEZERPUIZbAQ+DdAsCvgS9H9Rogl9xhacCU9G9VZC/FpIz93JUCN1Ahr0aC7UKE70SE+s1/xeD5uEavdRimidpJ+8UWC127/0LaKaU839fH0527U7etnDID7u0x5FdGMyKb/+ose1Z2IZ+iXhjCt6DhE5hTtQpwVwvYmJcBrEVXa0nRYtG/gL95wL+Xk+GQnbuR2+5lDI8En8v4Rbx7qMUcMSYpnmn39FgLbmj2+O95f2SW0uVOfAD0r+3QQZmnX34xAxsfT+n33Idl9XUprDUZFGNra8lH6BVMOk/sJ/urhaANC/QPDvHjaIp+89FVJEiN68Vvj2jkuZxhfyPPmEJTKixDYXFWJRu1K4iu+89eSLwNx
*/