/*!
@file
Defines `boost::hana::reverse`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REVERSE_HPP
#define BOOST_HANA_REVERSE_HPP

#include <boost/hana/fwd/reverse.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto reverse_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Reverse = BOOST_HANA_DISPATCH_IF(reverse_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::reverse(xs) requires 'xs' to be a Sequence");
    #endif

        return Reverse::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename S, bool condition>
    struct reverse_impl<S, when<condition>> : default_ {
        template <typename Xs, std::size_t ...i>
        static constexpr auto reverse_helper(Xs&& xs, std::index_sequence<i...>) {
            return hana::make<S>(
                hana::at_c<sizeof...(i) - i - 1>(static_cast<Xs&&>(xs))...
            );
        }

        template <typename Xs>
        static constexpr auto apply(Xs&& xs) {
            constexpr std::size_t N = decltype(hana::length(xs))::value;
            return reverse_helper(static_cast<Xs&&>(xs), std::make_index_sequence<N>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REVERSE_HPP

/* reverse.hpp
GRpVTq/YOOfm2O37RLmi82mHNpTTpbMS/zx8frnoYd7d0p6Hy2lZxs2yWVd3i7r1HHD7b6acfjLs9e87h8eK7B/U7j5RWE57RUcZ7r/eJfqxd9KKE1Xl9NPgkFu2f2w3DIu8cejvlh/pt9vOzdOs+M6wfkKSrJf3R/qY6Hj7jNUqg8PW0CtHAj/Se569ebdPrjf83S1twKjFqHxbe17vs7tFtZd25jvqP9Iv2u+Z9vj79aIek/wfWP+CykeNtBzXf4fo1MiQje6XP9KHNsxb13asSOTf6VfnxS8+0qHPVZ5VP+wV2RauOP3YsoIe9VC2d9iTbQbN5MGpa90q6B0nxWvPq7cZXDNzvEcOr6D7a5OUIv9Nhq6dJ6/3mVVBe7UL+db2z72G5T+Ny5+8roKe4/dpxG8+4aJrvnGR+5Mr6MlzTrTwfrDXwPzdVOlorKDtmprmyrTLDH3bRIhOPKqgf04QyQdnzDfEbw+sijVV0BXNNnR1ECUYFGGvWWXHT/Tu1QkbRi1aZ1CsO+q/h/5E+96OWHAvJdFwee4wWUnYJzpvYb/gELdEAx36cMI81Se6d0t+k/TIXaJveSXLnQ5+ovvuFrxd6Rxv6H/ek/fm/Cf6dkDLm+McD4hmjb8xoOzJJ3rtKucz/NAlIsc2fpO6CSrpnjsXztoQs9XQ4vq43dqulfTd/s757cclGX691GVkm1GVdPW1oYfj7yQY
*/