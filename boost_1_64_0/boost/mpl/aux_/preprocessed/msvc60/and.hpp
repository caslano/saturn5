
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
9wIYApxuArHhA+JYKiQVCpvApv/ngnTUyC/TJgzgruuIylOydRM/y4YZ/YMtH1fit9k4FhfRYXP47dXpbY0PwjmIWRuOCfKBTaYTmmtna+qc17tJBNhmOmRy9jKdBEFLEp0t6NrqGQb9Kjxpnj70NHeafWIm95wV8MVJIj/3eese/1q20w5QALXwpzqnxI8EZNL+YCXB96EFovgYtxiotGMmN/vngwSLCVx/uzFFsKt+Y8BGL30ER+Hkadej+McpB/STm5O9+zJNx31+JvMf/VKP88DtNB1dH3CZuB4dcbdU0AEHwEK/QytHeFlGxTkvdSNvvfO5NzvsjlCepo38IX33K0z/OAqiUDzeXGA9kKhHgT/7VJ9Gfr99WkqImyWNKxLV4x+rgf16Z+6ZDSWiDRMmWNAwfNSROX2zaj+K6iG+GKYvvyc6RGieyzaKAXOTaYbxSgZ1i2YG9Wc/pM0PPdaOVjgvaux+xQWQzZDHFbehidVD0orcJDcpV/SZM8w4KDJ9ueaxkK+uJzc8EwAJXL02vA3DLJzm8hP3SaObWqzxPDVgArCAMiwFNg==
*/