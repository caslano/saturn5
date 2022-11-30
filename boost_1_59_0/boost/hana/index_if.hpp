/*!
@file
Defines `boost::hana::index_if`.

@copyright Louis Dionne 2013-2017
@copyright Jason Rice 2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_INDEX_IF_HPP
#define BOOST_HANA_INDEX_IF_HPP

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/detail/index_if.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/basic_tuple.hpp>
#include <boost/hana/fwd/index_if.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/optional.hpp>

#include <cstddef>
#include <utility>


namespace boost { namespace hana {
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto index_if_t::operator()(Xs&& xs, Pred&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using IndexIf = BOOST_HANA_DISPATCH_IF(index_if_impl<S>,
            hana::Iterable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<S>::value,
        "hana::index_if(xs, pred) requires 'xs' to be a Iterable");
    #endif

        return IndexIf::apply(static_cast<Xs&&>(xs), static_cast<Pred&&>(pred));
    }
    //! @endcond

    namespace detail {
        template <std::size_t i, std::size_t N, bool Done>
        struct iterate_while;

        template <std::size_t i, std::size_t N>
        struct iterate_while<i, N, false> {
            template <typename Xs, typename Pred>
            using f = typename iterate_while<i + 1, N,
                static_cast<bool>(detail::decay<decltype(
                    std::declval<Pred>()(
                      hana::at(std::declval<Xs>(), hana::size_c<i>)))>::type::value)
            >::template f<Xs, Pred>;
        };

        template <std::size_t N>
        struct iterate_while<N, N, false> {
            template <typename Xs, typename Pred>
            using f = hana::optional<>;
        };

        template <std::size_t i, std::size_t N>
        struct iterate_while<i, N, true> {
            template <typename Xs, typename Pred>
            using f = hana::optional<hana::size_t<i - 1>>;
        };
    }

    template <typename Tag>
    struct index_if_impl<Tag, when<Foldable<Tag>::value>> {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs const& xs, Pred const&)
            -> typename detail::iterate_while<0,
                decltype(hana::length(xs))::value, false>
                    ::template f<Xs, Pred>
        { return {}; }
    };

    template <typename It>
    struct index_if_impl<It, when<!Foldable<It>::value>> {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs const&, Pred const&)
            -> typename detail::iterate_while<0,
                static_cast<std::size_t>(-1), false>
                    ::template f<Xs, Pred>
        { return {}; }
    };

    // basic_tuple is implemented here to solve circular dependency issues.
    template <>
    struct index_if_impl<basic_tuple_tag> {
        template <typename ...Xs, typename Pred>
        static constexpr auto apply(basic_tuple<Xs...> const&, Pred const&)
            -> typename detail::index_if<Pred, Xs...>::type
        { return {}; }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_INDEX_IF_HPP

/* index_if.hpp
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
*/