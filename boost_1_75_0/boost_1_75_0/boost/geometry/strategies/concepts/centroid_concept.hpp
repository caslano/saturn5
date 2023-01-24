// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CONCEPTS_CENTROID_CONCEPT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CONCEPTS_CENTROID_CONCEPT_HPP



#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>

namespace boost { namespace geometry { namespace concepts
{


/*!
    \brief Checks strategy for centroid
    \ingroup centroid
*/
template <typename Strategy>
class CentroidStrategy
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    // 1) must define state_type,
    typedef typename Strategy::state_type state_type;

    // 2) must define point_type,
    typedef typename Strategy::point_type point_type;

    // 3) must define point_type, of polygon (segments)
    typedef typename Strategy::segment_point_type spoint_type;

    struct check_methods
    {
        static void apply()
        {
            Strategy *str = 0;
            state_type *st = 0;

            // 4) must implement a static method apply,
            // getting two segment-points
            spoint_type const* sp = 0;
            str->apply(*sp, *sp, *st);

            // 5) must implement a static method result
            //  getting the centroid
            point_type *c = 0;
            bool r = str->result(*st, *c);

            boost::ignore_unused(str, r);
        }
    };

public :
    BOOST_CONCEPT_USAGE(CentroidStrategy)
    {
        check_methods::apply();
    }
#endif
};


}}} // namespace boost::geometry::concepts


#endif // BOOST_GEOMETRY_STRATEGIES_CONCEPTS_CENTROID_CONCEPT_HPP

/* centroid_concept.hpp
BQAWelf/FanrEFRa3KT4EGxgr9NmwntSqOuDlXACxDNw6Wuf3VbExw4T9udYToDPuL3e3YN/Q+q0Y0LNkfLbBSISV6znE39B6nS+9LrD+0aGLCnezqL/QOqxY/4d3UrbMyKDxc97StuHIsP7udsMHyA3xlKbcW37yRF0Ji9zAulZxiXDbjbvF4kpEvjnM7f/nAeMQA46kJN/iB0dcRYFhtYNFOGhDtA8vxqhwjNOqNlGDJxlO7l+Ek2b+vgkGizlHYWFU5leNQLB3kDuluHH33YWNBgYVtMzlvjhVgN8c7lnCU5MalAFxizcZaRyDD/N3+FpP78UxIDEtC6fIismnyIl53EPg2et4YPuh+8gkUB6nblBeI7wFIQT6HsOjp3JexxPwyLudU0Aht+njUXLWgm0OoZVWqfE7gegLAVkjp8nlvu2F5/CGVMsehz27rK/OQG64zxtMO/boq5RD0dOi27n1vXYb4k0CDfINtD+BdTj7kKNihiaDL4Y2b/xka8isif9cxJP3vxBZUTgz0m8wBfQwSzj8xcna8U1NxccnXWcyTHeBpYqRIgjwTZ5z/pn861OHHsVnu2CE+t8jyfyUH5rg94oazvKaP7+J8DvkNzuj+uSF2q7zEspvxe+k9lMDcf3s33w2u4E8/2IXE4C5jTh5Wmp8hQvBB2PTK78sg1BWj4nH7x+H1GnGGmLIUK4EPm5868+PUQ5xvwv
*/