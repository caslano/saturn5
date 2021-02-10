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
zh0RNq6ygrbNHewcnUXp48Lk7Ux1HtB17x0FJhPcR5puLvlkSk5yeX2qA8L9MLk1Vrtot3Y7phobFcKY59imqLKmyEYK+QFnfXdvjLX3kLhdrzx9YXvpSjrufkdIDZbaGbfaRV76LEEFAtequHkODebIPEpG2rMBf5uNkHCZetyiZ5iUlAEA2Ar/15z2Gi5cLSl4e/wBzSsXkKYYdVGgjP94wS4ybLeog7LvvGYSw8oMVGu54+NljkZJMQqebe5gr3KtqTku1s4PHNNXZEetL1gs16bEjiW1UqunRruPGtc/NG1HTUt8Mf4VjuSWiC1JJTWOgFlNWZSfPcffWWa3TWczgKHnz7ZwslxdmcRVlPG54ZuAZb6pg4/lybFyixshe7htU3YG/+oIVWal8oPg6JAimfMNDMMcKYMC49FUpdbGPk2BZ7D2Iq3hrFQ2BqQ/tvcR8SAGrC/WktDGDihDH6U4cGUed7giJt7tL2WeqylEXY4DmXaOCbCx5FlORFIwzSN6dU3OYsXk2l6S5V4/u+qwVXUFsOXv5iSxBp4InsjhNsmK61+09pPgVg/myzqDqpElHp9Da31oKwSvdaxTmmRTwYiGYh2afeEvUBKdkSVP0khblXmLP8qTDGhOWJIsAnEo1ygBZZo3FwOH
*/