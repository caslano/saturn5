
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to

    : equal_to_impl<
          typename equal_to_tag<N1>::type
        , typename equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value  == BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* equal_to.hpp
jg16P3JPRpHTqYFTo/e8djH9qJG25cMl1MRZxruL40uYbtE6y4E/k2XmtooyDY+hDPRgpm+cdsFLxc+0d3Pg/SZRUGGsLapRAsT7rpXHJykq+Qrx7cHBSqkKDkJIqNRWd+rWrjO32AJpA3NO278wGCYBl5Qr8R1my8R6wFNGrYY9r/spB1azfX4Xi3Yiz3GLvvnv9icqlPSVIoCy0Kidnb/WcL+1KlFpgjbatW//vJLgZwF3TiOtG4jTsDru3wK1a7BQf/OOrQgZCVq7IOZyvsPa1gBDWkM13Y9RCj1QdbJ01DxJfY8c23V7fBsf+0fMyCgMOtcD9k9BSgBraP57qKHX4WrW9Vnlmm++fdfiZcG3qqkmxnJthyLktaybbgI2hnq+F09pAlZWeq+u5HGaRY6Ag6slI48+16MWO5GlyZVg6yd9qbViA3j4e89rxsk48WJq+c+SlXtOgfXqCgcgOHOr2ilQE4b50+Z2Pg4vXsz2ym7g/ddpXXe3G1tgCoWRT82BJJBFFzy/SP37qmk4d3J958wHeiQkUibtcx60mJcr7PV6xuTU0nc7KiQiNu9H/jo/fxK35ehA9fnPeizBAVILjoV5u+4Gm5EDQIciSbG2Z3UoZpbJS4iVlN/9UE4H4AE6HYm1c3rMFrwfSzM8dey72W4wG5ZwLuG5o9kvXWIIKifwomcqTLpLM5jndBL38BXuDNfSY6q0rYkq
*/