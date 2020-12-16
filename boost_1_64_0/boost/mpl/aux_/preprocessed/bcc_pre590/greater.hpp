
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "greater.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater

    : greater_impl<
          typename greater_tag<N1>::type
        , typename greater_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater)

}}

namespace boost { namespace mpl {

template<>
struct greater_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value > BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater.hpp
dIjzp5982o9+Bs0Wg59ygn3kK+epkJFnaDFWML7fgSMY30kcR5uDcv1k8AiZd3FcPTVB59UtQNlOOC1B55EtwaEy/0qw09nIdC71SOcztofP2R72sz38LaTyl3Oe+hXnowfAItF3IS3f71h/GIN4nhV1yvo7QeqB+vlxpvME03kSPF32IqkXtoKdZN8/pOPLNuqD59nuXgTnyD4/eDX4Mue/r4TU/8OfON/dCX4Kvh7ScfIN8EcZH0Kqj9+U/IBvgeeAu0M6Tr4NXgC+A+aCe0LaDt4FZ4PvgXPBMuqH96U/gh+Aq8CPqB8+Bs35XpZL3wDPmZo5uZbLBIevuWKul6b5tV1f4tdHnDPAVlJnfp1/z/Rrv7wMlN9f7tdymQVOBTGnNOPXPL+WzxV+1ZuYYxo9udCv/W4RuFOe+/vVT8YS8B1wqV/15zK/zseX+3U+fg3YFLzOr34xbvBr+a0EzwNXgSngTWCez5xPM+V1Kyj9eDW4DLwdvBVc41d9egd4D3gn+AfwLnALuA58HrwHfA28F3wXvA/8ANwAShluBI/GOPcHsAH4EJgIbgI7gQ+D54KPgiPALeB48DFwIvgEeAn4JHgFuBW8Dnxe5ARfEPnA7eCz4EvgbvBl8HNwB1gOvirlBf7Jr/PunSIP+Bp4HPg6eAL4BngquAtsDf7Zr/PvN6UcwbfAC8DdYDr4FzAffBu8FHwHXADuAReD70k5gn8FHwHLwFfB98E3wA/APeCHom/AveD34EegLIg/BhuDn0j9gvvAU8BPwW7gZ2AP8HNwAPiFyAV+CU4By8Fp4NfgQvAbqWfwW2l/4PfgfeBB8BnwH+Au8GfwM9AKoPxAH3gIDIAYM63DwCPBw8GTwCNk/gQeCX6t+xE814q6pT47yuxn6OdLzme+AU8SPRXU+eV3YA+ZX4L95HdgqowrYLrswYKiH38Mav/5GbzeGPXU+blP+reIHdJ1bdCh98opz+0eem8c5Unn/CojqPPaTM6rJgS1X08M6vifBRaA2aDkaVJQ1yE5QZ3/5IJrwDxQ9gPzwaeNn0mdB0wNaj8uDGo/LgJDkKUYPBpEnZn56HSwLVgCngXOELnAS4M6L5oJZoKXBVUfXh7U9fUssBAs5Tx1DrgSvAK8BZzPeSLmxjybanSCKZfjZF7OerqB4+VtoFxfzX0GlKGZt6/x6boJusKUy91gIbgOvNTMPVW+h8FJ4GM+1c+Pg1eBz8r+AdLdJusM6b9cr/8RPE36MXg6+IqkA5aBF4PQMUY/fCjpgR+DM8BPuU7/DFwB7gdvBL/g+sT4GOK5zePZDppYuI/5LeL4N53j3yUcZy8N6bp1Zkjb6WUcDy8H8TwTlafzmtkhba9zOD+cC+aIvg9p+7gipOvJ+SGd5ywArxF9H9J5zpVsv1fJ+CRdiPOyJSEdB5aGdBxYxvnkcrbvq8EEGQfAWj6zd2zWOddzfn0D79vq4zlTyTPr+yytJ/O5mftutwR1nLtN2qHUd1DHuTvA82XeGdR9sLvAIqnvoO4r3cN2vz6o88v7gzq/3AA+J/NM8I8yvwQ/k3RBEeYRtv9Hg7pe3gI2l3YCdgafCOo49qSkDz4FDpO8gBPBZ9j+nxV5wOfAJeC2oO4rPR/UcewFcAP4Eihl8UfwBfBl8M/gK1y3vQruBXeCn4Ovcd32BlgHhI407fbPQd1nehPsAL4FJoG7g7rP9HZQ95f2gJeD74LLwPdEf0l7Bu8F3wcfAPeCj4CfgDvAfUEdzz4TucDPQa5reLYUY6vHumYR9dnioLbjJazHpeDZ0n7AvhIP9erVYDZ4TVDnK9cGdf9jRVD783VBba/XB7Wd3sD6XRnUdd6NIPc=
*/