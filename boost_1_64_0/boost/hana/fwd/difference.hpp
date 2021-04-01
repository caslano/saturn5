/*!
@file
Forward declares `boost::hana::difference`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_DIFFERENCE_HPP
#define BOOST_HANA_FWD_DIFFERENCE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename S, typename = void>
    struct difference_impl : difference_impl<S, when<true>> { };
    //! @endcond

    struct difference_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&&, Ys&&) const;
    };

    constexpr difference_t difference{};
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_DIFFERENCE_HPP

/* difference.hpp
Tk79G9WIshNL62zVBGQ+VGU/hscy5XnZmuwOCtpmJvHbFOgHwY2Lc5zjmjMKk8t1v0JzZaDiYMlysl1zXFHaA5eRtsH76X4jTK4W96aFUkRBT6B4IywlpFJI+Eztjej8lctakTFlr3hHBndO7pmVJKyeoPbkcveqd/6z93c2817QLsfmYpqaFXisdO4o35f8nomSG706mc/g3qkLG2WOE3a5pQMXmTA3Ko6JU8eTU7lMOkNGVALA9XSlJ4U8ThcqxKPO6HeP5glHwK0DQsEK8Ptl269wjsmPc9e7ubYxNgArxZYMar40m0HAGNfInAJNS+QxldoBQuvZT5s1mwn6jn9Pe5eAiUNsea9fITBjehKGDaRunT63Lh53/kzQjHTbfQBhnord3hN3yiG4PX0w1NLYb+UXh/2Ku+lHPHdMNZBCFnfNRpKqO0lf37OcKjZUVaXyLvi5A5cocGeQuqBbSghK91m427zlYK1lanbvxIrapn1YfpiE0hXyo/xsFjo/wRMAUriwRZbQHyB5DGCR50wLNmFStj4tqrK30aCg3LfBhZzH2M3MIGiNEA==
*/