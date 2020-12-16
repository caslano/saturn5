
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/and.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct and_impl
    : false_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct and_impl< true,T1,T2,T3,T4 >
    : and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , true_
        >
{
};

template<>
struct and_impl<
          true
        , true_, true_, true_, true_
        >
    : true_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = true_, typename T4 = true_, typename T5 = true_
    >
struct and_

    : aux::and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , and_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , and_
    )

}}

/* and.hpp
PlNkpqXiac6Rmh+Wj8fDpMd3Eafc/pLbWf72RkruFYR2xjOrErm56a5XVl7OQnp2usu+uL7RtlPprday4LsZaXj9wKRmZeVc725Sqdl0BasPnlaS1kLjUVPYHp0j0pw6O5Xl000+kvh8E/zdz63feHRxpObybPH2Uf4NnXkj95kHOWzmSw7NUcxztbG6Pqhrh8/caazuka81/Rtp+7zrHJS/vrW1XXl+AnYkz4505dm3YVB++em52e756KVBxuDmWZ75qG97UVn411+Ut/5MeZTvXZWVp/xoQ27fPnsVTzXMXwJ/l7samVN03z5Lerlpmfr33T7p8Ren76OD48iT0a4pJ+O6XYb1eonP9WGf682Z1uszr7Ve7/G5XjjBen3Ee231q9zA/1v+xca4OtHzLd/7XhzGu0ynJuF/w4+N9tflEqMvZZt1sc5bw5lTXhCGTh7bEBuduhrzDXud8kIZg9z6XBqGPu2kT3yMvz7djWevWZ8w66pbGHq4x72N0mOBnlHzCD2NsdqlB90wN3VsvjGgOAeQoL7H3LpojuTR5eGG3jlVlK5J0NKGOzf03/vRm/8k5rj3flStDaNL4D0fkr3RRvZl/KfAI/vo2uz8hrY6WNoo65V+OvTjP8UeHareRqfby7e0yXU28gfwn3KP/PDbZO3o4Ptt1jSWryM9ez+Bg5Ab5ZDcXJuyD8mHrEuHiWiKTD1zzGsiFl9x9BVDBveZfKZPzBuv55D/c8TpA1nrWyWU3Wry0Qbdix3WdVr1BSPPln01GZpAZKrvpRN+Iq4jyTbfiAre//z95Krsvf5v1Qet5RJjKQPvu4P/nFr+UmP99wQNMeYOue49QeZlWJcb43D2IY232xfkY0OX0sR/H9Tlxthlo0PwdZE4S/ntNPb78NGCqZtFZpmNzOFGH7WXOWliCDKVZ5aT/PdeJTb1L+cRxCuzleeYlJcRujxLGWucdORbfcyWNvXP75XIr7CVn5eTmx++fLO8hGb++b3aGAvybOS5NpuFLI/yDWynKPnFzez31sXn/Tp76+Kb2++tS8z7dffWtZP8oub++W3LfY48i79Wchq63DaSa55nxJzun88OXBRa5Rg5DGucaNMweJ3ub+G68w1903kVHkCBhIHaPxhg7tcqyPvNF4ncb11jYtwNb++g3tG846zyVm5z9o55XWof11qXcn1foXyLyaexeLB+oJ4/5veithHW51g7ra27ry9CF30fsK6JWfcyNuJ6p/uePK3I6RkYgfw1hM+5XjHEq8NuPSu179HjA/2kwa44o/Vu09/n+m2f6+8916Htnwx3n6T9vsHA+yft92f+fvdV/q/vnwy07zHLuU/ySJ1RvzS6bHX7PWvmlZ/b6/PHw99veSz3TxZEaN+B9iOwVUhnCcmftfb3TYenw5vkH+lm+BG8FX4LZ8nf0RwYC2+DHeDtcDycB3NgIbwdzocPwAWe/YjaN6BvGwk++yQ7eOLpmz+sp3iB9nEmKr3oStLbe4K+uetbvBGvi8uPovM3Wn7OroExMFl+WVPgWTAdxsNxsAucAIfDidABc+SPdRK8FU6Da+F0uA3eCD+DN8Ff4AzYANk3w3PgLJgK58I58E54J1wAV8KFcBNcBJ+H98GG5OF+GA8fgB3gw3AQfBSOg4/BW+Dj8D5YDB+AT8FH4Vq4Dq6Dm+Df4Evw73ArLIEfwPVwD9wID8HNsDbt/1lYFz4HG8It8Ez4IuwEX4IJ8GXYG26D/eHrMBmWwUnwLUNP+Da8B+4w9IPvwMfg+3A3/BB+Az+GB+An0HgPKTf0gZ9CtQu+vwduZx3d7Yd/XKF4w+Rn8EwjntrFEfULItAugNpFDbWLOmoXddU=
*/