
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
/50i4nNk9WViYK22KlJYM+LO2IGJo98JD5jSwvRCLWuvXp38VmuWwongiEKX7I5+ZK2CUBP4JNIQsF+6QlLmA6h2BSZgbXZCSphMJQDeNlTaEB0mXJBcEF8YMFAxV6tIQ91mo9H8MjLMTpnA+eOCeIKpzx+brKLFdHV5vnpLaZ/i48N7gIP+me8PKT9p0vXlwC/OOb1/zjp049MCh/PGFPTmdJ67oDWkQ999TYc5Xc7dFR0O6Rznr+d0iT+6Pl3n7hXtdyibw/vsLf2TuhEdrenEdzM6Ai9yqnF9Q92UjqZ0PXdDnHvUlaj3j/rl0+sd+JyIxDdBl7Q7yNFIFKSQ2YsyH/ZYEKmILwnLWfFkx1WFN/C1J1VnaQo8l/huxIG+HKyUbOsy9JE/vZtzmXhg4SOedrBHYSIgNDQYrIUJ2SoZl0o8CsGpe8pbDyhvNRroTOJrwpSAsAELoFpxHbHksTSchlxJLbemNh4v7ZN64+vD/CMMOy3EcLeqidyC08yUMY6oAio3GVQr4b2AgFb1A5atfUGBqsCvf1SVr6gqP3L+m3P+/59Cu7Rx7H13fkr6ZanYNe2qboBAVYVOrcCYFMT3U+g7UkYYJ5kGcZycWlG4Oem8Aqlq6mwFg6Im4G6AYWItlxPryXI5G1ue
*/