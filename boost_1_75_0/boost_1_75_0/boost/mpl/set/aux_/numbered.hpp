
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

#if defined(BOOST_PP_IS_ITERATING)

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/cat.hpp>

#define i_ BOOST_PP_FRAME_ITERATION(1)

#   define AUX778076_SET_TAIL(set, i_, T) \
    typename BOOST_PP_CAT(set,i_)< \
          BOOST_PP_ENUM_PARAMS(i_, T) \
        >::item_                           \
    /**/

#if i_ > 0
template<
      BOOST_PP_ENUM_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(set,i_)
    : s_item<
          BOOST_PP_CAT(T,BOOST_PP_DEC(i_))
        , AUX778076_SET_TAIL(set,BOOST_PP_DEC(i_),T)
        >
{
    typedef BOOST_PP_CAT(set,i_) type;
};
#endif

#   undef AUX778076_SET_TAIL

#undef i_

#endif // BOOST_PP_IS_ITERATING

/* numbered.hpp
779H25kygH+YhJMCHLH4Q9m/wZHfbM3CZxVs4kKMJB6zdSAuWPnq6LGwDiuvVXndg4kD9jaj2CzDwopq6dCLXj98iSt8sPBZZ+D6eJo1+or6iuSoNplA5OWTtzLk5Y+91oaluk/Gd1iuFeXoK79E0fZ25hFu95h9b3OXxG7KFxAAPf01FCQPUxD+7QuFF9woEHzuiPQsm3Lz/K0YfpCbnBAxre9Cy1+gP2aZm2o1kd2WrVkHdGUanb6R8PzafRgBCaL0RYWYoL4ycLEfNM4wLnRvaV3Iak4aUqKCNeGNmHoWIyCE8MSfIgJHRqF/M38jAieN7k/uuwT5QJlGEq3s0ybGn4tEklW++t+XGagZ6OjEa7kxpqkV8RacEfY3J1S0k/ZzpVFNvRfKBQdBsrTgqhA26HuUIiB1lO0GgR7hkGw8s08EH7oBFqkR/VxR7w4mBrvCx1Ec/Lt6GLW5yoyZlojdSdoy1383VlfYkbSFVPSOrS/tsny6I1Z2QFobTotYmvA90/CO4rW38Kg5L0cCvFZuKijZZ6zBezH9LgtgQN9SKn/+MhAd3mAXhv9Srl2yVsozC1sXDGvma4PQ3430n51ekpKUwMb2iVstR7N944vsuMIFH3YP/bM/etE+Ug9zdFtKZ9GAUve8dmKksxi42b2SmuOHb/o+xx+GYsZbhmkX/6EfXPksKlC4DDTb4lrwmoh2kjrb9Fr/Gkg7
*/