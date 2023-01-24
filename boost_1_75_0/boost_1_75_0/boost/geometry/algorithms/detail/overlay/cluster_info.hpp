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
EyQ8geqVmJIwSrooVjI93iloFOQfJd9j0s6i6gE/rQN6ZE7UWVQ/1tqtFdqtbki7XYjwOP83br/0j9BkanKRUaYmknecvfrSeMP++w0EhG24K3Iu6hhyLupNNcSfCAGgC/Da+GlXGuPekErTDg+DM6wwxr0tleIMYeRn8i/GPqNnS+kwPjxRZ0tPwieErvAdB8/zqdpe1yP04N2sb8iaIKOk3MQLZE1IIzJi1RKq7HSgleBOwyf02blEGh4Ad448g29jw8ZvnDkKSu9yovRGB0oPjEHpF/UzBU1mK1YuvDEN9pJF8NcFDiunu8nRWBCI1Uwopxqth5gcc6bSQ77dC3+95FuZfVsEK79Xo9E5b7MaaHVIg6zlw/E8PyFpfQ5//0vSsuwnexq5izTZLvH7XfQRSPkf6YQnAH9Xp5OzDSId0U9lJNbnknKYzAUEdFu2CgFxrvSZWSwQSvBykd2DdZFjtnys0rtg6Vi+Mu5Y7o7M87vj4icPQREa6BkqeJ5M186Tu8V96G8Yv46Sx/B9uW/oOeo5Uo/z8CdmkHrQNqQ1YPXobaDV8KxAc3ELoAQlwpQE6XGzsEGqFu7DuAiFJDuxWS4kj1fQ+GOjEZHfGd+YjMbDns3PlGg+FRmE/oW/hgyCo9BUaQ498jbUhl3CdHydEOFlWZCjOgk5YP9whHVe1voM3t9bwCMvgSJdgE/T+Z1234M6ZgIO543I
*/