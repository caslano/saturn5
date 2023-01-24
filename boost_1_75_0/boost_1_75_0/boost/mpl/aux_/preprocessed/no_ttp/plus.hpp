
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/plus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct plus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< plus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< plus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct plus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct plus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct plus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct plus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct plus
    : plus< plus< plus< plus< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , plus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct plus< N1,N2,N3,N4,na >

    : plus< plus< plus< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct plus< N1,N2,N3,na,na >

    : plus< plus< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct plus< N1,N2,na,na,na >
    : plus_impl<
          typename plus_tag<N1>::type
        , typename plus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, plus)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct plus_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 + n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct plus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::plus_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* plus.hpp
3aK235QHIIaDukgmlNi9fOREVqWLBHz+iDsi3kEGW4dyC/Di9rs1ObJVfDtSaKjgymfA0a7n0devSGIcSVyE/lURDYixgUuNd3r0mLH163vpMsGzhFAj2q0Jw1httf5zV6hG+HmYcxjerro2/nP4MZKXFMAlLIzZm+5O7cTw7MzYEfRtF+m1hd5H3YcdsrbgjeqNjkhsfgqUoW6n/bsETgojgEwPW0Jmre3HcUhCopEWRaIwGiF6AkpOsFQhrc/r5ZcSWA6orWgJ6BooGmirwRXBZwObjlFTKOLBeXanb6F/Sex6R2iQgHan7YEORgNXBkmygQqhLZdEK9zoQJQCFAJUYJ2cRaEThghuLKralucWmUtu0JO9LZDXjICM3rWJmVx1eDLRciDFAn0uxYqHXEODQa6c384whZU9C0K1v2TK96rJpwisrp7tZXcPTVP9wiFIw1vbcKVtzWZpSH+UevQyU/jz1/IklVUr+Hdqfkd23jf1RBGSkjYDc2SB5nxZPMSVNhWS6fkysh5jOt7DboOJljkllaWS1JLW6gjySteoxMYUV1Y77XV5/1885kPMC4HqUw5dY/1gUyXXJHjS22i5zl9Gtn0qg5McXzMsxStP1Ua6nUp3O1YLk8gEd4953dHEQ8vPgmG+9LzpQkMTsPQUXAZnJUzum2TE+ru0BMbkVn+m+9qGMDLhb6IprhYGH1/nN0gLUgt3xX5K
*/