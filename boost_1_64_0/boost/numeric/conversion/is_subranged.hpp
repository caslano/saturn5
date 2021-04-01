//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_IS_SUBRANGED_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_IS_SUBRANGED_FLC_12NOV2002_HPP

#include "boost/numeric/conversion/detail/is_subranged.hpp"

namespace boost { namespace numeric {

template<class T, class S>
struct is_subranged
  : convdetail::get_is_subranged<  BOOST_DEDUCED_TYPENAME remove_cv<T>::type
                                  ,BOOST_DEDUCED_TYPENAME remove_cv<S>::type
                                >::type {} ;

} } // namespace boost::numeric

#endif



/* is_subranged.hpp
XOC/p5xg2fHJ4xNxiG6jCN2SIeTf2rTWdIIConqwxjym9IEZGL9exE9hNcT9ToPuJFczE+WAPdhS0NuHzJmx7OtN4/mEYseIq6n8JOUzPdAYD8Ys7ZH15o5GCJXvnLC0wAA0Qe7s5zjdJcIQ4WJ2eBF0NmoraMkK+8tAcvCE/VxX+RDTe1D1eJkdIUhYkxdqXTr56d8aend1yBoWfgLsmBtQgnJC+xRBX0O+2MzG/pCGDW5u+3/m8hGkbUO9PZLSCDxF0/G/lckKjiGDIzhKT64NmfAYiQa5FFCPYdlkFWGtHy86sNKVQ/Lh/7FMBqYnCplofTJloq/jlEvgj880klPP/Vu/Ug5kgyxuQASzgbXpX4utTVCXIeND5I3NRVkL9YqjduViFN2oc83/WX4KUpx+e93a+uGSCXfCgeB8BkLdyA5pzi7vKKfuw4bfPGQPwm9/jtZR+x1Lr162il52J1MS0wqSN1rc5lpw0IWmJwfWXRptmcBJiMCakn0zWI2y9XToNyGKQ8lFWy6z+JVoV3tY8Pd1S170CEcDDmucdNYer+/Qeyt/Wy45vw==
*/