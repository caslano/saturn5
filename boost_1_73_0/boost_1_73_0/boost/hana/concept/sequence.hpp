/*!
@file
Defines `boost::hana::Sequence`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_SEQUENCE_HPP
#define BOOST_HANA_CONCEPT_SEQUENCE_HPP

#include <boost/hana/fwd/concept/sequence.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename S, typename Tag = typename hana::tag_of<S>::type>
        struct sequence_dispatch
            : hana::integral_constant<bool,
                hana::Sequence<Tag>::value
            >
        { };

        template <typename S>
        struct sequence_dispatch<S, S>
            : hana::integral_constant<bool, false>
        { };
    }

    //! @cond
    template <typename S, bool condition>
    struct Sequence<S, when<condition>>
        : detail::sequence_dispatch<S>
    { };
    //! @endcond
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_SEQUENCE_HPP

/* sequence.hpp
FIYXzGqhNL28nIZeoVIlEEu1SmiDAhapjIvfz55JS0dKPV8CLEOpEzfnNxEHD2A+yRaeWErSsE5yVOOi4yy0fZ8LBwP0ZwgnboxWfDrqJR0lisOV5yzd+JaFASoiM9U6Kte8QyARoIg0WeM0TbxV7FCz0ENtBIQ9YDvYWoOdvesNkLqpA64Kivc7Sac2a5ssFd+uF2MypPNVIJ5H3vJE+6WacmgeNOU36dkBxZVbybwlYNSJJxHOL4dz1H4/qn3/xx/f12mKcYKx1CnrXl9e1rfsdAMY7g96ry/bV7xdoyukIGhil2EH9B4axU6DCZoRtG63gWxWXhBfR95qu95ItSMMDQSChkc0vNGBIT8l5OeGANsA5/56yOkZqT6/20uYsfmVO7kFAedx/V72gCuiDH3R6bbLOxbjHXqrT/7kkV3LIcOIf+u0KnQueo0e163obljeH87qIzvD6azQk0ZGb1bhetkP5/7kHrq2GrO/DZU5bwa9677T7112Wh82I7m/FEaDIh8BZDuIvRWwn8j7q2Fso7NWf9AZKhrehOskvE/wnWfs0MLs0oW/DePTmLTeu+J4aDHUGTnKDznnuVV75MMSwB/wfVnbBsSQp+tlZsiiqF7/j+/l2I0mcnHQux45vXPnqn3VG3wgeCxb
*/