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
ceMoPgCM6lQJN5pY1YshSB4xTrliqwB+ehT+9Wlv/KGfb7WP85Ir+XdM5YFBsA7UmNUrZ5DGB7BLIcezXlL4HDb4FDKzvZ/qHP8o/2HOzsbutnW6j1EQ/GZIJemZE2jaCc0yszQbbEnyPbq3w7iduJjW8eqiRrDrFnI/C108srFeSfMfy3Pz1Rg4z563cXLYQngradLJvsPAioIAe+dVqetPimbneWqDr9P5XhQjPZALAZLBtzK3uHJXylcDgiP8pCcn5bOLpFrzOYAR0ftwISRyXcMyor5fbnw2ncoDETJoMVpYJfvEoYDvH33NSKaCF25LU6Sef048ONuPoXoxSoZgoIhFTFSLCA7BS+JWk6YfaEVP2Vn3kQneL+fMtO5V4Ir6ZMyKF68+W/kmy91BcqMbCOqvgeq5JTcJ8fa7CDFQ7HiW3eLvfUwaaVp0o3Eiyvt3mlHC63CE/i3hrLNGIyPHNojI3DHL2cYYqJx+sQFzRjKCOIer9rMAlRVK2wY3NZnzBy+c1/F6/zKaRqP8GdjhxKaouYYYWdqzg07kh3upI+N2lWX6gQt88Q==
*/