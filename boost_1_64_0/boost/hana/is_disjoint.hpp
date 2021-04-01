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
8DuSv9pGTprqeNg9hswJHGytUDeeQaBytYWYZpMBwYrXjLKk6DgSqbMYNePvBGrMnCiAdUNpemr1vXLrDFsbAWaYYgL3ROZoKwdcknLa/8lM4VLIq66wbXia4sirythgkKaJrHzK01Rgmazfb16769uoOq/0ZNFJkPX9MgQ9gSe0Pe2YpiD0UpIw4AHwfu8j2cKaTttuyfaDd+hPSN5szK+5z5xXHyik+l8/SMryosCVzAwJ6iF5hZ2SSbPzH2LFYA0uS+/ZW6YeXcqkg6/3Zz1KSaBCxPwm78sXluaAE3//cAJB3FYnyY/sEyD1oO2Sfkwe/kujAASu6n2cGWQFVjJDSJ7PyGteSozNJeJ8hcJfD/p2Eim6Pi9GOH1TZ77WQFF6CO3L/VgcwLH8yRmsVcjOilHtL1x/v7qQnDewqifRJ9nwz5BadX9/5ARRwQWN9xt4fz1Lgi2UDzNNkhAe9DPTt2QWE5gR8yimmRB4iz9rWHsIKPk97SGGwWrObWjh+6blEvJqoTKer/WmP+wY3Kw3x8Qu4k58hXmWNdF7c3qj8p5PMAhxmNpm+g==
*/