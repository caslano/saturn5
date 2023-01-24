
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
yIUH2g9Ny6NCtMP/+DDS6xmWc4V9IhULjzgcqPrILMtwMaXEhgyNdxQYlk30yYH/Jotxg7POAE4/9rnc4Yr+/aYBCaMYk4XSS/21+Qz8Jg/WJCqTN/wZfLMy2farH8U/AH9CVY10jy4KBhaCmztUswnuBP4sz3RIHXgtUBOAfRuogdEpRvsVSZM4uEPztk0I8PmWCTN3/z0SplvZIw42l0Zy+oX2MDqdA19oo5i7P9Ud2mK4xoVL8/vDlJ73ioDp/c1f9TpTIup+OVuReCDrftGDdNp2rV6NsGl52mX9MicKHSH46AvU3eI32GobIdnwUd/qVmXpQlAmn5lcGvrx17zXISltB+lTjIx4s5fYaub7Z4cTvy2BUXnDhwTE/FOVQ4hZmhlWblY4z/TtQ1tkDKZV5hR4KXxqVaAYBF1/oeSugtoA0gCOUyh+QFsKFKdooRRaggd3d7dAcXcLVlyKO0UCh7sH1+LursGd4J5zebiZu3va2Zedff3Nt/+NmaOpDJ21XrYI5BTzhWLwhMwVo9ZL1nGWvwPOtC05nhCSyMPPziZ462q3fMlZXePXip9Bt5R7CHTnAKIARVR6EVv80LQnBAyJAIHYzJn4vFlofrWOT2F2gUh50xicNGBfL2IdoBugYQG+sHb8W2FYPIT358Kw90JwrZnjfOifheE9+/alXYXbznjdnmlRgDdLgw3Jxb2nRfVnP0VJ0L7q
*/