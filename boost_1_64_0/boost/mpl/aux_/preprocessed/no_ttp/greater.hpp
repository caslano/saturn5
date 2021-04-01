
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

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* greater.hpp
DZUCMmwawzTCAXjCYoadD5xkmJIFbyeXaY8P2OdR6Dban0J9QwBAHoWik97Ky5z8x7WScUjcrbHQJ2KrRnaxmypQ2XNX2sMq+nl2yBgKwUzpHnwfIKMWIftJueVL6d701aS4FEntOO5HmbxXPjDEsf+lGF+6iZRvprLGbWyY9MyoyA0vc8BA+jKS+18ruypoxwjh0gnhVZw96jLfY+fLvjTFbXpXOEtiUMrI3tjrZSGKfUGwArfI3J+2QgrMccJdHuk+53Ee1xiJaGWPq12NCRUNYQPRXO0NOXL0pjXmAPv+spQT7orKzxP6+Vb61RpLJCCp8eD+8HGEyWPxNJXAJ7Giw+jPl5+m2TbbF7oD3rzB4WsbzvMnH3e6mFXqMFc52qKbiSlx6+e9hj7+CeunHF45cq/hJnGD3ZxCDP1BHKGOYSp4K/9fq0wOGm0KQRP51bAdSeO/YtHYGzFHvzBM9/7fF8vuDsw+YH0s9Sw9tX46JEayTkYf+fdXbUjPmrXPpxxOzS4uQqaU7hYEIjPB6cCQgV6UcosqpiMzx/AaGyoZwp8OAkiTsJRvFQ==
*/