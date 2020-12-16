// Boost.Geometry

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2015-2017.
// Modifications copyright (c) 2015-2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_THOMAS_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_THOMAS_HPP


#include <boost/geometry/strategies/geographic/distance.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace distance
{

/*!
\brief The solution of the inverse problem of geodesics on latlong coordinates,
       Forsyth-Andoyer-Lambert type approximation with second order terms.
\ingroup distance
\tparam Spheroid The reference spheroid model
\tparam CalculationType \tparam_calculation
\author See
    - Technical Report: PAUL D. THOMAS, MATHEMATICAL MODELS FOR NAVIGATION SYSTEMS, 1965
      http://www.dtic.mil/docs/citations/AD0627893
    - Technical Report: PAUL D. THOMAS, SPHEROIDAL GEODESICS, REFERENCE SYSTEMS, AND LOCAL GEOMETRY, 1970
      http://www.dtic.mil/docs/citations/AD703541
*/
template
<
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class thomas
    : public strategy::distance::geographic
        <
            strategy::thomas, Spheroid, CalculationType
        >
{
    typedef strategy::distance::geographic
        <
            strategy::thomas, Spheroid, CalculationType
        > base_type;

public :
    inline thomas()
        : base_type()
    {}

    explicit inline thomas(Spheroid const& spheroid)
        : base_type(spheroid)
    {}
};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <typename Spheroid, typename CalculationType>
struct tag<thomas<Spheroid, CalculationType> >
{
    typedef strategy_tag_distance_point_point type;
};


template <typename Spheroid, typename CalculationType, typename P1, typename P2>
struct return_type<thomas<Spheroid, CalculationType>, P1, P2>
    : thomas<Spheroid, CalculationType>::template calculation_type<P1, P2>
{};


template <typename Spheroid, typename CalculationType>
struct comparable_type<thomas<Spheroid, CalculationType> >
{
    typedef thomas<Spheroid, CalculationType> type;
};


template <typename Spheroid, typename CalculationType>
struct get_comparable<thomas<Spheroid, CalculationType> >
{
    static inline thomas<Spheroid, CalculationType> apply(thomas<Spheroid, CalculationType> const& input)
    {
        return input;
    }
};

template <typename Spheroid, typename CalculationType, typename P1, typename P2>
struct result_from_distance<thomas<Spheroid, CalculationType>, P1, P2 >
{
    template <typename T>
    static inline typename return_type<thomas<Spheroid, CalculationType>, P1, P2>::type
        apply(thomas<Spheroid, CalculationType> const& , T const& value)
    {
        return value;
    }
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::distance


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_THOMAS_HPP

/* distance_thomas.hpp
kH8HnKN+x+enzvzmiJ//mena4ud/7vnjPyg/FbZI/PzPPc8WP//zzF3Ez/9M8vcHlJ8Ke5/PT+mS5fOLM/eipyi/vvwmfvW7j/67kvrdW//9+Qfm78v036+r373035vV755iB03V7wqfRW4dcBa5n5RRtSYBax09As4iS78U97FZNyI/h6y+mRzm+VVzvFrdU2zaSbveAfWx3aqb3kxCWT8OzOOmvr0muSuTljMrxfrt5uq6PTTEBIz53Dqwnv2VfDvwR1O3yM/9Rppvpm61LzMinYqLxU3C1dDK9LBVN29WXgqzo5DuGgWZj8jZ6Py8lOlu8oH8VX7GOmhOrrxDOpytTlbzSmPNW+qyzCvTmFVa68MRSddRqdufynhS7JeunKSMlOw07n/NdJd75kRsSao02b7XLfYEXcjdhmut+X+CLL958aONZY0zr5Ky41f/E+uc4Cb5fRY5vn6ZsL3l+5NyfmYovFCrQ5/40pPvKf/sjNaX1DhKGDknEyxdTaKttkNHwE3Gd8hVnW+vwpF++7uSpTza97GfL+/Hf/GUmvqHd7Y8oH2GdK7cfDeK72tE9LDcH7gf10Sb2xzz6TLXk8MuOhNNbvLxduTlXTYlKwK9pD5b3omkPpvvRNRdqc+qf8lKmcbaU32L/dIsnjPin+s7DyLfoTef8ejPNBW7ml5pb25zDUrm/C8Y6axUs4m1ju2WfBlSBX3gQKjN+UtVvoR31l7ywHH+c/ff1PzH8i6Q1s+I6EbZn5iDq42elb5QOmhns/0Pq7jDObu4JKC/dMEOLmu/0hi/fL289Oy01OMD/ezz4jroV2TVT+80Q1kXlTmx43tRQX/jwXdxzXFv4zbwX0ocZCWl5HOKU1sCjbx/fta446K916n3xXWGX55nZqaMOcHHuSz5GFcdlGsJa8B6TdD371Z91YBSkbGkusNYUj3IWFLdPpZQ5vaxpLoaS5zSaj3bfrmh5Fipp2Oknrq+tKbVt4nGP6fneDNTQquvAe9KEdXVgsvt53FdTfBXOkZ2p8M357CWPxVX//OIzJm4aK1tBMpzs9SUl+rNC2mNpVr0hSfUeFXmu51nYOCaBUR+3Am7fG1lJpI1Hv9x5PhA+xnzi/jhUfIiv0eiyt+hX5hyhb1cGyC30CrXWIDN1LZsM5ipRiZT7VfFGw8eE7lHcA2RWWyR2S0pL9+jjZwIlWskEY6Z7S17Bva5RYxlX0FkyRwsmfzpE2/Uv0ZfoZ+E7wNXGs/72cSWfcF4e57GaPOrr/zTlwS1Nd3y89JhvLGUYfIg4+Hx0rdfjWuCvFNWeSwFJqXkzctOTUpPy6vI3LuR3o8ZkUh/SX8nd/wNb9XnDQlyNuXAIPu9uKbEm3zSorPvSlwI59zLqnNbB/vWSlviUnDNkVcUII9Z/HQqnMqnSOaPMlZIPvGik56m7IurfNK9xf68ejbNnSXPevyf1b1lPl1Gnk4aIt9dlHlxPu5i4o392pdG61nJ0OuAmad1LevB2VLO9vbV3to+VNvYLTqmSrlPw7XQxnWlY3j3xsrq2/rIB8qvEFkDRVb8NxZZsvYoIivYnx4RmTOkLbpxLZFZ6CgzNyWbV/9Qxg4pe18fEMEeialjwjCJWPJlEO4SrZ58a9UxPzfXlzER5ovZ/vaKzNHSLw7HtUJmQRCZ2DvJNZZNQ6+jTuNq/JXOckud5fKulpKtSY2kf7TsmV1pHwNaa3XvlCk38ruKTvP8UWadH26X2wa5yUpuxe8olvWesUPktxUdWuLaauXsLB8DN+6c/DDW4Zf47Yk8osdpv2vjHSEBK8ueB2yHDsVWHZgC5oS1H+PcB2aqdc9LZN0zxjK/yHWn5OVY1jkuMNY=
*/