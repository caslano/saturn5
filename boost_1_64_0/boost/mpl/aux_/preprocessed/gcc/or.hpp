
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

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct or_impl
    : true_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct or_impl< false,T1,T2,T3,T4 >
    : or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , false_
        >
{
};

template<>
struct or_impl<
          false
        , false_, false_, false_, false_
        >
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
        , T2, T3, T4, T5
        >

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
EU+yJaPIJnBA0ZsRg8fdqUIgMu2J79OWV7jxw9xN3pKGlNdqwei3WPzXqgig0FDHL7uEclwGDHwK5UZfza1kNKobKuqfe4PwvMFUM3Cvn2DaSRa1BraEhIQYFNMQxPcDNQ19B/xwnz3p4IHBGvjb/TKhTEV/Z0URSwDAxrE358mCloSUdynAw62f/s/bE7YJVNcYksFrLHfQF5EU9+N4AdWmMOyN5mretWcDQ7Ubm4euAprVR70sHICaBt0JLyUBdeV8s2yh/CIdSup1iXbC4PReIYchMYV6v4IZP5FoOqiuXeJFKUfStpnKXpKrep7SpLhxCy45G3eUZbBQpDNiYHO1RYL4gKc1tb0nDNgAKpvBGBYEqCdxpNJ8xXQ6wEI+DofrXOoGpZ+orfeeDxj5yYCT44x5ebeM0Yb3dH+qLmMl6Kr80Aduu29JP4FmHuIjzrTPGU1tvL1Te7z9rFLohiRwHLYKdw9ZOVG3vumoVxdf1KTMHW0oGg9A4lQpjaKqwbmq68ku/a3oBjqcf72HGDAU/Sz3KaZbcpdonBZosk+wIju5OKY+NuKIMw==
*/