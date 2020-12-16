// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013, 2014, 2016, 2017, 2019.
// Modifications copyright (c) 2013-2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_AGNOSTIC_POINT_IN_POLY_WINDING_HPP
#define BOOST_GEOMETRY_STRATEGY_AGNOSTIC_POINT_IN_POLY_WINDING_HPP


#include <boost/mpl/assert.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/cartesian/point_in_poly_winding.hpp>
#include <boost/geometry/strategies/side.hpp>
#include <boost/geometry/strategies/spherical/point_in_poly_winding.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace within
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template
<
    typename Point,
    typename PointOfSegment,
    typename CalculationType,
    typename CSTag = typename tag_cast
                        <
                            typename cs_tag<Point>::type,
                            spherical_tag
                        >::type
>
struct winding_base_type
{
    BOOST_MPL_ASSERT_MSG(false,
                         NOT_IMPLEMENTED_FOR_THIS_COORDINATE_SYSTEM,
                         (CSTag));
};

template <typename Point, typename PointOfSegment, typename CalculationType>
struct winding_base_type<Point, PointOfSegment, CalculationType, cartesian_tag>
{
    typedef within::cartesian_winding<void, void, CalculationType> type;
};

template <typename Point, typename PointOfSegment, typename CalculationType>
struct winding_base_type<Point, PointOfSegment, CalculationType, spherical_tag>
{
    typedef within::detail::spherical_winding_base
        <
            typename strategy::side::services::default_strategy
                <
                    typename cs_tag<Point>::type
                >::type,
            CalculationType
        > type;
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


/*!
\brief Within detection using winding rule. Side strategy used internally is
       choosen based on Point's coordinate system.
\ingroup strategies
\tparam Point \tparam_point
\tparam PointOfSegment \tparam_segment_point
\tparam CalculationType \tparam_calculation

\qbk{
[heading See also]
[link geometry.reference.algorithms.within.within_3_with_strategy within (with strategy)]
}
 */
template
<
    typename Point,
    typename PointOfSegment = Point,
    typename CalculationType = void
>
class winding
    : public within::detail::winding_base_type
        <
            Point, PointOfSegment, CalculationType
        >::type
{
    typedef typename within::detail::winding_base_type
        <
            Point, PointOfSegment, CalculationType
        >::type base_t;

public:
    winding() {}

    template <typename Model>
    explicit winding(Model const& model)
        : base_t(model)
    {}
};


}} // namespace strategy::within


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGY_AGNOSTIC_POINT_IN_POLY_WINDING_HPP

/* point_in_poly_winding.hpp
2xXH08w7mPcy55hPMPUxSRPzUmYLczczyryJmWbeybyP+QjzFHPdB3l+mOczNzPrmVczfczDzGPMW5kzzIeYp9Xyb+B5YG5n7mbGmMPME8yTzDUfknwts4bZxHQzw8wYc4B5nHkP8ySTbuR1zNzMrGd2MqPMBPNO5uPM9R+WfDlzI3M782qmjxllHmWmmfcwTzKfYT7/Izw/zAuZu5he5iHmTcwx5h3MB5gnmQvM00zjR9kfMC3MGua7mD7mDcxjzDTzBPNB5m+Yq+KSJubFzAZmJ/MQ82bmCeZ9zEeZp5nrP8btZr6BeSlzO3MX08kMMqPMG5l9zAFmmpll3secYz7OPM1cd4TtgbmBeRmzgdnO3Mc8yjzOnGUuMNd8nPvJLGduZV7FjDAPMY8yE8zjzBPMB5mPM1cdlXwpcyPzMmYD82qmj3mQeQMzwZxm3snMMR9jGj4h+SLmBuY25ruYAeZhZpw5xryTeT/zUeZp5vNv4vKZNcyrmQHmIeYR5jHmMDPLfIj5BNPwSe4HcwPzYqaVuYvpZV4dkWxiVjItzJcy1zFP7ed1zLybeTtzknkz8wjzGmaQ2clsZdYwLUwT08gk5sI+yUeYDzJnmMeZw8w+5sHrJWP7/j3fZcWn+Pw3Pqc/xee7T0samS9nns/cyKxg1jBtzFamkxlkHmbezMwyH2IuqvV+RvJc5mbmZZ/5z67PCtdS/YfgI7NXrKVIx5LOLcbPtpb6nEu630BnQj53z5JuO/qx4FhbvHf7F5/ivVvx3q1471a8dyveuxXv3Yr3bsV7t+K9W/HerXjvVrx3K967Fe/dik/x+V97ivdu//jpWV3ddKWtpdF+wOH1+juoUo13Bl0uOlayta7RHnKF7Z1eR1eI3qDEO7wuR5A1exVNtyvs9jvt4d6Ai4KKxufaT3WQuCD6dL4kpyPswL6mxLvy8c/m0z0+T5joCk5X44l8esjdE3b69/vg22WeAl1a0fUE7EFXJ1FGie0PesIu2ijbHg56iV4vZXS53dGxRypvUHSBnpCbyCpb7vFxn67lPkXCmGm1JRzfqbYCVYaDvfjbEfKjJZ+T+VboPyr19g6/z+fqCNPbZF329p7OTleQ6E0ijtRAr6iA36aErrapCa0L213BoD9I40qusCukTg3dKDSiFifRKxS5qqamSZkIelk+LqfjJfm4nEyiPau27txm31G7Q3nBrcZ49jz5eFfQj/J8aA2/yu1JGxpttQ3NzfX20B67r6eb6ItazT6HtwfljGt1qAg5vV4a0WhlhUMFGkwDTWk0cpKuUC21W1ruJ/I5nB4XDchR9gWCHl8YluBVWuxwOmV72eou0dfustl31NhDngMuepEaq25ptXc7KacT8eo6m7W2SR3lL2h1Il+HJ+DGtN2xXO/ZZ/e6fF1hN84cpdvqbM32br/TRc35Vru6O7oD9Myq6sYdNkx3dyDoCoXs7ejKHvqj1LoiAQdMUOq+q6lBqmSrf6DRa2u9ZVmLtO/8VqbJplOZpt/SXl6q1aBdLtj5CzU6OUsv0GqEwaLBRCWKtsbTBdvcGcA4Y95P65Z02zw+h1fJ+fzl79PfNPmaPV0+JS8dXzHmYr2uW9dU1VBjb+/FIiC6lMuS6/WVHNP2+a+asuvgU0QT/ry8XfTFdc3Wqk12kYGOS7kl6PCFOv1B2PTtQlNevlmmf1WJbblQxr7GMW3+bwjdBRWc/1sitmVTuYzNcEyb/7OlO2q2yGS6WciaxLew5ajuV8zAEdXmhRIZXfS0tJz8TD6Rj8s3Ps7eB+ZH92vHdY+rVzWdc9TRy4/1yzQazXZAv9fYkTqmX9OWmm/HiUJt3qoqS6HHYttCO4UET+4=
*/