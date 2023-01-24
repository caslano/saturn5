
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/divides.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct divides_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< divides_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< divides_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct divides_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct divides_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct divides_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct divides_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct divides
    : divides< divides< divides< divides< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , divides
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct divides< N1,N2,N3,N4,na >

    : divides< divides< divides< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct divides< N1,N2,N3,na,na >

    : divides< divides< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct divides< N1,N2,na,na,na >
    : divides_impl<
          typename divides_tag<N1>::type
        , typename divides_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, divides)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct divides_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 / n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct divides_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::divides_wknd<
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

/* divides.hpp
UVspG7bcaunA0uy8Pk9U1yhD7BjgMBhfSfd+gevP0CLfl2dv1RKxN+6J8tHnbmofLeK0uqIWGEx2FxJIMOZQYzNj0mOHtf7VTzgyQi+tXFO1SBc8y55TMs9UMv9mp3xbaUciOZZHdVRt4wu7Wf2It/62xOINreoJfB1LJAwnuthqO73jsnDC80n3StEoXaRsZOpSmcO0GkmudtiB4KQkxEiZBf6STkS0hqjcPBODsVvzwYGND6TdKodyj4lUAuo7M9jq3IWm9+ykZv1cSqOczookKScCS1gbE8gluCXVO782DrH5eZvHKOGVaVSx2YNvoUInGPGbfq0WU4E5pxqM90gxc+7zfjtmQJpn4z3h95jQtzgyQEzRjJ1XdKNR03kDLaw5Yinew8Ojtmxzjs7FhGxuQ+hr9WJAWbX7aVN6SIyWU7Q2TjbjW/DQ+qq8QOtJXaOBW16s5Ww34XkHn8QVyZUnixc0pjQEwEtNG8EqRyDUq60i/mCNWkI0bmFILECtHuKJkgXfrvkrnXHrYCUG44lJG7OBDfpOVYW3neJL9MGK5xI66JwZuV5xEzN2WJtOqdTdl88ci86fWVNcLNyDBWsBRVJMa4s/d6DUl/Gyb1aVGtDWpZxdRlWHSh4dEz1GGL8ShbWsrHxmOWRgukOUmEK+FbqsQlC9Dwta2y9/Wd4pOR3af8KsCaBqrxKa437lndbw+2BXupEDyTBd
*/