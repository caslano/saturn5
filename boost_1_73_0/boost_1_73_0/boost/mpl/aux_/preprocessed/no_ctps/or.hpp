
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/or.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {
template< bool C_ > struct or_impl
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : true_
    {
    };
};

template<> struct or_impl<false>
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : or_impl<
              BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
            >::template result_< T2,T3,T4,false_ >
    {
    };
};

template<>
struct or_impl<false>
    ::result_< false_,false_,false_,false_ >
        : false_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = false_, typename T4 = false_, typename T5 = false_
    >
struct or_

    : aux::or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        >::template result_< T2,T3,T4,T5 >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , or_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , or_
    )

}}

/* or.hpp
5vQElkNtcG0bVn+dkR48BXNwYxXic9o2xaXJ6YxcK/51Cs4ZOUP6gaBncv8Tk4sLWWle6cu/efWgN1MY26e99aHmU2B1XYi0a4GlstpcvotsoqJGqzqD5CYmIppDzrbcBNAVSNpoo3U9taz9fk/NxZR/Y2VdcJrK0jJg5KK1Ggpxh454T+vYCg43Ej9fU4936ow3EPq/25jEEPm4MHt1I3ZMYxPUXqWFVJjFD46Ywm1Z6wOsahMruOeqxm9+ysM3Thg0RytcF8J0NumskHYBAlSX0IyYjiL8GIZaymJGMMFRMMH9PiRhxUrelwXzqpJtlXJ4F39aA6syiFfJGpQ+FPw9mJLwdz0+xMaXiOivQWXefEToIp6+MUzx6n5t9dc84i4gFwWHfSM0+gE+c6ycd6QwYKBpK5Swg5lbovNCPlgmRCqqv+nzWWcWGZUbhBf8AO7kyp74/sgNhuXIDyawWMIi9sFxA+oENPCpjwYzbkp4KSrWdBYb1iAr0BsOiiuFXYeMq7QRnQJQN1LLVBZP/KdomxaUpbTdWkqzPLfu6Mc+IeNpanvGijwqv2z+FEpQnrXw7o41WxhQ70kaDTm6rk9d6oyp41qOOyY6cidjz7sa+1empLHn235wFRAWNTzdyQofQxmxNhMSPH8U
*/