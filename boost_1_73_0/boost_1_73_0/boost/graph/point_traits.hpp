// Copyright 2004, 2005 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_POINT_TRAITS_HPP
#define BOOST_GRAPH_POINT_TRAITS_HPP

namespace boost
{
namespace graph
{

    template < typename Point > struct point_traits
    {
        // The type of each component of the point
        typedef typename Point::component_type component_type;

        // The number of dimensions in the point
        static std::size_t dimensions(const Point& point);
    };

}
} // end namespace boost::graph

#endif // BOOST_GRAPH_POINT_TRAITS_HPP

/* point_traits.hpp
vmp5YeYFsz3R1OgySr00nmbXQRJ68H0WjcNFGk68IPUmYTpOonP4ES287DL0ptEs9Pb7p++7vTct7/oyGl9iIzfxyksv49Vs4l0GH0IvCcdh9IHbWAZJ5sVTqA6NT6I0gwZXWRQv9qDv0MvCZJ5iG9h9MEtjL/gQRLPgHDoKMu8yy5bp88ePx6tkBqN/PInH6eOxnP7eZTZXM3kPg5gHN168zLws9lZp2PKwZMubx5Noin9hQeDhcnU+i9LLVj4a6GoxeRwnXhrOZtgW1IvClIcdekOxPC0s5i1hxFGGf9J4kWJX15fx3CgI64itTFfJAjqCdYBCkxiWueWtFpMwocI0c9mFWFNa4NKtycc78eIFDMbbaQ+97nDHOw/SKG1577qjo/7ZyHvXHgzavdF7r3/otXvvsbG33d4BbH0EnSVe+HGZhCl0nnjRfDmLwono8/4+j7e2Hj/y/jQJp9ECpnc2OPaPu6+Hw6Nn/kHn9dkbD0v8KVqMZ6tJ6O3g/vppmK2We5c7+GIKNb2zYUfW0gp/P4tgA9K9y1fmw/M0vXyGTwsP/XSaLUV5avio/WPHP9zvjY79I634dLzIZtRCuACQMYv3OqMu/Od3e0adRZjBDLPH0UKrqNdrD07bPtXUqwXJMniMFUtqnY2G
*/