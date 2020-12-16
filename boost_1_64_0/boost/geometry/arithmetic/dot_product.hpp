// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ARITHMETIC_DOT_PRODUCT_HPP
#define BOOST_GEOMETRY_ARITHMETIC_DOT_PRODUCT_HPP


#include <cstddef>

#include <boost/concept/requires.hpp>

#include <boost/geometry/geometries/concepts/point_concept.hpp>
#include <boost/geometry/util/select_coordinate_type.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename P1, typename P2, std::size_t Dimension, std::size_t DimensionCount>
struct dot_product_maker
{
    typedef typename select_coordinate_type<P1, P2>::type coordinate_type;

    static inline coordinate_type apply(P1 const& p1, P2 const& p2)
    {
        return get<Dimension>(p1) * get<Dimension>(p2)
            + dot_product_maker<P1, P2, Dimension+1, DimensionCount>::apply(p1, p2);
    }
};

template <typename P1, typename P2, std::size_t DimensionCount>
struct dot_product_maker<P1, P2, DimensionCount, DimensionCount>
{
    typedef typename select_coordinate_type<P1, P2>::type coordinate_type;

    static inline coordinate_type apply(P1 const& p1, P2 const& p2)
    {
        return get<DimensionCount>(p1) * get<DimensionCount>(p2);
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


/*!
    \brief Computes the dot product (or scalar product) of 2 vectors (points).
    \ingroup arithmetic
    \tparam Point1 \tparam_point
    \tparam Point2 \tparam_point
    \param p1 first point
    \param p2 second point
    \return the dot product
    
    \qbk{[heading Examples]}
    \qbk{[dot_product] [dot_product_output]}

 */
template <typename Point1, typename Point2>
inline typename select_coordinate_type<Point1, Point2>::type dot_product(
        Point1 const& p1, Point2 const& p2)
{
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<Point1>) );
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<Point2>) );

    return detail::dot_product_maker
        <
            Point1, Point2,
            0, dimension<Point1>::type::value - 1
        >::apply(p1, p2);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ARITHMETIC_DOT_PRODUCT_HPP

/* dot_product.hpp
HvGZx+jqMap5i4xxsAcOSxPtola8oa9VDuKU3sXbqdhKuiQoHys4mHqMCYmFxgI0Q1Hxp+kwRCylCLD+ftPlDk1e+ow4yYPSdr8NazPTfR/KO2M/i3C/Q8q5lBl4ejd7tfo1d1yiXdoMMiU5kVE4Q3b+6twtqYbMYtDNvZ/ZwVH0cJdc07zgXGe2KzQ2yV2IM78B6muN/ebHE9SFxlOWRGlo8MMYhNRlgTLsfs24SrZV59JCq3I/De6j7eK0XBTUZmMJ6lySYQ3n1p39oKxjfQnG502/5neId97yMzVGvbFSCtiArVLyfL1VWmPd4JIzxcFrbBu+Lw+919g3yHFz82lrPtzQXzpA8pqPNrwmDwlrPt7wuoyV0DXm1vyknkLoUizikPusMHX3ATWRVdMHucpHWWx+h+zqZS0ldKMeKPUyAf6OUtilEqypQS60XwiGKhgqfUWx+HlJrJt2rJT7hdLWHtiajCYU2Jpm/MNMLCA/fJ4i97cUMB6+o0R1MKpPAgcbzLfyKT7wleauTOrb8mvv/KU5EW8+JIkVtdKGic+0bycu01DJBd1rXciwOVhpZIwLbM3VX6e79FeZArKvycLR07rmhKZaLVWkBjZ+UdyQv5J8JdfxHriG1gcqr5Pz1V3GC54Qp6Dvanl/ZJwe+fxuOVV6bJwe5G5nnwsrNe3flYUbITkQT3EUvZwSCFnHUPeyOSkxugL+PJYVUNHcnkWQjRWk8ybocoeLA0psqypJL2uUvsxuyAf06vt6B/b7fCkqg4mutbnSVrqgsG2b57p4bg/JzzzQ9+A7Zulhsq0LTSXXKkFDzbN6ZZbUYfkIm3TnWqwP8Rl7yH5BpLd3dOXU+doqbuPFHzc75Aec695pW6aqX5RchxIyatxyoiYUrnlsKhK4DQK3KZuEzygeP93A7xfxGCkf4HkGv2HoSuNleX0Gr2g4Ev57DO9nvT1r/hIeOebi15gL+X1/Z0lk/unNKRVbRWkCnKSEDX3qXTkNfrQlq3TQhaujO65/tLjNXK077eKhXNZBDIrUY79wWbzCarm+cZtUJEP4kgNbbc3t+Fyx1YbQkoEEsBn44qtSjfrmxIo0SUNm0btJcStrsGh6hFkrR8xzWORvNP7Ox9+F+JuCvyvnOb4Wfs6YOTmjDlKveUDPslugv8mDVZt/dH6WzZ+ljzXyjdweropdXKBkleOgoiUDv+FK9rcfPbjWYve3L19k6wbxsLXU9jL6LHHbA7dU/weuiv08a3HLg5y2DJMHSfJMj7FsJfndbqu0qVnybJzA/Xw2biAoH/rMdQ6xOsPxTnFkV0+iBacKOAkdzUAe9msB0XIBsPJ7CDsxJHyt13kWi86XezvoWy0hnmtfPyy3vm1V9HL5I0+T/bfL6spy2XypHp4N2rw5G8v+poVhMAVXTTyK4Km+CN1tS9i56a1eXw+X8lH1M3nlyv1iIerlaumX92upGFYqMv3EZbzlMg6BmG93FE+FDK97USssr9pSPm8lO+Nu4aRQco0KsHa4eLeQApKCUAV7gLdGinVRgoXZF/eH2RcDsgqwbwPDosTHklSSCidDwc8SvvkWnBVZnTfPtXLFImsD7FweUER0O/FBzRdHh3jU/X3xLZ+Bm3zaB+WC52JrRMvxBQjX1F5WApj3kuOlrGSDWcZJz+LFjynS4yqLKqNwh3qRKezGsRPPq0r6Yag4kuN2deHM5lU5fihRyyYes8xlmZHyQvFMi/J6c7Y6b7pObpGy/ft9Q6UAsrZqTpSn39sjt21/K7FKsXRTnT8KYUbB+YZVQr/mYM53kNvO8YbNou6sc7bO7zxrpeH4YXb+D78UBYh1cCr72LXByrp8RtXlciQ=
*/