// Boost.Geometry

// Copyright (c) 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_SPHERICAL_IO_HPP
#define BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_SPHERICAL_IO_HPP


#include <boost/geometry/strategies/io.hpp>

#include <boost/geometry/strategies/spherical/point_order.hpp>
#include <boost/geometry/strategies/spherical/point_in_poly_winding.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace io
{

template <typename CalculationType = void>
struct spherical
{
    typedef strategy::point_order::spherical<CalculationType> point_order_strategy_type;
    
    static inline point_order_strategy_type get_point_order_strategy()
    {
        return point_order_strategy_type();
    }

    template <typename Geometry1, typename Geometry2>
    struct point_in_geometry_strategy
    {
        typedef strategy::within::spherical_winding
            <
                typename point_type<Geometry1>::type,
                typename point_type<Geometry2>::type,
                CalculationType
            > type;
    };

    template <typename Geometry1, typename Geometry2>
    static inline typename point_in_geometry_strategy<Geometry1, Geometry2>::type
        get_point_in_geometry_strategy()
    {
        typedef typename point_in_geometry_strategy
            <
                Geometry1, Geometry2
            >::type strategy_type;
        return strategy_type();
    }
};

namespace services
{

template <>
struct default_strategy<spherical_equatorial_tag>
{
    typedef spherical<> type;
};

template <>
struct default_strategy<spherical_polar_tag>
{
    typedef spherical<> type;
};

} // namespace services

}} // namespace strategy::io

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_SPHERICAL_IO_HPP

/* io.hpp
eUxDV7yCFTEv15sqWB3fxI5YFTtjDVyEtXAn1sYv0A0LcJ1pgJHYCCdgY5yDTTAFm+JhbIaPsDlW5PrSAn2xJfZADwzHVrgYW+MB9MR76IWluc60wQrojdWwA/ZHH5yAHXExdsYd6IsZ2BPvYS98gr2xlCP1JJZBP6yN/bAL9seJOAAn4WCciv5IvcD1UHk/yHtDY73QkP9vke8bf5HnBkexJX6Fk/AbnI0ncQWewu14Gj/Fb/FLPIMX8Ht8gj9gXZZ9Dlvgz9gez2NPvIC98SIOxksYh+k4Cy9jIl7F7XgND+B1nEHZb+BWvIXH8DZ+jXfwCt7D53gfy+r7HsAm+BDfwkc4Bp9gOuam/oy25zjHSeiAszEvzscCeBcL4lMshHYOHO9YD4tgLDpjPBbD2VgCF2FN3Iq18BjWxl+wDj7FuvgPrIe/YTPUv9dtjpHkl8SXnm0xdi+N99XZ+ld/aUywrX91W//qOYkd/m/rX/049cBtkhMPUZqS/EhxpGRSGukqyT6W+GKSDymSlEjaQTpFuk8qOZZ5SQNJMaQkUhopg6QbZ+uT3TbZpv/2yV7374j/p03gsOCo1xH/r4/jr6jE8ZvGAihPciCVI93Xxx//rlNi0Nu85e3dvqc6jh9e2IY2n9LmN1AVg5Ek+XmQnElNJb9TWfOTWPzsx7tr5VdFqtEBpLKkPqSHfM71jyz5EcJkaOuc4/wcVfH1QRYxruHqfjylPD1l/btI2+sUY3kMe1tWHIcEya5/aTyQxXjPErOhlFE1DjDfewzTIinDfCmD0/OsZRgbFRoTbCxEjvpwkHJYxAlFhkYGy3jzStnGGmKsZZ+p+gPwkfK1lfKdkvIpY95KuaJ12T9GpFyqfZIsz2X4LiRjlBvzcyM3VX7me0TyDHnJOLv9cqnH2Y00K0Nxpb9SUztI2t9Km0t1+3gf5XNDwkKHK2McK/vXWelPVbu9fIa8g7lNYcrgdXzMvOm5LNZRtcezt45rc794HcfpzOJaxpqOgXhVeS1jAIeOiYrSf9b4e5+s20nai6qOI81t56nedoY2pSn2hvY4jKnJ98rc0qZUtU1jQkKjlWPzT41RnNM2pNptCW1tS/9f25b+q9uKWmsTmquU/vfhM3bdPRlSPtf7ea6/PaPQt6O4fhqu23KPgOXlXYQ91pbKobS+GQ+WwaJYFsthOcyc/5TM76Exv6u8y6iItbESNsXKSptSuYbjAI02pY58riwWwSrohK2wKHZCZ+yDxZTlyTUYe2osL1nKswYrYQq2xLXog+uwC66X5UXq5HqKi2R5BTFIljdPlrcQK2IiVsdF6I2LMQCTMAyXYCy+i+NwKc7GZTgflyv9Ccp1En002vBOk3ynoyvOwCo4E5vjLNlOs7EtzpHlHiXJ9ZDrpHG5xSWGNrNtsDNWxzJYC2thHWyPdbE7umE/bICB2BhHYxOcg83xXWyB76EH7sJWeAhbYwZ64k30wl+xDTpQrvZYCb2xBnbELtgJu2FnlDZFmdc+rolZ2xR1lfXojlWwNzbAPtgG++JA9MPh2B8jcRCOxwBciUNxMwbhFzgMz+BwfIojpB/HkVgTw7ANhku5IzAMIzEGR+N0jMKZGINLcQxuwFjcieNwH07AAzgJr+FkvI5TsIr9y/sutD3LtD3LtD3L/N9+lhlJI65E0g7SOZK+IVh1ki8pZoLtOaRtsk22yTbZJttkm2yTbbJNtsk22Sbb9C9//w/+YUPGMypjdAN9A4DX8P4/v9n7/+ryPr4HOqMv7nbhP/sNj0il+3lfr36ZDQCy8a41813kTmOfX2H8V/X+eYPkWUbaHJQmfctnt6VmzdPQZx/bQLrKemnbA+kbO0s=
*/