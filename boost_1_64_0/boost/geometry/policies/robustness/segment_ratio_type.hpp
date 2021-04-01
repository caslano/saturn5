// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2013 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013 Bruno Lalande, Paris, France.
// Copyright (c) 2013 Mateusz Loskot, London, UK.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_POLICIES_ROBUSTNESS_SEGMENT_RATIO_TYPE_HPP
#define BOOST_GEOMETRY_POLICIES_ROBUSTNESS_SEGMENT_RATIO_TYPE_HPP

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/policies/robustness/rescale_policy_tags.hpp>

#include <boost/config.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace geometry { namespace detail
{

// Temporary meta-function to access segment-ratio for a policy
template <typename Point, typename Policy>
struct segment_ratio_type
{
    // Type in segment ratio is either the coordinate type, or for
    // deprecated robust point types it is a long_long type
    typedef typename boost::mpl::if_c
    <
        boost::is_same
        <
            typename rescale_policy_type<Policy>::type,
            no_rescale_policy_tag
        >::value,
        typename geometry::coordinate_type<Point>::type,
        boost::long_long_type
    >::type coordinate_type;

    // Define segment ratio based on the coordinate type
    typedef geometry::segment_ratio<coordinate_type> type;
};


}}} // namespace boost::geometry::deatil


#endif // BOOST_GEOMETRY_POLICIES_ROBUSTNESS_SEGMENT_RATIO_TYPE_HPP

/* segment_ratio_type.hpp
ll+xc0gCizfywe7XuckCFSDzPowJv/f5K8LvcmVhGJvW+rMSODX+kTceQFMOP22+aCuu/f4PgT5yzQK345bbC63ybQEPG7RvNzFUFx0mFxTNs2N22i+ydhmggZHpruMaeivTOh3ueqb6n0NJuAh61Jq6MxBeeuihsKraXHyXGyzPOgW7dSoCzfF6/AsEGfS0W8v6MbS73WsiGlTq40cYgLfeDeZz8DNd7RoxFK55GQ3A1f1Jwiqb30MDE625lmxX0HyjncPHeyzEumeBGHLRC8XqBDJxfc4STRSputE7NcwNnuH0blOjmiwSEAVvmNULPV4MOb4OvBy/qjYPkXDxkwZJV2fhgh+CZuYGycUZauu28rlSX6HjSrv/T20YNP/Emu4eNtuf9tdKL1vbTK3JvvoYi8Eq1byx/HWlczc9ZtqNfYxy4t92eREuIzTi3oYVEm1AGMTBp7q95yWVxwzj6Wm6ZQjpVqHiBf3aQ6/xjrkSsObk0deMZzwxyVhiUvJ/CkwuKw689C7f3csAsONzIKTlhDP4H9uWnzGHgTYm+juFR1sJNIBI40URzg==
*/