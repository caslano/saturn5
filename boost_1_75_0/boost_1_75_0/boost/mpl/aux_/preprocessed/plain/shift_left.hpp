
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
+D0lJTflYQrgdQa4mkL+XALa3D1Bsu5WoWomt3yUKYKatJ0g1hIDA/6S/E/7YWSXLy86rMUp2kAlZO0sPAhn0LFLMB7D+5KHC50MJSb4Y4/WF4pvgt/iFz0dKtADej94AJWA2XZMPigovIlx4t6Ptt6nutxWhp8wjgSmoEM5+1YhiOyqloQ/nkeWstQkL3nH0mPpSTWYMOzebL1taJWOeZkeZmJGcc0/zZAOxGcpvM0+OuzA0K8dbhi5SJoIcLQfP6GZa/Z2Zw3172K8F82oeaYK+lw0Bll37Z11kLDKans2hgmh0qmvdftc/TlrzfekhKnK3nor9JJi2AyH/21sEsR10nNgfI+PWq4fOu++f6VjUjYGnAbPdg36gx5SPXJ87Na42AVE7OrfXProXbkmQuRTJfU8HpTZWw2nVghWXFPUdETQkGuNe1dXWeoYgWludGpeSJAyPfobT71EccD1C4gLphwUE5SOyoXGicn53keQvc9NZPqV8Z9dOYwJOlC9P9ZR/kq+X2WswDDF6KD8haOPZYxvjFaFJWgbUDPQSPSL4BftMroDptMrUzQHFKfFVbXwpYRyqEw9qTfHtyzdpXgbrG9i3yLk16JsmOrsQxDIZe0INw2Y65lbJWyzK8+oGZzt5AxcOk/84wIcGkpbeQy/aQtH5awtrU6HktWWTg3givlvvl8gf9d1dEBlEhCMEnF8TPe6CQNVcqnr
*/