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
Hx5Hj5fvk8cwzjl+kRq0y4GRxJ6Z8kyVV5p16wFZo20IqKEW02CFx2y7qkHrnGCS0wUIo1stdxXvtlOFX/WuRoDPlQ2OqD1ueMOZRoUVYmDQ/0bjqX28T8Kii8DZS0nvqI5RkEl6LSsLm3aIwsiq6a/Yu81AfFFMLJ/R/vhiu3nEsUnf1L479bb/zIL8RaLythtXC7rQeSJ66cqOOXkmlAIWTuZ9chx8fmi2ZBiZLStmxl1aYa6eaWfCBGT2352P/ZzpdLXrLaVOOKN0r0tADmKxnZsX1DLrxEc0Hm16ZOzQt1OGoYI8Oi+oKkm8wdpL5URZ2wejb+Lfe9h9b5PUc33u6YeYjg+lK/WdlpSgvynCzdakSA4r7otYMt01t0rlsNFaeZDk+eN5jId1Ev0PS5YO8PiXmJaUMmUpVvA+KH/QEphIABTVxpOaCk1/t7kEskIfvHcDO0fPYiRclyreu08nG7ye8VkxZq+ZPWqVcJ3ejaSQpe6nwZaD/7ISzLISfMP+VRLFnIXXFXYc0ftL6MV20o22jem2u/aDSO7XHKP1dwNTdkO5F8iQrYf4qIzJD3ahw/QrsQbvuOoD3ZfsB9jlZr4menDCDta9FPUWVL08edr8rc71sb8V5G/qGpOoj3h9AsA4ozl/qwXKFjtPLo5y/m4SfYUgUR3SPjk2TEp8cmyW9J0xBCGk92PzZo4xS5iecqOsIrzmqI5S
*/