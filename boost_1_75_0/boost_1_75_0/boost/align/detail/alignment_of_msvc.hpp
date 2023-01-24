/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNMENT_OF_MSVC_HPP
#define BOOST_ALIGN_DETAIL_ALIGNMENT_OF_MSVC_HPP

#include <boost/align/detail/min_size.hpp>

namespace boost {
namespace alignment {
namespace detail {

template<class T>
struct offset_value {
    T first;
    char value;
    T second;
};

template<class T>
struct alignment_of
    : min_size<sizeof(T), sizeof(offset_value<T>) - (sizeof(T) << 1)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* alignment_of_msvc.hpp
o86Itvl3aNPDzpueOCdnXQNQZhsoxPSqq1hhzSDdW2H8CpGi4+xePob7NoBqwpjAI+sBNVJ7r6FDZ+KlkBMszzDBGTybi8RWurxi7gUr/Atbtft33Q020vue8pCCaFsa6BmZ7eXd8IWEvo1bms7DbEmliimIsRPxVAz4PLwCh1JOnamZMegEJcpMnXGAtO8FOXKEDFv4CVIAkDLWNgvu7tE+oaJM4EC9JB0XNwC2+I0B33+Ma3QhLuQYFooZQk6DdcZRU8HPgwrDfwmljW2TwKbM2L/22BnZR1n65zkN/ZfT6w3EadP3B5NV1/mNkf01MCVxEvY4t9M1XYDy0JLKR56zlhc1JCHZCZHI9O6IJmBjZS9ZmvQopr93Ywg7VgX5OhK0ULGwoBBNKh/MZQoZ+TPtPdW2kKR3jpkNyRrWu+jEWcxkDnXGaQXiY7nKkv1ftgnpXgl0laxY6EmveKp7OIhKjywMLVwWO5rBs6HqVKITZD4ER3djzdXCw1TyJtK/wXNPinxiNHgar+qvnJas17CphiXMxdHOcGvrCDCH0nTWQircWmI6P8ERSPIe/80rK6+c9IfMRoce2+BDsgQxNXE6Z888AqXHqkosfqQg/dKdywdJh/EQ0NHN0s9BgP+2F4D8062XeVRmhK4gAyXyReUWDRIPM470e/4NymWQL3KjHJfDjfBmnPBcix3fgZwVJCm/xB6eu0GvOSTp
*/