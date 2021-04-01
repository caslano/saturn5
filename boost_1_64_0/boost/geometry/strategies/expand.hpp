// Boost.Geometry

// Copyright (c) 2018 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_EXPAND_HPP
#define BOOST_GEOMETRY_STRATEGIES_EXPAND_HPP

#include <boost/mpl/assert.hpp>

namespace boost { namespace geometry
{


namespace strategy { namespace expand { namespace services
{

/*!
\brief Traits class binding a default envelope strategy to a coordinate system
\ingroup util
\tparam Tag tag of geometry
\tparam CSTag tag of coordinate system
\tparam CalculationType \tparam_calculation
*/
template <typename Tag, typename CSTag, typename CalculationType = void>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_TYPE
            , (types<Tag, CSTag>)
        );
};

}}} // namespace strategy::expand::services


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_EXPAND_HPP


/* expand.hpp
RkZCOQjgBk76Ge3cz7E6Dvw7WBZPk0gm/GHmXte3wXdVzY7BK/IHifG4PT51DCdtC1z2mszrZGnKFj6zBn4+SzeJl+HLunfEwM6SiNTErhue7538CzWBW0hp7oLaJwFLkN8JZvnD6A5y63CKoEO/x3lD7Mga9OuBtUDUc5jKRtj+3C9j8ezJ0VQaiHPGbJZHS8E/3bt7TX9WMehcLUQERy9lnG2OrdCto3x/F4oElyr0VzCM787tlnnsQfpcCswxahzm6IFqxDEBGEnVJA0gMLh+fAD/7CgDIieWBDF6lc6ija/oHn0I+Cz+LjMOd8rAFqXg4iuVDpZr1Ubf71zDOpHM2H6oRdsw48E/lebcwWd2cDv1TYj1DDf74aYGqkWP1iSaIRB+wzXefpNUcFYLdDynKXi/BIufF9K8qK1Hwr1LqReNZyaEBOo+KBGrZePxVkGlBKpF4s9Q9Sfm5Q6sg4pkfhEpx0HKkBF6fEq8PBk/wxYzAGOAGywS4T/gQCSS6ZSbRG5wtAkllJI7AniC66dW8W4fYuiLeOIsqNg2l7gwsNZ7v3RUX7eYDQ==
*/