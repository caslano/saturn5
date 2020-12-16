
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

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct shift_left_impl
    : if_c<
          ( tag1_ > tag2_ )
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

template<> struct shift_left_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_left_impl< integral_c_tag,na >
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
    : aux::msvc_eti_base< typename apply_wrap2<
          shift_left_impl<
              typename shift_left_tag<N1>::type
            , typename shift_left_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_left, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_left)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, typename Shift, T n, Shift s >
struct shift_left_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n << s));
    typedef integral_c< T,value > type;
};

}

template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply
        : aux::shift_left_wknd<
              typename N::value_type
            , typename S::value_type
            , N::value
            , S::value
            >::type

    {
    };
};

}}

/* shift_left.hpp
3G+L9Xjv3d65LTspJ9yxLfJdypO+ecaD9liPWat12vMC5aTptEe+j3jUpuc8aJO1j3p3cG7TS5RT4dQmOYx60J5dHrTH+ll4m057XgnhfXt7DD4Pu9+ulz1ol7WfEjo6t+t1yqmzt8vxM6Xb7XnVg/bYxqPUac9byt+/JG175POZ2215w4O2WPfrvE7ObXmHchL02iKfcTzZr3cfRpu8/Z3b9L7yt0CvTbad2/02vetBm6zH6GJpU4C0qTPxIeVUNbQpOyLT82P0pjaqdsjYEvxN0ewrB3Xq/Yh6a231Ht4xebl+3drzPp2d6/6Euv0mW+s+/GNwuX79mv3gkE79e6k/xlb/kR1z33ajD4q7OLfhM9qQZ2vD4R9jl+jXrx0vLcC5/i+ov9JW/5EfUx9zYz8sCdDf/2sc2xEfN/o0D/pgkxvbwBLoXPdX1G2ZYq378I/faW0bX/dinfq/pv5wW/2Hd7wudeN3wNLVue5vQ2i3re4jOz6HuNGGUp02fEcbKmxtOLLjcZmLNvSX73PlMgbARqKVuL8T+994GeOG0YbSLe7c19kwHmphPMvJfZ7xDf9m/NLo+tchttdD6l/72l5H2sbFLCS42ps/vTA71zpmZ0uso015jD9gkfXxw29ZH77vaMa6ypqv3CVqH+vme/qzgLfUY6EvDqSsvChNP6R0l3vJpB8GSD/4NXwny8+mG9y5B/hor4cyPlcF2yi5e8P30p717ZF7XlVjLLIumvUJC9Jfn23xDfe9/p3rk8a69A5qWJ/X4jXrI2MSy/rIfbSVx2CcCP37UI3uo/V8/Aj9+2L/+nEl9O/39fy+3qM1roT+/buej/tgdN/zXfX3AZ8wqWxF8qju/X59scgStmZIp2MzHkSQRa7Ry7md3k21928+prrPs87FfM/a5pNr4NBJZ74HVfNVuSivyjYfIeW1a6S8GBf1rlfnWXJR713qPFCaeo3LK3FR77Xq+VzUu0qdL0pTr3F521zUe6H6/lyHeg3zSmnqNS7PMtG43nz1fC7qzVNv34lSbyPlxbiod6V6u7mot1w9n6Ze4/JKXNQ7QZ3PykW949XbV1OvcXnbXNR7vjrflot6s9XbV1OvcXmWRON6b1Ovh4t6K9XbN1HqbaS8beONy+uq3g9ctC9OvX1dzBejmq/GxXqMUO8HmvUwLq9S5uupM99z6nplvu6NlGeZJPM1cvwL18xnfLxK08xnfHypcDHfhertppnP+Pe3TjWf8e8bkSTzNfL7kaCZz3h/LtHMZ7z/Vcl8AY1sj1rNfMbbw2+yzNfI9ojRzGe8PfI08xlvj0rNfMbbo8bFfCPV+98Uma+R7Raumc94u6Vp5jPebhW2+Yy3W5lFvvfhRplPnd86WJ6z6YntsBd2xlCMxj44EfviZAzDXDwJ52N/LMYBeAkOwuswEm/EaKzEoSjPbcn3L+aV9qif27pU2lMi7VmIAbgI+2IpDsDF9vL4/mNcXpKUN1nKmyLlnSXlTZXyzsYS74Y8icW55CAjkvn3RtxFfE60zCOnGJFMGOVRLONnG3AD1hAHiaC55DYj8ohVxNa5Ph496yN5FfVyKhrnUxymef7HMW+i5Ex073mg17Gun5dTTsTIU7R5EB3zH64lHPMeOuY8dMx3mETMVz1DtHqE/TminSPszxFJHkNyGOo/U7Q70Mv2XNEe+tuWxxD1njHayPv7WGY7hvG6Fp1zFRrkKZTnkDagwbNIkpcQJ9PPYV62Z5ICY3lvu/u5CY3zEhrlJHR8Xkkv/6BnuQcP4HCUfIMun2lKQftzTdp8gtVEJO/txhS05w7U5g08xPYLyvexxBGZRCmxlthJfE74FvB7SSQR84k1xFY=
*/