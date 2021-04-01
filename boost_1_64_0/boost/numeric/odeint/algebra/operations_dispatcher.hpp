/*
 [auto_generated]
 boost/numeric/odeint/algebra/operations_dispatcher.hpp

 [begin_description]
 Operations dispatcher to automatically chose suitable operations.
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_OPERATIONS_DISPATCHER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_OPERATIONS_DISPATCHER_HPP_INCLUDED

#include <boost/numeric/odeint/algebra/default_operations.hpp>

namespace boost {
namespace numeric {
namespace odeint {
    
template< class StateType , class Enabler = void >
struct operations_dispatcher_sfinae
{
    typedef default_operations operations_type;
};

template< class StateType >
struct operations_dispatcher : operations_dispatcher_sfinae< StateType > {};

// no further specializations required

}
}
}

#endif

/* operations_dispatcher.hpp
feggNPBquW9ClnzbG5Svx91Cb4NgKVAKyM2GQ0N/m2I5RbazH67PZyx5wZveEGBV/d2Emkk3fK/i4Q88PsnrL0al5GaMhsSLJehOjQC5YhlLEmkLwZQ03rdtgMf76W1gupPchG6ytieEkiObZVGldpngqZRXUC+mTmZKWQ31+M/EnOsZyph3kZsXCZLBsPtEg5wqsfp0196U8hehzif1DBZlPum1Pe2Ckz8M6QbL6c1XoeD+Cnk/PQ7CIblraWY7AVzESLQpmDhC1v+iFMEQrSKivJx+5Jagmn+JCf5vt7+zOsB79Y5AJIMqEnrmim+qMo/2Xyn9jtGDF+0OUsWDyWQ5pJ1lZT6P/x4kG+Dx1oJod+PUqj3GjM8/Rx6stpPDJCiNoIe4odqU2hrPUEBg1caRe4rkhB/I7BDCaBe6r5o+xcWh7TQChRB39oDwvsHKyQhey4xhQPAwV9uGFhgIm7reONNrZl3Lcr6mVe4gJ0GGjzp+FMFCZqVUVL60Y32izQWrHSshw9VZ9XedlMyYbnBdI3tZI+dkxKquZyX8sSzeHZq0wXVeW9glpA==
*/