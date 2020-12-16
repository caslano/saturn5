
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
tmtu9vuO8nzlzaS/PmGNOv/N9tLx73R+5p/EsW+u7C/7cF7HPSmHmq5vdqZBxGePP//dzeVe2V7ZX7h9S/zRz6+53XLs60cezrxp15Wby+1rzna8RebEyL+TGupjeudLjOsCGAntMBoWwlFwGZR0mJfiPZ0lks5SSccq6eRIOrmadIp9pJMq6SySdNIknXRJJ0PSSUAqJZ3Jks7VcLykM1fSuUnSSZJ05sGu8GbYE86HE+ECNV2ZHwGnmKQ7VdKdBkPgdNgSzoDt4Uw4Dt4IJ8FZmnRLJN2JJul2lnS7wCawK2wGu8FY2B0OhD3gBNhTk261pDvMJN0hku514u9QGAqHwWg4XNIdAa+DI9U1J2SuAcyVdLVrTrTSxF3sCNvA7jAS9obt4GAYBRNgNEyD7eFi2AEugbHa83mPST5MYs+HwLEw1CP2/EB4g+RjopoPmSMAM0zysVtilu+BreBe2BreD3vC/bA3fBAOh6VwBHwYToWPwlT4mGbNkVKx196kfhdJrPQVsCX8gdhbCaPgKk06lT7SWS3pFEs6d0g6aySdtWqMexnLD5pKOtoY9xsknY2wMdyk0QsVvSgTvTdE703YFv5K9JKQeNGbJ3qN4TTR2yLlvRV2gXfDXnAbnABL4GS4Hc6C98I5cAd0rXVRJumPlfS1a128Lem/I+m/K+m/B/vB38FR8PdQ1jqRseuOMe2kp1/rZGRD0oPxMBaOgd3gWNgXjoMj4Xg4C06ARfAGuAVOgg/CyfAROAUehlPhq3AafB1Oh2fhDPg3OBN+AhPgp/BG+AWcBb+Bs2ED/E2Ecv3IWHbSMLl+lkq5WGFHmAs7QxscDPOl/O1wCiyE6loZO73Xn2lB1AM4HTaGM+A/YSQKVaJ3VMpVKb8QeQ79SPw5D8PhBdgVfgzHwb/B6fATOf+fwkz4GbTCf8ECeAneBT+He+AXsBRehkfgV/Al+DV8F34D34cWKbcG8HPYSMrzKtgFXg1HwMZwAmwCb4RNYQZsBpfBELgGNof3whbwPhgK98GW8EkYBstgK7FbbZFx5/AHUj7KdXZOyjVC6l0kbA3bwfawPRwHO8CZMBbOhx3hItgZ5sIucDXsCvfDblL/usOjsAesgD3ha7AP/AvsCxviTz/YDPaHbWAc7A0HSLkMhJPgIDgPDoYL4RC4CF4HC+BQKadhkm90ZNy5o6zIN74p16/UizTJdwaMhlmwE8yGveASOAguhWOhVfKfA1NhLsyBedAO8+F2WCDXnR0+CwvhSbgMVsLl8B34A/gRvA1+DG+HX8PVUKnTxbATXAunw3UwA26AOXAjzIOb4Da4Gd4D74RPwS3wBbgVnoA74G/hTvguvA9WwT3wH3Av/BzeD5WYMvtgU7hfyrPcIuPS4adyfYbDI1KPrpLr7GrYGobALrA5HAVbwOkwFM6DLeFqGAZ3wlawDIbDZ2FreBxGwJdhJKyAbeFPYTv4OmwPz8IYWAVj4QXYCf4Ddoay1pKMH6dtE/+1ay1dkueMz2Fr+CWMgpdhB/gVvB5+DSfCb+BU2ID0Z8CGYudti4z3hu3keovk32fETjcppx4wCvaCHWFv2AP2gXGwLxwC+8GRsD+8AcbBmXAAnA8HwSXwWngHHAL3wKGwFA6DD8PhsBxeD8/CUfBDGA//DMfAT+FY+CUcB1vh/wQYAW/Q5K/0Qe/5myz5myr5my75myH5myn5S5D83Sj5myX5my35S5T8zZX8JUn+5kn+bpb8zZf8LZD8LZT8pUj+Fkn+0iR/6ZK/DMnfYslfluRvt0XGkYOnpZ6Ewq2Sv3eknvwBRsAqOAy+D6fBD+BN8EO4AP4R3gL/BHPgeVgA/wxXwL/CNfA=
*/