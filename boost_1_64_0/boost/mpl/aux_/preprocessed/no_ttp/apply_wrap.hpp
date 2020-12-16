
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply_wrap.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F

    , typename has_apply_ = typename aux::has_apply<F>::type

    >
struct apply_wrap0

    : F::template apply<  >
{
};

template< typename F >
struct apply_wrap0< F,true_ >
    : F::apply
{
};

template<
      typename F, typename T1

    >
struct apply_wrap1

    : F::template apply<T1>
{
};

template<
      typename F, typename T1, typename T2

    >
struct apply_wrap2

    : F::template apply< T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3

    >
struct apply_wrap3

    : F::template apply< T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4

    >
struct apply_wrap4

    : F::template apply< T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5

    >
struct apply_wrap5

    : F::template apply< T1,T2,T3,T4,T5 >
{
};

}}


/* apply_wrap.hpp
c+rjvzOOj/8K1cenkq9eOeNLP+J4fLtV+YrKiO95Vb7sMsb3rCqfZ4HEV874csoY3xuqfKvKyLfPoKrnMvLtVx+3Fzie3s2qfDFljG+T+vheM72Oxpcu+Vro5PtbFdV0aPLpHd/nkPIlX4Hkq4ebJV+SrD/J6I3TZf2Zga1wJoZgKk7CNEzEdEzGTLwLTbgGZ+EWnI07cC4+jfPwHzgfX8e78DjejR9hNp7GRShxy71Gtsk6cfeU88be6IN9sAf2xX7YH0dgKE7CAWjCgZiFYTgPB+NiHIrrMRxzcRgeweF4AkfgKRyFn+Fo/ApvxW9wjMyX3EpyH1LuTypxBynrESqfx6S+V0t9r5H6flzqe53U93qp7w0Yg5swFZ/ABfgkPoabcR1uxQ24DbfiDqn3nfgq7sL3cY/U89P4M+bgNXwOqxHj8+iJL2BjzMVB+BKG48s4HF/BRNyH0/E1nIt5+ADux8fwAD6LB/FFPIx5+Ba+h0exEI/hDXwbG1Nv76AP5mMzfA+H4fs4Ak/iZDyFMfgRJuHHaMJPcAGexkV4Bh/CAlyPZ3EHfo678Au0bb++kvWqjO1mAMPkSD7PKpZ8yv6lNb8rn1Q5X01Db0xHP7wTAzADQ9CEA3E2RuMcnIZzcTHOw/U4H5/Au/BlXIQHcTGewSX4Ky7F3/AeVPY7f8FmuAKDcSX2w1U4ER/CTHwY5+Lf8G58FO/Bx3A5rsZtuAYP4OP4Bq7DAlyPV3EDGqiDjXgLPokeuAW9cCs2xm3og9uxN+7AcbgTJ+NuzMSn8AHcgw9jDq7BvfgOvoDf4It4AV/Bq7gPqyjHteiDr2IPfA374H6MxAOYiAfxHnwdN+FhfBKP4BZ8E/fiW/gqvo2vYz5+gsfxR3wPr+P76M5ycQI98CSar+NVlnuocm+V5Yb2diXvbL0s11uuoDf+hD5YjO3wF+yC17AvXscR+BvGYyXKycbKuBbdcCPegk9hNXwFq+MH6I6foAdewVqorP+1sT7WxfbohUashyPRG8dgfZyADTABW2Ia+mEWtsa7sA2uwba4Advj09gRX8XOeAi74BnsioVoxMrUTTdshkHohz2xK/bGQdgHw7EfjsUQnIL9cQ6G4gIciA/jINyDYfgcDsZcHIL7cRh+isPxc4zA73Ek/oSjsC7zbzTWw7HYHKOwA47DHjgeg3ESDsLJGIG34R04BZMxGmdgHN6H8bgCp+FfMRk34HTchDPQsr2Se8DoU87xwipNPkfXA/Mk3yad64FLZf+1DL3xHmyD92JHXI5D8D4cjiswHlfiXXg//gUfwAdwFT6OD+F6ZFrlerfcP8V+Ote7u8j16a7ojgHYGgPRH7thHwyS6VeWxQIZ32HZL3fi/ymofL6S6foaffActsdvsCd+hyH4PcbiD7gAi3ARXsIH8TLuxCv4NBbjy/grvo3X8H28jhfwBl7CSsRZg1gqY12sgk2xGoZhdYxGd0zAWpiJtfEurIP3oic+gXVxG3rjQWyAb2JDLMRG+A364A1sivWol2bYAZtjILbE4eiHidgK78A2mIrtcDn64wZsjzuxAx7Ajur7HFdk+Stjv3qKtEryTZXzvUbKdX3JlyzHfdPRG2egD87ElpiKfTENB2EGJuMsnIVzcCHOxWU4D7fjfDyIC/AtvAuPYzbewMXYmFiWYAtcij1xGYbivRiG9+Fw/AtOwBU4GVdal0OD3GPFJ3XeGzxOpm+8TN9E7IxTMBxvxwiMxiiMwXSMxRUYhw9iAq7DRPw7TsMFbpZ+iC53dzc07UHfuKQUkqN+idbxt32k3fy/AKv0pP9eUgQpndSX/I9gwUr65kF130WHFlW2679o9cE/tw+joo4=
*/