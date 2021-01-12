
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_DETAIL_FORCED_UNWIND_HPP
#define BOOST_COROUTINES2_DETAIL_FORCED_UNWIND_HPP

#include <exception>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {
namespace detail {

struct forced_unwind {};

inline
void * unwind_coroutine( void * data) {
    throw forced_unwind{};
    return data;
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_DETAIL_FORCED_UNWIND_HPP

/* forced_unwind.hpp
698HZH90wisRN68Fo3sydpXzi8w+2H94XvUMql6bu+R8AXp7evn0I784TflKnLuIs1zcvByM6tXrL+dnG91MD0kcbfSc3IlMRAu/fkh8NfZDiXMLcR4v7nYGo3rXhsl5XjDdahHsG2yn/Siav1lIA43168PEt+8+LPvBE2euuH3PxHmqnM8j342D3YPH+MXp1/81Tv/+H20H08TNSN++r/49fVTKyOjnmiTXVwbHB/cuczNe
*/