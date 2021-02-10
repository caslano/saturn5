// Boost.Geometry

// Copyright (c) 2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_EPSG_PARAMS_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_EPSG_PARAMS_HPP


#include <string>

#include <boost/geometry/srs/spheroid.hpp>


namespace boost { namespace geometry
{
    
namespace srs
{


struct epsg
{
    explicit epsg(int c)
        : code(c)
    {}

    int code;
};


template <int Code>
struct static_epsg
{
    static const int code = Code;
};


} // namespace srs


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_EPSG_PARAMS_HPP

/* epsg_params.hpp
sSe9wj9gJvcUH8JY8KxhIqElh2PYOe33zk4Gn9im/Mq8WtqMi50CFZKHosmfPFcEJ8FMbPFGeQRHG6uQATlQnuD4yPjwyJ6YRJvNE1nI5F7ENymGJZFUEd2OhNi+VIvRP4CqkYfQvjQVA4ahV3z1DT8Z5BG6oNwWbpAUxSLXaQ8FbDWeNvTOSByRGeB1fUMzefvVpn7d3F7f/oc3Zsc3MpU5cP7q9JVRyJwkyUuj6cDcGw9yN5Suo/KOSTy2IGuhalyGeeQl1S2D4tasfDLkzLFPWNDjsXsbwVgbtqiyns9mjkd28GcpolHLGXUcf7ieCX8UAz2WQ/g/E8S3nvOqT2SMm5R43lqxhDQn11bDq5rE9g50gcvvvDK2X4Y/B+cnw6v+ZafXZAtAv8GaNvMGs2+9zulVE+F8gUVxdp2Mi1FcqHYxnoNlpopsDlJZL64qwhAaRWbDkk5s+Qt5NPrGE8bzIIyiHHz/mP5orXnurIA1C7U1IH4IRdfr1W5AK8jKBrS4LaPigxazewco7ksjGfgg44LBAn1I8g8Gvb4z00w04uPwpPOxf31x9u4CGmngmIof+B/rH4D6o2wJ1kkGRrdfs9Mo98aVwIRNjju4seBZmlHF60gKvz2I5CzlVIa6V4WcKdFhYU2iP3bi
*/