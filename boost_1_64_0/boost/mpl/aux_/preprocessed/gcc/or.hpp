
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/or.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct or_impl
    : true_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct or_impl< false,T1,T2,T3,T4 >
    : or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , false_
        >
{
};

template<>
struct or_impl<
          false
        , false_, false_, false_, false_
        >
    : false_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = false_, typename T4 = false_, typename T5 = false_
    >
struct or_

    : aux::or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , or_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , or_
    )

}}

/* or.hpp
hwNhFbwEfgoHwb/BwfAEHALP0eyGYTAexsDLYCeY4DrbSebJmJ9RN0LyOVLyOQpGwtGwJxwDR8Jxkr/xSr2LusV9vQuXetdW6l07qXftJT7+lDkmlJH4P0b6GtplFbsWiF1Xwyi4GPaDxXA8vAYmw6XQCkvEz8vhrXAF3AyvhQ/B62A5XCV+Xy1+XwM/gGvhh/B6+C+4Dv4Mb4AtsG09PBfeCCNhKYyGN8HOcAPsAW+Fw+FtcDzcDGfBO2AR3AKXwjK4Gt4Fb4Z3w23wHngX3C7+ou2VuSvoFn9F2PeF4aLc6P+0gZfDaDgadoZjYQ84DvaGiXAgnACHwCSYDJPhNDgD7oLp8GE4Ex6AGfDP0Aq/gUXwezhf+mMLYFN4NQyHi+CF8Bp4CVwCL4VL4QRYAmfAZTAVroCZ8Dq4FK6Cy+Bq6dfFBci8E9hZ6lsj2Fvyny33fw4Mg3NgR5gr+73kKetySyWdTJN1uT2kPf8DbA17SjvSC54HL5Z2pDfsCfvAvrA/HA0HSDt/CUyDg6D8DjIHxP3v4CTRO0Xaq6lwCJwGJ8Lpkl4KzIRXwlyYCotgOlwEZypnGJaLPuqg4QzDz8+y15cvYAd4DHaCx2Ef+BVMgF/DkfAETIPVcCH8Bl4Dv4Or4D/hffAHuBuehE/DH+EL8Ce4H/4LnoCn4DfwZ6i1Y7/A5vBX2AoGNMQe2ACOhw2l3pwNJ8MmcCZsCvPhOfA62Ayuhs2l3uwMkDke8FzxQ4ic16Zdr8vZdgdgKHwTxsC34IXwbTgMvgMvh+/BBfB9eDX8AG6Bh+DD8CN4GH4M/wIPwyr4F/hXWCX5PgK1++VT2Ax+BqV/KfMx7HZaavQvv5F29TsYBP+pnI0bK/HOQUoRdf12m7OUs2wlXLCHcGkSrrWHcCVehivzMlyFIR/mZwFXGtIzD1etpLe6tjODt0p6tYZDJFywSbieit64raLXQ7hEL9OzGOwzD1fqZbhyJVwa4u5M40rFvv2GfQEUPzvS8xAuaJshPdMziGO3SXoewiV6ES4WsWxzf1+FUf8aSj0MguHQ2f+XeIkBxv5/udyPj8AQ+Ci0PQfArvBx2Ac+AYfCJ+E4uAfK75qMcWljX8bftZ2S/i7YAt4P28AHYDTcLek0IYFYSecGaec6aO2spPOMxH8WhsEX4XlwH+wBX4Hx8DU4Hu6Hk+EBmAoPwtnwDbgQvgm3w7fg07ASHoBvw7fhO/BP8E/Sn3oXHocfyPPjIXl+/Bh2gIdhT/gJHAKrYAL8FI6Bn8FUeBQWwM9hCfwCroRfwjXw7+IP7JexKW3Myu6Pvrb8y3sZafdbwlB4LmwPg6T9D4ZdYCsYC1vDflI/hkn9uBy2hSmwHUyH7WERjICL4HlwA+wAN8EoeBBGw7fhBbALNl0Ie8CL4BTYFabAbrAYdofLYA94F/wD3AFj4auwJzwAe8G/wovhl7AvbEze+8HmcCDsBS+BveGlcAgcDMfCIXA8jINTYTwsgglwCRwKS+AwuAEOh7fBUXArHA3vgWPgw3AsfBKOg2/C8fAITIJfwWT4I5wEG1FOk2EwnApD4TQo7yNplKQ8Td5HnpD6XQ3byu9kFPwOdoHfw6HyezkanoTZ8Ec4D56CW+HP8DH4C3wN/grfkLOK3wIN4HvaR1gNG8KG2NMIBsPGMBQ2gfJ8LeNZ2jsb4/P1DKmHV8K2MA1GwZlwFMyQ+nUVtMI5cD7Mg1fDfNFT1UDGk8Bsqe8DbPedvF8SPYVS361S3xdIfb9a6nsxvAxeA2fAJXAmXAYtcDm8Hq6ApfBaeDe8Tvp/q+DzcDV8Ga4Vv10Pj8B18Et4AwzCtvXwAngj7AtLYX94K0yHt0k=
*/