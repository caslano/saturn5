/*=============================================================================
    Copyright (c) 2016 Lee Clagett
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_AND_07152016_1625
#define FUSION_AND_07152016_1625

#include <boost/config.hpp>
#include <boost/config/workaround.hpp>
#include <boost/type_traits/integral_constant.hpp>

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#error fusion::detail::and_ requires variadic templates
#endif

namespace boost { namespace fusion { namespace detail {
#if defined(BOOST_NO_CXX17_FOLD_EXPRESSIONS) \
 || BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1913))
    template<typename ...Cond>
    struct and_impl : false_type {};

    template<typename ...T>
    struct and_impl<integral_constant<T, true>...> : true_type {};

    // This specialization is necessary to avoid MSVC-12 variadics bug.
    template<bool ...Cond>
    struct and_impl1 : and_impl<integral_constant<bool, Cond>...> {};

    /* fusion::detail::and_ differs from mpl::and_ in the following ways:
       - The empty set is valid and returns true
       - A single element set is valid and returns the identity
       - There is no upper bound on the set size
       - The conditions are evaluated at once, and are not short-circuited. This
         reduces instantations when returning true; the implementation is not
         recursive. */
    template<typename ...Cond>
    struct and_ : and_impl1<Cond::value...> {};
#else
    template <typename ...Cond>
    struct and_ : integral_constant<bool, ((bool)Cond::value && ...)> {};
#endif
}}}

#endif // FUSION_AND_07152016_1625

/* and.hpp
+WiD9o5Mbt2/bKS3tDdm0CCp2Tb8ilYHrzt5E+NJIumsTwSSQQ+DVDBxKOmU/D/a0M+WjkW55rtl0rShWnNbduCWPBfuMtqDBVtOnozDYm861ZbM8L3kyUaztmRINmXaO/V91X279L1P9kUZWvXYK9D1y6ZBTvCJDdcVir6m9mRre6fetNJOPiN/blbZT/1noT6qOUTXUZGXm2Cb//9+iZ4mtxAWV1Av2bu1lpWRvWtj/7ip
*/