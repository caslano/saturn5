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
U6eL513v/Hte8qhd7IwRlHd46AMxSjmg3q2a8+/N+8Rb6tOnMOHXjebNeKlxVLsVlZQGJpPrkeMwOAJzB0Wk+69hPDtMdYSFGvU8XYf/aDgWC04hmQkmo8GSQ4bPwNaz2Jq6KHARW8Bcws0nw3QXzD2S+7mOefdJbQkfgNDtmBXex9t4N0J1XC2I1JXmhpQJof7KZkjdPqj7tUj+TBJbscUOdxZ1/I/MGuPDkraKz2WrHXcV0Tx0h9FcgrlAH3Fqr8PKXYuWd6gRtsxvsxscsSaBQHLknh4ze4rl2PgWSZmz+Rsrywzs/fjlWVIDDKSGfwPr/dn9SD3v4g2ePMMjjqKhXZeVNaIv9iEuoQQllcMhwMcT3bZW2nXnZHjhxyNs8rPHcS8qUFv8Uur+X7hr0AB5U9gaABH4dsL6mwHuCOO9oqRogmAAzJLVLaoOHoc8PjBhqRa46BVkNxnjzbdk/cMFdAY1hZ7GGCbVYCSWNDvGb6Q/vck6y4m+S13VODYZWPVrDyxw5dWgz35jn1jwWOLZ4ASfIjw+If5FUs7OIJjFLZ2EGbfkc2u3KA==
*/