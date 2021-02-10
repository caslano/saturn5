
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_right.hpp" header
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
TMbBiILDLyXxSQGDpVQbCQulEsDYCQgJdi2b0hU2BaERZ6WFXNgCUGmTOqrEIjNHDZDGCENwXBJ83aLGsVpJAzlnJfaNlUwsyCYTcYboCKsbkFf6fFuKqm6IaUvqhUMi0pRX6HfXGoEjW49J9GOEC9pY0QYgRGMLJpPWpIDSw+lsHt08BIfWnYfZY7QzHEcE3gt8HBh4U3CnOKUA3s/KhX+B832/j2R2FPDxdUNQ6jOvRFqD3SlgqUEbG+txxpAxjQq5BFdnyrgkXDe1CFBWyqhY5WOCnz18oP623A75m65DnnBOdvYSM/Gqyunh8+RxfjO7d8hFHPMSw8f02G7/u+9RKrv7f3ayqv5TNwct2UsK6U4n3f/3/QZQSwMECgAAAAgALWdKUrV74o2FAQAAAwMAAB0ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QzM1VUBQABtkgkYLVSUWvCMBB+D/Q/HA5fBjV1ndssWUFkoGxM0W7vNZ62rCYliTr//S7WKWNvg70kl9x33333JcKhdTK3mDJRqpWm7QMPe22WNmWjLJseF5i+ZWyGdrtBNtTKoXLhLFdrZIJf4II3DFcwR7NDE9pySQiDdXWg7DJ3ecPJu50u3EQRTJ7B7q2stEVG5Q1C8FMF
*/