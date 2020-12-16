
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
template< bool C_ > struct and_impl
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : false_
    {
    };
};

template<> struct and_impl<true>
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : and_impl<
              BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
            >::template result_< T2,T3,T4,true_ >
    {
    };
};

template<>
struct and_impl<true>
    ::result_< true_,true_,true_,true_ >
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
        >::template result_< T2,T3,T4,T5 >

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
1sa+6IgzsC6ux/q4E5/FeGyIZ7ExnscmuIUVd+YmDi8ikogj0gg7+sX0ISKI/YTSdyaYPjPRxB4i7+/AO9E/xp2QvjT5+tFEE/GdcvenSWLeZhDrQWd0IzJ57Kv67Xhnwo3wVvW3Ce6c0+cmfZCh340r4UXMlD44W1DdB2c/88nSF8dJ+uOkES48tlL636ATBmAE4cHjaIwlEvL019lP6LqwDdAWUzGLUPffcZc+PDNV/Xg6ExuZ98YI4kIX5jEFswhrpV8PsZ9lSYQ3jzNxJtoP4/+IaB77Yiwa+/7ESv+fu4SNJ8+b/+vM/yWiM/NKn6DUrvwffX4cCBfCnQhQPMN2RA/+Lhp9MYrY4kY73NAzp99QvCdtJvR9h7pRn2fuPkQOLPPkcd6+RK4s70Nk89huBH9PeCnLMIyI4vEqjCeSiY3dcvoc2YzM6XeUYaHvkQvz7oQXEUxEs2w/kUSkq/omxWAckUSkEo4sy1T1V/IiIqXfUkKe3/VPZt4bw4hsHtuP4hjvQVuJPcRRwoVlKeiNs4m1xF3m4zGJyOrBuhvTV424Reia0K+JcCN8iUgilkgk0girplrfIG3SJm3SJm3SJm3SJm3SJmP+/4Unmf8fNzkwYqJPcJC/vgvAI/cBOFhZZ8p9uRjvx5S8Um8iWfldws9NeYsefQf36TnUR9+GgKKMI27sC9CaGmTQXlNe6HlO/CNCc+ff9kgb7CV3UpX4lDbEmG8DiaDCc5TGNlCftMFQZ3ep06mk3B8udZYlPqPOBPN1TgiMMI6jXnheKN/zl7q7GHNeZupOoe6kAuomqffQ9faSeh1K5a/3c+pNtVxvQKiPrKkI+TBL9feT+mPM1H+D+jMs16+EX3hIK35Dcarf5CL81mFh297eKn8bbjZTGmKxDeT7C8/XFfbct1iZf+62lusNf1zP3fQ79ZJj7yOvdXfiFm1wNN8GkqCFv9arSp0ROmOdPvruD1VV+WT/4NBxk3wMPUwqqfLKjOuc67cVLL1W06TdlWXbKQu/pN2R5tsd/jCvVVXdpv4Ml7jALivKdQyFPZW/PanK+5WF9hT39WuuLUm0xZDZz/2ati6Tvy3fKO9jFtrysK9pVZtM+/Y8bVKvTL3PNpppV5ryXmO5XeOD/SaEP2ybjNupHiEryvX662ydvz3fNlNe/Obb8yjvPep21ZZ2XWVb5V5hIMOGh+dqY4qZNt5VXp+W26h0K+Lgmql/dT3stlO/VtXrUh/zAWXzt+172uZmoW3Ffd80ty8T2WbKSvIe81llzW8n3wLaMl15p5kQMfFht5F6HH7DyvK8v5czf3xFWmjTo7y/Wzq+wi0cX5n6cYmK3y/gcY0Xb74/SPH7BVjoX2Ch/4Wlfg2W+ptY7hfTaYy+Pftr7er5oOH5yXeOOUePbfG05f4y9/WfsfIdWr5bu/LgKewsO7SW5FNrozPWxdZYD92xPvZGJzSNby3rs5f1qfN5DSUv1wirYmNVuQQp97SZcvOk3CtYFuer89AFlFsr5dZJufWqcqkFlJst5V6WcnNU5TIKKLdcyq2QcitV5XQ3LJebJuWmS7kZqnK2BZRbJOUWS7klqryvo5TrI+XUed+Ksl8rYV20w4ZYBVtgVXTFatgNq8v+rqHK40fK+ivL+tV532HSLk+0weFYEUeo+4MUUH6SlA+W8pOlfIiqfEIB5T2k/AApP1DKD1KVT81V3nLe2gZdpHxbdT+Gm5bLj5PyAVI+UMqPV5V3zFXecn8YG+wo5TupyrsVUL67lO8h5d2lfE9VeV+L5VHKN5PyzaV8C/X+L6D881LeW8qPkfJjMZq/zTOuhGlMicWWx5EodAwJM+NHmBs3oqAxI4o=
*/