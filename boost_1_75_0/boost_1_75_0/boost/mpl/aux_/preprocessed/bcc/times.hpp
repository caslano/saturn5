
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "times.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct times_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< times_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< times_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct times_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct times_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct times_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct times_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct times
    : times< times< times< times< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , times
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct times< N1,N2,N3,N4,na >

    : times< times< times< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct times< N1,N2,N3,na,na >

    : times< times< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct times< N1,N2,na,na,na >
    : times_impl<
          typename times_tag<N1>::type
        , typename times_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, times)

}}

namespace boost { namespace mpl {
template<>
struct times_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  * BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* times.hpp
X9Hw0pi9esgYHs3bK5ldKpLiyTdJ/gW9YX5yoj9r9ARL242Y4L0QizsjP7ndybOGXwebznMgCOHRuxvbsnaiFEfh3uq0rYzaXjbrypfoF01r1iednvsnzRg7ms8b3MZKtcR+Dx1FTB9pQpwTSHwh7lOQg2CESlMLcRcQOMZXsr1txqFQmdFE7+86qvGWI+ia3g+WKCDY0zbqbkBj0kPU5gVj9M3lZPTn5mUUUTHfbgH+IoVtvFYBU3QP5uQirmIREQ6XnoFE4G7n4JH6NxF3PvQ7Mj1dk79hr9sjPA7jE2y4sydlxz88lKhizoCnAH9YcB4T+TnAgQMzqvt3CTHzX8Nj3r3FQc36XJC8RJHsKqASnzLgsmFPGxI5EqYZxZnLZJBNC+9UElNM4HwAJ263zAnrRD24uvW0CD9V5ZNVdEKB/jEr74RB6ndFUY8yxVRY6plbjNeSQBWGh/aU5gSNbnZqr8J4jrBbxtOMC3mj+JyNH5F15FV2LWgARubXk1eIfOXX/NKdjDk0vTX0o57RA9PtHyNiS3ynL5d0lltWMG5xsBkKDSKS8aDBLjbH6AB+aRfl/elddKtQi1641SXN+yc0YU84qXIwmiPJ5zsnOuMRESr0hAZhZG6gA+6oPWgndsVGFs0fetwt1/Z8yMRwda2PUeF/2sm2uRY7j1hdpTRATMaIXYihA+Smue9ATF7niY+4dns8WVajRnCQ
*/