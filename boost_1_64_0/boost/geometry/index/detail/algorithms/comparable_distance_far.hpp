// Boost.Geometry Index
//
// squared distance between point and furthest point of the box or point
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_COMPARABLE_DISTANCE_FAR_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_COMPARABLE_DISTANCE_FAR_HPP

#include <boost/geometry/index/detail/algorithms/diff_abs.hpp>
#include <boost/geometry/index/detail/algorithms/sum_for_indexable.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

// minmaxdist component

struct comparable_distance_far_tag {};

template <
    typename Point,
    typename BoxIndexable,
    size_t DimensionIndex>
struct sum_for_indexable_dimension<Point, BoxIndexable, box_tag, comparable_distance_far_tag, DimensionIndex>
{
    typedef typename geometry::default_comparable_distance_result<Point, BoxIndexable>::type result_type;

    inline static result_type apply(Point const& pt, BoxIndexable const& i)
    {
        typedef typename coordinate_type<Point>::type point_coord_t;
        typedef typename coordinate_type<BoxIndexable>::type indexable_coord_t;

        point_coord_t pt_c = geometry::get<DimensionIndex>(pt);
        indexable_coord_t ind_c_min = geometry::get<geometry::min_corner, DimensionIndex>(i);
        indexable_coord_t ind_c_max = geometry::get<geometry::max_corner, DimensionIndex>(i);

        result_type further_diff = 0;

        if ( (ind_c_min + ind_c_max) / 2 <= pt_c )
            further_diff = pt_c - ind_c_min;
        else
            further_diff = detail::diff_abs(pt_c, ind_c_max); // unsigned values protection

        return further_diff * further_diff;
    }
};

template <typename Point, typename Indexable>
typename geometry::default_comparable_distance_result<Point, Indexable>::type
comparable_distance_far(Point const& pt, Indexable const& i)
{
    return detail::sum_for_indexable<
        Point,
        Indexable,
        typename tag<Indexable>::type,
        detail::comparable_distance_far_tag,
        dimension<Indexable>::value
    >::apply(pt, i);
}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_COMPARABLE_DISTANCE_FAR_HPP

/* comparable_distance_far.hpp
6mHKcx+PiN6ljfQtsSP9QnqYetBvVUdSy5Cb6O7ZddDr0HN0bchNeAMHnTqNLjjo1F80/KBTV1Hrg059Q9995tQjtOMzpy6gLSG3fOs+yjpxG0z2q8Q+iOzzxD6Q7EViP5XsE8Q+gOwFYu/fpLFeJHqGpnKe1OWobcSBSfo+u/5zqZdaHUNdQuMsrkfM465jCP4N6xj69POm6RjqImMxV70sMs4dOYXXzo35N9HQ3AUHLpR4clOoH6PlEW1/b3+EWw3zrPRXVjh5vJ5g6Yksra4sqaiSdU2ha+vJ4b6rLdmHeIfg70KYv8GkGvvDk0w90aMhrC89+Gea+7P7brhnpMM9dlm38HtcuvFtZnpT+6HasPWBsLigPN37hb489TrPoZODytPWQ5LODj0/LuUJPA3r+WF/1/L0yKGmrTFGUp6seB6c6pw3LTT2YsLiWTe3tsSYFbvOhzkOIV1O82tLZpeRf7SH/fGVVPE3z6pU13hEHxRoXPVFTVf9eS2FznghzFEpRj3oJt/x0vtlxZwnnYCgxcAnRJsfRltue080O73BedQ4XTlTdUeZcc+EW6G4SXyJdppG91SxrLdwvOBWLustJL/SFmQhELrTzuXzAe77PF+G8q66qLykqhS6beeU2fNN1gXbEe1aTzeEe6W0A1YY7exvOZYBiS8LmEv+6zz5+HstnwV/j+6Ho6lGZeC3++TNPdRfki0/FW7p4Oc0LmykLheraUxh4juw03eoDhd+qc7rNrMdYwBl7AYd6vSvlsdulcDBxtqsLb3mB/RtZtQ/DZri6AL8fRUbJw9FreS0svhT5a20vV8Z9ou92Z5+9MZadorslYXeWDts3hsrR8658W2h2r6oyr7H9jnxxclZ+8NkP9vTG+Hwm2oczrlejOi92d5+3C5JHkqb3Y/i1DK6JcJ70Bvn+S4qTpl34Bs03nqbvjES426jPx9O/Xc88V4YTftaKIerp5t3haBXaqUvvoW5xst+++DXJh1+rZZdbNtHcO45cHt3DsnfSgnjGMJoa4ThWzYpdPed34JjmqwLUKZAE73stMRehuqnWI8SRj7828MfMvazu4+Be54ZdqLhbsWp9AKz34qr9MUtQ1h2v6DlV+uLC/7iUeMLv3j44X7yrZasCRzfAxnO922vPkz5IPq8bid7vBJmt19JmJdFEuassDCDmjCXIMwO9H7d8ifDwxyf5QxzY1iYbf9l2NOUPNiCMK9PRZjRy1/3xSb6EoayDjbe64VRZDgM+o6GDMlXxloydILdKv+YI9TV2Mr/tyRDspIXWajXNxjfbLn8sC86yfHG3lTYEaS0P5XA+TCd4fgk7I/DJOP3STBdYAJ+09wIcxVMNUwVTFf4/Qa018LsjOAumTEWRl207no7xsKt1DPAStu+/SIzoDLuly+EOQ0+BV9LWyW698L6ZF4vZFqE0DtS/XpEP93TA3O60ajt9j0arIfANL6+GNYvRqQnz9qj8RTze0gc53yYbAi20xbnRYFq3KDDQik0q2OXpg57nCVz9WMS5hvksvei+vPeCvpYXs9W/XksPLdkBp+ROVfLPxf86ngENDLGCLCcfEfYNhZR6RYp45aAEuagMNog7JmSt9hWlHMyIZ6CMJ6VHjMfxzSSj4Vhfe80dT+IxyyyHwQ5ecwi421KL3ILCB2lEYW/KHTfmGiCQkNxprH7Sik7Styonz9CcULfk6P283UzzIjMRaPTmtHYC/B/I+WIdS061xt7EM25UVyGwKPqWrzsW3ddi6OIdmCU0bbFFKMtLGa9hr7gww69hkyzJ0SzKZwmh2k8JXBDexNdkTg7cSw6toQkaVN7ok7O8athdi5hHY++5YPdvjumRPQ=
*/