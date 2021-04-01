// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CONCEPTS_SEGMENT_INTERSECT_CONCEPT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CONCEPTS_SEGMENT_INTERSECT_CONCEPT_HPP


//NOT FINISHED!

#include <boost/concept_check.hpp>


namespace boost { namespace geometry { namespace concepts
{


/*!
    \brief Checks strategy for segment intersection
    \ingroup segment_intersection
*/
template <typename Strategy>
class SegmentIntersectStrategy
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    // 1) must define return_type
    typedef typename Strategy::return_type return_type;

    // 2) must define point_type (of segment points)
    //typedef typename Strategy::point_type point_type;

    // 3) must define segment_type 1 and 2 (of segment points)
    typedef typename Strategy::segment_type1 segment_type1;
    typedef typename Strategy::segment_type2 segment_type2;


    struct check_methods
    {
        static void apply()
        {
            Strategy const* str;

            return_type* rt;
            //point_type const* p;
            segment_type1 const* s1;
            segment_type2 const* s2;

            // 4) must implement a method apply
            //    having two segments
            *rt = str->apply(*s1, *s2);

        }
    };


public :
    BOOST_CONCEPT_USAGE(SegmentIntersectStrategy)
    {
        check_methods::apply();
    }
#endif
};



}}} // namespace boost::geometry::concepts

#endif // BOOST_GEOMETRY_STRATEGIES_CONCEPTS_SEGMENT_INTERSECT_CONCEPT_HPP

/* segment_intersect_concept.hpp
37Z0TB5uOck3JAaOSqCbMy761ug+JnzMI9qhJ+v+t5qd+ZEh1tyGi9tIowaiN17shYkwLt/JxLBviOZNfyuO0q/DrjWykCU6zIKrmGCRDsFvpAhyc5FkoodpakkhtOJ+DFDqBMStsiPu2x1p8w4jMYDItV/fZzHlNxp8muWdQep+wvHy3XYJaWoQJFrq/wapSAvpBjP2cSMlHwwuzrUBKlSDAUkD9sO4hEsExQS0WULEZ8FCMiib064u0v5BPWznotN87Nl3tSWOIOV7BKMQo7pdfUsKSobrcG06IlerkBbe3zhhSoLdWdKglcLxNWfCwvABAZJYCu9vAQMUoxrXOD8P4Ooxmvc3gfeuqTmEmu3Osu0CzIf68Vy6uN2yLDat4t/OGCmvhWhKRbU45q5gZRUbm9AXs1A23jO1Be40Cc58qr9Wm0Ki9oGsbBpIP0ZWXzHxGOWgUErUcuZUHXv0k/t5yh43t0xKKFReGS9yBJ8EKLZ5Y72LHBck/goY+Sbc2t3X3vNSDOqjshSaVezfA2sw6BZkJh8hm1ORHxfI/5UzW1ySfQGVXWVTDg==
*/