
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/inherit.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    >
struct inherit2
    : T1, T2
{
    typedef inherit2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, inherit2, (T1, T2))
};

template< typename T1 >
struct inherit2< T1,empty_base >
{
    typedef T1 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (T1, empty_base))
};

template< typename T2 >
struct inherit2< empty_base,T2 >
{
    typedef T2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base, T2))
};

template<>
struct inherit2< empty_base,empty_base >
{
    typedef empty_base type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base, empty_base))
};

BOOST_MPL_AUX_NA_SPEC(2, inherit2)

template<
      typename T1 = na, typename T2 = na, typename T3 = na
    >
struct inherit3
    : inherit2<
          typename inherit2<
              T1, T2
            >::type
        , T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , inherit3
        , ( T1, T2, T3)
        )
};

BOOST_MPL_AUX_NA_SPEC(3, inherit3)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    >
struct inherit4
    : inherit2<
          typename inherit3<
              T1, T2, T3
            >::type
        , T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , inherit4
        , ( T1, T2, T3, T4)
        )
};

BOOST_MPL_AUX_NA_SPEC(4, inherit4)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    , typename T5 = na
    >
struct inherit5
    : inherit2<
          typename inherit4<
              T1, T2, T3, T4
            >::type
        , T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , inherit5
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC(5, inherit5)

/// primary template

template<
      typename T1 = empty_base, typename T2 = empty_base
    , typename T3 = empty_base, typename T4 = empty_base
    , typename T5 = empty_base
    >
struct inherit
    : inherit5< T1,T2,T3,T4,T5 >
{
};

template<>
struct inherit< na,na,na,na,na >
{
    template<

          typename T1 = empty_base, typename T2 = empty_base
        , typename T3 = empty_base, typename T4 = empty_base
        , typename T5 = empty_base

        >
    struct apply
        : inherit< T1,T2,T3,T4,T5 >
    {
    };
};

BOOST_MPL_AUX_NA_SPEC_LAMBDA(5, inherit)
BOOST_MPL_AUX_NA_SPEC_ARITY(5, inherit)
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(5, 5, inherit)
}}


/* inherit.hpp
Cii93NMEArthPM1sBM/hekcEBL4y4ZleHNVQ5Jne3/0dr1kPxpW/dw5c5eytU0pYhXoiPqzQJSU6mwiYh3sbYNOfpQsT4evn58h9/TJCCml9QNvQRHIBpaMX/R++o7L/5ao5vLOkh0WpmMPPXrcVAg+vmVLimb/wbVoA9VMeheAmaU4Dta8h3GCvFx6Gz1JPeQv8WsDNOvGZ0gCWoDZ0+cr1OgfbCu6dNr6As15NkeQ7F4OHnk+Am7ltfA+DIEerL9uXXOyvI/Yoe0LOf7atds6Qxi+HYqeFRlbOI75UBHljfy9ay4dcemJ/61I3aQdfnGVQY1KK0z0FVa+v2vIW93uTemvzMDR4mTAEQFq1DqekDq4cLudpg47T3DfHgvIAdhB5mNzxKSG/H8bNQ2fJO+4HJdXYczzFgCQWCycCGhvCCL+eWW0lTz96Y8fuU9DXba590GUV/rWjPWWuo5eGv1bO+Nz8WvvQnIN3HcLBpcbRxsalRVig4xS/+liUHfCnJEmJp++pTKWLN7WzOO+VkI0GtgM+ov6Uccu4qbSo1wz/9Pj6ppJCZ6OHFcEeWSm/6//QZwyiOb0+yck28IooXiwvT/cCSjs4Vl1EYW3YYk5HBFz4LhWtenk6XDucXHr4oJtpYA/1PUcIVh9LjkS2hQeem454k65tXW9C8PTIbZZfNZ7DMUvMLD/UbWpIS3sE6Z/d7B8cUH+C0J2k
*/