
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
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , or_
    )

}}

/* or.hpp
Xoxj8XEchy/jeHwbJ+DfcaLytzpM90xwp+KohysVRzPFEYcR2BLbYiscia1xPLbBudgWs7C94uig8uyIT2AnS9/SZ7ErvordcDt2d85jqfseuExxWeeTaatyb4ex2B5bYAdsg52wM3bGQdgNJ2J3TMWeuAR7oXP+pYbqk6j9WedfmqJyOAc74rnYG2dgIp6Pw/ECnISpmIuzMA9no/q8694G+dN+rH3etylfr+Bk3I7JuAPn4ltYiLtxOe7Bq/HveBPuxyfxAD6F7zvzp/sRuNhL/u5W/u5R/u5T/h5U/h5S/h7GKfgo5mMRFuITls9PxdrPOV7er6Iqqw8zdsDG2BUd877E4CSMxfLt6f4B9veyvWbaXhzGYgtsgS3xTGyFvbE1Our7cm3veS/1va221x7PwA7YCjuiWa8wETtjEnbBdIzHDOyKF2E3vAy74yrsibdhL3wae+Mz2Af1uUO/8xufLTw/d/RXXAMwAgdhSzwL22ECDsfBOBoTcToOxRRMUlzD8BIcgdfiSLwRR+EtOBqd4/RHaz4TP9/7crVejL/vkVqvluqjr/kQirRefT/rlWi9SD/rlQW4XnhjV3zRYb7mVyBpvfp+1kvQepF+1ksJcL3llvjsfY0/tKy32rE9P+sVBbheiW2/vuYRKLVuz/d6nOwVr3e0athvPpeAqz+0777Q9n7QdcZ76//sq++ztb/zqe/rbO3nvJPH6t9s7dts7ddMf2ZrX2bf/Zi3kzz7Ltv7LXvrs+yzv7LXvsrqoxxQ/+Q+Z3vtl1xhf2T1RXbrh7yOFOvqd2ztc2zrbxx8X2PvfYx99i+29ytWn2Lv4+xPuNpLX+Ig+xH76zdc5KWvsPoJ/6ox8wPtH6w+wW79gX2PjW/tC+zqBxweSd9f0jTSctIjpH2k46TwKMaeJ40gpZGWkzaStpFKSWGN2D9pACmFtJy0kbSTdIIUHU09IWWRNpC2kA6STpCiG/M6UgppHamYVEaKa0I/ZNJK0pOkQ6QaMcRBGkPKIl0TE+qjHFpCS2gJLaEltISW0BJaQkto+d9cfpf+//NST9n4/1mR/Daq9sWT1R9/Bqmu7tG9bLQx/LpGWCXb+P9J2WZM6Wmj0xcH097d0U5rm9EnLH1ehW3IP+/JOplp5e0gFWOC+sh/pBg/IL1KjKX+YjR7KGSmBdM/0R7jg5FqP651wvVcwXxX3/5txJJT4BrXPRpXxXD/PT+/kCfN18XqdfnZOfa8uvW5n6E+9+8pr++StrP9sG9teVVrb7Ne0BXMzLXyGe2njX/xtzUCHj9feXaUi2J3Hzv/hKOvMH+3jmHPY5qzq9+U1mHeAYqzvK3g0fL19Jy5qn38d2fZWAewP5dUhTSV9AZxx52oqGzMSkAHrsDbxdvnqviCNpm55hZ4zlIHcgvnUQvcY1yqGJsoxmjSDmJc7T9GeqMFH6POE7f5AaJ13zUC32TfRf73Tc+vjOTMIPpcei2jwpmUkr2MZnJsda5Yz6cgz5VDPY3+lPPcyvqI8ttTZd2d9Bb5Df/eb36pyvm/qqyv0TgBV+g8XUEqYd8pFe5bxRzkdVP793Hd9F0+E9RH/0rFeBnpbaN8fqggRk3wwjHy2xfH7H/2g+1aYr12KN6JRJM7z9WHcD2xGruy9tO5pYnGR7GdTw8ogELV6QtxD3koZr/qP+QlD+nZ1uthXABlXNH1r8x+vbP3gbbl6XRdA63vJUd5fJh1zIrHYvQTnczxmcHOe/F48Enyo9cetx1Px7qbWNfY7xNaV/O5eFxXD3lcVz37mi5V//oxKtcRuJdANv5YQbma3U3999GqqN6a8/G43ktVN9zn0pidlZqRj/b6Yq3vKlu3vhs=
*/