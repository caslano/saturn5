
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less

    : less_impl<
          typename less_tag<N1>::type
        , typename less_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less)

}}

namespace boost { namespace mpl {

template<>
struct less_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N2)::value > BOOST_MPL_AUX_VALUE_WKND(N1)::value ) >
    {
    };
};

}}

/* less.hpp
V80mlaMJuPfYq+kqfb7VS+0CRIxctdRsnjy6XPcZd+2ruok0CnBfVLhJNmqEtVrSrOT7l0tCW5yqkQgw58kB2dORq0NbkzK48Gz6zjaioeOUQHxZ9DQfE874fMlyyDoqZ5DrmU3RwHZdL//p6zcJw09+BifTo0f864uONiU29AMnUlUetjXcRm2fjwng5cV929FmAQM8UevFm3CWJ2TP4yZ8MwNVef6+wIwLCdTfhSO3lO7h096/b6N6bW+6kV1bJ71nXxuhEYqr34uQsocRW1L6c1080YCem4OnKzv7l3BBFnfWZQp32bAZSPSDG/gAYNoIBTE8XIRmIC4ac188O+Mj6a6QTr870l5JAwN3u94kIwwF1MNxpw/cY3DzaZmPrJngEkGgcCTbs0wQEm7RFy5QCZQaAZozBdgCeUIBIpdh3VWX8EsyWQSq8Er8gzUsZWH2gvnBKSYDcV4t1FvVs1gtK+AMptgH9nxAFmKHzSJL+4ayEEiUv4y34M43HRH/V5tn+u//sss52Vv8i4cTtXN+NZRlksDEVIAlix3rQ0B4YkY0W81EhB3UQFj3KymxUTYQ42WIZ+KiwRl7fRt2VmJlcuIYYUXtF3oPL8s02ZXO3VodFBamZVQwr/B+LNobkjbujPJ6kj2XiACRlAp0yoiOi5M8g6rQBhtLPfYyJa+AuXUTqc7ziwUJCbeH2XGvhLxMGE0sDiUdimOY
*/