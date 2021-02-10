
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_left.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_left_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_left_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_left_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_left_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_left_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_left

    : shift_left_impl<
          typename shift_left_tag<N1>::type
        , typename shift_left_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_left, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_left)

}}

namespace boost { namespace mpl {
template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  << BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_left.hpp
KbU/1F55XRDIlhqz79uHA/fnRpMNh34+FAzwAyuGMjSMPlZTDM4Z1B53lQpcYOcJtfWBVIGuxMu8a80lyB4Wg9Gfd7c3zB9LQGlVTYNb7BrjmKNscTx67mGpDaH6UtriTofKdQFb2mlbMFmMbJS5q2smDu5mQly8rtJsmcwuWDdZrTPBQ9G4LzEKjxZOHDmM6KXuJ/9Akxjmzgbe34MrQQ1egHfk1XW5H6IYwQDAOX/7B9btQX2gx+Q4o+2Ax0IFhaoM1GKoCPvnw0p5/CSyOPGVCxOQozYLjMq90unUtC64vE9uky7WHJWz+9p1PoLkKU2R/TzSr6obQ9e8Hd++P0ewSNJtBNlHssBlBGm2WiPvdrw/12+bZRbxtPMQKU5mxPlf+wNQSwMECgAAAAgALWdKUgSMCpO0AQAAsgIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q1NDJVVAUAAbZIJGBFUsFu2zAMvQvwPxAtip4yb8N6CQSvWeOhAdbFi90W3U2R6VqILRkW19Z/P0pOGx8sUSQf3yMpCT1p5TET0tjG8XHA6dWNtc/Ez6oQxap8ELu82gmZnjwynYPPocTxBceFNzUKOeLQTeytFalMhL8A/sjFA8AjCmoVQUBmqINnh3dQ
*/