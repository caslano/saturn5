/*!
@file
Defines `boost::hana::then`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_THEN_HPP
#define BOOST_HANA_THEN_HPP

#include <boost/hana/fwd/then.hpp>

#include <boost/hana/chain.hpp>
#include <boost/hana/concept/monad.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/always.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Before, typename Xs>
    constexpr decltype(auto) then_t::operator()(Before&& before, Xs&& xs) const {
        using M = typename hana::tag_of<Before>::type;
        using Then = BOOST_HANA_DISPATCH_IF(then_impl<M>,
            hana::Monad<M>::value &&
            hana::Monad<Xs>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monad<M>::value,
        "hana::then(before, xs) requires 'before' to be a Monad");

        static_assert(hana::Monad<Xs>::value,
        "hana::then(before, xs) requires 'xs' to be a Monad");
    #endif

        return Then::apply(static_cast<Before&&>(before),
                           static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename M, bool condition>
    struct then_impl<M, when<condition>> : default_ {
        template <typename Xs, typename Ys>
        static constexpr decltype(auto) apply(Xs&& xs, Ys&& ys) {
            return hana::chain(static_cast<Xs&&>(xs),
                               hana::always(static_cast<Ys&&>(ys)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_THEN_HPP

/* then.hpp
xBfIhs3x8tzRAHkY+0eThXGFIilz1lr42I7VhVdwjxBFS4WTPcclB6N3H7yMC3VPYQAguPlHbne34oflow2RcrkM9fzu+H1+UoGFFrqUoyNTcKisvXjD09sCO4Ct0X8hvyWccfE0cJFB140DAZDD97HeP7pd8qzLIF7UC8p2qDdRKmdJlZg7eY+Sc8tIU7MZ+2OTdBeRhWlIIcASrohFX7FOoHBAfrbAqgQl/HNUFvdMriePT9DnWz7Xy8hMlKB0MxXPZzpFasY9UI9YtPXiU2yuhOJAqCij5hrOnF/+E8OCX1pf5zLJP17nBG9El1rFZcdd8pS13U5o4D/jSL6S+XH/u3O7l9+IBU7UxfbcG32FgqRpKf62WiP1u3cI8jAthY7JjJyLMpit+vhcS6nwKOy9p8lTPTyiJsszlSkUKASvAoi1GgIhBlUTj53KZUmTPPLafgSWDT295bZAqAod4uBegvTc//WVTYyFdRSrXdyOFCV2K/Ophi0W7Aa4t9u/b8eqXKqFIWWzJWYeaZmz+Yo1EuJhf6uVCe6+M5k533uXI2HJ0NDT8DJJpg==
*/