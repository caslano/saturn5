
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
4iAEwYVJmBzOTRnetuSpfhsoPKBtUx2RQu7C41I39pm6MIJ9v/UYLY5z8OwzNs9yT7k3iEcncEInrjS6mWT5ciSIkZDkPhsMGzBaTbLtZkxNjtRsTXQwAS2mnBDbnH9L9zalCo9karWNYt44dOZPwU8lkreEcA2DAbZEj2H57U23Yw5rLwaTMjlYCorXJIjIlgnnyfaH9kPpTS9LNi4IBu9XJA44ADzMhDyHqg+6+vy8PJdUSJT16rDl7qef1AUaX8nRDWcvfJUAXnGYUZ8pThs5FVxx4jfziKUPT25/HVP4HK1y2bBOu+B0APM+x0s9Y1/3b6lPuz7KAHiPk8QPEAhizARohNz1R3RjSboKnbD8ksbx4njLikiY9Qk8/x4cp319unIZvGgc2s4G7oLJ/15pqwg8RdaQjKJSeZ99xMDH06i11NhfJgrAu1dYpaUrXn3ZNMi9z/ynEkVMhGo+4WJzm1tGtcx25gfkjumIm7+X3g1RSwTURAXgnAtQPg0ptpQvb9WZdSKoV6yUJ31G4mZ+3fDzkIZn40beeZ5zZiv67eaHBZ7lAzB+8w==
*/