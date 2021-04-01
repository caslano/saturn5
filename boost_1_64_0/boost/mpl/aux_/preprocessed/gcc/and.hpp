
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
UQDPg3ZITWa8rdmDsdwc0ttfGzMurIyBgDo6ek6fjNzRk3dtOK1+jqWHwFKQZX/YEjna56jwJItL6DFJOUAOW5P+NvhbcZvGPNm+zsqNQYTKz7XFWY3qvFYlQ9r9hNYkV1zvjThH9ZqRBMffvnwGKgtfDKdU7DnwGr51Vco/N1uKC5qYyzAhGxV0RepnjK7amQMS1jrqx5F0hbmTXwV8r+MFYBTYEVFqSsEq2Fa9/2ZJKALjQLNWJYTUzMjmKH5SPOzcwfO00MunjI5todB5P0hTiHiXzm2ld/xMV+lPxmphZPg6Bxz4ptr6ZWvXcnBqwOSrdGu9OggO24aPq4GrBPchY7ZTVay5LgD07ne892DMAUtkzs6ZCvjr2+2icNfqWkOs9/fNYzZM04pneNYkCeksa1Ibc6TE09FCeQ2OzDa7z8ZV0QDv/q5DvQbfQ133lQzG58rv/+sbm1QX9pBlbTgMIKP67pDvoxJf9jufFi5apUcm3Ia4R7h6fcHtVkDc2FVtMjX8VS4N+8ItI1oId/Ud2ZujKBIvmd5MyUjmMqzx/lj9/yrw1T2ZbQ==
*/