/*!
@file
Defines `boost::hana::Iterable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_ITERABLE_HPP
#define BOOST_HANA_CONCEPT_ITERABLE_HPP

#include <boost/hana/fwd/concept/iterable.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/is_empty.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename It>
    struct Iterable
        : hana::integral_constant<bool,
            !is_default<at_impl<typename tag_of<It>::type>>::value &&
            !is_default<drop_front_impl<typename tag_of<It>::type>>::value &&
            !is_default<is_empty_impl<typename tag_of<It>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_ITERABLE_HPP

/* iterable.hpp
UkiBxa0iIAawVDfK8U4xZRMrIT1znRYuAKAUWqLCHuOWNtSlImyFxH6FPxAaPflbvBw2AFIr3lDgLD1NGRhxWt6AAFRmsFO5jx5gedcnQJ1OY52Zhb4thJ+DH+9tzwxHxgB9ky0ZmYQHlddDYVpLQMD5cOtOBV9cnuOY9n4S544lD+aQfTHWAzW0BmKmoABqfiAuK+2KPv/APWGFON/tCfpqcl4H7hVZvQqXmGD85LixLyNDufsQkX6wokFNfo6pOVCJ6nYwlBV7C0se2ihW59Ymb71a16vfduR65HmPDsLD+hyt3lKSl10fsZVoEYeIeBUzuZVmDb8xmyB2Tpufijg18XPyAxmI5bynaAi0VlhtEBIxCxPdZvPddZM5Cl/K3GXZXZQfIZU07hQeM4OCdxj4reHZIDDcB4vHtExz09ehl/2eqG2WayppVUxnw1Hwgg4c1rJwgzOIBxJiTjv8xIrrExUVmGOCrhhbrbnuuy6eK4KZRxLgOPObwBWiqq1GvL684vPG5Ps7TI0x1CS+WH/hIPdlAD9YBml3K+ELIzRQ2IrLRO1bBfLV8g==
*/