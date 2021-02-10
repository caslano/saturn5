
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
template< bool C_ > struct and_impl
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : false_
    {
    };
};

template<> struct and_impl<true>
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : and_impl<
              BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
            >::template result_< T2,T3,T4,true_ >
    {
    };
};

template<>
struct and_impl<true>
    ::result_< true_,true_,true_,true_ >
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
        >::template result_< T2,T3,T4,T5 >

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
tv/xvgFQSwMECgAAAAgALWdKUqEFs+aTAQAAqAIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QzMzZVVAUAAbZIJGBtUl9PgzAQf7+E73CZMT7Nmiz6YCo6FeMSkyHgjL5VuAkZtAutTr69RyGbD/ahhd79/tz1pCPrcmUpBFnpteFjQ93OtIUN4SGLIZ6nK8je4gjnkERZAlIcEqQYMEeYUvtN7dRWBYFsaVt3HC2UUyH0OyAvZ/yBaInAlcphL8BUG8sBa7AwZLFy18w7QD1DXlK+QW007epK09WkIzsZaYdEn8HZ1pvImyJkq/HTG0ZxusLzszNGo/3KS8xN0yhdjOF08R79G5biD5UUYz1c5l1dkXZjmbn/2euGsHbbPTQElFo15LuIrdKfxPXtdG1UgbuS9KDel6xPHPZdYIQYIChHJ57zUojjx2WaLeLLYyaLl0kmZrMLnE4H2tn0gmX3CP4cjbHhFbXVusO+S6jWjlp0JWH/6Fgqix/ERia2NG4C8tvnMsG2Nc7kpg7hJY0SVNz7rjFfNuinIUW2dEM/qtnWdMqqfPt6H0Dfa5/Au5+XRQC+RLYacMPTDGeBH6HhZn67TAJ4fllkAVs+SEqx9yEOw/kLUEsDBAoAAAAIAC1nSlJK
*/