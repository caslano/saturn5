
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
xUXZHrrbiOP9U/GzfoysJ1/NXVrd9qI80d3WT93u9lf3Ntb4XG2D+azEGbENET+0a06EDBi1f2rF5vVi8yNINfrq7taxOb3YXhTAHAOt3Rgqdsu4ke8ImVJilXkCbSl4IzKIz0es8pwn4Jx/IPar7R51oPd5twLdQZo+56TzKx6fr/G1TXSdKe01C1np6GOtLv6YbS1odh9PRRuFMUT1+1DmJsh3joyNfvLNrQz94Qb+cyM/uVHsFSP/eeCxV/Rj1uw/P7x+TJz955/fX374DU4//I5fzjiwXf740vdsM8Yct3FZX6P5AoH75y/o7Ph+24U5V9zV6YdHdgRnfVy7+Klw3377SIvc62GozAdR/c4Txb81CXaFyeqezHLcQDlO9YvFy3EJsCNMhH3geBgOk9zlyH0UDtEpZ7SUEwP7wTHwWDgWRsJY2FAPuf/Bjjr16Cfl9IdHwQFufz4ix8XIcao/v7sc1wN2gGGwE+wJB8NecBg8Bo6CvaXcKqRG2udTKbcDXCnlThF/XwoMgVPhUJgKY+HJMAlOh1nwFDgLpsE58HR4MZwBL4Mz4eUwAz4Ms+BjMBu+BnPgm9AK34Jz4DY4F34M88Tucovcp+B6sftwWCZ228Tus6Q9imRc2OEgOA+OhWfDRFgKT4Dz4RlwASyGZWL/uXAFPA9WwYXwEbjI3T9yz4EDdfonWPonBB4OO0n/dIbdYBcZd11l3HVT5k3USLlnSrnqvImBUs/jYDCMgN3hINgbRsL+cDCMgUOknkNhMhwGM+EI6bdouLlNg99228qDm/TdEidBLzaCYVwE8e1KHAS3j9czBsJoNQ6C1t+rHw9h12jjmAhanzDxEcQv3HSMBG18BPzHEhcBG5e1ttQirvgIW2Dni8SvrImPEDXGM0ZC6hjPOAnidyZeAnZDNWZCDfSKmaDxRauxE3Zik/imtfET8FM7YyhwMW2txlDAb60XR0F82RJHoU15o0+7f7n4tfX3HNb6uSVmAuTzTtgb/QZxE/CDYxP/H+P4nr/V/Yfr+LwcevnHJY5CGUxORS+UOAriK/cvjoLEUMCXrr8fsd3RbuMkhoKBf10bSyHN8T1/i69djalAPAXxvWv2J643iKmwen0rTUwFfb+8xFjQxlfw9tWrexfHUx+4lDriu2/W3sUzoK/9i9tc4en7D+XzOqjGWdiaoL+f8Y4Ez1gLu/lMvAUu0swTQGKQNKQUuR5Zh2xDfi8z5wmYyUxmMpOZzGSmv9k7F6CoqjCOr0pp5gMREAsVfEVKBoiApgWE5TvyiQXxWhR0BWQXJVNTexeWWalTVlRO05SVTVZWVthYWVlZ2eSUlTU9rKywLK0s+93db/deTqxCrfTwfOOZ354D93/PuXuvl+87L23atGnTpu3YsWbp/88PXP//tWE2s5/P0r/enhRDGtKFmPwas3+dnjD3XPjGzIWWfYj+1Nd20NrXpvSv17T48xz5/tShdo21j39eo+bie88f2kXOb+nDywpgH15T57reRkvp08q8ffju+x2Jy2K3vf7tb0tPOfp9b8daH9t3l7qv/z0hT43PrHuu78hlZ57oWtMzcH1sh+tLS7HJcwNjZY5XkHzG6HuQdcBhJOwmfQjdLX1Y3PN+54CGS19HF9hG+jiyGjkXrGpBW7/zwVx1zTsnrKau6fPCttYFbm7YgbqmzQ870tywmL1/fX7YiL3/vjliq7hX1i/QsV1t2rRp06ZNm7bD+f+lR83/L87nn4ANgQO0DuBSyzqAG8T/ntkS3wLmQAe+eu0NnjWzivP5lxBnDFcemCA+eDVswC7DB6ceQ9z+fritpWV9K1mnz7K+VUlpOXlzrDsTAnxjrau7mms=
*/