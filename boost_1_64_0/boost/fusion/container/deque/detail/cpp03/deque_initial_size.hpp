/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_DETAIL_DEQUE_INITIAL_SIZE_26112006_2139)
#define BOOST_FUSION_DEQUE_DETAIL_DEQUE_INITIAL_SIZE_26112006_2139

#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#error "C++03 only! This file should not have been included"
#endif

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/vector.hpp>

namespace boost { namespace fusion
{
    struct void_;
}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/deque/detail/cpp03/preprocessed/deque_initial_size.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/deque_initial_size" FUSION_MAX_DEQUE_SIZE_STR ".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion { namespace detail
{
    template<BOOST_PP_ENUM_PARAMS(FUSION_MAX_DEQUE_SIZE, typename T)>
    struct deque_initial_size
    {
        typedef mpl::vector<BOOST_PP_ENUM_PARAMS(FUSION_MAX_DEQUE_SIZE, T)> args;
        typedef typename mpl::find<args, void_>::type first_void;
        typedef typename mpl::distance<typename mpl::begin<args>::type, first_void>::type type;
    };
}}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

/* deque_initial_size.hpp
wjI5ZBudbpNmppOpjKtxOe6ayJX8uHRp7ac0pA/M0rMDXivo63G1VntMInSU8NNtkiA2cM3gH8jgJ/+jPwlHnPrkHYoca1vsDqiGiSOFOB7xoUeI3LYCUTBbBV1+P3e+Ok4tO4Qk4T2Uz9/eGMXgiHhoP2CsJPOzLu1zW1HSEbgdTwY0QZVtHHx2sDUfVvg5xmvbRXP7GXekaqDqjo60majFHRfYtJXGzpUhAfouLZXVQfLdraKF1Fxo892IoHivGjf0qQyMIME2f7fcqtlfKaiDxGdC8XfwrhrKSLp9g/MmMBdnL56LubdcJgu+EF6mTnuGrDfQlWz4znkPWPkWoAv6b65wrnUdsppCD0YkT/9PYboQ/z2dfRLx5IMBNISZYYvphys1ESbr5HkYZIwPWmtawMEuZwYAEhacAPV2EvVTwxuOUiLvruBc64ukLI+cfPNSyiGiLnTCZ09PAb4+/ICdyVSUC0SrEO38xoxj4GWNAmgAFSdMqqNN9unZzRTpShht8bxYELAsnj4ham0VWfJesCWsH+UQHvVO2/uUhgTl4fGzwDhnA6M3vw==
*/