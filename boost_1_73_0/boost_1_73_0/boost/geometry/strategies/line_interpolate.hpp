// Boost.Geometry

// Copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_LINE_INTERPOLATE_HPP
#define BOOST_GEOMETRY_STRATEGIES_LINE_INTERPOLATE_HPP


#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace line_interpolate
{

namespace services
{

template <typename CSTag>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_CS
            , (types<CSTag>)
        );
};

} // namespace services

}} // namespace strategy::line_interpolate

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_LINE_INTERPOLATE_HPP

/* line_interpolate.hpp
dRYBxwLnIV+WE+WO54kprPN8VifyH2iEPrlPAmm8Fh9NidLuTyXsRNRDkmCwVBzwHQdjFFzz3AWCh+rzuyw+kDqvz2N3VoAygU3KI5zpYYXVCbg5+NPEAsZAs09yqJnMAFlEG+RtaoO0f4g4IxGfEPqH8xIUc4JbkuiC6P55pMo3Wef5y80+M3H7LQ7qRDPxtI5CBhnrNqBzmb0CSMnGIbsO1MgOQgOLkJsTWUqdUET2wwok+tBaoYHbs0J7JpY=
*/