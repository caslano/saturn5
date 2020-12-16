// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_INITIALIZE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_INITIALIZE_HPP

#include <cstddef>

#include <boost/numeric/conversion/bounds.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{

template <std::size_t Dimension, std::size_t DimensionCount>
struct initialize_loop
{
    template <typename Box, typename CoordinateType>
    static inline void apply(Box& box,
                             CoordinateType min_value,
                             CoordinateType max_value)
    {
        geometry::set<min_corner, Dimension>(box, min_value);
        geometry::set<max_corner, Dimension>(box, max_value);

        initialize_loop
            <
                Dimension + 1, DimensionCount
            >::apply(box, min_value, max_value);
    }
};

template <std::size_t DimensionCount>
struct initialize_loop<DimensionCount, DimensionCount>
{
    template <typename Box, typename CoordinateType>
    static inline void apply(Box&, CoordinateType, CoordinateType)
    {
    }
};


template
<
    typename Box,
    std::size_t Dimension = 0,
    std::size_t DimensionCount = dimension<Box>::value
>
struct initialize
{
    typedef typename coordinate_type<Box>::type coordinate_type;

    static inline void apply(Box& box,
        coordinate_type min_value
            = boost::numeric::bounds<coordinate_type>::highest(),
        coordinate_type max_value
            = boost::numeric::bounds<coordinate_type>::lowest())
    {
        initialize_loop
            <
                Dimension, DimensionCount
            >::apply(box, min_value, max_value);
    }
};

}} // namespace detail::envelope
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_INITIALIZE_HPP

/* initialize.hpp
TxzIbRiX5jgbDWvp7lL74QSDBvuu2ZkTg3gUnj4oeKu5nGSlEetRNKdYaYTCKJrTbDTYtnS006vZnmGlYRP3kOpr/v0sO113cwdVEs3HnGOj4zfWnU5ke4mGs0ovztVoJbtFAyWzCwLxWU59tf24EpnnYGYsIuF5YpHxmk6kuCeq6Zy3jotkXOVOT/oz5xBaUOrnKpf0QYv0PV5f3hcdl376M7YI/3R+X9EHbSaZ9p3DXNUHrQgXC/NFfETi6bRh08p8dsS3dxoauCEWlcGBY+QzThx4E/gHiAPfhXaiA3vIgdVqsCcc2EEa7K8O7DMN9jcJowiqYBsc2DMa3RcurEjBhoySsF9rbcc6sG6tbZkDe0Jru78Du0qjizqwVzVYrwOr1GCHAfsSWLsGO8ah23Kggl3l0I3T6K4Zhcw2Jz7XYNc5sD002C1Of2drsLscWEqD3efAhg/U5OHAPinS5OHAZmht1zuw+zXYiw7sP0Ua7511TNXoSECYMzmJBhs0WrZ9U4NNdGBbaDLadbTsb5JGt1CHFazfBMiGfrfYfTafqLV7PskVTGrYXa2erWsz8D0zdVuU4NPdFiUiWdXsXCef0RRTbaHCkFL1jhSf0p02e3lb2oHJu6AqH8nyCVz2n4226WMf5MMRbWtjp/jEaINhFA3+Uz71pehzEtOH2oubD+UTr0MRnIHb2PSaXTiMT6hVeIzBxBh2dGg0RwRoVL6s+H+kQYOh1PBH8wmeG2GV4rrZUgbC4ir8MUG8tIgF1IH5EKGVoS9rbfaQ3NFXq6Dago8L5JAvBuqpeDNPn47j04cjotJj++MDeHEhWJf5PP/4FMHoO8/cxKz0mP2EQN/CdcsBgrmFouE8vw3nreIgPk18Ljsw82RJ4zs/OInPQK3Hm/8pJm4G8887N1Tet75T+QzixeA6zekOjcyZiBMJChJsBTap58fPdGmwBNRXLJRKHmcr+5B1TmlUnOTiJJwS8UG+XP18B4/OU4NMxnTchQrn9TtVm5+IfWyL0Pu4mE8v3JWC8uRwqYOjfw+nZOw/a413NscpeqJNheRufBCzmnHGSdbc7TJvvRgcbS/91geXNV8Xd4WLwzyVMFc917raW59oV+K1udaDszQCb/IEbCDnFKNlPetl/NyOjg+61YE9ocFuF3YVP/e9kII9Cex0YFtrsKcduikCVqD/inSSLBt8O89aN3mGzzIOidemhQLADa1+sZ7P+nCNg6Og7QVwcTIJ1cfzfDbWkMRzUtjRKk2SZ8s8HI1kBOj5rNc9XDa+TqsdvOnB1az0ffyOKwMOX1E/aYI0/AcOXjaHGzyc0KbNdwOfzayZGZGyQqjsF/zQ6lgs2V2ti/+ET9gLO0j/WuQG0sf+zMW3c8uPlBj18fFqj2EaHsOu77cv9LZsSd1OfDJUx7GVNNxXejvsld7nQHe83ERyI6q7CXxqODGiJ7dp/naMqOph32jt2FOMqurEA8aAEyFIJJPqoPzpnbsAx8+WVdX5+xrkwb0IwGszROFw2mreWyo4EYG/fr21whEJKHu1rQeXDl6X2VCJy2nconAp92olL1z8cBPPXJVPG2ng1bz6GIP5KZs51sCb8xyvaLix21BaI6fp4ScE8YEaxMQgXk2zjzHENBV+soEX01TrnCrxuSO+0uqFdQ2BeGtnAy/aK/ntAl64jZTjJ63wjNK33RQ82WGl5zQjXcgdF2E/k5Zztkf88X/wDE2Uv2hG25buDrWe6cyDc0J5hUJrN4lPRS4EmYDNat9OG+PDC/9cQL1PrCGTbe6w1fueDMal5jrkAZC7lA8Da8nKxSj9nzEmGEObejWJTzEj/4LBe+v140EXeH+XNYsCuyE=
*/