
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
OnpYl1DquWklHBq2I+gllOE9B/ib79Tq52vbL3QJxgkHAqqjR3pJfeA+aPh+AWP210U5+S3xeFDGVh/DQ0WSXKUO6XnZeRF/g68vQl1+ChJKMejaiwKz7owJQyPPxiBRlmuVhKyUk6dqHM6l7vf0kBhc9SxmlGNb0jwuPaBCRAEcO4V8f2OsW/9KSX0/kHdDUIjbyqxLWxdNVCYep0I2P5gRrkktNQyK7ljSomdUd9ko01ILs8GKBetIXNomO8SDBMssdRp0bk2xuSfGTQ0hauOO3722ZOxbrlHCxaZTpMI9ym6T2EaNQ4a6zraAWNGdIibuN0uSdyUrLJBPnQ+2IE+yrofN7huWGlke6d38jIVF+mjjWaP2fmwocM87yYsB5D73l9cwSyct7o7qUc6ZtoplGjzKW2kfS8Kc5R1/jgblsKB1bGLBDd1pLJOKCyW9fAFzyC64TWg21BUPDsRG8da8XoCpN0A0CYvqn26IgylEbgkKAAYCD618ROrUFULweng9SuncpdzdMdPE1A+RJfwnd9GWzl38b7o+BJ9buBhMdXqVR3R6ssWMtA==
*/