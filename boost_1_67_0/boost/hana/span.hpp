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
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
*/