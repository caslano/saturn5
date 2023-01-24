/*!
@file
Defines `boost::hana::detail::variadic::take`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VARIADIC_TAKE_HPP
#define BOOST_HANA_DETAIL_VARIADIC_TAKE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/variadic/split_at.hpp>
#include <boost/hana/functional/always.hpp>
#include <boost/hana/functional/reverse_partial.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace variadic {
    struct take_impl2 {
        template <typename F, typename ...Xs>
        constexpr decltype(auto) operator()(F&& f, Xs&& ...xs) const {
            return static_cast<F&&>(f)(static_cast<Xs&&>(xs)...);
        }
    };

    struct take_impl1 {
        template <typename ...Xs>
        constexpr auto operator()(Xs&& ...xs) const {
            return hana::always(
                reverse_partial(take_impl2{},
                    static_cast<Xs&&>(xs)...)
            );
        }
    };

    template <std::size_t n>
    struct take_t {
        template <typename ...Xs>
        constexpr decltype(auto) operator()(Xs&& ...xs) const {
            return variadic::split_at<n>(static_cast<Xs&&>(xs)...)(take_impl1{});
        }
    };

    template <std::size_t n>
    constexpr take_t<n> take{};
}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VARIADIC_TAKE_HPP

/* take.hpp
no5d/Uu+REx+PZZhYr48ejW7OD8SGbgrsesSbkDbaO9lRldC9mKUsMgh8/r1+Fb4e/RSZkV+89AHF8MhHV0ZNa8xKl3qwtlKp31ITK0r5ERzsX2/NJjfiYqk9EGvkKkz/7TSBmfU/NCeU+4O07Am7PlGNOw5+z56pEyGtQQlvgBoplYtSQfRjiD2hNYNIG0DYrBe0hEQPNbvjIB0M6u8WviqAxEQ8kNQ+ThhpqFaEAPVQrR+KxT4/AL1axfhO7F7MaUZvXwlpO1dpQTi8kbsJ5QwYlcJD6NqxmDAIF6K7PMBlYcSQkMtvtESqS5cIDQgMwlnEHuXFBxAhRPlhPwp7ddWNG+bjoq+B760t0LDgmrmPbYIqi8dsJeNwPEFrxGw6PIR6ev8AwdOo1+NS1FZJLNcac/vVALYy+3Yy2r69djNkjHWzc259gPYzRY40ajppZoFoSUjtAPSqfyuA6exuz9g3S08/NqFGoH+T/VGUI0QvRHUdz40go7N/00jpGpoAB0lvRFCfjs2AIbKWC1I8aFqtgKyn39rG7ScOLbiGIopS+2CVKhpldK8MpGPTVeSdL51Im7HI/OA9NTjApWSSdblHDeKVNPMKAW5QGZbbmJmwG9HBE5xFS7bQSVbuZtXWgMkc3rAbQ9I19oPSouVsNJS/xm6IU5rk0xFWoHSqTTXH0M6lxaAToYNJcP+gZRiD0lmD79Cs04Ppr0n
*/