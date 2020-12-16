
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/not_equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct not_equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< not_equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< not_equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct not_equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct not_equal_to_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct not_equal_to_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct not_equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct not_equal_to

    : not_equal_to_impl<
          typename not_equal_to_tag<N1>::type
        , typename not_equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, not_equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, not_equal_to)

}}

namespace boost { namespace mpl {

template<>
struct not_equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value != BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* not_equal_to.hpp
7un3ZxX3zs96dB31xK3fnrt7TGCuC2mdxKzKNbA2yrVlVCZP+Q3jhZ5YWX7DVJXfMNWwFVbHAPTGvlgTh2AtjMK6mIoPYwbWkz7UR3AVNsA9+CgewMbyW8YHj6AvXsQmeAX9pU+5hfShtpQ+47bYGx/DEf9i717gayzjAI6fhlpyiyG3mGRG2lwSJYal2VzGxDBml7OZXZ2dYSq5lFuFCrnmFkJuEVNGLrmUhCS5hFK5lRWJdPu9Z/9zvJv3ZKeOVJ/n/+nt2zmd87zP877vOTvP83/f58VmmIIt0IotcRi2wlEYiOPwMZyGQbgI2+BaDMYNGIJbsB0exfZ4AjvgFQxFLSfUEe/Czng3Po7NsCu2wnAMwm4Yj90xCXvgcIzAadgTZ2AkzsXeuAqjcCdG4y7si99hIuZgCv6E/bCQdk4HlsR0LI1W+zysHvL3V/4uX9K2gYnt4bhHEPsdX0MvnIeVcDHWxTfwUVyCwbr5Zt/EWFyJfXEVDsO3cDSuwcm4FudgNr6L6/E4bsYzuAXP43t4B3XbiqVwB5bD97EGfoC1cSfWw4/wEdyNgbgHw3AvRuPH2Af3YTLuxxfwU3wJD+JSPIRb8Ah+gkfxMB7HX/AL1M6P+xIr4wn0xq/RB7/BJngSW+IpDMTT2B3PYAyexRT8Fkfgd/gc/oDT8Dy+gxdwM/6Ih/AiHsNL+DVexkv4M2rn+lzBQvgLVsBfsTqywzn3C7AlemAg3orBeBt2QU+MxtsxHothMhbHTCyBz2JJHIml7OdmeMjvC/ndoR1XYdpxJMdVBTmuKqIXVpbjqipWQ2+sidWxId6DD2ENbIE+2BN9MQFr40CsgyPxPpyEdXEe3o+L0Q+XY2P8CJvgPnwIv8CmeKv2vSHHWzNsgM2xMQbgQ9gCu2FL7IWtcCgG4ggMwnHYBhdhMC7DENyFbfFjbIc/YHv8CTvIcRWKRdlWHbEedsJGGIbdsDP2wsexN3aV4yUcx2MPXIYRuAp74yaMwlMYjd9hDBZnv8ViaTSjF8ZhI4zHh7EvdsdEjMYUHIKp+Cym4Qy04ExMxzWYgetwIO7BTDyOT+IVfApv4fgYjLfiEP4phkPRF0diII7G1vgcRuHzGINj0YrjTHJOGL6IE3AFTsSV+Aq+jVNxK07DvTgdP8EZGKt9jlZ7mqqt8TQFrfFU41NqfMpt41NJHE8TWNatUWNHKlSoUKFChQoVKlSoUKHivx+FWVJucP6f6aasaRnWBNtNAP7mPQC0+fkLUelLPto1A7EZycmZtnMDynrltuWC6q+rUKFChQoVKlSoUKFChQoVN6///0D9eu64B6C9/38hX/+/vPT/PbNU/1+FChUqVKhQoUKFChUqVKi4af3/+g80cmf/Pydf/7+C9P8rq/6/ChUqVKhQoUKFChUqVKhQcRP7//UburP/fzZf/7+S9P/9Vf9fhQoVKlSoUKFChQoVKlSoMOz/9/0H+v/u6Ptr/fwqXpQh86Tb79dSlKUQiydLCHNqH8u9B8CjrZgnPXftkclma5/UWFPu3PQgce2c6Nr4QgBl1GLOQQ/bTOWmPHPiV5P5UN9jKc6ykeV+bZ1vyNzsV9eZO118ckaSSdbriRKGc7G/tOTP52IvIXOxb2AbWFA/D3uUPPaSx9FoNAf7pXxzsP/CY/n/kcyfbpuffEhuPUwd/PO2vZjcD2CjtD2bpZ7W9iVO2p7ez1LQto9d6p62u9rWJ5cat3WCtNVbjq2qLF/48a/F17TVVkUm3k/LLNDxRdswnvGrWHM61ZO2SXvTLTG2erSUejxT2HFvP7Y59cSvqIe/k3rk3g8gw9LfXLDtHvvGNduduuXb7rKd09x8zMl8/X8=
*/