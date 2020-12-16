// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015, 2016, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_SEGMENT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_SEGMENT_HPP


#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/expand/indexed.hpp>

#include <boost/geometry/strategies/expand.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace expand
{

class cartesian_segment
{
public:
    template <typename Box, typename Segment>
    static void apply(Box & box, Segment const& segment)
    {
        geometry::detail::expand::expand_indexed
            <
                0, dimension<Segment>::value
            >::apply(box, segment);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<segment_tag, cartesian_tag, CalculationType>
{
    typedef cartesian_segment type;
};


} // namespace services

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::expand

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_SEGMENT_HPP

/* expand_segment.hpp
wIm4EG/G29CGizENl+B9uBT/gLfjRlyGT+MduB3v1PtLlb5cUJrCm/pLnS77bQz6443YDWcY97vm6vTjLPLlE8nnT7E3fib5/TmOxJM4CmsM87PL/MZbzK+75EsgDsRLMAR74ijsheOwN+r7ncxvisX8rpb5XSPzC5P5jcYIDMcJOBbV+lj6MsFki/r4HlnfldgHV2F/vBfDcDXegkWYgGsM32mvlvneJfMyfqf9cZnvEzLfLTLfJ2W+T2E8Po2L8RnMx216PSt9juAEi3rWLuX39zgQszAEHSjXBHo9f1zm08ainu8v5WUAtsaB+vKlfw+4w2L5RVI/r5H8L8Y4fACX4IOG7Vkm85lMlLptzyPy/ff3sTN+gIPwQxyLRzESPzKsj/S5QVrZDsbvycv27CDbsy+uMkwXJ9P1sZjuPpmuCHvgGsN0hT8z3UMy3R9kuocN01XKdP0tplsq++ft2BvzDdN5XSj7t8V0d8p0BdgF79KnI2S6thbT2ZTqEJNk+tmG6aJkut4W022S4/+j2As3G6bLk+lGW0y3RdK3Fa/CJw316HGZLo3/VTcx16M3NFXLw40YhDfjOozFFzEeX8NZWI02vJj5JONwTMFwTMOpmI6zMBNnox3PSV0g/R+wz6npaIEztZvdjNcVr8XeeB1eiddjFEZiCk7APJyIa3ASPo6T8UmcIssr9ZI+CbBIXW9p96X+ZDZR19uOgZiFM9CBKTgPc3EB3omLcC3m4aN4O27HO/AlvAvfwhX4Ia7Cb7EQm8r3HdrgGhyDJTgWN6CSXpalvtuP+yV/WmKapLdC0rtb0vsiTsa9GIP70YavYhq+jtn4Ji7At3EJvosFeBTvxo9QrbflHXqcLcs31tsXkq8dsSUGYWsMQz+MwnYYh11wFl4k28HPW3vfnXWW7aDsZz5yT/IHb3W+f8cg/AmHoLekvykuRR9cgc3wQWyOm/AC3IK/wzJsiS9iK3wN2+AJ9MOv0V+2SwAqaeiEv8Mh2BrD8DIcg8MxHK/Ca3E6RmASXofJGInzcALehhMxDyfjKpyCazER16FNzW9WUN6rV9NCvqiv6J6X/H5S8uUpyZcytOE2/D0+i8txO67B5/BBLMfNuAMrcSe+jhX4R9yDH+Je/BZfQW8SUYXN8S30w7fxUnwPr8D38Uo8ivH4ES7CY3gnfozL8RN8FGvwGTyF5XgGq/A8HsRvUcq99j4878d7lvvPyK8APIG98AuMxRq041e4BL/G1fgNPoLf4nb8K76MP+AfsSnl8gj64Dn0baK/Y8475+ryr1bG1/vEVbfDFAzCaLwJp+MsjMEMvBFz8SZchMlYgCm4AefgU5iGb2MWnkQHXsiy5mJbzMVuOB/74q14KS7EK3ARhuFtOBoX43TM479bcAnOwaXowGU4HwswD+/CFXg3rsUVuA7vxwosxlfwYXwbS/AobsRj+Ah+jpvwG3wUv8dS9JLvsbTArdgRn8RAfBp74bM4ArfjKHwOJ+DzOB3L8UbciXG4C9OwArNxL+bgy7gQX8ECfBVX4Wt4Lx7EdfgmPoZv4VN4BF/C9/EkfoBf4odyvKz11t+J90qX8jBSuZ5VBsh1ZlsMxUAcgdPxKozHUZiOo3EejsXbcRyuwmvxARyPH2IkfokT8VuchD/hFFTqpRswAKdhL5yOQ/BGvAZn4Ci8GW/BWEzDOFyA8ViAs3AtJuBGTMRNaMMyTMadmIpVmIaHMR2PYRaexmysRYd8p2E++uEC7Iq3Ym/Mw8G4BEdiPo7DOzEaCzAO78I0vBtzcTnegStwNd6DRbgSS7AQH8P78Fkswp14P76CxXgQ1+GHuB4/xT/g1/gw/g1L0Lsp5Rib4mY=
*/