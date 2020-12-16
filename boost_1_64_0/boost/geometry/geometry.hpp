// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014-2018.
// Modifications copyright (c) 2014-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRY_HPP
#define BOOST_GEOMETRY_GEOMETRY_HPP

#if !defined(BOOST_GEOMETRY_DISABLE_DEPRECATED_03_WARNING)
#include <boost/config.hpp>
#if defined(BOOST_NO_CXX14_CONSTEXPR)
#include <boost/config/pragma_message.hpp>
BOOST_PRAGMA_MESSAGE("CAUTION: Boost.Geometry in Boost 1.73 deprecates support for C++03 and will require C++14 from Boost 1.75 onwards.")
BOOST_PRAGMA_MESSAGE("CAUTION: Define BOOST_GEOMETRY_DISABLE_DEPRECATED_03_WARNING to suppress this message.")
#endif
#endif

// Shortcut to include all header files

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/interior_type.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>

// Core algorithms
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/radius.hpp>
#include <boost/geometry/core/topological_dimension.hpp>

#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/arithmetic/dot_product.hpp>

#include <boost/geometry/strategies/strategies.hpp>

#include <boost/geometry/algorithms/append.hpp>
#include <boost/geometry/algorithms/area.hpp>
#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/buffer.hpp>
#include <boost/geometry/algorithms/centroid.hpp>
#include <boost/geometry/algorithms/clear.hpp>
#include <boost/geometry/algorithms/comparable_distance.hpp>
#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/convex_hull.hpp>
#include <boost/geometry/algorithms/correct.hpp>
#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/algorithms/crosses.hpp>
#include <boost/geometry/algorithms/densify.hpp>
#include <boost/geometry/algorithms/difference.hpp>
#include <boost/geometry/algorithms/discrete_frechet_distance.hpp>
#include <boost/geometry/algorithms/discrete_hausdorff_distance.hpp>
#include <boost/geometry/algorithms/disjoint.hpp>
#include <boost/geometry/algorithms/distance.hpp>
#include <boost/geometry/algorithms/envelope.hpp>
#include <boost/geometry/algorithms/equals.hpp>
#include <boost/geometry/algorithms/expand.hpp>
#include <boost/geometry/algorithms/for_each.hpp>
#include <boost/geometry/algorithms/intersection.hpp>
#include <boost/geometry/algorithms/intersects.hpp>
#include <boost/geometry/algorithms/is_empty.hpp>
#include <boost/geometry/algorithms/is_simple.hpp>
#include <boost/geometry/algorithms/is_valid.hpp>
#include <boost/geometry/algorithms/length.hpp>
#include <boost/geometry/algorithms/line_interpolate.hpp>
#include <boost/geometry/algorithms/make.hpp>
#include <boost/geometry/algorithms/num_geometries.hpp>
#include <boost/geometry/algorithms/num_interior_rings.hpp>
#include <boost/geometry/algorithms/num_points.hpp>
#include <boost/geometry/algorithms/num_segments.hpp>
#include <boost/geometry/algorithms/overlaps.hpp>
#include <boost/geometry/algorithms/perimeter.hpp>
#include <boost/geometry/algorithms/relate.hpp>
#include <boost/geometry/algorithms/relation.hpp>
#include <boost/geometry/algorithms/remove_spikes.hpp>
#include <boost/geometry/algorithms/reverse.hpp>
#include <boost/geometry/algorithms/simplify.hpp>
#include <boost/geometry/algorithms/sym_difference.hpp>
#include <boost/geometry/algorithms/touches.hpp>
#include <boost/geometry/algorithms/transform.hpp>
#include <boost/geometry/algorithms/union.hpp>
#include <boost/geometry/algorithms/unique.hpp>
#include <boost/geometry/algorithms/within.hpp>

// check includes all concepts
#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/srs/srs.hpp>

#include <boost/geometry/util/for_each_coordinate.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_coordinate_type.hpp>
#include <boost/geometry/util/select_most_precise.hpp>

#include <boost/geometry/views/box_view.hpp>
#include <boost/geometry/views/closeable_view.hpp>
#include <boost/geometry/views/identity_view.hpp>
#include <boost/geometry/views/reversible_view.hpp>
#include <boost/geometry/views/segment_view.hpp>

#include <boost/geometry/io/io.hpp>
#include <boost/geometry/io/dsv/write.hpp>
#include <boost/geometry/io/svg/svg_mapper.hpp>
#include <boost/geometry/io/svg/write.hpp>
#include <boost/geometry/io/wkt/read.hpp>
#include <boost/geometry/io/wkt/write.hpp>

#endif // BOOST_GEOMETRY_GEOMETRY_HPP

/* geometry.hpp
7FckUn9WwvPvrFMPmhGYGbNBNpF1aEZC3ffrdUJoRmAyZsMdG5nSjMDcmOlun9UdLR2M9zAjp+MRmpFQp5eTcgOtDMyS2a+SdZE0I2vtulMuVjbUA5g1n3t7A2+0QDAXfr28PvmBegBzZnZCfqcbmhrMS+v7uth+aMVgWv/f3IlJ39FKwfD9LAlscv+WN2lGNvA8Ypaz8cIM6g9MykwxqfQXmiuYFbNlT5NHo/kKa+7YZx2E5g8mY9b2a/hFykWoe9llAl2foYJtebJuBVqssOYFzyyaezwYZrYWrNa+uuVoOWC+emCSAOU6sP/qnz6ElmpvIKlfWVdhA1uNDaOswSKklXXJYP/tbtWL8qxJ13WFRbZ8aE95gpkzG9BwzEg0N6Guc3av2ZQnmIyZleGJfyhPMCmzNDNpGeUJpmDmPWTvFspMWHPdmvu6lJlwlsItMd/QkoS6nTrZA9HUYJbMDKJKD1PWYKbM3gRsPIVWAGbC7HQbh+mUtbDmvWMPPqCVCWtOqNKPepDW0raMo6ZpaAowI2bZuwc50xzA+IxSVTFn0JSCRXQe1o2yBuOZtb/W9DFaqGAlWwpNaQ7COeMvJdnQHMB41g2K2oygOQi2rL4N1amFc/Z2O/CO5gBmwUy9eegmtELBLs3Nt0LTgPEZSaO8k9AktbX7U20IoFzkgnX4uGoPmiuYnFk7o+tz0BrXpvfyCrPv++EHzQGMn2Wis/N6tADBPC3axKEFCfZtYFI8WgQY793Yw6cazUE4Z1hwnA9aKhifw9SkprvR0oX9Jm33b0xzADNm1iyx6CxaAZgVsxkdvi9HKxXyrN7Lvx1amXBOpxdHf9Ic6mhfE7bnHtRDqwnGs/5RJSkXzUOwTZobA9F8wfi9J/RkyiI0fzDeu96Uu8ZogUJdH+MBY9FCwXgPFrdq0IzihB5UOndz0JLA3P/YerD3CR2jKE9WlwLmNM1yD+UJZsds63+DnqBJ3eAszL5dajoMzRXMklmMpNocygXMgtn8sB7BaAFgNsyWh3SpjxYBxs85bftKfbR4Yb+Dx7I7oqWCWTPLzpzXBC1LsOq3crwpF2G/yZIbEygXYT+7I20XoEnqaq/Z8UCmDZoCzJ7Zxt3j31EuYDyXei6PyALATJjtmRO3Ay0IzIHZZt2VC9HiBMsq/dqIcgHjPfR/8/k85SLUbau2MQatEKwqM51Lb1tS7/XgZ5NZ2ZdAP+odjPf+2z/cnnoH471v7aLrTb2DyZmNiNm8Hy0UzIzZOPnZU2ixwllaXzn3FU0FVouf5Z7HKrQcMD6/uJBpadQ7mC2/JjrYu6OVgTkxm63TfDGaq7t21gGnPM9Q72DmzNqpDPtT72A2zFLjJvuiRQh1pq3SeqDFg9nxHjbk/UZTg7kwGxvjMxKtAMzjj20Am7DxmiOa1MNA0uv/JlEqN4J9sr1NuUR44P2l0lSnWyxH2+pB794VZp/YuSvaHjBDZrOOOOuiZYEZsTXDX0xaX2mH9fLA8JypOof1bsfWt0YrZ/v931rtL2yApu8Jvw9gVjSn9Wc0KZghs9Unug5Bk4PpM0vopFSjuYLJdSrfdzeBxTi/n4gW6kU/txX2Mmd4DbRYMAtmia1+OaOpwMyYjZkxbzNaKpgRs9G1nvVHSweTMVvRso0hWg6YKTNFy+970Qq8KLMKOzShuzFaIZiU1c338O+NVirst3fpizZoZUIPiYn6rynr+tpnGbe1WgqaAsyKmbufpS+aNxjP039173ZoSjAbZrOtVxxCCwKTM5Ov9WtLcwDj51xd93dTtHgwa36WOQ3r0hwEO3b17ly0LDA7ZtXd1vpSnmC2zLYMOOFPmQlrvtpa/gFN7g3vRMw=
*/