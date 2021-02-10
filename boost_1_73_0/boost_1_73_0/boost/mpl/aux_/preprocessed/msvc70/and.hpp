
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

    template<> struct result_< true_,true_,true_,true_ >
        : true_
    {
    };
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
Fbsc9300MS3tsfv9vNTjZGZxjc4Nrla/RKJ8FrG/77sq9jsnWbg64iKZxFmVySaMQXKKAyfHS0JifJUHCb1C0q4Ye94yzcI0dTI2Sc798Y/oiC6uXXO/XDscDtz57lwqpTRLaOImUQ+db0+B/ojNqKBRktMu/mVrFWSzG1yVfbaDLna3WcR9n6szU5sYFVQu2sXX3PVH46sAVRjhsqzEfe6IuyTN/AVQSwMECgAAAAgALWdKUs7dy93bAQAAMAQAABwACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q0VVQFAAG2SCRgzZTfb9owEMffLeV/OFHxtszQsYcaC6liXammFQRZtVcvOZqoIUa2oct/37NN+NFKe54UJb7z13dff2xFOrQuVxYnTFbNWtPnBdtXbQo7YbMsW4QX3N9lcaCKAgsoURVobEwZ3NYqP8tKfioheax6xa5ghWaPJrVVgUz6VS3NF8qp2IkPPw/hejCA+Q/2TTkUkO3wEwxu4FHvaWI4gOFIjG4ESe5/ZiyWE+B3kNoQ8LV6QbCvNq+1RTbVjcPGpVm7Ra/763jpNjX7vmuaNvV2BbRo6WFkNDqR/OAsWJ7WlS8QLechIElsNmGlc1ta0IUgG7UhkMsOSEXtTaNqUE1xIJfv
*/