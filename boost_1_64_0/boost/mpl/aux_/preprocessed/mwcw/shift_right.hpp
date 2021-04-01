
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
EX1qFMwYqOtoX45YILJXCPu3W36PtDvPoUSuLLPBgg71TVvppG2X67uYV24ytLfCpcs5/TOt2vHIXHDWVh4LSKfFRZXoNetZa5db8zz5aE3a9+7/uNvMB3OtFD2EALHALzBfD0klK+0GOxfzN+VSUlcOMk4PX+QswaY/E6CvEQHYl/ZJivyKzwDnACZ3m5oFb7Dj4QQTREbyTJhQLJRm1ZwIqvunwDIJurH5vem8+bSNPDG7LCQYCAxrohamfavSY/iOufGamQrR9ZCyhbSqG8C4gjMwqNor3Dt2O/U92tjCz1gmTr6VrnJ9gbQvTl1ngYfqwhID0FBrFumTJ9hzCUwgYNwr4DH4BonGzukAuVdiSbEIE7CDHbNT5uOMHr4TaMHzMknrRijq6iqqK8oHWou1wGweolYoL7jc1sifCXDyOkUrhnP81X644A0jCL2y7VI6rMOjzoFbBa7ReK5P4VJkQYU7/g7MM/O8SuMy2xJ/CmhYUKlDdFv/Z5he6eBPFpgiZFVST4w5qKhEBm7B2/R9UkMgoRMStd2gtSkw4H34pTMF+EKjwHur4g==
*/