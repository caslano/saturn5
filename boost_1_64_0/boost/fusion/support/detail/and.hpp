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
gh1tvG574TtazNIAc9THc1+a7vu0U0o4LB+ahxz24JY3EtapkD0PJZ7Gbrmq32vPTVdgD0Z4nGjvpTMpYBnR/IP+JC2vJ4wHnTNNZK+PUWIEth/JEyzveZe4z1g2PNfARxvx0qJf1Z/CenJSztHIXRHf871n0p+MOWaMoI182B68wfzyBJMpmphwmhxtHe3OMQm8+04weaqPSu2Sgo3Dh3nw65bvuY4mablySwkP9yYxTSYYNtUVpdNYrtPn219b3hWZAxWMqbpar1/qiS/BnjzVx2h8YJFiYfB8gzeUL7fzWkgbsoqu4BRd6h/tAOd8oUXrh8vUSRqwPHiuwf1vyxvrc2SiJi9i8mBbnUbvyQRPWW+08x7LhecZfB9/GX03mtLtrltGenvTcWE5mNi87iAsThZHY6UVlg3PMYhlh3gV0dkZ57IhQziEF5ZrzKWB7wrP6zP75W9PsDmTPmXeYTlhziE9/tmX8Xe9LW2mWoKgN0vO0BIXZJYv6Neof4xngVOpFmxH9aZmmuPzD6iNZQBzYE7KuYj1mbH+jQiXQGzWr7Tzh5U9UnnNFrjHm5eeM4+xNPEryJoZpTzpYzK154UXD31yn6/gs20nU8idWsSHW8T2u3FcTwwzm9VHt3yecC99kJyWx+8eazS4IKDXhQfZOCmplEoVq4CUAQOkkYdgHM+Z7aqhz3owQRaJaJ6fu3PhQd+2rnQE1XnsubWNiQPnMeg24pWES6nKcBuyfuXiAnKFbxxsvHa3XMGAryHk8Wl5I9GBJ5q1amDHXN0QB6jlySRpK4P1annUDOLSGFEL24/+EGMFE1MqHdrH9bt46dVwfz3OnZ8h2RRRyYkyRcNo73hpFk7LDjpdeNFbqKXaOK4gFhqE+avoQwS42oiV1+6WS4TrzZ3KXb6KZDYiKyd1GGRemci8AjrX8sV6PRZ85nKUuTzBTWW+8FUsM3fCc+sEtvE8Xeb8VSyz0mXnM9z8e5lLI0aZR93Abe9SNpkl0X5SwCck6AbuJ+c6X1rfNfrUphg+twJxegofsmv1mknrpx/MBQ/bX8G94FfxOsmM6zpf7fVfXbu6Va41sEVseVY155ambOvl+clxSTAJa6odzpOobyVRnbA6dn4eT/B0fdpp3qfPfw1/LwZpaaAyoTt1iJe7gvJdwjrzNSRzzMIIEQPI3CjX/nAeyC3Pcwpo2f+EItuNxBchfmKhRXYcxiohQprJO9clkBe+TZC8nHReS1e6nMyFBDvDQTe+jXh1mUTSZxfNZJGq8K1yXRxk/nnLfznIQG0ZOdI7M2HblV8jmS0xkrouG3c21lrt62VQRZj39YMK7RsiRi9NNUe5ATvpgL1lh32t5RGCGFOGh9P/MHebwlIbjHNb1woTSivGlp5FQ+y4y2DD8nUss3beCJf8fynzswfMT2BM7YyzbHlUGdwJj+xwrp/IakOWneL/k6xwDv/6xI/K846bGEYf+BrUgm5uQoyi0Yb1b3icDC8a7gxrRIdDGejIuW/gs5I0viyyNJLG/70No7GCoM892w7ffd/A7wrWlV5PygL48LS7PGw8e5xqa7CYwXi3dV32yaYcmVyk44P5BPN60n6bkqfehkWkzr6T8dSGRWxmz/2ebyBfR5Ulz4vPrGV8DnhbG7BvTWTupDHeC/NfyAyLGfggfQOf56pleFSO1EhlGH7Uu19PZM8+09IG+m9kL7hYdtCdb+A3DOasd30e3PF5G9tan/smfgOyWndCNNJv7h7sbB/O9rfzLV8kPNtocmGsWPgxvYmxWnjQ+7b10ous2zPl60veiSbe2Mpgd09a3mdz5kOWWhOznvDbmG7puCKWeumioqdhwKDCvB79NI8=
*/