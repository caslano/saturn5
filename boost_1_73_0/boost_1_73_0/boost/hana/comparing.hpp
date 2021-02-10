/*!
@file
Defines `boost::hana::comparing`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_COMPARING_HPP
#define BOOST_HANA_COMPARING_HPP

#include <boost/hana/fwd/comparing.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/equal.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename F>
        struct equal_by {
            F f;

            template <typename X, typename Y>
            constexpr auto operator()(X&& x, Y&& y) const&
            { return hana::equal(f(static_cast<X&&>(x)), f(static_cast<Y&&>(y))); }

            template <typename X, typename Y>
            constexpr auto operator()(X&& x, Y&& y) &
            { return hana::equal(f(static_cast<X&&>(x)), f(static_cast<Y&&>(y))); }
        };
    }

    //! @cond
    template <typename F>
    constexpr auto comparing_t::operator()(F&& f) const {
        return detail::equal_by<typename detail::decay<F>::type>{static_cast<F&&>(f)};
    }
    //! @endcond
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_COMPARING_HPP

/* comparing.hpp
E9UHvbbSZje277ls6uJRKXyxow3ICwOZnZdnhNdtyodrbsooQ3X+LqWMqM8D92X988f26Pqe1tqvm3XKB2ofyMcxjziQTFB4AduqT6+H1Fg7ofeC4oLfk7eClhTLFYkIuZVcR7OnX0aRKoElRNQakBX17OK2pOvkx1ntlaeH1jo/RAxd0uaVa6FQKKWssDZGHFeGzISlFw8KsOc2RtWlpFo3cnqwbg5ObsHLltrSeajLrsjbG7/Dw/QpGqMVk1K5Mg0GspEDhXraIuYX7uVVeHkwLjaK9JlMY5prhWFqVt3ySVPzFtuW064uQYMw0bOUZLsazhLv5FLxCakKZa/PQ4kGe71W5YAUIP39esnCcXiSTBe+f6+/00t/NQq5aig4qVO+5uVx4qu8la65JIrL7QBq5N2Kr8t7Va0K/RK1suPGQAYrQn8OLCaRVvAHloOBXwp9fs3MAW3B6blGV/cpTywyikpBVUyPai8VQOLls8liLjFVcvx7Ab4tcA2hIQMDVH95ykb2KQ2VQbLBcKINBsguB5fj3ol10Rl1znVmymocL3sd8QvxNuJ/o7cRsxJyGgIJ+dxYDiq555V7cV8tsgQWIqh9cmG1WIhpW7cevsYZaLSIeeavKo4EG166YjSiaEFsCGkARpd1ejno
*/