
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
hicfOsB/xb3Asqt5edOxAZt2rNpZdPTAL299nrGh/ZC++3ePHvliVMOKF2anXvlt1Z5NYLNEXzxuYuljI37y8OfLnrjxlQ0f+hnbQHTvEzs9f/z6V64PHtj8s8G7zt8K8xN92JF110yr3dx/+v6DbcdHPfUw3t6O9L5PW6Mti6fcu2XXI/O/KjsQwdvUkf7CWUW/Uauq9szqP3nG4rGOUYwtInpFxY7gO4e/GOn/w4rR/rtGvwjyJ/rws6KuVy4=
*/