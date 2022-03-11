/*!
@file
Defines `boost::hana::lexicographical_compare`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_LEXICOGRAPHICAL_COMPARE_HPP
#define BOOST_HANA_LEXICOGRAPHICAL_COMPARE_HPP

#include <boost/hana/fwd/lexicographical_compare.hpp>

#include <boost/hana/bool.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/front.hpp>
#include <boost/hana/if.hpp>
#include <boost/hana/is_empty.hpp>
#include <boost/hana/less.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto lexicographical_compare_t::operator()(Xs const& xs, Ys const& ys) const {
        return hana::lexicographical_compare(xs, ys, hana::less);
    }

    template <typename Xs, typename Ys, typename Pred>
    constexpr auto lexicographical_compare_t::operator()(Xs const& xs, Ys const& ys, Pred const& pred) const {
        using It1 = typename hana::tag_of<Xs>::type;
        using It2 = typename hana::tag_of<Ys>::type;
        using LexicographicalCompare = BOOST_HANA_DISPATCH_IF(
            lexicographical_compare_impl<It1>,
            hana::Iterable<It1>::value &&
            hana::Iterable<It2>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<It1>::value,
        "hana::lexicographical_compare(xs, ys, pred) requires 'xs' to be Iterable");

        static_assert(hana::Iterable<It2>::value,
        "hana::lexicographical_compare(xs, ys, pred) requires 'ys' to be Iterable");
    #endif

        return LexicographicalCompare::apply(xs, ys, pred);
    }
    //! @endcond

    template <typename It, bool condition>
    struct lexicographical_compare_impl<It, when<condition>> : default_ {
        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper2(Xs const&, Ys const&, Pred const&, hana::true_)
        { return hana::false_c; }

        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper2(Xs const& xs, Ys const& ys, Pred const& pred, hana::false_)
        { return apply(hana::drop_front(xs), hana::drop_front(ys), pred); }

        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper2(Xs const& xs, Ys const& ys, Pred const& pred, bool is_greater)
        { return is_greater ? false : apply(hana::drop_front(xs), hana::drop_front(ys), pred); }


        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper1(Xs const&, Ys const&, Pred const&, hana::true_)
        { return hana::true_c; }

        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper1(Xs const& xs, Ys const& ys, Pred const& pred, hana::false_)
        { return helper2(xs, ys, pred, hana::if_(pred(hana::front(ys), hana::front(xs)), hana::true_c, hana::false_c)); }

        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper1(Xs const& xs, Ys const& ys, Pred const& pred, bool is_less)
        { return is_less ? true : helper2(xs, ys, pred, hana::if_(pred(hana::front(ys), hana::front(xs)), hana::true_c, hana::false_c)); }


        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper(Xs const&, Ys const& ys, Pred const&, hana::true_)
        { return hana::not_(hana::is_empty(ys)); }

        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper(Xs const& xs, Ys const& ys, Pred const& pred, hana::false_)
        { return helper1(xs, ys, pred, hana::if_(pred(hana::front(xs), hana::front(ys)), hana::true_c, hana::false_c)); }


        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto apply(Xs const& xs, Ys const& ys, Pred const& pred) {
            return helper(xs, ys, pred, hana::bool_c<
                decltype(hana::is_empty(xs))::value ||
                decltype(hana::is_empty(ys))::value
            >);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_LEXICOGRAPHICAL_COMPARE_HPP

/* lexicographical_compare.hpp
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
*/