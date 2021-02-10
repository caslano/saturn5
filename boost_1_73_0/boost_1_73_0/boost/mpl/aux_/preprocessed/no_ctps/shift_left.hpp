
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_left.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_left_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_left_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_left_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_left_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_left_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_left_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_left_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_left

    : shift_left_impl<
          typename shift_left_tag<N1>::type
        , typename shift_left_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_left, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_left)

}}

namespace boost { namespace mpl {
template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  << BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_left.hpp
721buAVb5vmaNV1NmpW1fO9Zxi/JjAf9mI3hDdsPbGOnC2RZi7u69/lCkgwMnn5OYZIksPoVsW+SUEDe4SdI5vDbfvhMmkA6E7O58JqnlzxiAShgcBe7Q8BL+Y4Re5b+5MUWutRYHDnpFH52ZqjgORORJmfOYy63AkaTNJncxoW6j6fz2d1kNv8yithXpXBH8as0W3QCNr0vFrEHawgNxc9otlQJuDscGVSkrRGgauvwosr7HQ4u/xKvqKkj9r0zpo8rlN5bj64fkBGLS2tjP7EwkowfR+Qn91DrgRMmpw6BF4SOF6wi2nn5KRwDWVuDdrCvJPkAOoegjSNfD2wJ16pr62uWDbIFq/Xm9n7q74eQQWZk4xftWbrsQYW2gHSDsNdUwWHVnkfYllKhv8DDDciUbRppimBJcH61XL3lP9biatjvevWa81DqrPO/x2687T+h4tA+yNLjgSo8LBcq6WCDaGDkKksjlgV3HrBrLVk1OH96zGHgw+kxRWxpHQn4z8VpqwJu+M0w+YxfMBk/s/nl2f8DUEsDBAoAAAAIAC1nSlIMSvgMSwIAALsFAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NTc0VVQFAAG2SCRg3VRRb9MwEH631P9wpJrEEFtg
*/