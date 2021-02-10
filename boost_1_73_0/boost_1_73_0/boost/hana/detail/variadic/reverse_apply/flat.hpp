/*!
@file
Defines `boost::hana::detail::variadic::reverse_apply_flat`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_FLAT_HPP
#define BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_FLAT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/variadic/at.hpp>

#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace variadic {
    template <int ...i, typename F, typename ...X>
    constexpr decltype(auto)
    reverse_apply_flat_helper(std::integer_sequence<int, i...>, F&& f, X&& ...x)
    {
        return static_cast<F&&>(f)(
            detail::variadic::at<sizeof...(x) - i - 1>(
                static_cast<X&&>(x)...
            )...
        );
    }

    template <typename F, typename ...X>
    constexpr decltype(auto) reverse_apply_flat(F&& f, X&& ...x) {
        return reverse_apply_flat_helper(
            std::make_integer_sequence<int, sizeof...(x)>{},
            static_cast<F&&>(f),
            static_cast<X&&>(x)...
        );
    }
}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_FLAT_HPP

/* flat.hpp
0d7IWazalFOsJfQUazbhEmvtekw/jWnAUrQN+EbcYS0yaGHrblClTXONucLapNBOAKquUU93mVBTyxCKRduAb8ISrKXbNNKYKaxh7bbUbcoW1tNRLFWbMIbmYmrJTc4SYVXeL7Pd5q2RbHdZnH26++RZhdJf5upiLdRMu6ui6XasrYkXSlm5doDrutt0abTikOvxxgIKgdoaoRrKNVfPtfVSB79YfC0rQJNmzOKNbQFNJmMth4q8et+wofUmvtVhfW2F5haBpk2tO6pS81gJRVTXWNdGWN7YuoReZfkrba2yytr2worm1h9dqbGp4by1W8wt2UZ1jbXtbk3nrWVzrQdXWaW5Da5mX23t21Go1JAhrikZVkl55XRRVWVt82XT5upnShPg1PHNu+EHKc29aHKEA+Xb7NxZ8XY7t6i39+JJo507K96ekVWPqKZK+/VXPbKaKq23oLrB3WNs7Yd2r3krbF7181ZRpT2brp+3iiqt5ZTaeVt/bO2Hdp+RFVli7dCqqrTnorWDq6rShIt6QeAv6eL8Kv4kD9ETxVRf2k98quzMJahpUO1eFuoSFDWodp9jmorB3nOs6w31niNtLSnXVrqHhbFyRisqrW9Kr5rN+4xxnSHea4TWhVbNuhpUW299VrOwBtXWWp/1
*/