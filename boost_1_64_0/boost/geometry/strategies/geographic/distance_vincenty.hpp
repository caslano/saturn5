// Boost.Geometry

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2017.
// Modifications copyright (c) 2014-2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_VINCENTY_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_VINCENTY_HPP


#include <boost/geometry/strategies/geographic/distance.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace distance
{

/*!
\brief Distance calculation formulae on latlong coordinates, after Vincenty, 1975
\ingroup distance
\tparam Spheroid The reference spheroid model
\tparam CalculationType \tparam_calculation
\author See
    - http://www.ngs.noaa.gov/PUBS_LIB/inverse.pdf
    - http://www.icsm.gov.au/gda/gdav2.3.pdf
\author Adapted from various implementations to get it close to the original document
    - http://www.movable-type.co.uk/scripts/LatLongVincenty.html
    - http://exogen.case.edu/projects/geopy/source/geopy.distance.html
    - http://futureboy.homeip.net/fsp/colorize.fsp?fileName=navigation.frink

*/
template
<
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class vincenty
    : public strategy::distance::geographic
        <
            strategy::vincenty, Spheroid, CalculationType
        >
{
    typedef strategy::distance::geographic
        <
            strategy::vincenty, Spheroid, CalculationType
        > base_type;

public:
    inline vincenty()
        : base_type()
    {}

    explicit inline vincenty(Spheroid const& spheroid)
        : base_type(spheroid)
    {}
};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <typename Spheroid, typename CalculationType>
struct tag<vincenty<Spheroid, CalculationType> >
{
    typedef strategy_tag_distance_point_point type;
};


template <typename Spheroid, typename CalculationType, typename P1, typename P2>
struct return_type<vincenty<Spheroid, CalculationType>, P1, P2>
    : vincenty<Spheroid, CalculationType>::template calculation_type<P1, P2>
{};


template <typename Spheroid, typename CalculationType>
struct comparable_type<vincenty<Spheroid, CalculationType> >
{
    typedef vincenty<Spheroid, CalculationType> type;
};


template <typename Spheroid, typename CalculationType>
struct get_comparable<vincenty<Spheroid, CalculationType> >
{
    static inline vincenty<Spheroid, CalculationType> apply(vincenty<Spheroid, CalculationType> const& input)
    {
        return input;
    }
};

template <typename Spheroid, typename CalculationType, typename P1, typename P2>
struct result_from_distance<vincenty<Spheroid, CalculationType>, P1, P2 >
{
    template <typename T>
    static inline typename return_type<vincenty<Spheroid, CalculationType>, P1, P2>::type
        apply(vincenty<Spheroid, CalculationType> const& , T const& value)
    {
        return value;
    }
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


// We might add a vincenty-like strategy also for point-segment distance, but to calculate the projected point is not trivial



}} // namespace strategy::distance


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_VINCENTY_HPP

/* distance_vincenty.hpp
/TJzAubYZ0bY73a2R+/C70y9I7vXuaSce53dzbngyIBv1sj+wAGr/PS0EPqrANmWdFYdZTxYKDLuxHVsomWAVQ5fDMnLcKeFXT4yT5G16Wn56ZL3vu99GF9FkrELP1l3CjwTOsreljppY5VVz8zs9JyIzi9Z53O+/Dk+yr4u0Bm5pUpueHdryxqvsq4yHpwg6Rwj8/9K31tkaa85cmFGm/+Xv6Ysc2xLm9HlGGt81nMgokOO6DBD5oIeZx1kQhj62pHooHQa66BD0eggdfIHuw5SMcNavz5fdVPmetjDDrR5gNPqplVfZe4glHM99nrik1cg8nqKvB64ow20hXB/eZazKRHJM8fPs0HkJQSTJwdXQml/ZbaHMYH3neX8gJIb2R3zsvarPxpjvxvaVStLq8xcRoyI5Kj937HO+/ClVjkMWLwAZbhTIllb8k9XqchzS7tOFnmVzlrlpaeF/o7la0fWMVZjXcv4Kus7vvHWUr8mJdjXWy7lR4HSLfL7/GXVr/0JgXf5pX4puZHd4y9Lpmec8ztJiUWmnJn+L7+TmHXzjOg4W+Y+Wbhu6JjwT5uOxoJbCPuaAWOQmn892Uj7rS/hWvIpY7wReLnU15vN9hFMhyQtjvD1sNgamGA8eDMCmsNFsIc25/vJKhPDkhGtgy0JWJPwBIw7yaoNUSiOdx7t6132PRjyVcXtMb4nN57fE4x7zQN/9q2btfatHdjWzUonOPe9BeeseSG9bkRtQt0TTrT3uT3J9yIlK3ybFmW9F+1OtM8le2ltUMmLzJZFWWnseU3gGrbUZyUzfBsW0qc6yltzTZBzXv8y5YVvu6Ksfq35tQHy5F0z3kmefp0nK6T5QXnz89tEbivJ14tlbpJslSuH2crvRyVPHcfQUyJrgMjqLXODQqusG5kbVEjOionOY3VpgJz/xVidPMmIvFoUaYdf43o3wf8XpVtGSp62s57KFHC67bzd6ihHXYdokdfk5EBBlCYzyvjWZJR9PFsXZe6RE6OMZ8X45ct7tFyVUGm4T9JkpvEK2V/3r0P7JU0jJL+HSH4X/2pJE7aF00hSxeoQ31fR/4aKrCtElquS+g4uh/7SvFkh3Cezj2W+NBVd59x/e/zlyPAZSjuUtu94trDP9bKffQFpgm/DPlq78MnC/ksodbVadNsa6nujTndRZPyznscddgFh5KyNv15VJxuR/yRzre9xs8mDhJpKL94hjXujk8pJe3LAnkKGw3ujx2JfWb4XSt6cwo3h96eGXBnXnc8NDa5lPNO3iXU9aKGkpZPUm7ZSnoW1zLREXj81ucUit1/A2ZERU4yA1WVOFAW1PDyg5OrvKP/RPCwg7T2nGHmYXrv8PHy/tspD636HpGWc5OFoOTsWW8cvLeZufhj3A/3rYmYdVRct/eboqc6yCx1lJ6VMm5brnqP9M4Q71k56fOLTw2oDU/ToI3r0MPQgEkc9pE6F3hc5zbeaJxkPehHQEubAAZRNgk+mXJj2naoIZa9PO6N7bz2jv0hnpcb/PsTuaMs7j/WslowRsg8o44mvL2wqdTMfZ/on+YXxqDDG1pEZZq6EMf0ljMqbfOsatfyeIXveZpwyNxJZ7VV7yPOmePPzAt/VViQFzLukPONcKm9lCKZc8/PCOqPidNemdrLdds5ArSz95Xnj9AWSUN5bg33LXeYixGJtR6uT7fdZr0B+kU9+xLarAtLtZLfKkheNU+QdVfLiZsmLAwG63Hhe8kKLxSr/0RTne08F0f7y/zP3nkwdYqfZ7dgM0vLAp0NEdrvUWSRHu11WHXaIDtUrowOMgkPQwVXfTwd1xiOUfoU+xEGHSQ53eNvDarofUxx9RdzaPjunGhE=
*/