// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_NORMALIZE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_NORMALIZE_HPP


// For backward compatibility
#include <boost/geometry/strategies/normalize.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template <typename GeometryIn, typename GeometryOut, typename Strategy>
inline void normalize(GeometryIn const& geometry_in, GeometryOut& geometry_out, Strategy const& )
{
    Strategy::apply(geometry_in, geometry_out);
}

template <typename GeometryOut, typename GeometryIn, typename Strategy>
inline GeometryOut return_normalized(GeometryIn const& geometry_in, Strategy const& strategy)
{
    GeometryOut geometry_out;
    detail::normalize(geometry_in, geometry_out, strategy);
    return geometry_out;
}


} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_NORMALIZE_HPP

/* normalize.hpp
7Dmqv4qDkhY5JGdqj6XtTvfBgnXhunwZ8mrD9o9H3CUODY/WqOnboHlofi2YQdE6K02Z4uEsLsjrjg3RWMiAeqwlTdSq/3WO2P2JfkkVbT0c/j9kWgUW0DU70AYH2qf5XZ3HlV9VfVuQDFJkksePtCW+fUmuAA+MpH1KgZXEFzKkRpR2G/uE+doyHQV/EtNLgUsPkhCbL321rmsd693C851nhYlP3w02c5G5NunLXi26Xa/ZTigtvRLlR6X2CZIfbf9ZB9eHw4r4RIm2vGsMW0jNUTlg0DgP7lHO/BMcv7gQoQoxpXcrlIsHvA3ZMAgS03WoOzVWMDfKxsof2Z6RUi/jVduFHBVatBAUPgWr8md0XxHROFJdWRX0yOvPDcrcJImHD2moXIDAUBEZRbIPT3g0Uic/DtX5mMckKEeUsf3M/pKw1fG/hafNk5v2OwB9mkaxcoc3Voy10/6+WxWYBosqDqmalCnIwr5Tgo0t99DlZ4RPfl9zhHnha7sDDnRb+1wu0T3dPTcAIep+0NYja6rQ8KUpOSaptCfKXl6VVEzAPgOC9APcbANbgQ==
*/