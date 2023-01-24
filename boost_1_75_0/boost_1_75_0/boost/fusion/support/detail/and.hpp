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
za5btxkNE4FC1h02TKy5w4eJdmM0vTxGLUFNqJ8eLxlo07CueW9T64Pqw3JmJtwbeprQ2dWjsapV/FbT/QlAE4uwDdwnzTtTIHUmu6PBqy5fm0p/P0flJbVCxwtX1V6sdBZsU3ux/vXo5UJXI7Ld1P75uGCz2i2ZJyw95MZboQtrvGFS21lKjbfxy647bG5/xhpvjc9Z4w0TXu9KG1HEft+df5ZyUSO+w0bTeJduZY03I4rfC7MnSmqAykqvlPk5GzQrvZLXZI0XG+fCtmoWWaVpR2eNF7NaNd6qswPK3EGE54OKKaJtZkX0mR5mYyb5MqKbXEUTOimboGZTFZVRGVD453D77GJVFL8L+4i+78w3QZXtxvcP5fpxA5raghQGm7Hg/6d6ZK34sqlTZl8EypxmdFQ4XUycjhihcMo//P7Bp4zTk5+C0xdkTl8O5Jx25pxqP/zefQvtfx75hA4m6Hyvl+VkySZZMvaHZPzaWTLuucEk49s3uGSsM1LnUNSFrix7k/gR1931yLRpl9j5YrM8ut2i/E6MVEa3vTtZPn/bqRyQ7dJJuT/qxocY48Z3VZ3FDWrAhwB2/+1mKHBMcEkXsaksWkyZGyaryQNIlfvnkqjKff6K+9MMJtTk57qZUIKUsX9XF/mCLanrCsusNPyHCcs3yQU0mmy/IcOVAlr9CSugQwzo1TpscYTcJzaigOxdqICYb4P6yn1u
*/