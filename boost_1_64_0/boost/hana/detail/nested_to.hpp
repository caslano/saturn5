/*!
@file
Defines `boost::hana::detail::nested_to`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_TO_HPP
#define BOOST_HANA_DETAIL_NESTED_TO_HPP

#include <boost/hana/detail/nested_to_fwd.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/functional/partial.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @cond
    template <typename Algorithm>
    template <typename X>
    constexpr decltype(auto) nested_to_t<Algorithm>::operator()(X&& x) const
    { return hana::partial(Algorithm{}, static_cast<X&&>(x)); }
    //! @endcond
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_NESTED_TO_HPP

/* nested_to.hpp
YX2c1h8aSpFcruRAzV+gI+28saoUmspVsbTOmnQrMbXyBinL67QfTBeV94+FiflTlueLamYvoCWQcMAd8PIUOLrUX9OAlYjmNg4FnujM8c3sYuUvPxGywiAfAzN4M/tSrgEWtmmXdNrYBIYVBuh3g50m67g6PzgFKeU0lhPXirxsAQnwc3bV/BPYFysM2AdYX4nTsErDXrRgBYTJA7yfT7NC/pMCgoHXEr5OIrRXXgf9PfHP/K0bF4daPfAVIZQ12c6S+hUEYZ7i3HPoZ6Nju7H9PbI/z0Jk6fu5RSvl2bpyafhMG11hvRAWufFkxYDc7fipFewbvu+r1tlLPXzq0ZXLRCYd89LaEQCQ1mMW2ncyzq36l0jyBFwvaHt5cf6PKkLolVNENSEhbOFmfIiWBE8B+VZNzSxnvRlHPP/YJsp8hWNKZciJWwnobSN8oPyUJkgfZrc1DeTVKwA1y8S+YUhrooJ5ci5J5SCd3kBbY8YG+Ypjso0SFbRl8IhUZwZH5No5NH7/uXkIEmFi3On52bIIP9lXl+wIxe1Aw/+IbOv7SNOvTDSHLA1/Eg==
*/