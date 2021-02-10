/*
 [auto_generated]
 boost/numeric/odeint/algebra/detail/norm_inf.hpp

 [begin_description]
 Default reduce implementation.
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_NORM_INF_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_NORM_INF_HPP_INCLUDED

#include <cmath>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

template< typename Value , class Iterator1 >
inline Value norm_inf( Iterator1 first1 , Iterator1 last1 , Value init )
{
    using std::max;
    using std::abs;
    for( ; first1 != last1 ; )
        init = max( init , abs( *first1++ ) );
    return init;
}


} // detail
} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_NORM_INF_HPP_INCLUDED

/* norm_inf.hpp
K5q2PEhm+r3o0ZylcsNetClUx/TdHnk1vqLkcGxUb3ZPq4uw9UnrNy+nYWM7DLF2z43/AFBLAwQKAAAACAAtZ0pS0lCU2bADAAARCgAAIwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliMTkwNi5jVVQFAAG2SCRgzVVbb9s2FH7Xrzjz0ME2tCjtW5NsmOs4q7E0NmR7RbYMBC1RFleK1HhJYiz77zukbMteVjgPfagCifThuXz8ziVJ/8s9EfTh6EPCS/DBNVhMtfqTZfb/tQl5guYPre5wPRYkgdbkifTguMkTdIMJ2US58HtCjgW689j8J/GWd8RvUYJm3nKo6rXmq9JCd9iDN6ev38L3uLw5jeGSSs4EzCyTS6ZXMVzkQfJTSR8fTwz7MQZmgYqTjat5yQ0YVdgHqhngXvCMScNyoAZyZjLNl/iDS7Alg4ILBsPJ9HZ883MMDyXPSu9krRyYUjmRQ0nvGWiWMX7f+KiptqAKNEfnOTcWHTrLlTzB2Aws05XxPnx4KowCek+5oEsMRC2U1tbmLEkypwWiT3KVmSTbXv+ktNXuJrcIoqJrULUFq8AZFoPXjKFSOS/8ioSgsHZLwU0Zt2gwlMwTpcEwIbwvtOPMNLAZzDb0xF4NakTMrV+M
*/