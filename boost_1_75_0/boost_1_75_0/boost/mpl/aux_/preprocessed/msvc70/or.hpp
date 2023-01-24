
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

    template<> struct result_< false_,false_,false_,false_ >
        : false_
    {
    };
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
1xIZ4+qdRR1dzFP6taNzh85CYYQCJKBfhAIOIJSEMueMpDlu76+64kntvePb84SE9ZXX66lQD2/uuJXJ1jkhQTbnBmYzpygSpnnEOP/Cv8Ox0WavMsDn5Ojy79e44tXUt1bh8+OlpYwkmCOxt/r17jSNjETLjM96heoz5aMyDnEj84bFnETzh20ExqqOq757cTbmE9U18/V+UJFmZg8RfHf+KS1hCeL3nnduYyw1GR55qwSbMVM4VxvVYZ8YprHPISzpwYYJp6UOoMqcZz8RhRtFceGP8ZQHC2RUqpAt192Ak8es88orztppfpw7g3UxPg2pQKtvdNsLrVAzf3/YMv5sIFhFX3/bLI2r00CA+gfEhqoKdM8PBHjeP9JT65tugV8oTF+vZYm7vZ6jPO/5lUeWuvwbrvufRTbjt4MV6DWcHDOYCbnrtLAxPC8On3ow/X2pLnUV805BsnHMq/Jc6R4n/IunLFfVrZj4NzOUnTnKd39FBlJ1PY6i8TjMB+ly7OGUSaf0sTwrDLcXqqUBV+jxaKx8CqXHm96pDo2qvmdCSHZ5/334gq0/JW46a9Vw/Lt7jFqW6nCJqRstnr1lRbe2iI3fd3MvzyD6ucr3kHQybkMqrHCa/Su5MCaM9gSEB1YjwPgV3889V1UBmc0O79YCSjt3cHvtZ4sk1w17KnRck+dSofiOymui4NK6a2U+RKgSXjQr/48JeLuS
*/