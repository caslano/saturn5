
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
O/Rg6DvjzqkRQbeoD5m4cZbQ0uIX2mdql3D1JRErrXGgxajsM/ol7CeWkRyzj2kyPbJhkjedCQgzSR0NDvCReiYaGjj63ZLkXJeJzuyvvn3l99kEaVWPsSWgoDEdwquhFn5vf2zXTzAxf2VruM1X63wHlgXLdM4AqV3fszMWWqbpxe22rDbF8oKxiu2uSuc6H1HhfqTI1B9wNM0EQRiohnAEahHC1KBVHvaIFs586+hMnHN41eKIl54ZwF21vgNjY/wwOnLadRDc4I3VjNEaD9rVGNtvLwmUP0DjYgWGItNjaCiCayJIUC3kSyTEfXrHzMR9yZqVdXbq3T+eA+9MCSz2Gt9UP3T4ibXx6+M6EdVTkcMmEeXmbw4sPOHdKiv4nIg/95sqjPAEK9OPWulpTf8DUEsDBAoAAAAIAC1nSlJXrGobQAEAAPsBAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NTQzVVQFAAG2SCRgbVFNb8IwDL3nV1igqCfUFtgYU1SJUZDQxHaAbUcUWleNaGOUBCb+/dKWj8tOzrOf37Md4dC6TFpMmFC6IB8OePklk9uEZSdT7VDayw5tJo/IRPgoirDj92GD5oxmYFWOzMN5pVC7DoqsBZ5tW1LCNOlG5waF
*/