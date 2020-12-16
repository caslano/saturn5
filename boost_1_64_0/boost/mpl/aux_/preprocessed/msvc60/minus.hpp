
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/minus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct minus_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< minus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< minus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct minus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct minus_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct minus_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct minus_tag
{
    typedef typename T::tag type;
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct minus2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct minus

    : if_<

          is_na<N3>
        , minus2< N1,N2 >
        , minus<
              minus2< N1,N2 >
            , N3, N4, N5
            >
        >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , minus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct minus2
    : aux::msvc_eti_base< typename apply_wrap2<
          minus_impl<
              typename minus_tag<N1>::type
            , typename minus_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, minus2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, minus)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct minus_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 - n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct minus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::minus_wknd<
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

/* minus.hpp
SeeG6I9BmO/GeBmpw+h3hLCbUEg4QSglXCEEDfczhBLGERIJWYQ8wvHhfv9142yUD/e76rE2lH54fEf4/UfG2qAfnWs+3oa7feRUNt7GpmXaMTci3vZ1Oe5GIn/Tj7sRRJqGESIJmYQcQj7hBOE8wXeknyGEMIoQQ8gc6a335528k3fyTt7JO3ky+RKS/6j3/6kpiYu6dg/tYf/H728DoLyDDggw2PtwpszJMm0lSL+phiAKzEIPW8qnI+TA0SNMybGJbrwntpXVN2AfvIuxltXLO4Ok2Dh7n9Wqdyb2uByRuByWsvKnCY3Zj+EZbVxG807Zk/cG+ricq8dzonGR5tgJUn7YVN4bBGFTtivXHXtqarxSBaLSftF/69im5FT7u+X5hERjsmX+siNdNOmUZkzS9J1e5KTeQDOOE3NEG1eOG51OnQp30kr97r2/jzxjy/5nyTuzVOv+p3bvFjmxtxv7VL8vSkX1+7IFumPmyjFnyTHjCS2UvH/OeszekRM5rvvHJJ05pvRXLseIkZ+5PYhPHeyCNZXOEqzHSLWl20zlLY68H5pucEzVXRzLx9e9PA5gPlDmU2PjZ5rMjnfObZRz7madP2HL9+4G+zunVsQzXdYvl78nhFrnz9vmZfsSmU+X7ctsf+9q0FxXcfa6A3I8+XupbX3Z/rJtPsw6X2Tbv6x/yra9HP+0bV7il287P9lfsW17WX+v7e+y/lHbfFdt/h2X+gkpVck/NCmSLsUvavPPmOS4P/S+ivyTe5W9zkFWIz6TKclxRoM2fWZLfE/Z5rur05P5rpJecj5m2f68Lj8v6/KzXJefl3T5d9q2f/l7mS6/SlT5FeDIb84pfS5o8mB2mDaNI+S9fB25D96AbYjrmZc0aex2vSFXaSz3YLkebenhXt8vnr7vc/5e8tr1CeNpv/yu3rcuDFOWb3mgx+FhFw8fGDRp8XtfvjOjl/U9XYxBvpNxq5TH1SBESmIHSvlbE2yBTbEHNsN+2BynYAtMxNZ4FwbjA9gOrf1ay/ctHJbjqPu1flnKB4uwA76CE/FVNONruAVfx/14Gp/Gj/AiHjXId6p815ZjfUKB7P8L1quF32Eb/B4742XsiT9gJP6ISfgTLsAruAR/xmX4K+5Eg1LeDFUwH/3webwOi7A6vo41sBSvxwtYC7/B2lhTyXcMwrqOckH5vmUbSSdHuSCq+uKpju1U701TZbsE2U793rSZpG9zbIQtsDu2xHHYCmdha7TGQ74jYZaTeHSUeNyI8dhF4rGminzvyfdhOXYmZMpvsN7svw72wfo4CNtjOPbBwTgGh2AUDsMEHI5mHIFLcRRuwNH4II7BJ3AsHsNxWIIT8COMkPdVk7A3TsYUnIKPYCQewZvxC5yBwVXJC4xBI27FOfgwJuOjmIKvYip+jvOwOgmThk3QjJ1wPvbABTgQF2IsZuBKXIR7cDEex1V4Eu/Cd3E1fohrsQzX4c94N9YinbOwOd6DXXC95KN/Ffkek++3cmxB8JX82Cj5ca/kx2Zsh1uwF27FkbgNp+N2NGGu5MMuSf8H8Tg+hJ/hbvwB9+B1HGsv1sF9GIT7sRU+ih0xD7vhYzgQD+AYfBynYT7OxCdxFRbgYTyEZfgUtpT3dKF4GIfiMzgNn0UTksfyHki+e5B4kS7a90DBcr9oh/WwAwZjR0mXG3EUdsJb8SZMxFDMwa54BLvhOeyOyndeGG5i3la+vkbXL1bgKL8KfWO1ZJlSrh2G6rLrCOZPTPE1bNP2jeXoF0vXJ1YC668h7CYcJ5QSrhACR1OuS4gY7S2v/W+Z/tD6/6lz49J7Wf9PRdnfPf6/Usf9q+Z8pvoq3xERY4dO6aXpAFA=
*/