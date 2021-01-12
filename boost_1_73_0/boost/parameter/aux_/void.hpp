// Copyright Daniel Wallin, David Abrahams 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_VOID_050329_HPP
#define BOOST_PARAMETER_VOID_050329_HPP

namespace boost { namespace parameter { 

    // A placemarker for "no argument passed."
    // MAINTAINER NOTE: Do not make this into a metafunction
    struct void_
    {
    };
}} // namespace boost::parameter

namespace boost { namespace parameter { namespace aux {

    inline ::boost::parameter::void_& void_reference()
    {
        static ::boost::parameter::void_ instance;
        return instance;
    }
}}} // namespace boost::parameter::aux

#include <boost/config/workaround.hpp>

#if BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x580))

namespace boost { namespace parameter { namespace aux {

    typedef void* voidstar;
}}} // namespace boost::parameter::aux

#endif
#endif  // include guard


/* void.hpp
ZzVrZzVrZzVrZzVrZzVrZ2doZ2doZ2doZ2doZ2fYj5aa9Q6Xrf3UrP3UrP3UrP3UrP3UrP3UrP3UbM4iMduPHqmG+l2nhvo9Sg31e7Qa6vcYNdTvsWqo3+PUUL/CMrOmXWw/MbafGNtPjO0nxvYTY/uJsf3E2H5ibD8xtp8Y20+M7SfG9hNj+4mx/cTYfoXEenvKfm5+WBP2Ay5jH+Ay+j+X0fe5jH7PZYwtXMa4wmXMzc9l
*/