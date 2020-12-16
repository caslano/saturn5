// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_BOX_HPP

#include <cstddef>

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>

#include <boost/geometry/algorithms/validity_failure_type.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_invalid_coordinate.hpp>
#include <boost/geometry/algorithms/dispatch/is_valid.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_valid
{

template <typename Box, std::size_t I>
struct has_valid_corners
{
    template <typename VisitPolicy>
    static inline bool apply(Box const& box, VisitPolicy& visitor)
    {
        if (math::equals(geometry::get<geometry::min_corner, I-1>(box),
                         geometry::get<geometry::max_corner, I-1>(box)))
        {
            return
                visitor.template apply<failure_wrong_topological_dimension>();
        }
        else if (geometry::get<geometry::min_corner, I-1>(box)
                 >
                 geometry::get<geometry::max_corner, I-1>(box))
        {
            return visitor.template apply<failure_wrong_corner_order>();
        }
        return has_valid_corners<Box, I-1>::apply(box, visitor);
    }
};


template <typename Box>
struct has_valid_corners<Box, 0>
{
    template <typename VisitPolicy>
    static inline bool apply(Box const&, VisitPolicy& visitor)
    {
        boost::ignore_unused(visitor);

        return visitor.template apply<no_failure>();
    }
};


template <typename Box>
struct is_valid_box
{
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(Box const& box, VisitPolicy& visitor, Strategy const&)
    {
        return
            ! has_invalid_coordinate<Box>::apply(box, visitor)
            &&
            has_valid_corners<Box, dimension<Box>::value>::apply(box, visitor);
    }
};

}} // namespace detail::is_valid
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// A box is always simple
// A box is a Polygon, and it satisfies the conditions for Polygon validity.
//
// The only thing we have to check is whether the max corner lies in
// the upper-right quadrant as defined by the min corner
//
// Reference (for polygon validity): OGC 06-103r4 (6.1.11.1)
template <typename Box>
struct is_valid<Box, box_tag>
    : detail::is_valid::is_valid_box<Box>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH



}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_BOX_HPP

/* box.hpp
PzhL7Q+uX8HfK7f62sBwdEyOkySH1j11bCpfL4j9hN+yGK1II6JI80aJpS4stRkdy1UmxR7smyxOB9/CXLs0bg447lkfsX+LccR2N97TPl73vfi+4yDrsh/7gQs3nhes160M4zXpaC/GjyRXONbSp7vVcqjV4cL8zBnIH0vcStjUmBqT99HdJjiUH78Oz+eoJYfE8P4tgYUi/qLKcOUgIdQvSp3FOkm16Hl3NOWRMXRF6XGZXH10cVoRh1LhfGkcb1rgRfJs+VigkKdyyIYX7pFjBHIb+QV4woBzY+34TuYXdovFfvoFi7Uzfr90eRoZ3Tw8QJ60mdGkl5fZvn8d8uTcbzVf39Hy+3KcR0SP+qML1TziPWi2MZJqB6V5uAodLfAwGjVlaYWHYfd0S7LTsUYLaRqeSXR2ru9tkIX2damtFV+6eI/vA5pMuNXitm0M22HiPQyqzLvE94A8EcTNlXrlWubdGQ4oQX94r8DlRlKH/0HgbkOk7A/+pOBZn+o+lUOOyGIlHW3Dp5R5v8Ylp8Vz/qpxsNlT+pUPgiMHf1kd+v15Ci+rh39mOFKXjvNQhsP65Dz9W+WwTh3vvyqP9bqkhfRYtyy/Y6XGZ/36PYAaj3XMY3THC3XL91BYnHXK2OMsJnXpsCc4jHXI+wAZC3Tn8CcxHuhsYRRf1RXvFWSe1JHH53icddN+HzTZiL85N6r9wS+Xh3NDyDbO0+eD/cs/jzkT6KaKNRoN+7709ogn9+SF7fG2mEtfYqGLH4UcP2/UyXOlEo/eEb0ljE872oStzF0Z4nS3lx432dGoj+PSZZn+1FxweCIvmvvcf2WAk3toAsQ3bZ7OoU5I1NNTYl40Nn5qhlMan5F65ftRMjyU2/epTwsxv4NLJuTvzmjCdeMMxzsw5Flnn+c1HO8g8Nivcccqu+2uPuYdvELj9dDOScHrasarTQb2vZ/Os8bL9t2p5k9qhvcVHKxzMf0Q8jtdXkO+W5Lge1wUHK2B95vGOF1/IfrNwwJOuAdokcSCOZrEcw6POXQBubxzJeL4CWVvN0fEHHKxQZL1cmQTHlXMON/rq/J4L/TiPfFqxWnrZlNZVa7fVMt7XgOO3FPEnO6Ygx+qO7/nVeU482N99MY8qmNr+Y7X14xHln+/Xkb58inLXNaMw2dMlTEJXWHpsOVBGuG6zEqJ0RxdZFNHRZzYpo6OOLpNHRPxdJt6vsqTNqXzdJvSuZpNHRtzxou4hDbYtxtxYrtbG3B4o7VMZ13EiW1zfcTRbfP4iKfb5gadx7bZXA/VRq2KjSizcrBjK2EfW9G5ZuObVA7beKdq4+5C16Y4feYEPrSS5zLxdY/8lWHGA5fG77mK8Pjc8kkKpzEl7gKJ8HCN85QIj9c4X8icwPVxeC7Cw/u084yr58ELEc5rtc3XWcPz2SfDN5sBaD9iwdp8cWWIGT+pUG7t3SL2sRE5GnMvOEJbf91O9mXnS3FBNd4XlftCd1B5PYWX27kdvkTlPIK14zTvtd6ZKO/PUPM+6fJOJ1nSDDwCecXTInldqryqkMcrJayHmorzXUOOV1d58X1D0wqPV2bEGnmGJw+Su7ROb87JlUv8bXmZ4Gnz236tWfLkihD3b3jDjjksz4gTe4ZFOs3msF8dcfh4nr8vJMMhaxzasvqEgW2yf3hdhkeZZp2freF+7ZJ5b4x4XIUy72+OeLwi5edWDwg5oa7Yx31LJi1Zz51N9OnUubBJfliVVC+O91bBi+fsuXznCJ48OCt1dacsX5ItH+f9bS4ttGXHl3X3DuDm/kvklZv9WNJm34gMRO39mCO0+Yd3ivmObqFsypO2vlKu1PsnzG7q5vjqIp6r4u/muwI=
*/