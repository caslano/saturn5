
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
+uFGNPxO8MPTHyNxAGbjQHTpwu+P8nq8UXk9DsYiHIJ/oA82czX+7rbDYeiGw7EfjsD+6Ic+OApH42gMwjEYiv6oxwCciYHIvfgr9rV+ZXXJ/a1/1dfqwPt6kv3JceQ7vvp39avWS/wflpigr6P4/xnWtFtZTCvnFfPlPCVexnMvXmSKKQ3xls642N8ylnsdrx2mGsutPKenaKGM5Zbzc4431Z6HV32+Wt35du3P22t7fl5dHPG8q+FeSp98/GjUppQTt4dmN/3wYMrh2p+3G58bI9tItl0WWf3cGBsZz2eH7bAVdkZ79MTW6IUO6G/2vIKZ2Bbj0Qln1NP3PONf9r3Wkpa0pCUtaUlLWtKSlrSkpfqN//V6neGfsMSo6UoDwOXH/xkteA+z/v9uZEuyK/lm5f7yEv8PH+6rfLBHby/62JRVqsU1xadbll9vai0xf+Ks1Cr7le34O4TPjZVnaTvI8jGz9ZEW8p5OmMq8hFnl7QJZFnXXP1d13F53/XatuirzQz7a8mCXwd+0jH16iccHdntoQJf+IqlztoX0S6n7i2ykX6oFumJLs7g8q5Yx+cmvrGoclxdpcbmWtKQlLWlJS1rSkpa0pCUt1Wf8r4+so/j/edbUdI8vif/7SrzZhxzqovS/l8f/fHBZ8F9nsb/E+qbYP5XMZ1yRcf2orob5n668tfdj3a/pljW4+7EP3uP9vzfcV0fqUup4C7kh2VMqrZnE9c2xMdpgB7TFPtgSdZcR59c0xrc7p8X4WtKSlrSkJS1pSUta0pKWtGRI/3z8H1lX/f+Zqv7/ZRL/95T43408TbnHtyr+j/wX9v8r085XeLvBrYZ2g+nrfVIf0mV+r791yqBeIwe8YBoPINuAbVPFeIAW0m5gi25oV4/jATy1tgItaUlLWtKSlrSkJS1pSUv/01Rf8f/0yLqJ/1+S/n/18/4CJb4cSw5Xxv+r4n8+uM77/y8p9r+CY/0XDbH+0iFOPR8NsPrGsrCZxZ2ztwaYxghIfbMe6jECVYz9b6yK+VvhWGxdj7F/iBb7a0lLWtKSlrSkJS1pSUta+h+nv/f5/2Xx/+XH/srz/6cTZ5dsU57/H8Sjbo3P/9+ueh7AlrL7AbRnTDp2Rh2v2WBf3h6g05e3BTio6qHRX7QFpKC6LUCH5tcCqO/Dnta74j3UUz0qPj8grU/Fe5aneRqnC8umZfmSste7V7yX/qoGVZczfJDquoeEK7+ccZZyf0d7YzlnYTTr4Ty9vJwp+tSwWP3ci5bTVlXO5Ig5vKS8rHopm6yrlM1s3TzM1r2PWV14mpVdli+tWDa5H2T1932suk2o7u4HWdv7NX5uaPtZeWLttoSP+k1qN+XbnI8+iUqru+dz04bEfYflOyr79BZ0JJ+UDejSgPsXYxcMRVd8DrviBeyGgby4BzZmn+mJ2dRLL7yVcrljP9bXA79rzPECn23C9UKob0pbFXbgA/riCXb2G/ABdpp+ONaO+9jiNex7/XFPa45jqNzXdyB6tuU+tviNE/ehxYHtuKYGV+BofB/HoPId9UcpL9/V6sv701XG8v6KofgbPoeleAF/x0DlxVLeq3CvFZO4gPJa4g2U1wqLKG9D3Ep5r0Yd5b0G2/MBjTCf8jbG+ynvtehPeZvg1ZTXGrMob1OcR3mbSXmbS3kdpbxtpbxOUt52Ut72Ut5xV8l3Vr7LW7AL2VeO169JeXdLed+U8mZJefdIebMxDHMwHvfhfPa3/bgXD+BR6uMQtqI+DqML34MjOBPfxjnUz1Hcje8oy/M9zMVW1Ncx7Ex9vYsz8TimcWPSPHwT38Mj1OP72JIDxwfoQn3m40w8gXObcd9uZXn8CN+mYCc=
*/