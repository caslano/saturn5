
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater

    : greater_impl<
          typename greater_tag<N1>::type
        , typename greater_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater)

}}

namespace boost { namespace mpl {

template<>
struct greater_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value > BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater.hpp
/Mq8U2MAAUMU1Ba9qbJi4nGswnJfmYMZDnkA5WOvKdQlH/rFhfDsRlG565B2qNdDGvdJPlBJBGSXPuZFDJFNnvtoLg4qDqq1uABm2g7ie5OsDGwNO/bLQzRrMaKaCTDugGgk/hW0gzpiMmyzVlkbFpZdd1VFPe3zb2Y074CjyvjVu4hzo0BIlSo6v8ItSX71Rt69MAy1x2T5D15PGpOOwdL4zK2jUEFmQMm3/46JcPdwEn7tfvGBt38zT4MnZcjU7I44HMub6wDCg75Jwv9njSSu2YwYBhqF5Xa8Cqf8QuQ2a8Kr6gdrnKBql24MAE3VkvsssOhefVRTRbvT8o4Mvm3HDyDcB/LrdZKGny5YUSyxaVgJD68l+5mnFBKU9skCmcOpU3NrPMBo3vGVZahJpl3+Rdt1IZ2W4ZDT0LGBrYo3d2d1CzGoTrWai/9UEBatGQferP+hJ36++2oSEk54KJWY3DkhA/ZMSnVeumCeKtDn6SdKWXIFThKqEZW5FzPDlwSps0QGBkcdtg5CmmCAh5LWdmoIoX5FneJYJrNNc8q0APEN2lFUmiRypA==
*/