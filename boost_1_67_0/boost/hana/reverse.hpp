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
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
*/