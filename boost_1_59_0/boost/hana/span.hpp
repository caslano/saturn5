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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_SPAN_HPP

/* span.hpp
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
*/