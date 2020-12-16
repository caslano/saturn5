// Boost.Geometry

// Copyright (c) 2018 Adeel Ahmad, Islamabad, Pakistan.

// Contributed and/or modified by Adeel Ahmad, as part of Google Summer of Code 2018 program.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_KARNEY_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_KARNEY_HPP


#include <boost/geometry/strategies/geographic/distance.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace distance
{

/*!
\brief The solution of the inverse problem of geodesics on latlong coordinates,
       after Karney (2011).
\ingroup distance
\tparam Spheroid The reference spheroid model
\tparam CalculationType \tparam_calculation
\author See
- Charles F.F Karney, Algorithms for geodesics, 2011
https://arxiv.org/pdf/1109.4448.pdf
*/
template
<
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class karney
    : public strategy::distance::geographic
        <
            strategy::karney, Spheroid, CalculationType
        >
{
    typedef strategy::distance::geographic
        <
            strategy::karney, Spheroid, CalculationType
        > base_type;

public:
    inline karney()
        : base_type()
    {}

    explicit inline karney(Spheroid const& spheroid)
        : base_type(spheroid)
    {}
};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <typename Spheroid, typename CalculationType>
struct tag<karney<Spheroid, CalculationType> >
{
    typedef strategy_tag_distance_point_point type;
};


template <typename Spheroid, typename CalculationType, typename P1, typename P2>
struct return_type<karney<Spheroid, CalculationType>, P1, P2>
    : karney<Spheroid, CalculationType>::template calculation_type<P1, P2>
{};


template <typename Spheroid, typename CalculationType>
struct comparable_type<karney<Spheroid, CalculationType> >
{
    typedef karney<Spheroid, CalculationType> type;
};


template <typename Spheroid, typename CalculationType>
struct get_comparable<karney<Spheroid, CalculationType> >
{
    static inline karney<Spheroid, CalculationType> apply(karney<Spheroid, CalculationType> const& input)
    {
        return input;
    }
};

template <typename Spheroid, typename CalculationType, typename P1, typename P2>
struct result_from_distance<karney<Spheroid, CalculationType>, P1, P2 >
{
    template <typename T>
    static inline typename return_type<karney<Spheroid, CalculationType>, P1, P2>::type
        apply(karney<Spheroid, CalculationType> const& , T const& value)
    {
        return value;
    }
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::distance


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_KARNEY_HPP

/* distance_karney.hpp
c5Myw9rHKahPRFGY3hG/EXClYeM2Jc/t24v0mrZoob9dvAayR+7GNcMl4x7V1uGfrGw5g2BapUnFXlw4+jl9uwBdZA/Mp9+DyGQ/2GPar52hyyevGlttVhaKvrtx9XE7cc83xj9A3ww3ynoMs5VJZE84Oi9zic4BedW8ijyMi8FdjtuiyX7KKjuLMk3KoeJg7zcUO3ay/2bLq/bQsMuT4wEWXVaJLn0lH3pKPpwK0MWblJmX5M5OmZblTgtHF18eWM9zfFRd7CewhxYrLKDs4p+2yqWalLtPXpd2BCqdfZawfr8Xyu/67EP3MP7devSYnpdVEj+Xz6+X6XfkGeXX0/R71ufXw/Sb5/OLM/0GKb8evU2/o2uVnwpb7PPrbvot9fl1M/3yfH5KRrry697X9LvO59fH9Bvp81O69PX5qTzo7PNTedDC56fyoL7PT6Wjms9PpePsGuWn0vGVz0+l47Dy66bS8a7PT6Vjg89PpeMxn59Kx0Kfn0rHNT4/lY5hPj+Vjo4+P5WOKj4/lY7vnlZ+pCMUO/2+vikZit1dDL+p8wHKZhd+cpZDPaf3X7OlDm9tbG23XtnPHy19yHDpQ4rXW9qPNqhIR6KfkQm53Tr3IdazNpV8/Upu5nTrebDjol9HSU8b3IsIdm2w6SfdSvnntuzn0qx58qh8N2CU7EUOw72MzAQHmbM0c36ayboQzouVdR7OE209yxIPyT/8dAlqrIqVfEoL0HmA2PsfIeU4xCxHB53R1ijFMPrfipbjAdFvqei3GLdNK8eN/vpJEdJdh2Nj21+3iy3thgNtmdisY+DTThy5A8aOETXlrKF8b70d3I5OJRad9ENW5Y7VdS3zixRpg+o8nKWsSkRuF1w12V9/BbkFmy1yp7u9cf4GBcu1PSl2W4POF/qIrf36Ijca95qWXie53qyc6VjjzcmNXK5Z9psc5L6O3FIHufRgKbMqlW9nU2QGbcOtxXZ/V5HZBbdTq+jP2WXKtIxZWehyrWn12ZpeI3KbiNzGuBL+L95BLqe58nMzvfOwBmvY8Q0j3UHnhGLLv57Ir4vbhfxkm3y9ahklXAG5ZhkXitxmIrcp7g2tTtvkyntFXuQyzbx21bXXqzeRWWyXmeZOT8nP8iaZxiqnhZPXgXVsjMhf7SB/N/IPhCBfmdOsgB5m3jevJzb6cDFS19/W5t52PaSmlT9WyflQyfs82/leW/mLDtGSFy7cHnSIKw7UQd5EKlD+g0VmbZdd5vPITLDLnJ2f6aayZ+R703JuzA4jz4PVvRUuezvfy/95bLJVM1cvreHUvWBpr6H/P3JFfiPzvbMM+VnuOe6sCshW3xYS2XVFdh3cPmQXO8hmHUE79JyTFoZc6rljms9F29vbO1p7s8vVjDen+3I8dNnB0uyVbwi0F/mtzPfboLLT3B5vRrntTOaEQeWerO9cx+OeDyJXn+hEnl6p36y5+N7nm8v7/H7kJljlZuWkpIlg/p2aYrTsCOfCMZb7E0MGielkOS/t8/ekkLEBc7kEOQB4bTXihuPg++hbZNWXD0wZumWUqVu16M9f0sLp582763Udv10+PzmrbT/Xr9KkbCz3jf7yBePd6wN597rMnAc2sI/VB7Q83mbROQ/r+Vq2hlymweZEo+XbBwNxjaRsDyLPEyjPOv+LqCzN8eJF3Y+48qz1q1R0aYWrKe8NH2lz0QBdKjpPCtTJpd6V3XhZx7CMGN842kjG0UNaG7fp1M2Yp0ZYz828+UyvO3M8tjVQsfW/RdreZtxhrc1vD9QjKSXLk838Ncebkxf6emJgmxsBDTv0EpPY5k+A+TjTX7O9H/hNtm2NJM+kHnfDfYqurlccdeUfWdw=
*/