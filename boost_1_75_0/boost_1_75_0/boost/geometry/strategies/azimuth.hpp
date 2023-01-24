// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2016-2017 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_AZIMUTH_HPP
#define BOOST_GEOMETRY_STRATEGIES_AZIMUTH_HPP

#include <boost/mpl/assert.hpp>

namespace boost { namespace geometry
{


namespace strategy { namespace azimuth { namespace services
{

/*!
\brief Traits class binding a default azimuth strategy to a coordinate system
\ingroup util
\tparam CSTag tag of coordinate system
\tparam CalculationType \tparam_calculation
*/
template <typename CSTag, typename CalculationType = void>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_TYPE
            , (types<CSTag>)
        );
};

}}} // namespace strategy::azimuth::services


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_AZIMUTH_HPP

/* azimuth.hpp
wdVNr6p1mpmXiC4udLdiAEScmlFOzxlduXWU2r2Q7jjpeIueDQZMenHVqCpDRu7pBqi6AvH8lh1vDBiPKqimkUxLuZAVX+5GhRqS6pC94ZErG7O3nuET8dZm7FfEPFzTwgrm7vXP6U3pM94IorEOeW/tSV3xzUUGrIgHUUMuI0jv99sFucV63zW8k7b89SRz/DkglEP/kaxjxrC6wyvSnhBvU7kBv5gipQK3/kNFIK2KR3JuLqAtACEHH8pf4zFBglLTm4NOHvpm4jr9ZVcpzoE/aFI6tQERs1Q/iktO6STkDyU2H0pOGcgjO+P3/3B4Svt29mnArPCUyoX0ELSZ8uGWiAD7PbL5wy2ZXUQnFGBSEYDHNPOzW0ykDmG1HiT/KlPfwcyliS58upgb8k0R95v9QrPSqvH56mIQGwlBpDhQPXAqzv9x115IZJi2RqFjFNQb+tGToeT8vldW39PNW+gVrzjP2LgVi1gv76Iz3sK0ASxm6+L9yXTFiyUv0XE7sMxHXpK4z3OQgqC9U9eKGHCAx4URDtiRg7Kuxa17TouyjkrfHwAL32HLkXis2XBfoDFTilz3a5/QT11rB7/4muT9nfxihcx3s6Hd7vgx76PnIMyA9DyscyJmj1FOGDSQgecmxjQfEGXWCFHIvZraiFoBiJGaOtd+FfQkE7grftae+Qa2XOvzJu8bsX4/Isci2KbepfX7e8uPtJlT
*/