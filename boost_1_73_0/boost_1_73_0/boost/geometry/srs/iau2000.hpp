// Boost.Geometry

// Copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_IAU2000_HPP
#define BOOST_GEOMETRY_SRS_IAU2000_HPP


#include <boost/geometry/srs/projection.hpp>
#include <boost/geometry/srs/projections/iau2000.hpp>
#include <boost/geometry/srs/projections/iau2000_params.hpp>
#include <boost/geometry/srs/projections/iau2000_traits.hpp>


namespace boost { namespace geometry
{
    
namespace projections
{

template <>
struct dynamic_parameters<srs::iau2000>
{
    static const bool is_specialized = true;
    static inline srs::dpar::parameters<> apply(srs::iau2000 const& params)
    {
        return projections::detail::iau2000_to_parameters(params.code);
    }
};

template <int Code, typename CT>
class proj_wrapper<srs::static_iau2000<Code>, CT>
    : public proj_wrapper
        <
            typename projections::detail::iau2000_traits<Code>::parameters_type,
            CT
        >
{
    typedef projections::detail::iau2000_traits<Code> iau2000_traits;

    typedef proj_wrapper
        <
            typename iau2000_traits::parameters_type,
            CT
        > base_t;

public:
    proj_wrapper()
        : base_t(iau2000_traits::parameters())
    {}

    explicit proj_wrapper(srs::static_iau2000<Code> const&)
        : base_t(iau2000_traits::parameters())
    {}
};


} // namespace projections

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_SRS_IAU2000_HPP

/* iau2000.hpp
hypxPfcpXKwWgI9lkiHvVjJoUdiariBUxka00T6pkZY7tXxmRTG3rtnJkkREXnoh2RClErZF+bvlulPL9QFxPkPwf8QTT6tRO5VkjG3PRM8Hp+6ROTXq9cVjWCQtO6pQdzHkM2uon4Bcw5+70NMR22Pj1iU5/V5L3h0MQG5THuXfIOS5JLSTnS5v2dbOGOodo64e+w5jiUUB4cn1OdgmVJU29lTrZK3Jc+uITbVyyj6OWy+2AC7+nDaOwh2uMp8EH77/2DY71eiM7WVqN6wbxi7U5bDleR965L7oHPPZmnl+sOG5aaDMHNcRfdPGSYOdDqcqCuiQtoEpuDJvNndMDmMRgLzcc1J55yAutvitbTXsriYLqsr6XEfq0ySAhBnKPFB50NIbRiYLaCkst3p+UwNause16QHO660kDS3GHLXAs33PHKaNI9iJLjn4zesB0GYO8JukM1KHTokFLalFh7QdZtby3pq1MrgTDgGejy1aLBsT7fojU20OBW2ZDY77Z4PXN3TZ69/oOy86/WO+fDPoLfGmBbORiruPHtketVDx4AtVPPgrVbTOfFcVDf1tKr4bFCoiAX6FYuYYoDwwnVNGAUH1bKJp3UA8oy2LaljpeE+t7C91GxCtqIncsN76yNn8/fL8TdM2W6m4
*/