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
2Frw3J7aOuAYNbdmay7ogCp+eZHQNlJxpOUwzZpYKeoPAE7npLh7wsnu1hDN4XbPrPWkiYoWaZzmvkQa5wQkGTiiGsUDaA8EwC5BkmA4Oo/bKIR+xKGTuMVGKLLq5ID0EoUO+tELpheKjmE8yHOihQRqp15xM3XbKOSzVmKEkE9Vs4QaS0inKa2YyaIsQQCaJYfV5IK113jdtR4S95Nwx+5SiKTI4oquLBaTo5HtUBefWIRrRO1PauQZgoJajVA=
*/