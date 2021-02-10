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
O/jO+dbpcx91HQhPv7OUsrlzoOJ6y91y+Gpm0q0NpWU2oxz6MxQaJ9Eq7IUKWhTuvcBYUC20m4lEFa5C2+6KbRixDOTC+HSSN7+VRD3gySvaF3VMkw398BarMLswTsfB2QUM+z62EiuT39qHT/+oCinwyUEFyu9VXwwHv75XpIIhekgy7Y34Rb1hBCLkIa3D0F8gSu7uGzYZZv4u2QhgmN9+i3lXN4UZ0GlRJc/rY6v+H9sFNtgYx0DzFMD6tw91RhaV6emEs9sEfXruU2ATSRX+QHwD0/JaipOqu/XViLAjFpSHJRAnWx5pdRNbjM+qbOQVUvmd8mFl8IsvycVRS8bjT4lAoweCJprbINYB0WB7WSrdvMRAjsuG11+eI2iITRxrwdQtR1Pkr4FumJbLhflARY7Fll/2BqZ3RhA5Zv5Y/faDf194abTHPhtmplncLLGdqcfYwAJ7LzDAAobfwcg+SYBYC8gyfbUGNhumPhslQh9tXxMjR/QCk3+iVdxjzkq+073+xeVYJjjb5HJjgRGQ/y+QF57X2D3mgKBbbkrkd5mrnsXe0oEWdOPmbmS7aeWPhoyEoY+kLLClnLpMM4BYztBsT0x+pFX1P2XQNOZqQGXDlw594ehV7UeSgWQ9VwvXWhJlg1Bz0LRI
*/