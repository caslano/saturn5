// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015, 2016, 2018, 2019.
// Modifications copyright (c) 2015-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_HPP

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/geometry/algorithms/detail/envelope/initialize.hpp>

#include <boost/geometry/strategies/cartesian/envelope_box.hpp>
#include <boost/geometry/strategies/cartesian/envelope_segment.hpp>
#include <boost/geometry/strategies/cartesian/expand_box.hpp>
#include <boost/geometry/strategies/cartesian/expand_segment.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace envelope
{

template <typename CalculationType = void>
class cartesian
{
public:
    typedef cartesian_tag cs_tag;

    typedef cartesian_point element_envelope_strategy_type;
    static inline element_envelope_strategy_type get_element_envelope_strategy()
    {
        return element_envelope_strategy_type();
    }

    typedef expand::cartesian_point element_expand_strategy_type;
    static inline element_expand_strategy_type get_element_expand_strategy()
    {
        return element_expand_strategy_type();
    }

    typedef expand::cartesian_box box_expand_strategy_type;
    static inline box_expand_strategy_type get_box_expand_strategy()
    {
        return box_expand_strategy_type();
    }

    // Linestring, Ring, Polygon

    template <typename Range>
    static inline typename boost::range_iterator<Range const>::type begin(Range const& range)
    {
        return boost::begin(range);
    }

    template <typename Range>
    static inline typename boost::range_iterator<Range const>::type end(Range const& range)
    {
        return boost::end(range);
    }

    // MultiLinestring, MultiPolygon

    template <typename Box>
    struct multi_state
    {
        multi_state()
            : m_initialized(false)
        {}

        void apply(Box const& single_box)
        {
            if (! m_initialized)
            {
                m_box = single_box;
                m_initialized = true;
            }
            else
            {
                box_expand_strategy_type::apply(m_box, single_box);
            }
        }

        void result(Box & box)
        {
            if (m_initialized)
            {
                box = m_box;
            }
            else
            {
                geometry::detail::envelope::initialize<Box, 0, dimension<Box>::value>::apply(box);
            }
        }

    private:
        bool m_initialized;
        Box m_box;
    };

    // Segment

    template <typename Point1, typename Point2, typename Box>
    static inline void apply(Point1 const& point1, Point2 const& point2,
                             Box& box)
    {
        cartesian_segment<CalculationType>::apply(point1, point2, box);
    }

    // Box

    template <typename BoxIn, typename Box>
    static inline void apply(BoxIn const& box_in, Box& box)
    {
        cartesian_box::apply(box_in, box);
    }
};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename Tag, typename CalculationType>
struct default_strategy<Tag, cartesian_tag, CalculationType>
{
    typedef strategy::envelope::cartesian<CalculationType> type;
};

} // namespace services

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::envelope

}} //namepsace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_HPP

/* envelope.hpp
TCg3RQOJaCKfKCUOE7VEp3tYJpFGFBNVRC0RtJK8I+xEMVFBHCd8V7EcIpJwEMXEduIwcZ7oVEj+EHFEPrGJqCJOE53uZTrCThQSZcRxwms1yyMiiESigNhKVBM1RMv72J+IaCKNKCTKiCNELdG1iGUSicQKYitRTZwlgtawTYnkNV7/Vz8+znvI3v7gFT5iZqadb31m5mQl2NR/ZqcNnJWTkpY4MGRQyKDgpIFzswcHhwzT/5Z7xdCB6tcyBibaZuXM1v7O32Y6QpQPHgzKnMXps3INN9LfK06539SO+/m74r10J6QkZGVmZyY5AvtO6Rc4yc6XEFMWpGTMDhzDh31S0mxZ3O+O9H+qPeeq8o2Icm+5FicCiaXE0S6Usypnf11Tp0bGjomOiY1PTNQ+n56Qk+3ITFfS05BvDGh91gf4G/q8N32TmRnJl4W1b9YM8FOGOxc5y0vGT8bLnMOVrwvyBxlux6bNtfHjs2bLcGmnz3A+eZ6tTiB91TO+azhTqN/GlfyokmuZDMmPFMkPr9fc80O+mvF/nh9xTfVvTjI+4xHHyI9Cc37wzRvP8tGQb7dp3xrId/smQoRHfpi/nXNU0pVGKANmEx8r2+l1LV2ujwQ7P+eSmaV8d7/e72HKNwMtl32FLDtf2sX1kftN3fETJU/UZbsyQCkmXg35hsrPffNGLWZeklclrm+O8VEJ/ZvY8v2FNPZ3h3NYmTK9Wg7StGlzsVkXWa9sdVioTGv89nIMun83a4wzbek2R7L6LYjjyvUl+RDL/nLFG8p6u3+Xii+w6ttS5scw+SSa+h0cpQ0Y87Ap955kHh3N3x2fFUuy5rIK5L/+/YjDMi77hfP31Qf5XfYH4/ckgqV/wSwpu+nE56x/3pvu2ykpJaMBZUP7ztNneh7KN+o8y4t8l9Ocj16mfDSXqf2SVvXba+QrcZLl+L3lntaUjBRHw9Nq2N7yXVdzmnxNaTJ/C/TsBdLfh3KfFePxS6Wce6RJmVYp7A3f343pst7f1eFRddR/MXXUf3F11H/JddR/dov6T777JPnCR6O1/PyZ7ef7O+kDX/IqBL9SjqOH3PPKuZwGfPPM4lvdnnWCrIN13sl3YWS461upeWoZkOGubxgVGOsM621lUR+o++Btb7OeksfGfFkh+bKICCCUNJ1hfsffdssXjh+Z9vn1fmdVli9pSsw2fFdH9svsrAQv87HC0UKdwQOShiJJQ947lmlQP7HfiGO5e1pi3NLS0aPsKMMtvrdNnVhIftlbqN9N+kBNH8Pd85xlyToa8/qErGeI1CEDpA4JO+yxnspO08i8Vre/fEOHnaaub8E0/hs61t8uqfvbOtbfRqnrWzCN/4bOP+tbOY391o/1t3vq+pZQ479xY/0Nnbq+hfSf+yaO9beE6v5WjvU3cer+9s1Hzu1ysqKySXzngMLqAwfnfLnvkfsa/00c9d60XCvJNVR5E/O96ZPSluhrvBzP4nA8h0vxvN62T64xIEPmY2zb973M5wdMwR8N0xXKdNEW030kbfuO4ST8GNV0y7kypFmk21tpO4xN8BYMQBt2xtl4kd5GWM575XyY+ZjaCE+SdEfhHJyCC/AG3IzT8GmcjuUYg2/gDHwXb8ETGItfYLykfxaex0RUFm5DX0zC8ZiMUzAFb8Q5GIepaMN0XI8Z+Ahm4lm04wjW4fc4GrNwGmZjKubiHrwND+Fi/Ajz+K8Z678EW+BS7IK3Y3fMd7XFlPNP5i35bnxG11a2V3vsgR1wGnbEBAzAFOyEqdgZ07GLvl3lnBETLbZroLRx64HdsSdOxiCMxV6otm2X8zw5/2M+prbtz8p23YHBuBOH4Ys4HvfiFHwJZ+I=
*/