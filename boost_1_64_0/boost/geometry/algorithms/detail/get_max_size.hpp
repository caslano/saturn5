// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2014 Bruno Lalande, Paris, France.
// Copyright (c) 2014 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_GET_MAX_SIZE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_GET_MAX_SIZE_HPP

#include <cstddef>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename Box, std::size_t Dimension>
struct get_max_size_box
{
    static inline typename coordinate_type<Box>::type apply(Box const& box)
    {
        typename coordinate_type<Box>::type s
            = geometry::math::abs(geometry::get<1, Dimension>(box) - geometry::get<0, Dimension>(box));

        return (std::max)(s, get_max_size_box<Box, Dimension - 1>::apply(box));
    }
};

template <typename Box>
struct get_max_size_box<Box, 0>
{
    static inline typename coordinate_type<Box>::type apply(Box const& box)
    {
        return geometry::math::abs(geometry::get<1, 0>(box) - geometry::get<0, 0>(box));
    }
};

// This might be implemented later on for other geometries too.
// Not dispatched yet.
template <typename Box>
inline typename coordinate_type<Box>::type get_max_size(Box const& box)
{
    return get_max_size_box<Box, dimension<Box>::value - 1>::apply(box);
}

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_GET_MAX_SIZE_HPP

/* get_max_size.hpp
qOezpI2Fzwc9gI3V+uZo9JUG9e2cKvbrmI69Px7tjH0lETcbcdLuar2KKbt8UMX3q3jDo4wfBF8GLsOm7mV5i7NhyBptT8QNI/ysSvucCqeFLCVvxYr3pOJd++1pofMbSlzZ2pTO7+byuTw7Ed9LcMnTjpJguA/xgke7Z0DL/3yfR4x1dPxr0e5NWlmXFxJc475O0OoPofUGUd4l2X4M+oi7ZJXMdD/2FsjD6J32EQzsrap9vA34s0PwDczorMS/uErUucI3sAfmBvu4S6qC8Vp/LxU6pekZ2IeKg/TeVxWM1zL8AMXrcXCJGgdfVoX7JFjv+GP8qwLj2eneh0JstJ4z+TDhSP9Q2sNrStT8lvJpdDk+JmgVq7kC80m/8BOQ4QboeIma9yiRc0Z55hA+LW0heEA805E8a1vzecHzFTxed/NPGfaNHM9fFPIsXRQ+P/ZlJaN/Khl9xfexQUPy+jXwfgzbY1l/Tncy+g00kV9tSJ18S/getXnkeG1AV7SscN5dle0Uldf1HA8aem4L5dspyifjrxJ2fKea5/gh85ctp5b9TUJ+ul0amObnp8A3daTxDaxL2YVbqoLxbar8t4EerdODHsqDdi/Lcwf8hmfmZv2Gu5TfcLfS5V9w/jaOy0+ysPnfQ7Dwddy9yxtOidpHIOV1gAqK8X/+9CFpTTr2qa7gOUejP+7LKJ/qV9zmbLycY2XcK9DmDnK9s8+scOgcpNJdlafF+S3LTsQL3/kQxcsyXA07nasMv1N2A3OLXA5pN/+g+Auz739SOMg/gPOIkgXbKCGLP4v2TjDNP7f3vzCe1U3Ug6SHiwi5nGwbGV/X1VPK/kt8jfs0fJD7ofNC9hb/71W5Zf8PJXuZJqNk/4ySWZhu/KuK7+/ke7mk/3lIybQytH4oNiL7LMOP4+s5hTcl4sp+X1XOt3ewBi5bK4d5fueoSNBeFEaC9mI68pkBPLY/Im4W4iBPQwPv1+KvkudspJuDdCPh83h2PWuGR1N+CM+MGLEmRhJpvAdF4VKvnwApvgP2GJM3r/17DKv36AE9ukxM3v36oohYo3WyGo6nB0f5ukMByvtm3iTT2nM0KPNr/XlFy4PB8/AmoNxfHU2MUDrAKR3DzSu0DC9C2Qy2D5sHmMGU7waWYo9GI2RQImQQya8vzo8BPvolUx7uexZkdcnoFcNLlY4tgo4tjOBcDuschxm3GHGFwK2gv1rP+O0apWdVgs5C0KkrwhwW58lhbuOH5lM6fLKN10WC/e8f5mf7g8fmZ+9gpnS2zb8Y+CMcRh6M7z75LsrxEdAEH5rmy0T87Pnuk/7DkkjwTcM5gsf9wJf0lkaC8bH5QX9lmcpvv4pfjra8AnWM8lm8kyMCHzJs4jqRcbjrVPEyS/H6CuTVYPPC+Qn3m9OtovBpkMF+pFut6Oq3F9eI+JGQfNcKnkcUz+tkHaNdoD6QVt2RPsX1C+cB/55jg/Vt9EDytj4SvKd7jkfpuT7gXwv8jRHWJ6THfaMh9dMVQXpRP93c/2T5qZwHvkT/symi7s0sUPdmUnhB4G7T3rExY8qxPlFAzG1l22P3utIWmqgx7tFUPJ2mp0ZTvhUKjSF7JOtUj8nOVnV+/ly1F5fiWRaqLRZDFlFFA/HcnnulrIGvaRYXsi5anJjCuSwEp1/igHeNM6js10Pzg3qk2+nOSNBWaXkMi3qXtqlY1fuotJPMm7o3FDr37kVBu59S9jONcEr0KfJ9pDcc6+jskW0cdPR99/sItm6CffgbO9ZFN2xcu2l9q1WrsAjup89zeU6KZrsmqmPga+0HzeNDacZSvN/I/WReLhD27gSsnflvkl4YQVrCRVsL+EyvUz5T9YI=
*/