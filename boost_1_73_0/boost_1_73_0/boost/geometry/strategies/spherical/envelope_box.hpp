// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015-2019.
// Modifications copyright (c) 2015-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_ENVELOPE_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_ENVELOPE_BOX_HPP


#include <boost/geometry/strategies/spherical/expand_box.hpp>

#include <boost/geometry/strategies/envelope.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace envelope
{


struct spherical_box
    : geometry::detail::envelope::envelope_box_on_spheroid
{
    typedef spherical_tag cs_tag;

    typedef strategy::expand::spherical_box box_expand_strategy_type;

    static inline box_expand_strategy_type get_box_expand_strategy()
    {
        return box_expand_strategy_type();
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<box_tag, spherical_equatorial_tag, CalculationType>
{
    typedef strategy::envelope::spherical_box type;
};

template <typename CalculationType>
struct default_strategy<box_tag, spherical_polar_tag, CalculationType>
{
    typedef strategy::envelope::spherical_box type;
};

template <typename CalculationType>
struct default_strategy<box_tag, geographic_tag, CalculationType>
{
    typedef strategy::envelope::spherical_box type;
};

}

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::envelope


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_ENVELOPE_BOX_HPP

/* envelope_box.hpp
zdbJBMVLwP75HCnHBJbMItg8TZdwPKt0fX3DItgKRE28Ybx8HGOd5PEcUB2ERhC6cAMoeVmZdEZSYkIcg+4A7i6eGCyUEccrOL8G4zIP3tJH8B/zRxLn0SKrvxP48zmNp8HuKrz1rkLhPOFsKk66CW8d2nemdwke465ZJR/qE/ec3O+c63V1l0fZeB7NcniBZoDBxnTPnBeawV4Jdez3NAQAL3evbTpGIZ2WD5/sMkCC186EzeAvgfvdK+e7Q0ZiGUUxF+j7ZHnXEMC7wDUrX+arwsqf3bdqbyCd8fAh+w2evdEXCvhtPgX0rsEk3GbjvxcH9DJuOPb7j9xSrNrbileVLibeHvrrKpx8wqs7w6/T9UpuKrE2mhJHQm2PyBDfSJ8g4ps43EZq2PLQfPN11Ed3Exx2KQcir9Mk+AeAlMZyUJ2eJ1ZEbAz/Gps94l8IDHiPCbzee2BCq3Asx8tfqfzOdPC8Oxwfnfd/7A6GvfP+EF68StO5Eqkxim7Ke2CEk87psOugg0iBNP4u/mHYI/5Bq4X7hb/vvb0B9ReOde8tCLJ5ClLFk8bF4Hx0Pj7pnPVOPxIp/hUXxZ8ORsOLpl5JTyTAB4GBw8rMbKvo720Qg+EjmpNmxb+Qy9BGgjdv6L1ht388HnT/etkd
*/