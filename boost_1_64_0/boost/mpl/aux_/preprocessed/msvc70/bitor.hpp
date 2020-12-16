
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct bitor_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< bitor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitor_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitor_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitor_tag
    : tag< T,na >
{
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct bitor_2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitor_

    : aux::msvc_eti_base< typename if_<

          is_na<N3>
        , bitor_2< N1,N2 >
        , bitor_<
              bitor_2< N1,N2 >
            , N3, N4, N5
            >
        >::type

    >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct bitor_2
    : aux::msvc_eti_base< typename apply_wrap2<
          bitor_impl<
              typename bitor_tag<N1>::type
            , typename bitor_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, bitor_2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitor_)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct bitor_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 | n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct bitor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::bitor_wknd<
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

/* bitor.hpp
YUdsjXHYFpOwHd6F7XEt3oHPoB/mYgc8ix3xY/THb7ELfodd8V/YDd3ZL7tjXeyBvtgT78BeGIy9cTIG4Bz8E67EQFyHffEB7Id7MAiPYH98FQfg6zgQi44/h+wffwLk+NMXW2M/DMQgDMIBOBoHohmDcQmG4DIchFcwpZJcQ5Rri0Ek5bgZK59/QyWfYeiFw9EHR2ArHIntMRz9cRR2x7HYH8dhGE7Av+AkfAin4JMYiQcxCs9jNH6FsXJcisNbcBp64nT0xhnYEmeiHybiEJyFszAJUzEZN2EKbsXZ+DCm4i40435Mw6cxHV/HOfgVzsWLOE8+DxdgD1yII3ERTsbFGIeZmIlLcR0uw8dwOe7CFVLvfG+Q64x8N5Tzjg4m4pB6XyOfb2uxBa7DO3AjBuO9OB63YAzehxm4FZfhNtyK23EHPoj78SHMxYfxdXwE38Gd+AU+jtdxFyrB7cEGuBeb4pN4Gz6FnTAbe+ABHICHcAg+gyPxWVyAx3AlvoD78EU8gi/hZ/gyXsbXsYFy3McW+BYOxbdxDJ7GJXgG1+AHeBDP4lE8h+fxY7yI+ehN/X6KPngem+HneMVSP3JNUq5VKtvBE9fJftZC2n8b9MbbsBO2xQBshwOwPUbh7ZiKd2AG+uFG7IBbsBM+iP74D+ws7b4rXsJu+B12R/kNjFx35G+JT/0bmFA32T/RB4fjHRiGPXAkBmA4DsJROAFH4xQcg9NxLKbiOJyDEbgQx7v9797z5Y+418vv9Zt07X1ebuTwnoKb+3sZ23u8/D6/m3H0/i7/jb+dyT7gYTpFukTy5CSuG2k0KYW0jnSIlEe6QHI/5GHyIfUihZHiD7l+d+N6uB6ux8173JTx/8qoswq6//8Eg/v/LyHVIi0gRSj903cVjaeI6O7f2zKirnBEVNnHilj7qcMY52qe6fg8tWHNS79fdIbMF/8c37Ub4D6cQPxRq/Txa8cth6E8Shl36VFn2GrLuWfxuD9eG7++9PvMl6XMueSn/J0aPdfyPF9VB3V5flL+PUUGuFnGHslr1nFOpwzmQDikmQMhm+cyfrNovMmD1GZGgno8s+14lzO8ph0nmSPjZKmAZF4qGlMtv/2wPM+T32mkSJ0c+832Pu5plVjWrbDv/ZW1Sn0ajr0uGkccsc46X4NtOzgr1wmf55SzIe7DySyTt0HfDopHCMkY0TL8liFuc+nbXOqyaJtPbFux9662bDPN7xGuyvMEa/39rB+nfs3gtwQ3tL8lkPclzJHfBsg4lsFyWqU8cSPdSoqkXEGFvxMyz1RV77TUuLiS5xv3VR8nZB+R7Sn5PSH5VZf8lOWi2pIM8kuKmxuZlJ6Y6Eie6vmYG1bRl2k0saQY5ZE+q9R1W8sTLuVR1992yctb8qpHmkp5NhrklZJujnekLLb1Z9v+UtjA6vwbVtXnH8H7sg3ynxOdmB5XhvzDNflb2mFshms+Fdd8KqaDgcrrJ6e/7LH0Zb9xiUsPVn731e1Bf+x8KlEmOb/BJTIGxWZsi0nGtmBr9MHe2BT7YHMcib6YiC0wA1viAmyFV/Cau5yHyPkJ+Vjmb7kkHzLtZGxDe2yGt6Mf+mFX7IgB2An7oz8Oxi44ArvhGOyOMdhD4uiJi7A3LsEAXImBeC/2we3YDx/GIHwM++NLOADfwIF4FoPxEwzBz3AQXsDBeBmHyrXRYdgMh+NtOAIDMAz74UgchuEYjqNwNI7BSByLaTgOF2AELsfxuA0n4A6ciHtwEu7DyXgII/E4RuEZjMa/41Q8jzF4DWPxF4xD5T7c09ATp6M3JmAznIGtMBEDcRYOxCQMxWSMwhSMw9loxlTMQDMuwjm4CufiJpyHO3A=
*/