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
SIa9Wx7LJRP4cKIExnLZlFr7xPLb0hv2mkWbXqm0aU3zadX0+r6OPm2Yov/6+dRKp6nwerEyzTcncRScXz0g5pGWosN+LVZmTX6p49gB1OOgpq/AEzFwFeJdvbwYAA2xTYajmajXlxrQ9eU1C8WARuCNAV+gJwYO+8TAtf4xcEx6t1DvMz25pVOvV/lzHoiRDsIbDPKqQcw9rld0MI6hra9R2vpjWvtdp8Xbjdh+n3B9vGiuYl3mPl/35iwKwNU=
*/