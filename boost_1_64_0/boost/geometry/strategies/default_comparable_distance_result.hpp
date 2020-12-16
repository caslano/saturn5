// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_DEFAULT_COMPARABLE_DISTANCE_RESULT_HPP
#define BOOST_GEOMETRY_STRATEGIES_DEFAULT_COMPARABLE_DISTANCE_RESULT_HPP

#include <boost/geometry/strategies/comparable_distance_result.hpp>


namespace boost { namespace geometry
{

/*!
\brief Meta-function defining return type of comparable_distance function
\ingroup distance
\note The strategy defines the return-type (so this situation is different
    from length, where distance is sqr/sqrt, but length always squared)
 */
template <typename Geometry1, typename Geometry2 = Geometry1>
struct default_comparable_distance_result
    : comparable_distance_result<Geometry1, Geometry2, void>
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_DEFAULT_COMPARABLE_DISTANCE_RESULT_HPP

/* default_comparable_distance_result.hpp
b6srCWxEQIDt0VFiXgwyIfa7kUiUjbWLd8LqIOjQdMsVkbTN8Ecm79TxEpAmz+SYishc5tS3XyJO9eE898n3od3YmTtHboJIkGu+eh2TvDERPHuxpswh0qOWDKQtyt7xJRXOjjXbXBYXJxrB3O8iTKbIZdfF446seQ1A7roknSk5yt96q6qmtv8JUQhrZuMehw71WIppMoq5vzHrEICSFKtU1GIqs6F175h/y0gcKajJX0hjRNMaKmWs0BTpGdRqA1S1BHWlAJXnb31PVUC3PPGaGRokSkypiDzAzfrhi5bWJG0YHe2+VmTh4SmYMMCh89QpF7S3hSCcsb0ECAkgH2GQt7xInHLvcq0DtjcH3cl4OJB3Y7oaL0TLmLhdvB4q3erlXozLYLjWZknIyaZ6btDjTENFDck0rkyXjLbiz/G4/+kNjrx2UHoiTK6neQOgSSgUOw5RJD/HnUlbwijVRMwH+CFbJVPnzjTsrq8znaf8zGg6zBQ98nto+JLOzH/JqQb+jFrjgGuN1ug0W6Ozh9aYnCbAUXNIdM0if73ODkMt4ZK2tm0KutMmZLObWTbX33qZU9NFPc6tc7eXR8dybqJv0FgQLuOvoT+g+a0c5reGMVqql69l9R3++uhGTuU8C37D6zCLf8xk3LzFnsV/tZR4tLwi8glH3reFaPzkMoMTlgtSexRUU0fdmf89DNuAIwdCzMQVqV3Ww0DYnFwaVbi9Dc8Euo5TBHfet03EhoFdmvPMePE6tUsbhtA+d3FLDmk4gYA6X6sYT3HO1yryjDUP88c9AurQhgsc1j9Rh/WPOf01HJY4x/CBb6eVMLu0N2N47HDsmixAl5tEcy1BgnSmwHeeUnvDoShh+AvvDXlJc/31vDdMbpWY5TBJP8H1rASR0f2qX+lG0W/UQ02xccOFFZGpWcR8h202hgHMG523VHKibiB1Zy/wkhcpX0XaJFcFJamsxHQ+w5IbW1awqpaB5m63jOHou90Tsmi3e8kmtdutULvdnGvY2LcrmWyLb9YCzUsqzi74nZlhuyVSV6nUVUKZoQpVuMJTkzE+kzFe/wJiXOsyMD6z3dyfr9h32WDfb98vlV+lk32NYjomXUebcnbtx0dboGjABi0O64DPnFxXOsyNnYluVH9lCY38a3EQOzs2lhIPck78gEy8DBOXUNI856QnukXS72HStP77uky5/iGq/1qqP+6nalwNB7CZr5nR+28SEndU8kIUbANmwsEk4E6qlZCGM1VHT19D2sclKFW1wuko9oxdjLMb6qrFsmiPuQHfuYyhUAZqoS2ohNqLsMlauQGXYyl/ezi5lIzYHXuoydFfet0UMTRXWAurtd3QrQoPZCWnM0DSbxu0DheRipfUfyOpMFS8lmu1BGoVGxkLOKdh4gwB+u5ZDR3rM5Pa/0lZnylYH1vnF89+z1yC0yu0g60zuUZFru5gNT+u8nGg7UWqCVTzyg7KM5XVwiYQY09awmpLM5bovs9cYeH/75OrXeAA1o3swcwYHkO2nYkWlQiB9tJAjUYm+ikPAcWKYiN7S1Ub/SOk2vtqY9oA0vaE0kotURuRYiFcM0OLHEJDaZi2IjLQlcZXJ5FEjzwCMI1EyluHXPQ3bxznUee2RN+OJ0QmFEbQQUu1DoN1YFs6c3Uw7c0YaCQjLHM6AYCZsEgm7GhajIC2B2CUmuFUQjCVElo6A4nw98I4l+pP0+/rfEy1X1CRW26pA2stcs8J7bHWxzdC3eyCut2bJbKYOxw3sP1BnCtHy2WpXLHCtZnknnKNU2yEQzZYMspFUTgABqZ3eF2YhqE/rOX3qPxr3bRL0OK8dlw6xs3T4tLsOB+tMLW4dBWXkgY=
*/