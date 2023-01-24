// Boost.Geometry

// Copyright (c) 2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_UNIT_SPHEROID_HPP
#define BOOST_GEOMETRY_FORMULAS_UNIT_SPHEROID_HPP

#include <boost/geometry/core/radius.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace formula
{

template <typename ResultType, typename Spheroid>
inline ResultType unit_spheroid_b(Spheroid const& spheroid)
{
    return ResultType(get_radius<2>(spheroid))
         / ResultType(get_radius<0>(spheroid));
}

template <typename ResultSpheroid, typename Spheroid>
inline ResultSpheroid unit_spheroid(Spheroid const& spheroid)
{
    typedef typename radius_type<ResultSpheroid>::type radius_t;
    return ResultSpheroid(radius_t(1),
                          unit_spheroid_b<radius_t>(spheroid));
}

} // namespace formula
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_FORMULAS_UNIT_SPHEROID_HPP

/* unit_spheroid.hpp
iVHD/iqwEMGSH1xmJITI0yO3HNEaPq9jc7ZnkFDReKwJuBybK3lLRE4lZuYTfl73p4C8cWFlt6Tt8pURUPhXGydCPJ7D4RFfaLEF1MRI8rW3ZLskoqLgA4M5KkGx952dXzB5Iwj1ODkwlh6hIaEK2WV29YlbMoBV0khFxIlV2xRMCmKpqewBnEO3EOnUUupGkvuSKnewP0bbwJVYO4FRNgFHZwuzDEsJ3Ovrsb/JdBgpdo/wou4N2YGqCAoSAePatOj9srcuDs8uIc0tZvcuq9IyJJs7B0mogLDU9raw9ZtxG2dHIaubXrC1Pm/7qQkV/gRbXjOebFn0ioID/QWWtWLGof7eWPcl4FoleNfg5rwwHdwXWlz6+81inIexPjUWXNIHsaf/SBc5ZEaa/qgYtADKJbSxCjVStvx5ckCpuPJw+FxVpjQShCozIke/uzlVIU3tbg4n1uNrty0hUeqH/H6UBFUm4RySTw/k/57BuX3hRL82ZooqOxSxayyv3OS16ouu/qpP8Tr9FNNWWS0K8Nt6rjhtYge7D1f9MpdQOx4mIQBAz5lJk389+BLB7QniRMI6PcCAYuUW2vK1Mtf5mjt0CDnJNzYol0TYKA0FMSA3lgApqNjrP17SXkRvGTbA8tKJCKtNYY1ngnKKSn6S7HFhu4B3D0q5yFF3v3z80HK+1VhEXa8xmcIRl7gEglpJ2mSbUkoTNm4++G0s
*/