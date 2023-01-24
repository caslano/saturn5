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
afLp5WKRWHyV5cin9iZxRdkJGVjO6yWUPme5xX4m/R4rNsvd18hUiMnnCjVoXqeMJ3da0grwMPaREKnoJNxeJN12ZuJ58rOskjDeVN43eZVDwetgh05wjAdrLZivVAGUm59q2M8VSu52yIgnZRRJoG+D0fnOgvfA1uj0sCDbf/l7cCcwq8MovrwYP5NrvKQ8G6iSyu3O+TGdAVRpYx3XnzBd53pAsbXzViV0560VB7mmzkDX5LH1+/qTOXYg5l+K6kRs9VXZsrMxZPqL/lZUpyAmRboq6CHE0op6rXeiGNXJ3t4xdg/BOPuatByeNxw/8llnsjnbaaSnIYCNvDB2Jiej7v3AIldz9ByNHE6qlOn8Qvq11XvtoXcmoZ4tb6kOHwS1VyaZj61Iax+//lhkoU/pyXIL97UEu4Sif013MZBF4/fa4/HAhWy2LwrCRHqxC2Y+PqP5BlMVY4FsA1GQDhm63gKPUcC07C3jZyXgbjDXM8qlVZB04YjJwwmY5VK+sKy/uH808V7/ktl00OSWw/c34aGgJcT8NHirqe/DOG7dxxHcQnzWwF2vRGrBREDyZwrXlPQb+Kerd0GaL6M7tIRyNSu3A06UuOEeIvPlB3HvhBLlTwX3UxMFqJZux8Y9em7j1Q+a62fg62qaFBqXq8RZ+mqUBXeNsrRloNNlzeMUNaEyF2q/x06ZHYCBMnH5MglbPHk835iiRX7j
*/