// -----------------------------------------------------------
// lowest_bit.hpp
//
//           Position of the lowest bit 'on'
//
//         Copyright (c) 2003-2004, 2008 Gennaro Prota
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// -----------------------------------------------------------

#ifndef BOOST_LOWEST_BIT_HPP_GP_20030301
#define BOOST_LOWEST_BIT_HPP_GP_20030301

#include "boost/integer/integer_log2.hpp"
#include "boost/assert.hpp"

namespace boost {
namespace detail {

    template <typename T>
    int lowest_bit(T x) {

        BOOST_ASSERT(x >= 1); // PRE

        // clear all bits on except the rightmost one,
        // then calculate the logarithm base 2
        //
        return boost::integer_log2<T>( x - ( x & (x-1) ) );

    }

}
}


#endif // include guard

/* lowest_bit.hpp
H1HHfx9Rx/dF1HH/iOCa1v+nXp97G7n2t2+8oeewkh5/fX761OTp39TucEKvj1evT3rwbH5Qf4+McfUsg0/qnvy9ApGzPsH9KLC/96xPxJmtYtgALoStYCnsDcvhYbjO7HPgGafh1EUu0nDWcnuX18FYNcereQG8Ey5U81J4A1wFN8KL4I3wangTvA7eDDfAW+CN8Fb4NLwD/kHDk/QF33XDzpHp07OALrfCOHgXbA63wU7w
*/