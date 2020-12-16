// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2016, 2017, 2018.
// Modifications copyright (c) 2016-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_AREA_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_AREA_HPP


#include <boost/mpl/if.hpp>

//#include <boost/geometry/arithmetic/determinant.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/strategies/area.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace area
{

/*!
\brief Cartesian area calculation
\ingroup strategies
\details Calculates cartesian area using the trapezoidal rule
\tparam CalculationType \tparam_calculation

\qbk{
[heading See also]
[link geometry.reference.algorithms.area.area_2_with_strategy area (with strategy)]
}

*/
template
<
    typename CalculationType = void
>
class cartesian
{
public :
    template <typename Geometry>
    struct result_type
        : strategy::area::detail::result_type
            <
                Geometry,
                CalculationType
            >
    {};
    
    template <typename Geometry>
    class state
    {
        friend class cartesian;

        typedef typename result_type<Geometry>::type return_type;

    public:        
        inline state()
            : sum(0)
        {
            // Strategy supports only 2D areas
            assert_dimension<Geometry, 2>();
        }

    private:
        inline return_type area() const
        {
            return_type const two = 2;
            return sum / two;
        }

        return_type sum;
    };

    template <typename PointOfSegment, typename Geometry>
    static inline void apply(PointOfSegment const& p1,
                             PointOfSegment const& p2,
                             state<Geometry>& st)
    {
        typedef typename state<Geometry>::return_type return_type;

        // Below formulas are equivalent, however the two lower ones
        // suffer less from accuracy loss for great values of coordinates.
        // See: https://svn.boost.org/trac/boost/ticket/11928

        // SUM += x2 * y1 - x1 * y2;
        // state.sum += detail::determinant<return_type>(p2, p1);

        // SUM += (x2 - x1) * (y2 + y1)
        //state.sum += (return_type(get<0>(p2)) - return_type(get<0>(p1)))
        //           * (return_type(get<1>(p2)) + return_type(get<1>(p1)));

        // SUM += (x1 + x2) * (y1 - y2)
        st.sum += (return_type(get<0>(p1)) + return_type(get<0>(p2)))
                * (return_type(get<1>(p1)) - return_type(get<1>(p2)));
    }

    template <typename Geometry>
    static inline typename result_type<Geometry>::type
        result(state<Geometry>& st)
    {
        return st.area();
    }

};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{
    template <>
    struct default_strategy<cartesian_tag>
    {
        typedef strategy::area::cartesian<> type;
    };

} // namespace services

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::area



}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_AREA_HPP

/* area.hpp
mhzAl+Dus5wz7G4/3m09QyqGkVODZylZJMrt990rc/DxSD2HtJ0xh9q6qefgG8Bu27kVuwu8pZyJ2tYW2EhdY4Mcuh8oeUQKdntZmqyipx3fSLAp9Rziwkk9gM8rB5aZknJLwblB+dygZ/C9cWVDtf0dVXUtmm/sZVpZ85PLtShJ2LW90wkbeOpMqfA7vi6XU+b4G+cIhR04fu32t9MpqVE/5YIun9R/YHV1i93WWF9XfaW9dldV/VLL3rciRW3d9WdKEVPLJ6nYWdM9oVCP8HkfPEsO4X2DLiei9Y1vl4uAbjhb3rAHs/zRdc1Irq9rbpFtGxFxWZS/J9ghbo+FRvRbXCR6nMp5QQxMuCdEH8u/rSa66K7n+jHrqp7owGpNa5Sh2afV8CrrVXX5w4lc5JEVenVFy/Qv5i1FuUXpCTm6UNrrDY3VzTZ7U22zra6Ga/BLHe4+An7sAPIjot0R8sBbdi6l4TKsB0cUj0YjjBZeW2qa8fVcXytKliXk7fO3pUr61qrmumqRLKt981JLGhua1d7GlJVRkIL/x5gGcdQSpYorFTHMtH61UInbyx6vSzkC6aXGwypkVu93L1nX1FzF5d8g5PxN/MUixsfu40rNiNvkerscy+3I0rkU58mA9pQawkUgvT+vkesXb9PhZTp5ziT6vFK+pnDqyeeU95TiYIntyBUMEQ2p59MOB2xK1PWbvM8Q51Ci21a2V0n4wrJ6ZO4ntadYxEtXfpPYq3a20upCfeFw0KrCVE3SezW7IOzQi27QtQU6v/AyjmAX0SGtXsyT+JFEsWCiD2nTQoVpr9LJbwFpCCEv7gI88DaKbxDHbmkZr+Fc8mv9XqXf4j5mqfO5vI4PMEJJ3y3MSd9blgtt499ixF3eRZDF4aU7gHqcaAXFZCrf7K+V98DCMKlb3GCg0H2YWRedt2prA9yV/YAriFqtiIlTg7wi/F0JYu0eX3m7jx5XZIj4li9BLmnAD6+u4TuVX0BafsN4O3S8a/BXyi9lLrG37O2iE4hJqxSbySMyjWOnNLfORH9Zdi+N04tirUv33/cr8V3Kh67U3J23Z3m3fZcmrn5fHipcHcod6G1Lum74cXwMaZfCN5fdmoa9IfENip8tnAE/BpvoRk2ZZ85xTT4HEpRvKmkd712hJ/pyXidbod5kYnRXptCcXJXqLQBdyzs3TNLT6enA6pD9fr1qlcKUlxsvdYj57RE3CnfLu0Nh4X5xTQG7Ej5KDij1Clk9EGCZySZ/U84qz/FzlVbWyu6o199k1GjVH0DWa3VyCmm/9l5XM1L7VuiJRvl+Re17uNS6o6p6aZ8Pclzd3XtlPN+mAzLOrdkvY9wO0hf+5iJt8EsFt+V2fFXJU1Elxk/WeRUkxdr2+4NOej5i8kfQzo4LtpRfiKHD1m6/wPKWcnrhmdMq8EVJP1VO6l6+W/ixiMnbCnhijxPnJewXDy7T4oZBJtCiXDuuwhn4k1bLfX5aq+Oev0cZBznhk+ouoJ4OvR7u8ZQmRfxou88uf6u5i23BvsmCH4Q2XWihb6macsvmCru4Dvi5tNmCc2kzpcRsrtB+WXNvhmnA2Sbosiujcms+hQ9ffLMS1dyhsS8K9cB/ttP1Sr2a8wdtF3UWaP4Ir6f9LekU4vwrHCR5y/XwuuYmG65GXBhCedPmQe1bG4h+LlK40j0+sXN0NfC1Jp0UaaK56jEJaUQ/VLTVDm8HrCaIwpTh/cGSdivRTxFTPZ29Spw57HjzgaU8PUQ/Wophru9bilUR3Z+PqYte1PEzbalb1VJxzybvfHbUODc6xffmRl2zK1yPe8Ba+RX56Kq3u8LNvSF8ZbbAYOk63VKkxb8NRz9FTXY=
*/