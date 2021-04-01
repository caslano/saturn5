
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

template<> struct greater_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_impl< integral_c_tag,na >
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
k3KyAfVvzc6F4jFu3VQ4O74y209WHuACM592jaDVtVzc6GNVAcqt5D5gX3fUkpa6u+dstxW8LPfekeC6Qy8OLMRahd5v2kkFBpxosku7FUvMN3G+XnCAfe+lxR2vvE1+2Tjns/dMO6X5q1ibaQGhkcLUHA4qigJpdRzOw8Q15Pr7VHPFjSd/cTjkF2LPYCL30be+YIBoqGh5NezKq1+D3mwU2PGgvkupiwhYS25fiYNkr3q6EirfR3n7Zn9VMJAviG/lc+TYCJF55kw8bOhXVhe+LSUZmtE7RkCjBR8EzRu3S9hwIjLZMpVToKKLHDQozsmVyO5nH6A4tkQPLgVep5ecH34u57T2gcC2/lEzByfdVtK/3x/AeI9hezqL2NaB1Tzvjfna7/7PBfNxLKNGlI/Y5eyIv/XCd11Cc/5M+4YPdnk7qxqZKprBZsn4NDJGAu2RQJMqM7wZ2+QJWhVcGd4tbM1UrPYOz2xnSi8Hs5wvLRnCkFHy7QGhNDkZ+L9IczSuk+sKQpgOS3YQc/Vzyvkhepi1v22Pu8IpA9CvC+/QGSrh9dJ1u2Ptgg==
*/