// Copyright John Maddock 2007.
// Copyright Paul A. Bristow 2007.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_USER_HPP
#define BOOST_MATH_TOOLS_USER_HPP

#ifdef _MSC_VER
#pragma once
#endif

// This file can be modified by the user to change the default policies.
// See "Changing the Policy Defaults" in documentation.

// define this if the platform has no long double functions,
// or if the long double versions have only double precision:
//
// #define BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
//
// Performance tuning options:
//
// #define BOOST_MATH_POLY_METHOD 3
// #define BOOST_MATH_RATIONAL_METHOD 3
//
// The maximum order of polynomial that will be evaluated
// via an unrolled specialisation:
//
// #define BOOST_MATH_MAX_POLY_ORDER 17
//
// decide whether to store constants as integers or reals:
//
// #define BOOST_MATH_INT_TABLE_TYPE(RT, IT) IT

//
// Default policies follow:
//
// Domain errors:
//
// #define BOOST_MATH_DOMAIN_ERROR_POLICY throw_on_error
//
// Pole errors:
//
// #define BOOST_MATH_POLE_ERROR_POLICY throw_on_error
//
// Overflow Errors:
//
// #define BOOST_MATH_OVERFLOW_ERROR_POLICY throw_on_error
//
// Internal Evaluation Errors:
//
// #define BOOST_MATH_EVALUATION_ERROR_POLICY throw_on_error
//
// Underflow:
//
// #define BOOST_MATH_UNDERFLOW_ERROR_POLICY ignore_error
//
// Denorms:
//
// #define BOOST_MATH_DENORM_ERROR_POLICY ignore_error
//
// Max digits to use for internal calculations:
//
// #define BOOST_MATH_DIGITS10_POLICY 0
//
// Promote floats to doubles internally?
//
// #define BOOST_MATH_PROMOTE_FLOAT_POLICY true
//
// Promote doubles to long double internally:
//
// #define BOOST_MATH_PROMOTE_DOUBLE_POLICY true
//
// What do discrete quantiles return?
//
// #define BOOST_MATH_DISCRETE_QUANTILE_POLICY integer_round_outwards
//
// If a function is mathematically undefined
// (for example the Cauchy distribution has no mean),
// then do we stop the code from compiling?
//
// #define BOOST_MATH_ASSERT_UNDEFINED_POLICY true
//
// Maximum series iterations permitted:
//
// #define BOOST_MATH_MAX_SERIES_ITERATION_POLICY 1000000
//
// Maximum root finding steps permitted:
//
// define BOOST_MATH_MAX_ROOT_ITERATION_POLICY 200
//
// Enable use of __float128 in numeric constants:
//
// #define BOOST_MATH_USE_FLOAT128
//
// Disable use of __float128 in numeric_constants even if the compiler looks to support it:
//
// #define BOOST_MATH_DISABLE_FLOAT128

#endif // BOOST_MATH_TOOLS_USER_HPP



/* user.hpp
dO5SIBzfs7r7sK4eZVCPGJRX51kztiLWs9fpAEpyZ4mf3+GdO5ZNlMSVatnJI0ePPmN6JHU6ttghqXPBJI9VW/Z17q5p8TJq1eWl8cuYkkVUxEmRs5NTU8e7Nk53Oroz0FEhqqiKizSUt/iahYH5Ozh//RqRVVVtGeVVzmTBUyfL+dIFbcvrvEmSJCayVm6GPF8zXL4Wrp6fCR6+tm1P6HzpqLy4KcuYnbll8bT1F3TxGoisXMf6rxoZ59vKOpEcGRWBetx1vVfGUZFXSSZzVmxBTLyeHvcAlvhLSVG2dVT05Ok2vXZzfiPQ4yGf/1jdZGmpZMtu2bpp2iX36WRNXR/YdZ20UZ5EPVnQJhSFslqf/1l5lhcylik0TCRcCjpHvwyw5E64aRpetHysHoPYJEPDi3eiZVNHUWnatLSweGap87mKLX7fz3bQPmtSKRTv2wdk/kM10j67lfRZ2saFLFpomm0YscfzpG0KbCTlRZHm4+RRVaK8D9N+ayPF8yI3bexaiH6BgCV3UVUTF1FGJrYF+OfKohN0k7uT9nkrfe9VNiJWrtOm25nC8my4uCdEXs5UVRc8E5kvb7DxajuBDV49vGn67OZycO/sl1GzOKkalWW514nTG4Nb6Pv9ifvTdSNro0jWjbyS3LV1eIkR3Ksc8MuZ5mWdK9FqOyUNxhgPh4ncFiorU5HJhOh3uGzlwu3a+unmdLMJ++q13r3xSb+skglZVk2Sx6bdtNUTAxdjwueB4SjrrCni7MryTywtLC275CF4J0za3lapVGktRpPPnGs6+g3eSWTHTLuqtpVoryibL63AkrX5Oi+eyw9pu3kSpVGM8xA222v3zwO9N5orTaoryp5Z0rehvi+OPTsl41dIGCBSm7lrM+4TJvfQNnNeVlLEV9Z3tAH/gF05m2Bu7vXLOaYaGMJKNrrNfdueCmRWoGieZfKKMpPNJeM14Ml8mV/OUZhTS5g5SmjnzIm2a2e35i362GfKUlYyaxSr+BTde58h7eCiAhvgtWnHYDN4e79Bymx4xPOWZ2x1MShzSMpMi0yKItFjMMMX3J3tnPOxFUvrKI3rYjS9bdyyDNVY7VwZBp2dv9PneVaSpQVPksrU+eZ156OEa9cdRG8iFlWseGpEvNqinY7fT8qOm1rCMM6Y3uq6JbzDXiDlplzmTdHWptzlYbCf/ZKPPZ6DweQSAPNQrrda4zp4kdSjqWTTVqrq1GI7xsP/zMdP5yLV8caEqTdM9rbmnk5+Sfu9yRJYZ3X5Zvmic+qvfWzJaq0TyW3dYUIfzFO9/JmU3cZVWspy1KULqwsUezdpp9DfS2Cspt529CJ28gHE/mWdZ5Xd4q+vBfre7WOPVypqShnFts44Ibmy9wGejOcmzio10vdi0L79Bov3/GnM22RkI3xmhmIPkXIzWEp5VMqRnhfmqZ6nSJ3zNGuaNu9sxGWfxDozUrZOFxfLthzZ9cKAli19bMnyspY1L1NTaT0sDz+D1vskKbttahU3iRr1of3exzMCH1uxqs5UnKnaVlwPSSg9iBm18QC6H5Uw63CwcjfwnwGmtbUBAaeXYak/3n2ELLk5gLanjLlqChG79jzjCN3/3hnIK6o8i3OZ+fKWV/vy3FkAbWMjlU5/l3tttBK99xA/DWTmIipVq5LxbZx+Ziez64NLxM5aIaMsb0djupvx8e1GIEs0RVQUqqDt68ty4+WBZN+diLbMRWKb51aCiRX39szH67AIaZvmrdl2w4ytrWRz1X5fDV2+QSKjzSSXYK+mPfULyrLnRzTl40tWtLyENSd1MnA2QRnc55kWMcgoeDeGXIIvzC/XAp7EcEuyqE6KCIXcsjRvFuXTkIg=
*/