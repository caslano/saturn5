/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/target.hpp
 * \author Andrey Semashev
 * \date   21.03.2009
 *
 * The header contains the \c target keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_TARGET_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_TARGET_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass the target address to send log records to
BOOST_PARAMETER_KEYWORD(tag, target)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_TARGET_HPP_INCLUDED_

/* target.hpp
2zqK6zqEs5UJv8MiMRcy9nKhT3P+11A/T5DrRUj6+BHlqd9KLMnkiSzOzz6Un2uNUTg1e6FEXNrtMtPozzYJWCOoL3hVGQ8i+VOMb1FvoWnkKxvOVkqjp2iLcPlwKZx2Jwobp43BbzVdLlB2j1SS7yfS2daTT2kuQ0jciQHXCvJWu/nJ70n8+rNVnyuneKcaGzlPqs3yhEr7KKqrztpN0A6L5H0q7HziH6YlaWFtlh8MeznF31cvFY9qnfQo9Xs6hNpkrL4S7Wa15XoqSx1yHc3vEdwvSWncyuGCbdldzEE4+3uxDm/G9hzOal/Yh7jsT1LcJeqbXLDhkFvMjvbEOdpzEAHZUGJN4N938HkRPycJT2Jp4O82Awd1zhfM6xXk5Vm8LopX0N3i5Qd5RRavfZDXzeK1CvIKLV5qkNfV4iUHeV0s3iWtFa/A4i0K8lSeTw3yVJ4XKF6+yvPsIE/leUqQp/JcEeSpPI8O8sw8/2kbWZLdRsbv/nD7mMVLU3sX8f5l3nabPayG7WHWmcAM/uacmcEmwATgA0XAdsE5QWVVcD4w0wg9l0f7zEk2V42zsR3oLIDTWI54641l6g6eVGAL8n9NdxhLVdjg+Yvp6v157d40lsMmOl2m8G8ui+R36AvB/VnTVBqplD+fLZ5aMYDznk9hntE7wj47EWcNr4P7WDTFjuA4UQ53JaZ+bwNzNK8YpSWKJVqceAUuRU/E2ztOnKvH2uKtVmPDlxTvZ5qZv1nyGJluraMQ/0f9GbTKfvC9Q9ds4StVHTdFnlFr7Bf6bUad/LJsfuNUWb9rH17WcvV+3UR+3evdd5wQ4b5jtH3IN279qk+iDcP6lREniKIRJhYYxf0qb1/VrzDP3HW/ysunc2uqX3WlsIOc+hXijdyvUoA9yP8Xp36FsPX6lWq31eT3A7fbCard9iP+Vr0Opd6K/jUzpN1qVR33JbmOoozLcBI9L9XboV+Nh7sO/ewDYDb1r0RxGfA1uBboW8PQr87TWosP8Hcm+tZIOFvfUn1/bsdg30/ndh9J6byFUSlDZMHnfE3bre38d9vT8x6W4Pd44r6BP6y8OPurc1LKpy07s/V/256+UPJ8mXW3OcCOcMeBYX3HLprvO2kOPIK/s3YkcB4/n8LPF/B37S4BjgKuAJYDvwWOA24HVvD34CqBTZFGFbA/cALwMODRwDuBU4AvAGuArwKnAt8ETgN+CzwG2ETDqhwwF1gLPBC4BDgQOAt4CHAucC3wWOBTwHnA9cD5wDQda5jA1sA6/GsLXADsCzwROAB4EnAS8GTgWcC5wEXAU4FLgacBVwAXAq8BngncATwLuBN4DvBI1Ou5wNHARbz3+nzgbOAFwKXAJXy/yxprTAImcns0g1sFB6L1CBM7A33AQmAWsBuwDFgEXADsDlwN7AFMkbyXnNcjjgP2Bt4D3A+4DVgCLOb7Xmbz3vKVwP2BXwFLge15j/lE3mN+He8x3wIcAEww95RzOZ5U70C8r7kcKXAPcjni+bMByUAvMAXYA5jKe+fTgLcBmwO/BqYDOyFAC+AUYAbwemAm8BNgFrAL8tkSOA6YDVwObAX8AZgDNJDP1sAOwDbACcC9uN1ygT8D9wYKA79tYBSwPbC0Aes3oXug3T3P1nrOcqznrIF7y13Xcckll1xyySWXXHLJJZdc2lPr/xXjdtP6/0X29X8+A38vXAzbKY7shP9s6/9IOdL6v7IpNyH5Ukc7rHBeq1f20Jnkv7/jWrlwXOd23rsvnNabndfElWy02v9dKez3oc8j/yzFM+CWEq+lWoe2212tO5yySeZQrOlF0crqAKEpm+xe5Lc3fFLVdw/Ps63H+cP6lLLDNmI=
*/