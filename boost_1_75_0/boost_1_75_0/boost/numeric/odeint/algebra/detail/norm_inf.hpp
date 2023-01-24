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
LPpZYwh9hDSa47kIl9eBKAIX6wh4bMyziM6B+UeXVWxEaLGeT9FDYc8/Ycl0CdVa4QrIfQq8u4d5JoQ9u5jn7rDnQ+aZ4w573sVMDmF/jZdthVVAuLnDsHQU/z/Dnu80+z+aBaQLfhKQ+m0I5cJCTkWrTAa0ui83xoeSwX0o3MGUdG+dbuw3mETmMIPgiwqpyu0vYVrSa/iSToX7tXC/RL1vOblW1lD6hQUlrCAR54sVWHGymQ1nu6XSGkhmBalICS2V5sAFbEIGTJDL0kgtbKCF7FnFM/IoRB4VG5NSxar55Bc86Ym+F5wHRu2ZAz4e+o6QNQFkWMeUTcaCwdlyzlfyzhPAPPs499qG73WzKr+lAotmqldPhu8LMpx7Z3VDaihInxYeJPMGEwIip0hWS2UiZn6lcycF2Rx0oIxwQQqdqEUcCeofnyTDGEcCYEhDGDDUuEHQSusoPgupCTQL+83t4oatcf6/+Nn4uiZ+NmKltpiN28tJZp9PzCdmNr5ZRrN0fpBmqYQN57MxnM9G97CB7PAsJH2O3nBjZi6S2dh0aihvecyksOFYD9BlzE2XVKEL9KNFshe7oq8al1GWFTEoJ58QfgJ9UA76udW239yJ1bY9Vl7th9HI4KNRX60vqFSJHeE6jI8VzTBGhGN+UCHMMwIccy9WnEr2dQUiidiJNcM7U5+MQUpnfzAZWeRmA00HEdw4UMfODQtr
*/