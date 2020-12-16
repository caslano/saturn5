// Boost.Geometry

// Copyright (c) 2017-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DENSIFY_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DENSIFY_HPP


#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>
#include <boost/geometry/algorithms/detail/signed_size_type.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/srs/spheroid.hpp>
#include <boost/geometry/strategies/densify.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace densify
{


/*!
\brief Densification of geographic segment.
\ingroup strategies
\tparam FormulaPolicy The geodesic formulas used internally.
\tparam Spheroid The spheroid model.
\tparam CalculationType \tparam_calculation

\qbk{
[heading See also]
\* [link geometry.reference.algorithms.densify.densify_4_with_strategy densify (with strategy)]
\* [link geometry.reference.srs.srs_spheroid srs::spheroid]
}
 */
template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class geographic
{
public:
    geographic()
        : m_spheroid()
    {}

    explicit geographic(Spheroid const& spheroid)
        : m_spheroid(spheroid)
    {}

    template <typename Point, typename AssignPolicy, typename T>
    inline void apply(Point const& p0, Point const& p1, AssignPolicy & policy, T const& length_threshold) const
    {
        typedef typename AssignPolicy::point_type out_point_t;
        typedef typename select_most_precise
            <
                typename coordinate_type<Point>::type,
                typename coordinate_type<out_point_t>::type,
                CalculationType
            >::type calc_t;

        typedef typename FormulaPolicy::template direct<calc_t, true, false, false, false> direct_t;
        typedef typename FormulaPolicy::template inverse<calc_t, true, true, false, false, false> inverse_t;

        typename inverse_t::result_type
            inv_r = inverse_t::apply(get_as_radian<0>(p0), get_as_radian<1>(p0),
                                     get_as_radian<0>(p1), get_as_radian<1>(p1),
                                     m_spheroid);

        BOOST_GEOMETRY_ASSERT(length_threshold > T(0));

        signed_size_type n = signed_size_type(inv_r.distance / length_threshold);
        if (n <= 0)
            return;

        calc_t step = inv_r.distance / (n + 1);

        calc_t current = step;
        for (signed_size_type i = 0 ; i < n ; ++i, current += step)
        {
            typename direct_t::result_type
                dir_r = direct_t::apply(get_as_radian<0>(p0), get_as_radian<1>(p0),
                                        current, inv_r.azimuth,
                                        m_spheroid);

            out_point_t p;
            set_from_radian<0>(p, dir_r.lon2);
            set_from_radian<1>(p, dir_r.lat2);
            geometry::detail::conversion::point_to_point
                <
                    Point, out_point_t,
                    2, dimension<out_point_t>::value
                >::apply(p0, p);

            policy.apply(p);
        }
    }

private:
    Spheroid m_spheroid;
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <>
struct default_strategy<geographic_tag>
{
    typedef strategy::densify::geographic<> type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::densify


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DENSIFY_HPP

/* densify.hpp
M6Pwax5SDqpzvapOu1m+/KTUr7lEf9LzeEWTHu2d9hxUCm8jV1a3L5Rru80sf7MIy3XgIEwmmMZpVHu8v2knb6fs5U05Fxc/j6758xhi2Va1NPlkeoj2XL1SKn8PojbRlQgkr6kZ2rzeyTmCfNo9R0h7Tq6DhiVE5dvG1WrKMzvE/UQzYqCpHHXyVtzjluRL6rTSnlWVTbqk30LSby7pO+3Qpn8nxzE7eVCVgTvpmT5Py78vJwYxLUibh2Qje3dkMX4LFtKOVvbttZKHMMnDGCLIVA47lTxEUY+tV7CKnH4TST9WpnnY8mQgV6o8ONXWtikHk4c0VR6sWSh8G1iPbzOVPKjTWynpZRBuxFZitTN/29JLtKVX9P1Bece9+pgui1EfR/zdLQvwI2jTMp2ETeu8Sy8PGJ5gvppUnLa0NT8NpA525B+pg7GJ2sVKO1e1v6ry+43kdwiZc8eHcBJtn+v6+ZV2Doe9ItRZ9Xvu5bin5IVlyHHJenxmmTJd2xZMq6Mt1+GU69pXC87nnZattW3a1va7Xa8sVef1gLqWBU4n3ImpxH2mf3nNnMcIQ6TtgotktEjnONn3VPVeznNyv5Ol5D3PyTQpRtu77a33RBKmqvJ9SvLdUvabJsTMmpStJd+x0XlvFtGZNdaQRGuk6Pdp0/mD9j23iqRdpLTNIixtbsnHtHqWuTtL+bUjxpjavPr5iOfSTMiwfg/1HjR8WEiQ7xDfh+4wT9bz3GjLfTalzHxwJNNU+43k9abktT7hIvmdUZM879HLK4c58jslji5SYRF3lMe82yvVQ7u9HiGfoXppcxkrkauOd7u9LMe8CFU+yte3U29082GqdzGGyYa7y4fUG9W2SJd8NCdciUZEqKne6OYj8a63hbW+NCDISyyofmNE8A+mT1U5plbGcbVY4l5zftT3jshG+ISiHwMKvPepOo7Gstj89z4T7Nwf9XKu8zp5s1x7V61LdgNtPf/cjTpo+X7iBHPZ+vULCug9JCQi2VicehZY3Xw8m6AuP6Y31Kb5BWlm6KVpugpZjDTTnNRpdpE0Mxtq6/Jw8ndRSTO4czuvEGO80ZxikdMbaktPaT9cqWqaZlpMZHJcuLptHyAvB50q655E/OLEUt8w54ODP/cSDGEJIePCbHfOi3D/Ud2WUV9r8Gxs+WJcWfKIMdiNfzmopKnc6pMUC39eoJapT/sB5md3TLRcGGOv47aH5CU0X7sgWqmTkoSyn6navMp+UD7febmdcn5LmmiUOv3WftKX76rG6mxqyehJzpNt8FWMMLXRDqnWlwt6k1XtY951rPfxMy20AiWW7WhK35G0GZvjmGXdGQvTvL7XHdVti5v8HVBN2jvy249MyrQ8rQPV72r1Mw3Btv04374fSbsqljzn/f3GWd+6NtzVCI82mMc77dGY9aay/8R3njlMntFVtk9DguNIPPdATE0JcxqpTFthOReQhrlcleUcZDmf8e9vvc1yJN/DlPRNz3epv+/EdqjBFye9w/dlnQKxAUG60n60tnGM5uWd4osG8zl5XHKk7MOmbT1W8v50Vcu2dzti+Xuds/o3wkXZ9uvKsJ74HEbVIi/HrdteKSSOZoVf8zBt62nvK9tatoNSZxPCpTxt20ouY6m3qzyfZslrCzkmDZMdugHhQtQhmlRjHT4wp8dv16IfhxqZ61XIMOYxl88v5mVwzqymfvYtVxa2jXAj/kWMMpXPKSVNfi/TqC7GMSfvb2ZPpU1lNOdjyyn1eYc+gLxvt/j9I/X7rdrrd1v8fpD6/XSLP86rfr9Y+/1f9fvp2uv3Wfz+svr9hu31Py5+/9rijgtrr3/wRVfT9Bd3rD50+vikm4+57K0=
*/