/*!
@file
Defines `boost::hana::is_disjoint`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_IS_DISJOINT_HPP
#define BOOST_HANA_IS_DISJOINT_HPP

#include <boost/hana/fwd/is_disjoint.hpp>

#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/contains.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/none_of.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto is_disjoint_t::operator()(Xs&& xs, Ys&& ys) const {
        using S1 = typename hana::tag_of<Xs>::type;
        using S2 = typename hana::tag_of<Ys>::type;
        using IsDisjoint = BOOST_HANA_DISPATCH_IF(
            decltype(is_disjoint_impl<S1, S2>{}),
            hana::Searchable<S1>::value &&
            hana::Searchable<S2>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S1>::value,
        "hana::is_disjoint(xs, ys) requires 'xs' to be Searchable");

        static_assert(hana::Searchable<S2>::value,
        "hana::is_disjoint(xs, ys) requires 'ys' to be Searchable");
    #endif

        return IsDisjoint::apply(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys));
    }
    //! @endcond

    namespace detail {
        template <typename Ys>
        struct in_by_reference {
            Ys const& ys;
            template <typename X>
            constexpr auto operator()(X const& x) const
            { return hana::contains(ys, x); }
        };
    }

    template <typename S1, typename S2, bool condition>
    struct is_disjoint_impl<S1, S2, when<condition>> : default_ {
        template <typename Xs, typename Ys>
        static constexpr auto apply(Xs const& xs, Ys const& ys) {
            return hana::none_of(xs, detail::in_by_reference<Ys>{ys});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_IS_DISJOINT_HPP

/* is_disjoint.hpp
yWY+m62Okqr2RFSmJlO8f7zH5VVT5E3Pg2IrafKeO1SmJJ3Lai6XoYeh5mH3GuFvLB+zaMU4xQY5G6AW8S1o4u9Im1eORi7ZMn1grMWkN9jk6jUok6SRqyqmUqcmjWVLHjpnVikNaeUqm8/c8v+jNHuIdL3Hb0U8BZr9SGlUNc9Aic3nkufph9PdftJYSLleFyt6KGnVisZYVM/KFGmeZ5ONiJFuHW9RBjGvIf21WfSA0vzSexQ0lms2PenRDJj0elLaSlqZIvy/m793mR8+39Aq60MvxkwYW9KEeLcJ+TjIO748x25cV2DiT+3wvn6YFKuapcs51U7kK40Eqpo/K7UyuV4USjRUljHPPgmlvKtZMH/Dm92jdS1f56Q5fo5CyjqLcoxlkzitSYqZceV5C7WleP5uNLln7NXPyNOqKU3ldWnP+5/iSBxTzuNiZW/xyi2EaJQ029YqtN5SGOqNpXYnjeyU83fS/ci1KTbZ+MxDF/7flacjaa4odBC8uYOY9/4xSYsqUeddPuXeR9rnIqUkl5mHS7Wr6MmiuG7H/g8lJK2a99gdJUMy1I/J10tS+F8y/CVwOWrHQ1Weo9BozjNXQD1bNox46P3u2ftZuX51inHdP6VDPxqv2Ji0c1IpxQ8jIdXrmIZWil25p5JmQlLO3jsb5WGqGpt6nnl04wbZDlXv+vRef0mDFAsfwHu9V+v6T96REVarqaTq
*/