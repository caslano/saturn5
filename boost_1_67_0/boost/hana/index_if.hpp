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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_INDEX_IF_HPP

/* index_if.hpp
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
*/