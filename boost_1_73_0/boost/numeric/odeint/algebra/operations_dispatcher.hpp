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
5YN57P+MTX/FYel1E1+GbazG2F0S0J3yQppYx9ItjHlPcBsDzK5ksZVyC0fS2dw8ljeVPphcWcjzXBrpoecXcqf2cLuHafjz1F5Di/al7TO0WP88gyn+ZnwAfQ/TNw2g72X66AD6PqaP9dAXkrk8nF/D9r6I2ztIANy6U6sVNsqlm5RrnY2bDGin29pWv7C4tu3vI7wuUz9dbq60ys1Ms9wq19rAbS74Ur3NJOFtQpuvFYrt
*/