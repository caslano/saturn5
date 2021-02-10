
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
pds6ituePd6yB6HHiNws7mmruT9xO5JB1lOBE2ihR+8tly3GHIvD9nGyVUj4Wwo9S1qy+EghlwViBcsCgjom39/qvLIfy/VS3I6PQtfprdVhrKl1e47TSxE/xka4rI/kTmaQ882aimPz5MQ4H2+1fKz2bETpOTOxnOXjok6Li55tqIy3oqTS6LYKcWtDRdZeUB3f8KXFots6iFsvl8jZRa/jm8GhcqCYzPARsgz6BVhE9kyVtutVBxeVZa6RjKerdAiHyxkkja9VGheXc9rklYYwmPtgMNvrg3lmcKmtkY5jhpJvccQQUfBWNuFsYiLjx+/Ad6QwDA2Tmnvfy4++EVi4zkX2eDE+nDzjZlGUyRizFnvyRrZZZ/vEjCbcLLf5A9tcF7ELNrtud6zmva6zITuYxxatyZPelbBhi05nEalqkUaxJZtTCCuO2YTlSsHYkLEUlznl6YOM0p+acR6U1GyfSMOwUR4VK874vriXJkWjaRRBRtjr+W7X2Tm7KA6tuScEXUSVJEVbiwnf13esGunpaD1YrjuJ7RfLbrQa+tvh7skzhulICPpdPaS3uGAfOdLrWyN/O+8MkmGmSvoTzos8kjUyXCOfLINpHTiKoyynOT2sxc6SZ0HcajY9fJQTjqHmKhjuxrY567Ls
*/