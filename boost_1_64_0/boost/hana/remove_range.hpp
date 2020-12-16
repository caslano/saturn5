/*!
@file
Defines `boost::hana::remove_range` and `boost::hana::remove_range_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REMOVE_RANGE_HPP
#define BOOST_HANA_REMOVE_RANGE_HPP

#include <boost/hana/fwd/remove_range.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename From, typename To>
    constexpr auto remove_range_t::operator()(Xs&& xs, From const& from, To const& to) const {
        using S = typename hana::tag_of<Xs>::type;
        using RemoveRange = BOOST_HANA_DISPATCH_IF(remove_range_impl<S>,
            hana::Sequence<S>::value &&
            hana::IntegralConstant<From>::value &&
            hana::IntegralConstant<To>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::remove_range(xs, from, to) requires 'xs' to be a Sequence");

        static_assert(hana::IntegralConstant<From>::value,
        "hana::remove_range(xs, from, to) requires 'from' to be an IntegralConstant");

        static_assert(hana::IntegralConstant<To>::value,
        "hana::remove_range(xs, from, to) requires 'to' to be an IntegralConstant");
    #endif

        return RemoveRange::apply(static_cast<Xs&&>(xs), from, to);
    }
    //! @endcond

    template <typename S, bool condition>
    struct remove_range_impl<S, when<condition>> : default_ {
        template <std::size_t offset, typename Xs, std::size_t ...before, std::size_t ...after>
        static constexpr auto
        remove_range_helper(Xs&& xs, std::index_sequence<before...>,
                                     std::index_sequence<after...>)
        {
            return hana::make<S>(
                hana::at_c<before>(static_cast<Xs&&>(xs))...,
                hana::at_c<offset + after>(static_cast<Xs&&>(xs))...
            );
        }

        template <typename Xs, typename From, typename To>
        static constexpr auto apply(Xs&& xs, From const&, To const&) {
            constexpr std::size_t from = From::value;
            constexpr std::size_t to = To::value;
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            constexpr std::size_t before = from == to ? len : from;
            constexpr std::size_t after = from == to ? 0 : len - to;

            static_assert(from <= to,
            "hana::remove_range(xs, from, to) requires '[from, to)' to be a "
            "valid interval, meaning that 'from <= to'");
            static_assert(from == to || from >= 0,
            "hana::remove_range(xs, from, to) requires 'from' to be non-negative");
            static_assert(from == to || to <= len,
            "hana::remove_range(xs, from, to) requires 'to <= length(xs)'");

            return remove_range_helper<to>(static_cast<Xs&&>(xs),
                                           std::make_index_sequence<before>{},
                                           std::make_index_sequence<after>{});
        }
    };

    template <std::size_t from, std::size_t to>
    struct remove_range_c_t {
        template <typename Xs>
        constexpr decltype(auto) operator()(Xs&& xs) const {
            return hana::remove_range(static_cast<Xs&&>(xs),
                                      hana::size_c<from>,
                                      hana::size_c<to>);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REMOVE_RANGE_HPP

/* remove_range.hpp
hvyYdvOQ1t3HnNQQyfw+cmVZ9LQvt078QY8K5krBdulnN5zz5hRjab/3BgvUk2WLxrY+C/7Itwj+yqJfGY4d9P10l095uMslEvQD/uWVA83+3nZ4hEC+zz7k0wOKb1LAow+luAbkzephIR99iDGf6HHR/v6X16b5IQ/rfdd1Yx4kx3cYtN9au4HPOxP07jRO9xtv6NNhYIJqObjzYv8+diOfB1fmdd+QaRlx2KcP942h59N6XnonyEM98tTP+VOtT5/gsw36Zif5K66NEACN+h2kGA2fBf10zI+s8c32yHdG+GFCuMpIx/pgP/MIuGHCHQNd2rzp5MrACdbu6d0N7yvg/R/O3/DAduD4v86/yeTtWEBf0G/ntuC6r2XdtpbdJwT5hJ2PHN/ezTsc3wFhKO4WxM/ghfScaqSSqpIN82+Ux4+O4kIufCe3meAWTioQPwJttIOm1iUUb+yNj8twFppeFEq03qdv5HOa1cFZA5TOchP8+fIq0NbtBumM6cOYAiYBjqhI3/XUV1PsjTMrQ+cWxHXSm8Wn4JuHcsNIoz3ME6hc39uGi5rlWHfrfr94C+6jZXFCAuewH0E69ceJe8jbbzC3nTiv2SVgvyJteWAal2+N4gNy5UTburnfPHINXz0kDC9JCYAHUo9nd82Mt2aNFaKUakANjEWPJRuHve1oERzf5HfCvN5F7DDKyzCu4E9rePh89LNRbMvztMxSXRpVe+sYRLAbx1l8yrdGsd51KXglkk44Xj0RZDmz5XoRLXu08wGQvfadqOoXVlE+/dY4rpDy0al9fPJHB1cgHJ1wcUAe9P72vqw+VVgYDh8/avUMtm0L7y2UVhSsFZXtW+fv6etbyRAi3A7AOhVH50jC+vO8dlO9f6a8jktj/FVjcC1B+0Vc198e4RuVQnZamcyuJSsKb4np/tD5uRzGGidzWlfPGtZcv3JqaxEWOqbX352mgzclpj8v0QPx4qktTN/6QUwHYkjH99K9lI5QGkM7oKpzGA/m435th/S0je5eh8SFu1TwE4CJCdUgjn82HppJWxbCum6Ka9Zvx/k1D0yO4XmR8emZfxZzNfBBW5dwZ9zCUY5zCDU40FbE18l4FawsTFnC3cTbUA1FB/RJUvgUyt5ZWeMD6xZ1pzqm4MRK+qc0hrFjhA9DH0bKh3OvYCjroiz/Ox1jZMsWji6n9ZW1yzLvX65NZbJ2wfEPcXxhYxsUCQjHHOzasI14znyM8lyUfovs6hriY4wwyj5F6Y5bYU3XFALowgUkv599bTT2vXRNW5eOjVqDe/DQVWybPyPecCOYa+EsAEFbLhcnJZwRMf3SIb3UJ0/ENDxPThQK6FL5y05t6YES0uE8ucSh0TzGc2bu2kT54lpwzhzO1wW+kX3tK/kbmSpKGB9H3PrmexSizgTKZ/PEFC23lZ7FqkBtR8aPwZCUSa/31dzuXxdtW/dtS3AIckvaNQTdPY3vI18d+Yv2WnndS8RR2NjCgvO83vGtAPanHKNdNB2XfRnfCnyAX/hthNvx6qxuy4TVfW87dzAGg9/QE6+g4rw03g+/lt8zZW2NsEWDfv+0KzOcp/P5SMZHMukxq9uKo+//vx0SNtWRUj7HO900qjIaXkKBNJ5uW2lOPfhrI2zHoi0aazsmBupjQ2itLEJfiBeVZARa/q7SWuWc6NjD1s7k8uPFXxvHuillq3g3YDW0QlFlSig51dk8O+tPCxPNFVXl64Dn+IF4Ff1Rsno6VlaF8lETWF4FzksaSNWXR/mA8rnItF1V1i5Ee5y+IqN8kH23mlnXStggShqfBPUvepiVxDk9zKX0PX6Ttb9m3MgaZJs+rdH8ARnbgu2+/Ncznwc=
*/