
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
5i9/3rvwwc9WUf0McKjsFpsBqjM+q1W+MCl6zk6+0Tk72fT80q4B9Iv+dnnLJTueMpR1W6NQivA7AM+aZ8LuUWlY+KZ1ilKXa+D7rDx1CUtmofPwXtNaQecs66douU5MMeuOWx+mvzSe9JBMgnlMEVyvdPOlMyzEZlDAb0cWGxSEJdKdwG28okX+ETvVdyKadSlYiGH3zlm+5JvbpQmmsUXRwip/qIZiulaUp5wGidENiJTatG8XA7k87FNgaUtRBszTiVLo7HBu3Ynlf8ItcqPvwbDdUI4LbHqOFmNDlboyGMm9XSQLO8/9yCsK9fYnFK6P7eKTgypxW1yCZgQ0fTRnRqsQLuy91Awtc4KqNeMVzb5IqYZbcJxT6sgob7QRVcGLmevCoIRg/cdYQjNd9eNaacTCemdI5rf0GdE3MKG6sEeVqL8Srx/OVA9mbVcdn8vyZh3X19z3H0HXaEbDdBiKciQFfdLfyOOtFhb3cqMQO+vw8alehppmuspUiaFI5QDBU/qDpsGvas0U3WklViNNCDR2LCZ3JeYJgy0EklXUc/W5SJ8w82vaNQ==
*/