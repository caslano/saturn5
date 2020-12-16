// Boost.Geometry

// Copyright (c) 2014-2016 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_FLATTENING_HPP
#define BOOST_GEOMETRY_FORMULAS_FLATTENING_HPP

#include <boost/geometry/core/radius.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace formula_dispatch
{

template <typename ResultType, typename Geometry, typename Tag = typename tag<Geometry>::type>
struct flattening
    : not_implemented<Tag>
{};

template <typename ResultType, typename Geometry>
struct flattening<ResultType, Geometry, srs_sphere_tag>
{
    static inline ResultType apply(Geometry const& /*geometry*/)
    {
        return ResultType(0);
    }
};

template <typename ResultType, typename Geometry>
struct flattening<ResultType, Geometry, srs_spheroid_tag>
{
    static inline ResultType apply(Geometry const& geometry)
    {
        // (a - b) / a
        return ResultType(get_radius<0>(geometry) - get_radius<2>(geometry))
                    / ResultType(get_radius<0>(geometry));
    }
};

} // namespace formula_dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace formula
{

template <typename ResultType, typename Geometry>
ResultType flattening(Geometry const& geometry)
{
    return formula_dispatch::flattening<ResultType, Geometry>::apply(geometry);
}

} // namespace formula
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_FORMULAS_FLATTENING_HPP

/* flattening.hpp
k0LbDVI/4ULhBcJi4RXCgHCnsEXYK9wv/IlwUjj/Rmk/YZ6wWFguDAh3CfcKPyfcL3xC+LxQ3STtJ1woLBJWCkPCvcJh4SHhhHD+Tokv4WphuXCnsEt4QPiE8BnhEWHWzSZPFeYIc4UXC68QBoS3CTuE9wtHhE8KXxQeER6/S/pVeIZwmbBYWCMMCe8R9gr3CR8SPiH8rVDdIvUSLhWuFl4hDAh3CyPCzwkfEn5POCZ8SfiK8Phmk9nChcJlwouFm4Qe4XbhHuF9wpjwIeEh4XPCSeGJHzXpEBYL64Q7hXuF+4T7hU8Ix4VHhCfslngQ5gs3C207ZLzL+X3CfcJHhE8KXxRm3GryTcJThQuFy4WlwhrhVuEeYYfwAWFC+KzQukfyFy4TlggDwrBwUHhQ+Lxw/sdkvyIsEm4S+oU7hGFhr/BB4SHh88Ks22QcC5cLS4U+YbMwKnxE+LLwxNtNLhAuE5YIa4Rbhc3CvcJ9wkPC54WvCk8JS/8ILxBeIQwKdwvvE35OuF/4E+Hzwkmh9eMyboRnCHOFRcJq4VbhHcIO4T7hQeEzwt8Kj79D4lm4UrhR6BPuFnYJDwqfFL4ktH5C2l94hnCJMF9YIrxCWCfcLmwW3imMCHuF+4QjwieF48KXhdY7ZVwJFwiXClcLNwqvFH5EuFf4oHBMOCmcf5fUU3ie8GJhpTAk3C3cK4wKHxQeFD4jfFl4/CdNvku4TLhauFFYI9wq3Cm8QxgVxoWPCEeFh4W2T8m+TbhUWCysFjYJ9whbhJ8TPiJ8SviS0Noi40i4VFgkrBE2CXcL7xF2CAeFI8JnhUeEtrulHsKlwpVCp/AKYVCodkh7XCvtI4wL+4V7hbcJm4Qe4SbhxcJc4RnCE4Wvbpd5QDgqPCC8X9glbBHuEm4V1gg3CQuFucJ3Cd8kzEg+d5us58KHhPcLu4T3CHcJtwt9wnJhkTBXmCPMFmYJJ5tkHRQ+I0wIHxQOCiPCgKyb4aZ/7fvY7DF7/Dcf5Z5U/O9m7hpZP0+1VKd8vk+jnfPUsDvlm8Bnv3SeitSmfOfxXSmLex1pvk34Wko4T3vGDnwe0pXVpHz34YtfOm/2u+Q/cMx+l5z9LvnPOGa/S85+l5z9Ljn7XXL2u+Tsd8nZ75Kz3yVnv0vOfpec/S45+11y9rvk7HfJ2WP2+HcfjZZVJZc7S9e5tlfU1dVXqbzkeU3A7VZ756xcs87V4A66auoqahvU+4zzqjp3RUA8VxueLe6gp77aFdzmd6uA4fG5r1FrUJKRuudoTtUVwQrWAeO89uj5vUeve33eoFKXyvXkeeTo9QZPY7C6/hofa5akSff1G75GvyvgrmG3b5xdE/AG3epMs+zBQJ1S7zU1Va6sqLrKdO42fP7GBg+znllyr0/qdL3UqYmS3JcsiZxvSJaCRwYD2/hvRUM9JfmMpJvuv930u6rqfT53VVBdaD7LVdlYU+MOKLVIn3PVv00/QO5WkbkFJSWULuhyBwL1AdVnpAq6G5Jdo/YYHp5SrdTbDb0iP7/E6Aj1ttS50R1vTZ0bnanUVRkrN6x2rS1Ya9zgSZ5J73mPntcG6snPR2nkVilPf9Y6Z0Hx+vVFroarXL7GLUp9Id2ztaKukXz60n08iJR1dao7zWs+sHOKh25QQ2kes5MuTUbqFjNy7zqaotrrVm1mK/v8Aa8vSCTUGSWuqK42yytRd35mwUana22+q8G73a1OTp6tKi1zbalWibn6fNUaZ2FBSbKVP5/u0+mqvH4P3fbAdL93q6vO7asNEk1XzFu9xrnetaW+2q3WHy21e0vVFr96OWPVurVOunuLP+BuaHBVUpWr1B9Mr7vJX+GrFt930p4=
*/