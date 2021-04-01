/*!
@file
Defines `boost::hana::span`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_SPAN_HPP
#define BOOST_HANA_SPAN_HPP

#include <boost/hana/fwd/span.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/detail/nested_by.hpp> // required by fwd decl
#include <boost/hana/detail/first_unsatisfied_index.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/unpack.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto span_t::operator()(Xs&& xs, Pred&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using Span = BOOST_HANA_DISPATCH_IF(span_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::span(xs, pred) requires 'xs' to be a Sequence");
    #endif

        return Span::apply(static_cast<Xs&&>(xs), static_cast<Pred&&>(pred));
    }
    //! @endcond

    template <typename S, bool condition>
    struct span_impl<S, when<condition>> : default_ {
        template <typename Xs, std::size_t ...before, std::size_t ...after>
        static constexpr auto span_helper(Xs&& xs, std::index_sequence<before...>,
                                                   std::index_sequence<after...>)
        {
            return hana::make_pair(
                hana::make<S>(hana::at_c<before>(static_cast<Xs&&>(xs))...),
                hana::make<S>(hana::at_c<sizeof...(before) + after>(static_cast<Xs&&>(xs))...)
            );
        }

        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&&) {
            using FirstUnsatisfied = decltype(
                hana::unpack(static_cast<Xs&&>(xs),
                             detail::first_unsatisfied_index<Pred&&>{})
            );
            constexpr std::size_t breakpoint = FirstUnsatisfied::value;
            constexpr std::size_t N = decltype(hana::length(xs))::value;
            return span_helper(static_cast<Xs&&>(xs),
                               std::make_index_sequence<breakpoint>{},
                               std::make_index_sequence<N - breakpoint>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_SPAN_HPP

/* span.hpp
9LQWq4Oa2Cdd0zf7X6IDXjrWnlgSTscyN2KtZcjYuafk0LmTt0hb0iF0tRoslFY5djg3Fjee1vf/32oxrK8lV3xmIEY2XhShAUK5+urRsHcmPYMGqsLFo/zF7Gy3hpLHn/1IlP2ja6SMogsBXjw/O4kHC9s7ZZs8Cj4iiduY/15gC23pRHYZXMDA5fI8KaVM/f5dXKMl0MMqE7ci2yurCW0LFiGSBj5g1raVzAoJcyOnrcpg/Ti6W+20ceVwiNMeSYuqZ4dVlnhX1hj/QzeC0qXa1XDZxtZ2sMalBKK6ePU9UGigz1RoqzYf1hZ1Iic4DwXcn8WqjSoATH0MxfO0IB2ZBTkXH4kItXV2gk50QsjKo6sm/xVA8Ee7LkoSZp0f3VmTr7jP/wqPMsU+4qg1GH9D0Vj0Xb65WkmfMZan6FKtP6Yu6VR4Djd4JeyA9feQkxge13CKw2pMph6YrVRPoCHQ49jr0UXv+dazxE4iGtWIVr65HC/xIsyQYKW0Nde3JhhiiQ9CgZlt1u9dD7Qq1grmcLgWK1AN7bQg8ke2Uv2SmDELHuKaViGxHA==
*/