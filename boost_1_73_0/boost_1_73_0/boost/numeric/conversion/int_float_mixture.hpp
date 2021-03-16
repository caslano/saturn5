//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_INT_FLOAT_MIXTURE_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_INT_FLOAT_MIXTURE_FLC_12NOV2002_HPP

#include "boost/numeric/conversion/detail/int_float_mixture.hpp"

namespace boost { namespace numeric
{

template<class T, class S>
struct int_float_mixture
  : convdetail::get_int_float_mixture<  BOOST_DEDUCED_TYPENAME remove_cv<T>::type
                                       ,BOOST_DEDUCED_TYPENAME remove_cv<S>::type
                                     >::type {} ;

} } // namespace boost::numeric

#endif
//
///////////////////////////////////////////////////////////////////////////////////////////////



/* int_float_mixture.hpp
Br4X+BfgNNH3H0cnie4oHzFoezMwQ+FfgfSBA9bDkFfEASwAcogtALcBi0CWSVgwntYlsadRKkuP4/Y4Lu9QvTUZb7KeMyOhp9K/EHU/0efA1z3srWYvvVsz84uDJV60QKAo/6YSZxrGG9gyzJwj9gZOwSdkvIGlyvbKAfGRvDe4143/I26wOFPti70qZg0v8oyZP2uYK4TzLYfy0T6kXDA1XAWcAuwP/ABwABAJS3XBDEE1QLb+WiCvo87WINM=
*/