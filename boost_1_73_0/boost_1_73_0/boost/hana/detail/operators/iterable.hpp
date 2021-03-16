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
V0y5w3LFcjQCeAkQ9Z64DbhnrjzdvneuqKJ9DNtc5tjmMs0i6x1tg6MNhG3ktM0VZkg478szTK3XJkLj8sYjBsQwlJUfaNe5yrIJK+Qe7VqqLJvcoAbCJvcqYRPqv59OdOQkm/Qxyf4/xSZLPJExb2STApV8i/eMfGGTM/OFTc4yE7uafNnHc3a+aI1z8uUB0XOBs4AXAC8G1nIiCqwDsj4uBLLss0w8Vzp2udKxy5WOXa4MO81PpsiJeW8c458=
*/