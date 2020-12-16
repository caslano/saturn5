// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014-2019.
// Modifications copyright (c) 2014-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_STRATEGIES_HPP
#define BOOST_GEOMETRY_STRATEGIES_STRATEGIES_HPP


#include <boost/geometry/strategies/tags.hpp>

#include <boost/geometry/strategies/area.hpp>
#include <boost/geometry/strategies/azimuth.hpp>
#include <boost/geometry/strategies/buffer.hpp>
#include <boost/geometry/strategies/centroid.hpp>
#include <boost/geometry/strategies/compare.hpp>
#include <boost/geometry/strategies/convex_hull.hpp>
#include <boost/geometry/strategies/covered_by.hpp>
#include <boost/geometry/strategies/densify.hpp>
#include <boost/geometry/strategies/disjoint.hpp>
#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/envelope.hpp>
#include <boost/geometry/strategies/intersection.hpp>
#include <boost/geometry/strategies/intersection_strategies.hpp> // for backward compatibility
#include <boost/geometry/strategies/relate.hpp>
#include <boost/geometry/strategies/side.hpp>
#include <boost/geometry/strategies/transform.hpp>
#include <boost/geometry/strategies/within.hpp>

#include <boost/geometry/strategies/cartesian/area.hpp>
#include <boost/geometry/strategies/cartesian/azimuth.hpp>
#include <boost/geometry/strategies/cartesian/box_in_box.hpp>
#include <boost/geometry/strategies/cartesian/buffer_end_flat.hpp>
#include <boost/geometry/strategies/cartesian/buffer_end_round.hpp>
#include <boost/geometry/strategies/cartesian/buffer_join_miter.hpp>
#include <boost/geometry/strategies/cartesian/buffer_join_round.hpp>
#include <boost/geometry/strategies/cartesian/buffer_join_round_by_divide.hpp>
#include <boost/geometry/strategies/cartesian/buffer_point_circle.hpp>
#include <boost/geometry/strategies/cartesian/buffer_point_square.hpp>
#include <boost/geometry/strategies/cartesian/buffer_side_straight.hpp>
#include <boost/geometry/strategies/cartesian/centroid_average.hpp>
#include <boost/geometry/strategies/cartesian/centroid_bashein_detmer.hpp>
#include <boost/geometry/strategies/cartesian/centroid_weighted_length.hpp>
#include <boost/geometry/strategies/cartesian/densify.hpp>
#include <boost/geometry/strategies/cartesian/disjoint_segment_box.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras_point_box.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras_box_box.hpp>
#include <boost/geometry/strategies/cartesian/distance_projected_point.hpp>
#include <boost/geometry/strategies/cartesian/distance_projected_point_ax.hpp>
#include <boost/geometry/strategies/cartesian/distance_segment_box.hpp>
#include <boost/geometry/strategies/cartesian/envelope_box.hpp>
#include <boost/geometry/strategies/cartesian/envelope_point.hpp>
#include <boost/geometry/strategies/cartesian/envelope_multipoint.hpp>
#include <boost/geometry/strategies/cartesian/envelope_segment.hpp>
#include <boost/geometry/strategies/cartesian/expand_box.hpp>
#include <boost/geometry/strategies/cartesian/expand_point.hpp>
#include <boost/geometry/strategies/cartesian/expand_segment.hpp>
#include <boost/geometry/strategies/cartesian/index.hpp>
#include <boost/geometry/strategies/cartesian/intersection.hpp>
#include <boost/geometry/strategies/cartesian/point_in_box.hpp>
#include <boost/geometry/strategies/cartesian/point_in_point.hpp>
#include <boost/geometry/strategies/cartesian/point_in_poly_franklin.hpp>
#include <boost/geometry/strategies/cartesian/point_in_poly_crossings_multiply.hpp>
#include <boost/geometry/strategies/cartesian/point_in_poly_winding.hpp>
#include <boost/geometry/strategies/cartesian/line_interpolate.hpp>
#include <boost/geometry/strategies/cartesian/side_by_triangle.hpp>

#include <boost/geometry/strategies/spherical/area.hpp>
#include <boost/geometry/strategies/spherical/azimuth.hpp>
#include <boost/geometry/strategies/spherical/densify.hpp>
#include <boost/geometry/strategies/spherical/disjoint_segment_box.hpp>
#include <boost/geometry/strategies/spherical/distance_haversine.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track_box_box.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track_point_box.hpp>
#include <boost/geometry/strategies/spherical/distance_segment_box.hpp>
#include <boost/geometry/strategies/spherical/compare.hpp>
#include <boost/geometry/strategies/spherical/envelope_box.hpp>
#include <boost/geometry/strategies/spherical/envelope_point.hpp>
#include <boost/geometry/strategies/spherical/envelope_multipoint.hpp>
#include <boost/geometry/strategies/spherical/envelope_segment.hpp>
#include <boost/geometry/strategies/spherical/expand_box.hpp>
#include <boost/geometry/strategies/spherical/expand_point.hpp>
#include <boost/geometry/strategies/spherical/expand_segment.hpp>
#include <boost/geometry/strategies/spherical/index.hpp>
#include <boost/geometry/strategies/spherical/intersection.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>
#include <boost/geometry/strategies/spherical/point_in_poly_winding.hpp>
#include <boost/geometry/strategies/spherical/line_interpolate.hpp>
#include <boost/geometry/strategies/spherical/ssf.hpp>

#include <boost/geometry/strategies/geographic/area.hpp>
#include <boost/geometry/strategies/geographic/azimuth.hpp>
#include <boost/geometry/strategies/geographic/buffer_point_circle.hpp>
#include <boost/geometry/strategies/geographic/densify.hpp>
#include <boost/geometry/strategies/geographic/disjoint_segment_box.hpp>
#include <boost/geometry/strategies/geographic/distance.hpp>
#include <boost/geometry/strategies/geographic/distance_andoyer.hpp>
#include <boost/geometry/strategies/geographic/distance_cross_track.hpp>
#include <boost/geometry/strategies/geographic/distance_cross_track_box_box.hpp>
#include <boost/geometry/strategies/geographic/distance_cross_track_point_box.hpp>
#include <boost/geometry/strategies/geographic/distance_segment_box.hpp>
#include <boost/geometry/strategies/geographic/distance_thomas.hpp>
#include <boost/geometry/strategies/geographic/distance_vincenty.hpp>
//#include <boost/geometry/strategies/geographic/distance_karney.hpp>
#include <boost/geometry/strategies/geographic/envelope_segment.hpp>
#include <boost/geometry/strategies/geographic/expand_segment.hpp>
#include <boost/geometry/strategies/geographic/index.hpp>
#include <boost/geometry/strategies/geographic/intersection.hpp>
//#include <boost/geometry/strategies/geographic/intersection_elliptic.hpp>
#include <boost/geometry/strategies/geographic/point_in_poly_winding.hpp>
#include <boost/geometry/strategies/geographic/line_interpolate.hpp>
#include <boost/geometry/strategies/geographic/side.hpp>
#include <boost/geometry/strategies/geographic/side_andoyer.hpp>
#include <boost/geometry/strategies/geographic/side_thomas.hpp>
#include <boost/geometry/strategies/geographic/side_vincenty.hpp>

#include <boost/geometry/strategies/agnostic/buffer_distance_symmetric.hpp>
#include <boost/geometry/strategies/agnostic/buffer_distance_asymmetric.hpp>
#include <boost/geometry/strategies/agnostic/hull_graham_andrew.hpp>
#include <boost/geometry/strategies/agnostic/point_in_box_by_side.hpp>
#include <boost/geometry/strategies/agnostic/point_in_point.hpp>
#include <boost/geometry/strategies/agnostic/point_in_poly_winding.hpp>
#include <boost/geometry/strategies/agnostic/simplify_douglas_peucker.hpp>

#include <boost/geometry/strategies/strategy_transform.hpp>

#include <boost/geometry/strategies/transform/matrix_transformers.hpp>
#include <boost/geometry/strategies/transform/map_transformer.hpp>
#include <boost/geometry/strategies/transform/inverse_transformer.hpp>


#endif // BOOST_GEOMETRY_STRATEGIES_STRATEGIES_HPP

/* strategies.hpp
G7DNpfgHUXAQGAB+C0pBNZgJrgV3gyfAS2AFWAO2vIxzA9gb6J2igAQlJHnSRrYQcmUrft2mLT+7tA2/3hSW9vzWUgfpyMVvZ/uzTDvIjtKVHwbaWX7l/9L9rrKbdJNfy29kd+kue8iespf0kL1lH9lXotJTesl+0lv2lwPkQCmUg6SPHMzfcB8qfeUw7l/1k/4yQAbKIBksh/OZ+BA5Qo6UoXKUHC3HSEyOlWFynAyX38rxcgL3g0+U38lJ/C7/KfJ7KeGecZmMlFFSLhUyWsZIpYyVU2WcVMl4meD/wv9pUi0JqZFJMlmmyFQ5Xc6QM2WanCVnyzl83j5dzpXzZIacLxfIhTJTLpKL5RKZJZfKZXI5f2dyhVwpV8lsuVqukWv5btN1cr3MlXlyg9woN/FZ3c1yi9wq8+U2uV3ukAVyp9wlC2WR3C33yL189vIH+aPcJ/fLn+TP8gB/N/SgPCQPyyPyqPxF/spn84/J4/KEPClPyd/kaT6HeUaeledkqTwvL8jf+WzvRXlJXpZl8oq8Kq/xt1D/kNflDXlT3pK35R0+z3hX/invyfvygXwoH8kK+Vg+kU9lpXzG7w99wd9YfSlfydfyjXwr38kqWS3fyw/yo6yRn+RnWcv0e17AC3LbMM9r423h5XOTcStva27JtuO26bZemJvefO7qdfQ6cct9e26Ld+Fj0R25vb+TtzNfSo9wY31Xbzevm/dr7zfe7l53bw9vT28vr4e3t7ePt68X9Xp6vbz9vN7e/t4B3oFeoXeQ18c72DvEO9Tr6x3mFXn9vP7eAG+gN8gb7B3uFXtDvCO8I72h3lHe0d4xXsw71hvmHecN937rHc/fiI3wTvR+553kneyd4v3eK/FKvTJvpDfKK/cqvNHeGK/SG+ud6o3zqrzx3gRvohf3TvOqvYRX403yJntTvKne6d4Z3pneNO8s72zvHK/Wm+6d653nzfDO9y7wLvRmehd5F3uXeLO8S73LvMu9Om/dbxCUV1VJ/yHHlIwuIcG3JlRMsc+oL7EPUJhQMarGZaUWy8g3On56yhN9XXryAbn+r3673y/SX7WbWO4npdnm54dSkyb3LOmVWctPztDZamet6z/iuWKCU+l56V74AXLzDH7/Yb811fzudkKOiQ06Gu0/W8QfmNigo/wnm5ekPAp7XeLIsRMzMvxfP8+emlHef1ZwWdWokn4l/k9Ii2YOGBIr5mcryysSo6rH+g8oTU3WB9mlaP8xYWWTaipLJoxdP53mahLrp5kf8c9W2jwMLFtOZsq4qdnK+b/svF6a/eHQ1OSxiZKyijJb+5ijYiVl5eUlKT8MbmYoJR8/Ud95WlKWKon0AmPTfaznIoHXDfg4erD/GOdRVRVl1f5PNKZn2F/SWi+tuqIiPYWDKj3Bf4w6TY4eOzUjI6MZP9lfiFkT/UfJJDNGjS9PEyVl1WMmp6f4P5ld4j/tiHTflb8ETegZif5hkEz0Z8kccwP6ZUsdNSlRM3F8ScXU9DrmsGs91x98l5Z8uDp9q65yqe6RtuZZwPpIKj9n3fxM9I+ThEv1HxIzdsw6WaOLrsL/TfJyl5reQnnZhIqMyU5mmKrpaeN1HHUqUpP9hHQPpjLOkwXJn5SodF33C2bOgb/oU3+8Pj2jpmrimBJGtDo9w+wjaUlu2PxRS013PwjPnBB6TVlqrt9yhn+3fSTS0pKLwt99s2X5zkaNTMuyD0En4ERiSvkv5pZMYh1lRJkt8rETRk9MLqO0nPRVYtJOmzS2oiZ5LkvNSo5P0ln23KqKyRVV6VmJKruZpCXXmB8QT0vzn4+R2kJmXnlFvKYyW8b4ieXrJqeyLNH6ceif6Gw17FFlqeM=
*/