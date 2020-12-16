// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_BINARY_SEQ_TO_ARGS_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_BINARY_SEQ_TO_ARGS_HPP

#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARG_0_1(n, prefix_seq)          \
    BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(0, prefix_seq), n) const&
/**/

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARG_1_1(n, prefix_seq)          \
    BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(0, prefix_seq), n)&
/**/

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARG_0_2(n, prefix_seq)          \
    BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARG_0_1(n, prefix_seq)              \
    BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(1, prefix_seq), n)
/**/

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARG_1_2(n, prefix_seq)          \
    BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARG_1_1(n, prefix_seq)              \
    BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(1, prefix_seq), n)
/**/

#include <boost/preprocessor/seq/size.hpp>

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARG_0(prefix_seq)               \
    BOOST_PP_CAT(                                                            \
        BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARG_0_                          \
      , BOOST_PP_SEQ_SIZE(prefix_seq)                                        \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARG_1(prefix_seq)               \
    BOOST_PP_CAT(                                                            \
        BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARG_1_                          \
      , BOOST_PP_SEQ_SIZE(prefix_seq)                                        \
    )
/**/

#include <boost/parameter/aux_/preprocessor/convert_binary_seq.hpp>

// This macro converts the specified Boost.Preprocessor sequence of 1s and 0s
// into a formal function parameter list.
//
// Example:
// BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARGS((1)(0)(1)(0), (P)(p))
// expands to
// P0 & p0, P1 const& p1, P2 & p2, P3 const& p3
#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARGS(binary_seq, prefix_seq)    \
    BOOST_PARAMETER_AUX_PP_CONVERT_BINARY_SEQ(                               \
        binary_seq                                                           \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARG_0(prefix_seq)               \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARG_1(prefix_seq)               \
      , prefix_seq                                                           \
    )
/**/

#endif  // include guard


/* binary_seq_to_args.hpp
sYxdpkXo+3WnkbeGKm/+Wpb229XzMnf7ry+qdBL05TxTj5T1Kpy5XpRAiLSV/rKa7hk9jvWS9y38ybM6yWeaWrettkqu1hn1VN2jjGTbyDNa033XETXfQNuX2vuazvUqmi3umY/80t73B2raaTYvz1SN38PNVZnVJW9OI60JapiPZtUe/UDGGe3WGtP6uduMNJ5Bmtswl3TczyGNbVZJtpmNpVXjPJlHU+dG7q/UvZd6rnrQ1LZRgup3xw1Yls17q+zcM2WeSw+padQxxjDzuVSuA9JmN+trfuaqzpPFVhj3LVneLadX0tRfVZ3hWAU7MX/kauOc4vnu33xeMfbDcmr6svoHpGLTfazPkauzf25hWqt3g5bnDvO0Yx5w7pBpsx67cn7flrHOrEFJ47lCkhoW7lFny33chGIFNU0Z/TT/t+vuOkZzGZmU7VgS2d8PPOt4BGV9R6y299zVxnXRFFvCWwyJnMeKsI5J4D3mgXWsAm+xEP5xsShGq1gUpYdd+ijpcpeGT69bOcHv04QF3mNRWMeW8B6Twzr2hvcYCdYxJ7zFkMh5TIucxtKwjjnhPYaEdWwMb7Elch4TwjrGRs5jVNxyH2PqfVo6DpY2oRZn1m1GikCNC6SbKdOXlVgGNbAW1sSHsBY2wdrYAutgO6yLnbEe9sT62A8b4BBsiCPxYXwSH8FV2Bw3YrTRNpDUWYa8ki9z20B2Z0a+fDAPOtBoa0nmq2wxX4SsTwn0w5Km5cXIfMGe80mbPi7vYhD+jK75ehn1XTlOZT4/uvYyX09ZXi/0x0cxn/QXkP7C2BcjsT+Ww1hz20qSfj6LfHWW9LtgAHaV+WKMep5sA5nPly5a5mslsRtaY15sgwWxLRbFdlgW22M97GDkR+pfQpBFfsZLfiZgIE40zRfpfT53G1gy3+Om2B5NZb5uMp85tscwWY/hGISPYSgmYEkciTVwDNbE0Vgfk7E9pmJXNd4d22OHLC9ClmeO7TFI8jkYwzEei0p/cek32gqTdAIt1neZpLMc8+MKY32lPhrUsljfbTLfdlnubtlvXpH1fQnLSX95/CNWkf6q+AcpB/rd5Xuf5T0jy3tWlvc7Wd5WWd5mtTz6ZXmb1PLol+VtkOXR727rbYr3clkty3taymWNzMf1WurvqLpdar4+dBfku4mx0nbKdHwJZ+BR6T8h/RdwLn6P8zAfiS3AIrgQy+IirIpLsQ4uwza4EnvhKozFdTgDN+A63IgbcBNuwWdxL27Fs/gHvIZ7MA95fhXz4z4sgAewBIbbiZ2DKVgNU7EVHmJ8WzyDffEjTMSzmITvYCqexDn4Aa7Ac7gRP8VdeBHfwi/wHH6J6fgV3sIr6GSDXMW8+APmwztYEf+CTfAWxuBPOEhix7+MDtyP3zD8IH6LR/A7/BC/x/MSS/4LzItXMD9+g4WxDNexIlgHwzEai2IbjMDOWAJ7YwUcgZVxMVbFlRiFq7EGrsVauB7r4SZ0rcc+bOjKBzZGTWLAh2AzrIvNsRG2wi7YBgdgWxyPnXE6dsU52B2X4mDcgSNwFybgHhyJB3A0XsE+eB374i3MjN2eZNRlIE906XIdjPOIMTQbQ3COnPeWYDGcJ8fjfDkOF8p5fDE2kOka4gJsLP3qfsAp75tVHQY6fJ9uptTrPyWx4s9jU7yAHfASJuBlnINf4AK86uD4wCv0v4A38CjexHfxe3wff8RP8A5+gX/BW/gT/oJ30YdM/YJ5kHTVcevw4b4EfbER+mE05sGWmBfbYQAOwHBMwghMxRI4BSNxFpbC+Vgal2JlXI5VcLX0r5f+zVgVt2M1/CNWx70Yha9jLXwLa+O72BA/xkZ4CR/B29gedRs=
*/