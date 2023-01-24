
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "shift_right.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_right_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_right_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_right_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_right_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_right_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_right

    : shift_right_impl<
          typename shift_right_tag<N1>::type
        , typename shift_right_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {
template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  >> BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_right.hpp
xhNoV1g3HygfGW8etnDdS2Z/p5Ds7b/5e8ujM730FRtOKYTWhQMLRHu3w6fM6G+UOvjguKXymh90IGZE4KwTVK8wZMY84L4mjkf0Bjou/Q2NYSoZJ8gu9HAnqAyCJlH0J2yR6q1mLAlpJrKLXgH/1zgocawNrW7nca7aAC5VrvY5M54yE9u0VYobmfaZqpF5iOnmIzB5kCfo8/auNpmg7qon/9SiBZVYo0yW2UrsFR/+Foc/98m2b3Dx4g5BTrNbQcgdVxfVZt88tAd83it8wxdcfjuLhIce3f4JSctQwvILKXmX6Ta45DrWhQdDEeV8Lr54LPrl88a5d636r8p4ODtSuOIPu7wnShvenUULTtpOvHbH4ves7trt72lUsPmuy97rtCeoY+mEqamWUNrgValyvlVpLjKa6eh6nTwuMnlSv7L33rYAnOOqXGCu0tT8ygcu9zBf9cnA6MenKrYArlNHUuN+/drYLT8yvVrapqRiy7cGXn9y2b9l6yl99qGu+IRS34pMgNhtnNbhJf0Avn5YsKgfg5Ai+Yln05f5Or6mdE7rycQvgPyq7C+mDlxZubt8St8wEtJnqlTRd8OehzmpgBLp75zQpRb6fPkhaK40ek2yunlbx0zDYdUa4VgVv11ryXaOB0lZloqd+d9bvx77vVDTqGbnc0LkS3WUiWbWhJdUqQgUv2JtCniMMGW+GSRGF0YHjPSgdrfY
*/