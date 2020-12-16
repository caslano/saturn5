
// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/unpack_args.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< int size, typename F, typename Args >
struct unpack_args_impl;

template< typename F, typename Args >
struct unpack_args_impl< 0,F,Args >
    : apply0<
          F
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 1,F,Args >
    : apply1<
          F
        , typename at_c< Args,0 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 2,F,Args >
    : apply2<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 3,F,Args >
    : apply3<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 4,F,Args >
    : apply4<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 5,F,Args >
    : apply5<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
        , typename at_c< Args,4 >::type
        >
{
};

}

template<
      typename F
    >
struct unpack_args
{
    template< typename Args > struct apply

        : aux::unpack_args_impl< size<Args>::value,F, Args >

    {
    };
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, unpack_args)

}}


/* unpack_args.hpp
pv8Lmt25PROkk0dPh9416JCif6gWfXnvhzioDp8WGhsdFz0l3r3V6NbuI5VBgqc9MS1qqvuAaOZujwyP5Z1o/xotKGl/Gds4SZ5zxBKqE6IIPynjWefUUcY2Hq9kPHB8INN0DBk5gkGiw0OYvmDy3KARQ3xLPMbxPldlnlntWN4yJ7VuvtdpYJ0TrAOlCwuJD9HOpfUNccyhro557MFntogy5rFanwAZf+SM1OcU4ecG1PNM8fUZ2X9oCcbqrlCjw1nWYxpiuuj6DTaXq1T1u6epn7Y+x6U+jQnlpA+vkPqknjWqj2nKPnKaxlRBJR/L+1oNpfwyvrvk27uc/fjuv5BvVpH5KrUpeZ7fSJ7auu6SPJ0lz5qEX8kzr8g82crMJluaccuN8vWWnd5PjplehHvk6/CxUb5xmm1c8vHdJV+ZG097TOi3+3lZ2RApy0DC75QlwLgsst0fvBwGx6GMJa7fRsEVzCt7TMo1jkCmDhnG5dLsm9KXzeY8kvHsZV9VlDa3jFIO/mFZyuGZq5ZjduegkLAwZapth5LM6VWhxu+5mnOazy6fWD53Usu2uI5mrnFtWTXneGR0qLoN+8u8Dbp5+Ak1NW0Zk5dQSv1Y8zlSPz/Zzr6EF8g76RNN/WQaGRKXavtSJk0d7Mss7Y9ue/tXMq/IS87JboRTLpyTuvJwLlKYksxBbCnLMRfDsujOhQLJ20e2RR9CeWVfnzPIW76USrM9pAzFfi9FhsTFx0TH2X3naMu5Tb4EF0s5FxAqUs5Uw3LKl43D/eee1JSTY8n+vCi6nHK8ab47jdq9yCrmzJZJuZfI9vX+1LjcarP3AGU3aPeKLH+hpvzaY9P2XLkk5XeVY7Me4ST55RuWPzR6VlR8qY9P7ZwnwVVtvhPl3HQ/X0fmPNE3g+bT9P5zkKjnp9FcLzZlyKUMtnO9VFb2WVFlMM34U/J5V6QMujwjqtnPsVOVPIOLynNaVBwTYZQ6T23byvw60rbq537pL2XKoUy280OtVNrJIsqkzhRVgm2hrbuvo832lmMstYh8Sju3DseZ3fY+7mhznEmbm1FEnqWdW+dYMXMkFph+I1TkHCGlnkPCeO6QouaW+PPmFDGeQ6LoOUKM50opak6UP29OEeM5PEo/F8ifNYeK8dwepZ/jxMlNiT/1XLvHOkatudViz/rdnV5+J6/ouUmM5wIpes4V4zlFip8jJMJB7msxluBtM6bRM/Iuwwp0w2exCaZiT3mHrC++gI/iSgzCF3EGvoRRuEp9d0LuO/GM5Kd9d2Kt5LceXTENW8u7HD7yDoefvFM1FDfjaEzHKbgFI3ArJuKbDvKbaHxe3u1YiW/jBszArfgOvo078SDuwpMyFtIp3I3qmM5nrXMXeOveSZF3OPBrrILfSH2uoQtexwZ4AxvhTVmvNyFL1ltb1qsdI/hzWe9lWe8Xst48rIVfataTJ+txNljPOVnPp7Ke87KeC1gTabbkt+Nyrwf9ZD3a344flnQfSP5HsA4exW74IfbCY7K+8YQAWd8QWZ/2neATsr5Tsr6PZH2nZX052BvPoDeexYFKETX7JUPW/5jBftkj69+L9fB92Q/7sC3ul/UfwHHIMSBjbct9lNxfeduMtT1Z1huKzhgux+1UbIwRUv5psj0icQDOxFEYhWMwGsdiDE7CWIzEOIxHgvmdGlyEszEFE/BVnCvvfD6B7+GTuAcT8RDOw3/gfPwIk/jfN7hI6rkYf8dkVCr7lHocyH0W+hkcB+Ok/hOwDT6G7XGinK+T0Bf/pj0+ZX1eBsfnSDk+A9AdR2ELHCPbMVAtl9zzoI9BuRpIudyl3Wos7VYTaU+aYh9spnkHNlXWt1jWp30=
*/