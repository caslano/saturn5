
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/and.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct and_impl
    : false_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct and_impl< true,T1,T2,T3,T4 >
    : and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , true_
        >
{
};

template<>
struct and_impl<
          true
        , true_, true_, true_, true_
        >
    : true_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = true_, typename T4 = true_, typename T5 = true_
    >
struct and_

    : aux::and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , and_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , and_
    )

}}

/* and.hpp
wAu+rRPAHwwIeIm/6aa1u9uU40P3Md2H56vXh5+VAP9wh52OT0YXYyZqYbvfA8MRjDAlOxY8gFu6WjeCqtQeHcm9+9z96ySPZddRIjmif2/d1P0o/6+6gwHZH3YPqB02Uiie7S9NIT6ufqnW0Ota9T6gSd9Uf9U3If2DYa8Hq+r2b83+Ryum+6KOb5uP2r9pyLTIIjYdx+c3cJWMp9AnrTm1t5Kf6+a+xyacqqLgMivZ6eTqctbEfCJ8RhJ6u8GxE3UqcpRmN1Gp/dFqRozmswVHDELJC7RTDG/OLijZyC54LiqNhPIaGIQ7d5Z36HmffkyS2Vk8/ESE8WQ684LjrvcOc8fy1u55igU57ZC5lpOOO/u2sGvU+WIL9U0CXxBZO+g0/yXcIr0ZnXKpapK1zSWKlVZGpUpEzEpxqeS2UFXpsJfSTv2OJUBWv+EDL1YC98kJRecjh53OR0C1OGwcJ9cOm93EYzhx7KPnsF9XZ/QZek9aodca8J5ezz9QSwMECgAAAAgALWdKUvcMACLuAQAAaQMAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyODFVVAUAAbZIJGCNU01v2zAMvQvwfyAy5NLNlZ3l0BqqgbQrlgJbEyRuc9ZkOjHqWIYkJ82/
*/