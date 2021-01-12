// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2016 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CLUSTER_INFO_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CLUSTER_INFO_HPP


#include <set>
#include <boost/geometry/algorithms/detail/signed_size_type.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


struct cluster_info
{
    std::set<signed_size_type> turn_indices;

    //! Number of open spaces (e.g. 2 for touch)
    std::size_t open_count;

    inline cluster_info()
        : open_count(0)
    {}
};


}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CLUSTER_INFO_HPP


/* cluster_info.hpp
o9G2Lg4z5TAx+BNDwv0h/VfW/wZqRv3fwKtt6G/Mh4FGyG4I/Ys+fqJTWnTib+TsugjziSmLQctWCWH2YZv7ETPO7IZspn55H8Rk66s2nksfcJW+M3E/pPcCiPiUxzzs/oix5oWj7lHf4taru3tn/53fWIwTFr2zY7JnetsDkG59AINXZrJnujpt0ymiBCv77IMcTZgoEs8PHvP0DW5XlT6c0kdoL8zy6EcRDTYoionwGErH
*/