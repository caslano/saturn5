
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
n9XwmkFVvgr85VVQT+0J2FigyCAT2wvy/aiLWq8sS0kv4A/j2frU+L0q+3qUmsDOGHGtrWd3ho4S1zLi5WVZJYBGQHMSTEbL0rviuDNQa7CUWUdUYe4j+FKxsqtlWrMA4D5R+7N+RLoRv9gCwoIuDBAdOdi66MGvfoxezAVS3Hv3ZfbxUNZC1F5HGllxPsd47CJ3UgchzpiYxZ+Z4X4zV+X8jlMIiuI/4J8A/4kbxz9cE9j4KExxwC/1MeRlvjTXgv/tyz6L8mag0d56/j/SQkO5i673xZMLARoPbzKXJtcHMeL4XMPd9hzjI0Gz0IxGP3kFwNCHb8LH4HfC6905i/feevNifuyx2hydZErpfeJBTJ0S7jNf/X9sAGi0SBbSbLDjoxJwicW5siGCX71ysKl4Z2Bq3DJYzDHS1ctksz7kvWxFE7p6IeSpzokH/FHzI2kmwsd+AoM+LVVXbbe3oDGMGEwcK/ck3LJJ9qzx4xoiMFRh5KHcGGQPTuxvcaHVBTSxOou1N0UgtYHdVCiSHb2BfRFQBRaFnwxFg8afCmP/TB0OsO2TLIvcZA==
*/