
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
kNVttvmpsQlpS4mm52v6VfHvMUSZqDMe/hbBW4JL4kb9FSzZae5ExFpTMeOIo/y8b3QFgHJXyOf/k9GcUqebOnaqAd6boYH7ki+qoV3DANfyHPVuteC0cFQxP9CRUrDc943eIrdnZytWH2pSXmUDXF/3sIiEt1mcwAbn1vKsIXVdrn2JpNCpjaVKB3+OARtN1csz18Xkn/rv7Og8EnVA+RBsMri3vVejs28HSYOjvYt1gBYrKUkU1qHBREx3UMyJ8tyu9rfX/tIC6s2SLUq9eymzr9/ssYwRFis4mIUEtGcMaAu/LLjUuAX6/0F9FPf2C4I3Rbygo2a3a0His0qGBhyW3frIr4Mj3+sELYQpzdfBk8+glOTCY1KFlmMxBNZn/4ARev0Q2EHhp3C+OkgAZ2MPVbw5s3rOIWKokVUuVeqYeY+hVCtFgEdZvFvbX2g3hMez3mjo0EJrU9nj0V2SiJBo3rrnu06C7TkFSv6iiHadV87XSrNU/LKzv/gYbw80epOoUtPOEP6WeG9BsoiXzCRHAwWcwwQW3qXv1N5+xqUfGz6khVQDIXplwA==
*/