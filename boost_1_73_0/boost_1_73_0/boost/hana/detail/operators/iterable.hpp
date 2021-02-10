/*!
@file
Defines operators for Iterables.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_ITERABLE_HPP
#define BOOST_HANA_DETAIL_OPERATORS_ITERABLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/at.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Derived>
    struct iterable_operators {
        template <typename N>
        constexpr decltype(auto) operator[](N&& n) & {
            return hana::at(static_cast<Derived&>(*this),
                            static_cast<N&&>(n));
        }

        template <typename N>
        constexpr decltype(auto) operator[](N&& n) const& {
            return hana::at(static_cast<Derived const&>(*this),
                            static_cast<N&&>(n));
        }

        template <typename N>
        constexpr decltype(auto) operator[](N&& n) && {
            return hana::at(static_cast<Derived&&>(*this),
                            static_cast<N&&>(n));
        }
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_ITERABLE_HPP

/* iterable.hpp
Bv+O3IYGp8UtugKlfHTShCEyKvcB+X0LdSbh2aL6AUvtMLWTq2pGfLklaKv41ZtChTNi8xudl5PT/ZfSU0FGcV26TFmOMfHRsZlGsAk8k8KvdSYJqB5P3MokhtXr9+X4Ft66jHCCf2Y+jGGeg9xZ0Ym7BdpiKjcwUu7rRywx1xKE23kI9ZXaMq1P4Vqt12W1J0gpAbF257Y8IxEP1EaEie5JPjFTSDqbdUo+hFJYpoPi+NnvRtbEPjdAU6uHs00HWpoaq2OA1tOkTdhdE3ZuUT5e3XauQRkkeqFJPrBy9EX0xXT03W2uVePVwwWpK2eWtc4PcJVSxvHnSCBPHBnN/8/J0KBHmGFUIAH7sxDvoQyfgwCtcA7aEa8Vg5SGWMVS6AWlbKVR8e29qUGRRZdNW7nadhUbXHMKWcMrqw6aV2lLHPtdZr2oRahywnYj90j2SJifUuGS0r2KirzjKhnD11cDl1ejrqFhRu3GtVgUOhvq4XPpoLjq6zWcBOcBDgMgQjLtlPx7Ty7lVVpOZhwExg5+dJi6TSL3C+NKHmdZJiDSn1zZ1sSYXFokSVi9hpPyO6UCVpKwaiWEZxcAoRVzTfh1/xh+fM5hsxxTUwjH1dS6IFK9H1kkvMCzxhrlYhheFe5VSmXZ7VLW1xye
*/