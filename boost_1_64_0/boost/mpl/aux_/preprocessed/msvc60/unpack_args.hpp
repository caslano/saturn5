
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

template< BOOST_MPL_AUX_NTTP_DECL(int, size) > struct unpack_args_impl
{
    template< typename F, typename Args > struct apply;
};

template<> struct unpack_args_impl<0>
{
    template< typename F, typename Args > struct apply
        : apply0<
              F
            >
    {
    };
};

template<> struct unpack_args_impl<1>
{
    template< typename F, typename Args > struct apply
        : apply1<
              F
            , typename at_c< Args,0 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<2>
{
    template< typename F, typename Args > struct apply
        : apply2<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<3>
{
    template< typename F, typename Args > struct apply
        : apply3<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            , typename at_c< Args,2 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<4>
{
    template< typename F, typename Args > struct apply
        : apply4<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<5>
{
    template< typename F, typename Args > struct apply
        : apply5<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
            , typename at_c< Args,4 >::type
            >
    {
    };
};

}

template<
      typename F
    >
struct unpack_args
{
    template< typename Args > struct apply

        : aux::unpack_args_impl< size<Args>::value >
            ::template apply< F,Args >

    {
    };
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, unpack_args)

}}


/* unpack_args.hpp
uH3e/Xbvy2OV/SU3zPl02ykXHsnYset8z0rfjif/WcfO+kGOKWvmGOR3Ja4nxPIHX8wiGGRMlieGY1PsjB3wTOyM0XgWdsNx2B0vwJ6Yi73wSuyNq7AflmAMHsNZhCrJ/yLJvxmmSP73SHt8meR3H0bh/dgDd2IiluP5uAun4QOYgw9iAVZIfhsN8vsPqyQ/P1wt+W2Q/G7AMNyEXfFGHIFbcDTehCYsxWK8GZfhLXgnbsVdeBvuxtvxMbwDX8Rt+CbeiQfxLut8avldhiYpn3o+9ZVSvhVoxJU4AVfhhbgaJ+MaTENZz5/PrfyWkt9YpMu54HkOaJAxbyE4SOo5DqNxMCZgghz3UKnnJJyDwzEPR+AiHImX4dl4F56Dj+AofAnPxdfxPPwMR+NhTMYmlGUMRuA4jMLx2A0nYC+8AGNxIg7CC3ECTsJJmIJpOAXnYipuwHS8B6fhTpyO+9CEz2MGVmImHsTZ+APOwROYhb7UWza2xFyMxjzsjnNxGObjFCzAVCzCGXgxZuECXICXYDEuxPV4KW7BxXgvFvPfXlyCL+NSfA0vk/MZZpDfT+hP2EZoQgiS68Soilcl8VrVHo+T71q8MInXjGC0ibdOFc8o8fzriJdszbf2eHkuxiupI16ah+Gv9dH9g59zvnmld72fdV6+0tvt553v5z12zzy/wvs/9dzztzjGEwS/VcwzJ4wgmAjLCeWEg4RfCa1XextiCeNX631e+qZv+qZv+qZv+qZv+qZv+qZvjbE1Vv9/dlFhVkP1//dzMAegE8GT0IGQqcxzj9auO5yTqvTk/bX+/9rmALRUrfFOTta5/0Xm1/bPl4+U+flrpNyrCNlKnjblZoI+b6+73Ja+5vxQ0uAd6r7mAtlHj7qUXeLJogSydgH7asYQtJTyz1E9C3uAzdoC3QgtCF0IucQL66YuOxmm5uVnFGTkFBpcH+sg+WnXlpY+eU/OdQh+T5hLvDRNfixmoDrHo1zu867f+W6INf0v4C+yTeY11h32OVdo+pelX1zbD62ppxKp4FflGfsvYQHHVdbdpp6K8pSaMteTnwvnRFM3Do7Fz0E9BDmoh9Y2x6zsOyrrWcjlqbnOsrxrxqSEEF4hFFEWQ0/18czLyM+ccbH5gBrp3Ltzro7YnKs4mz73pYQQSf8iyhHWy3xsyjenfG/NzC0wX9iprJNRfXwmF4/P3TU7Pg507Ryqzr/m+qaA1nEQYXJNsK96LRM596bMmRkFhcSRcR/zOebcokJNf22y9BXfLONbrsZLiVepqRvtd/osF+vkr5zzur7fQ6UuLiFtKSSHrxTUoLlmlDoJrhnPIp8HWW9G6iUqoOYzESDjRWzrvbzm/QWZC/g8yfiT4XLNkZz12tR87mTsjO25LWWf7ee4jH2LOJ5Z1VXNcfT379unus9giF/1613VrznukzPH7e+ay+a4D73h5rj90+ayOR57cPLnuO2OVfbP+9m/iU/RwJHzy5N6HLjjufmNM8fNaJDfitjJwdrTa6RPfy12wKtQ1nuR32rEcbDeSzt53+noi+2xM56BURiG/bEDDsaOeC52wtEYjhOwM07FCDThmZiNkViAXXAhdsWlGIWrsBvK8cnvMvapj8/BujRdsJV6jXt5n2cT+zXu75E+8J14OpbL8e3CYfgATsEHpdx7cAU+ijfjY3gbPo578Al8DZ/Ew7gPj+LT+D0+I+WiQPJ7ht85Ui4l/+NSrgNyPC9hO6zECHwFB+GrOBRfw7PxdSnfG1KPb+Jl+DbeiO/gLnxXyvk+PoEf4LNYhT/ih3ga5fkIg/ETDMdPsSt+hsPxczwPD2EyfoHZ+CUuw6/wHvwan8Zv8Dn8Fl/CYyg=
*/