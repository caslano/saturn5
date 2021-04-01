
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
gx8s0+q6tpLhPUqUJS0Hr5OBe6dH370OZBRO1bqtgpLuP7nRI+qsg3OrRock/usoIdzzH5Sy5eqdiFj4CvaJ5w4mvgLuD3r9J/QIZCstr7oTDQXewIokdIdjIbc8F7/x/NrkKzvYV34AP8k7PyJmq6K5ZWrmbpBrIzRRdKhEwGUVPP1QxbmZu3fCmrUVVcgaljUUYUjhCDxRPuhKYtEct+eIDJZQU+TsVazxgEDRXtrglaKosDz32wCpPSvxtfL5Zl8Ry4Svwww0wHXOjHMd+lkVlwLLKBkd31W2gU+IzCgAj66H4NhfVj8OUZAB78Q3xrf9e5wVKDGwbZH3FMJuReI9QQ8+1aBW+gMi99gi6upv6Dy+NPsvlM0AqPTvLK2ly9DwGVxMiiosbfHAtrNgQkVTlCN0pK3T+X6cry+7auppP9QYNEgs/DqixWc4H2oQHdQ912jCbfg0FpIKKklXu3x/mwTyGwRPUnnIdmvf9dOGw4V8MYZK03PSlsCdveq6p/Ns9yJHYmZVaMk5olwhzmD3CofwyCC/ntjL4CnMzLQ6piukSNEBnLhbhg==
*/