/*!
@file
Defines `boost::hana::prepend`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_PREPEND_HPP
#define BOOST_HANA_PREPEND_HPP

#include <boost/hana/fwd/prepend.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concat.hpp>
#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/lift.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename X>
    constexpr auto prepend_t::operator()(Xs&& xs, X&& x) const {
        using M = typename hana::tag_of<Xs>::type;
        using Prepend = BOOST_HANA_DISPATCH_IF(prepend_impl<M>,
            hana::MonadPlus<M>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::prepend(xs, x) requires 'xs' to be a MonadPlus");
    #endif

        return Prepend::apply(static_cast<Xs&&>(xs), static_cast<X&&>(x));
    }
    //! @endcond

    template <typename M, bool condition>
    struct prepend_impl<M, when<condition>> : default_ {
        template <typename Xs, typename X>
        static constexpr auto apply(Xs&& xs, X&& x) {
            return hana::concat(hana::lift<M>(static_cast<X&&>(x)),
                                static_cast<Xs&&>(xs));
        }
    };

    template <typename S>
    struct prepend_impl<S, when<Sequence<S>::value>> {
        template <typename Xs, typename X, std::size_t ...i>
        static constexpr auto prepend_helper(Xs&& xs, X&& x, std::index_sequence<i...>) {
            return hana::make<S>(
                static_cast<X&&>(x), hana::at_c<i>(static_cast<Xs&&>(xs))...
            );
        }

        template <typename Xs, typename X>
        static constexpr auto apply(Xs&& xs, X&& x) {
            constexpr std::size_t N = decltype(hana::length(xs))::value;
            return prepend_helper(static_cast<Xs&&>(xs), static_cast<X&&>(x),
                                  std::make_index_sequence<N>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_PREPEND_HPP

/* prepend.hpp
eAKEtWwzr9UByvg5TvhqsE94QUt83YY+JDqPe0HFTDI6KLh/k4AtLNElI577tYJ8OihtqAqJUD8uttX9PUB7iU2rNsSSP4SS2ejDbckdz7JprFsQhvcDt7SgfMFAGvNQoG1UtnYP4ihEi0fVZBxeuSN3ycFykfk5nt+RU1xsFez47omV/W7kOBo6TL1TUNjV/dZ24XOSAD1oNhx7pKQC+cCaSD+MHLL9uDUf91nT5WR+Sg+eQ41LzFpx4TyqromNqSgE7Hb2VLrZpK2bsS4LQnvTxkwD9jHYTtDb0kk5QHmIM96/hlpjbwvdbdnc20ulMJFWvMAnFxVdyrtAm2FpOq5uChNJf1pOkJw1okUx0nEIWnLFnv+SQsWboWBWuY8PZZWcQBg889e6yWmk5Tj6qvZCBsHfgRWU7uKnxkQ+ibjmP7mdXDh82wNt5hOaGyMQ1ag0rCyidqd3KM+KHZs5kdfHcnCoor7MR5Fa5xG1HPnUcjeuzzNFxbAzyRrRYSTSifxYpuPbaLRGYDa/DYYO47yVTshpHRom0+10Z7Y7uEossRNUrmpJVGJJzw==
*/