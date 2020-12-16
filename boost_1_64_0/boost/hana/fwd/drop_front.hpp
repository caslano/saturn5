/*!
@file
Forward declares `boost::hana::drop_front`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_DROP_FRONT_HPP
#define BOOST_HANA_FWD_DROP_FRONT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Drop the first `n` elements of an iterable, and return the rest.
    //! @ingroup group-Iterable
    //!
    //! Given an `Iterable` `xs` with a linearization of `[x1, x2, ...]` and
    //! a non-negative `IntegralConstant` `n`, `drop_front(xs, n)` is an
    //! iterable with the same tag as `xs` whose linearization is
    //! `[xn+1, xn+2, ...]`. In particular, note that this function does not
    //! mutate the original iterable in any way. If `n` is not given, it
    //! defaults to an `IntegralConstant` with a value equal to `1`.
    //!
    //! In case `length(xs) <= n`, `drop_front` will simply drop the whole
    //! iterable without failing, thus returning an empty iterable. This is
    //! different from `drop_front_exactly`, which expects `n <= length(xs)`
    //! but can be better optimized because of this additional guarantee.
    //!
    //!
    //! @param xs
    //! The iterable from which elements are dropped.
    //!
    //! @param n
    //! A non-negative `IntegralConstant` representing the number of elements
    //! to be dropped from the iterable. If `n` is not given, it defaults to
    //! an `IntegralConstant` with a value equal to `1`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/drop_front.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto drop_front = [](auto&& xs[, auto const& n]) {
        return tag-dispatched;
    };
#else
    template <typename It, typename = void>
    struct drop_front_impl : drop_front_impl<It, when<true>> { };

    struct drop_front_t {
        template <typename Xs, typename N>
        constexpr auto operator()(Xs&& xs, N const& n) const;

        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr drop_front_t drop_front{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_DROP_FRONT_HPP

/* drop_front.hpp
VvrmxV2sDpO8evumaZkmiUzRuvCIqDl8pYXYR7DsgbHSFVri2DVW5acQdFIUDdd0K1+7MNM7pBfty0+KttPXo+zL05re4EOEtLRrnVsvpm3p9Tn6/Ts2LaXMLqM6+FyQOm4sGx1UL+5FCL9+bzQ5juJ7EN9RJpNjLX5n8rP25fh/mV2OT+uj2r/E5n0t338AS+WVxwfPIPwzb1e3UJpxS7ocwNhP/OxzBuJniZN1kqn+gWvrsO/qR9aiosbAFaF3TFGPj4gqWfUSLO3biduj1y9jZKhvWVVNmyJ4e80c825T1mTaaEUtfEX83TxjwEq+zEdNj5qbJvYd8zYxjtdtAH4toCUBxh/DhXEApV/Gma3ozC4sWTPEN9Kt8STSowJDbmWxTn7clqR0dxIPqqVbddE/w+Zkcx7v/2cIf0wFvN8vkVdC8gIppWCA82jDlIlrsGFw1rgDm+7aSU/2RzOqyQn0d5akM1FrtJkcMrtDKA3Vgp0PnosRdhuCNHfmgc8gHoS+HsVp5eVoUc1iLh0stNZ+WmfbO2CihPIkfn3ag0c5xFavc7XcFAi6XOI3+gU/RWYJUlmqJYQEC/GmLDuiMTsDYNxTH5z2dWnMr5QZAiMYbHvDNCNi79dBkwm0BUhFzufhGChfiJQqLUEtg4MyPKZn2EAZzlPbQnB4uREQXeZ304IKR/fNje1OSIllaiDc+3hwDWuPqvP3CDEQRQiDgUsaya/YVDZoVX5RpW3NyCbbWgxK08RGr0d5E+QL19leyoTc1w8qNYeFTTm0Z4ZxPYg8+BpB0ddtay5A6geQmg5DmzDWCHfDpghBBNn3/HSW8xArWFke2k45ap/Gv+Aq7onAIp9H2S/EdYAcu24GXrnHqXFoTVgK4l1PtpAgM3rUy7zKRYBOOhyP9q/CXFh2IUPa/muaKR/oXXw9dXEbwnzo1bW5TGILmUCr/ZSG7hP99AOkIr0CIsIASiU0ev/T/pZ+kcQNbJrBXZEDFvoDZqHnuZluwd6yuzqJj77CLfCL+OgBb8dR6wxjvH3noGr0lb3+HXQoETyeRx2BwR0VFktgAHU/uNwpRtkwptX8eNS2HjvrRgQQTMwGkgwIbnuHa2Wy0ZD2XSYe+eAI9Hb1YO5arnpkQtV3mjTNLA1x9A6pp6iVEM9RQ6dW2uqmsT2lo+kGgBs4128ACnxzVtxlzwB08a+w866G2LaPkKwjYwmGnwoArtVuA6K5DnNxX7fZvzuU5Q9+oxtuT2bp6rLs4pjK/jzKIqGPsAdRQKbBaNRV8yaFTfid61aa3oppDhjWUWylbUYRnFVsJ9OPUev6dBYt5NPIIQN7ePPOZY97yn1mnef9hpEHQC06NzjQywcEz1h1CKIOEmDgxTlmh3lPGL/UuPJQi2gcmrPBBUYgOodJBMai3Ji4/2+fbhSQUyljdlAl5j1ICvHgPFxRcEvf0JNvouQsMUElguA8HzqONU01DBu0szyxD+SJVEz0AWmZnjdMeffhH03R6QSh2r97Z+j9KxQrOtKNgaXo5L/n8oxvz+CpUUANwsCpbaqN0O6XjXw87pP7j2l1V0GgPkE7v1yqIo49aSYFLguP5amjU+8GHd9W81xtmaTJ/4pjK51SC2Jwui49RSksyuqR6qqm5/+Bnn8J518r8lPeZynUpJSLE4xF+noEe1PD002OZ6wmx5oMk+NarDwe/H6Pw/7zeaT/5Y9q/wNctGoJg+x/1LDzRPJg4qUjbNnMF6H7d7RC9DBAdU4zcd2BFnE24aQ30h2l80wQafFvXILE4ytKLEY8g0atWxJIJokkWMgBgVmmqBnTNNeAZNv1ZKva16knteKsi8DK82Jz1KnttHGI/lQ=
*/