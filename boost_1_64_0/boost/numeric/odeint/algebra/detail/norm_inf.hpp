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
C637MryaMEoegl3znx8BKPcIA/KOUxS3xfzx2uwWgYSpOOReVjb30KbRJ3gTK7kC5jCRj7y334qr3TTGQEmh2VvKfp6n6PRR1ktnqqjrwLVmIHJgDnNa/heT5eyfk4IEvDoRRCWoJco1tJoxaoLqdLFOWg3G2acSmJ4Gc78yDer1YNPuLAb3Xe2xnNsRMq58SacLPO/e+MTwoDaI6YPLPTw2FHp6kkYFRBvd6/ZwglQtFkspkqu2K659fLKY96dZ3uWO59CCeEFhYXs/o+BKNP0a5XHa4EvR+vO+q35wIQIXyb8Ee1FPUJKBnbzK3UYDYG/O9/DfYEJTNma3Euc2X95aXxYQCTfKCKcuEerSQ0WtpDECieI6J/EuOQ7psRubignWg/XEdYev0s9rDodwuDnCMaLrDrhef7lHzGv+alhgNzicxbgvHrD2evYaEJfsqmJyrj2ZWdZpruejlO1BcDHpUWs9RGPXBea3AJ6qj+2ABa48i9GrgqdB5Wz/odN8n4rwzWFst/DutYCa7nSZJkHbzkRsWRTW107yGB2zBwzCl0nLJ4QqguxrAw==
*/