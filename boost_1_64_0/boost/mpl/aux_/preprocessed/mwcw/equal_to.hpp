
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
aePzTn+3999+xvkZOMzIxrZ7T1Ps1L+mkQZNfjpf09zfjfp73i9hkfgb2ts272mKraJGZ0tdf8+8C8cWs6EtF/eepi1fuxp9+T4s/u7taGUhxjZaDW1su3c0xU6HKvf3iYc159zzNGKAcX2sMLS3bd7RFFudr2hu97Wo1+VpnYGNw5TnpKGNbfeO9iR+osrjGfSUnHNvvy8e6GlrBLbWGtp6ce9n2vy0q9HX0ced/vq26OhBxmXeZGhj27ybDdTYavRq1k9TB9yi09WFBgPbR2J74HAj29vuvUypC05Vbt9Ah7TnTPo1H4tD7REA7MUGJBJ7o+z2zp8627KqMCO1IC3LokbpS511vJd9NUrGpYuNH2PHqtRCaat0tfez+J9uHPLEwXZlu6Qfdye8EptS7DZl5ylvGuqK2+dfC9iXfhixRdNPounjzbA5+5ac7cvS5/ubCOxR2pOxTWt/9WDPtfg+IWzKCNV+VQWb6vn0Dil5Sd7JvnravITatUQTw+wBr5B37BHIdrSXusVrmbpo+pSF02Zaps01W+LnnTcPHTb0QVeqRWyQ41UWV36JTc72Y7FZZ+PJMM+8GaO0ZYxwrFPovEXmTk+cOT9ObRD3fb3Cd93WK1TLzFags8E8xHNNynHYUO/VBqqaD2smOuran9T36VxlaV5dvHVDjNNuGukl3lausepL2meGe6Z9fCSavNpQmF/QirUrxQZdnDXhnum+mjhjvcXZyrVUJ0S2uEalGulBdbx92aN73/7kjaioDW8sKs7e+khj6/cw/DBA8X/traTPHsvpf/rbHfvj3h3yDINmf3654l/98bLBu1MOdtl0WU273mcePdL6PQ8/UO209bvz6w0L9izfNHLp/YHRnRu4EYMV/1Mb07c90uerZ0/3WvXhibJXRnpfa/FW1c4Hn9rz6ltvXn/25h6Hg0Z1+vvc72+PROM9A1s/v8Dbmpnxanpj/h4xPPFMyR1VM5YHN3bcsr71a34az5vwtsZp69f8NC1Q/KuO1w7sMvfux7Z8+NgHpqsmvuhtPkjbrclpXytRxrLJGLfNl+jXShwha8iNgsNgJIyDV8B5cDRMgVEwC46F18NxcDuMhjvhBPgwnAhfg1fDEzAGnoaT4efwWhiAHVNgNzgNyrh3GYumjlHDTv249xli50yxc5bYOVvsTIBpcB68Fc6H+6AZ7ocL4UswEb4DF0u8p00yVgzGSv70U9o0Jd4PZc20j2EobIDD4adwGjwNV8I/wwzYCEvgX+Ft8HN4J2yCd8Mv4QPwa3gAnoHPw7PwNfhPWAO/ge/Bf8FP4bfwC2jC7m8UwI7Y2x6Gwg5wKPwBvBJ2hJNgJxgDu0D7XpIyDg3aJJ+1e0n2kzUp+8POMAReBgfAgXAgHA0HwckwFM6FYTAZhsMCONS5dqCMO4OXSXzatfK2SnzbJL7tmnD7Wwi3WcLdKeHu0oSrbiHcvRJul4TbrQl3rIVwGyVcmYTbpAlX20K4Qglnk3BFmnKol3DrDMohXer7ahgEs+FwuAZeAdfCMTAHToK5cDnMg1aYDwuh1WmnjGuCfQzs/L2sJXgS9oJ/gM5yaCHcKQn3voT7o4SbiBxzC9cBRkq4YsmXG2EAvAn2gjdr7K2X8F0N4t0h4e+W8Dud4XCDvIe7VcKtl3Cl0LFHbKiEmyPhtHvELpfyWAFD4Eo4FFrgSJgCZ8BUTfmWir5kg/K9XOzoKnZ0gwNhoJRzdzgK9oRTYRCMh73gYthbyrsPlDVSZWyLOuaF+PRrpB6QcjoIu8HHYX9YBYfDJ+E4+FN4LXwKzoFPw6XwEEyDz8J8+Dy8GR6Gd8AX4N3wRfgAfAk+Dl+Gz8Nj8DX4Kvw=
*/