// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_DEFAULT_LENGTH_RESULT_HPP
#define BOOST_GEOMETRY_STRATEGIES_DEFAULT_LENGTH_RESULT_HPP

#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/coordinate_type.hpp>

#include <boost/geometry/util/compress_variant.hpp>
#include <boost/geometry/util/select_most_precise.hpp>
#include <boost/geometry/util/transform_variant.hpp>


namespace boost { namespace geometry
{


namespace resolve_strategy
{

template <typename Geometry>
struct default_length_result
{
    typedef typename select_most_precise
        <
            typename coordinate_type<Geometry>::type,
            long double
        >::type type;
};

} // namespace resolve_strategy


namespace resolve_variant
{

template <typename Geometry>
struct default_length_result
    : resolve_strategy::default_length_result<Geometry>
{};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct default_length_result<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    typedef typename compress_variant<
        typename transform_variant<
            boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>,
            resolve_strategy::default_length_result<boost::mpl::placeholders::_>
        >::type
    >::type type;
};

} // namespace resolve_variant


/*!
    \brief Meta-function defining return type of length function
    \ingroup length
    \note Length of a line of integer coordinates can be double.
        So we take at least a double. If Big Number types are used,
        we take that type.

 */
template <typename Geometry>
struct default_length_result
    : resolve_variant::default_length_result<Geometry>
{};


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_DEFAULT_LENGTH_RESULT_HPP

/* default_length_result.hpp
Fe4MhVwl5k8+MNaMATVGR88mTYxcvor7T/auBD6q4ozv280mCyQkcgbkWDFgKocREAMI3dCAqwZcETUiSiqHQSmmJNGoqMGgTYhWqrbF1gOtpWitpdYfBmotCAKeRbSWXppaaxdXLVKrhFq23/f/Zua9t7uBoGivHch/31zfHG/eHN98880lNfzh7fOKMmmEpHcFP2hoeV8pZ8HaX6K8ssg+y1sUHUIEdG3MlgDdldNz+PwMv7DVpxc4hj27y7BnOWYo+kwVxCm62ZmPeNxnUMuPnEaVxF7kT/ei4swXvpU7EXl/RmJpl0gEzHYdVBcfH3wmw8fEkQalC9wMIY7b+Bm7NVMlTFmTsFVbjYzSUq4rEX5YzoQNU6VY0aMI8RWcGd4KgPAXCy+4M1XSEs9EH3v7altm5vsLtGDSek8WE/bXkq9o0CqODr/clWMRmzFU3TIzufjczRuaYQJp+SORdTGR3XK7sYGca19tJ3qxGHI1uTr7hX+OZ9k7zH998m4zklVGH12UrC7gNcq3VOayyxU3TW8LbTZe11xuGGpBbvkF0cuJTaaVcgmhb+qWxHy1mmz+LgvA25HbbsOK3Sury7CMU7/plkjlTBETqaKmGdIEU7DWCtx+svfk4rUVKH7UAeeIBA/mtXVmbmxfPutUkOiZL55HsycT+LlzgI7lJFw0KV9Clbn7KRi+jH54P4Y9miohn2oFxhJFGo69sY1JUdATXcBl9tZGli6RbNUWRKsvc7ftDcLD3+mjkypH8V5GbFD0nEOF4XH939ooD3d+1MKNttN3jfoN52aB0aik77N0vPxi4+ZuLNCd9AQdBYY6Nf5RtgO1xPBFPDlkpidEooJOsTbuXF+Iw4Vt6qbO2NHhOfQkDaYQ3wbf9RoUCiYH0vHMuVkdaV7WyCd61F22COgxp43EHgqwww6HQ56+Ih350lxHqL6iAnBUT00XeuRIECjvzEdm76TnVP5ycA2SwOaAOgJFfbe2xVXhdDXV6oO7HS1QsYMpim9nT6aSLRgW8dgS6zieXTMTWxkQTh9GUnldmui3FLKtzbrAdyBrdBZuyFdw63KjZK4RJenKU10VMRjLZmpc/C6UpD6tGX1ghUuNmjjeSo58cRkyNkupUZvl87EylUleEamjXudkL0bSAnfpbU3eNTm6L9h9M4HSBMzSDbzBnXnl4vAcnGnM6X9tW5y4EKObFBeCiVoct4Qb0tls9bL1q2wtZauPrasssp7E1nfZepyPd5bY+h5bcTyzN1v/ytbfsjWg5RbkPP3Xn9GtRi0oqVDrtJMsJEUS33lbMu+4i01WAfJsbnxGeE0ggp5LQlSPcU1F6zTPvL/pVY0zj7EF4L17Y7elolXbXZpG1u6nwYzZfXKGyNoXSZPQg1FBHhY3XfWrz8tgRhw3C9oI51Yhj0F+NHzUztwTsqCKHOXDNTyXXQFZlUKWVXE4LyNnSVZPMx7NRYpHS/5yQb/1dTTATpTPW/kt3BvrJt4qJ0XsDRd8E3ONvM1cr0eKNVeK5Wi34/ZhppojFELuFv4Fn/1FYuvqKPUlZIE1+w2PacKsUlD7HbIS5teqSjjbVQnX1/JyQiQgofNHTsPaX9NHmPn2kxLmSXJ7skydXMMD1ApnfnNvHGN/ZUPp0ax+m5V2C98l+JB4chLOrOnOPzU1vZbSD2YlvWL9jBKpbvzkNeqkQlL4EFF+1tH6i8FOGawbG1mNCm+4yVCBxd+YxM/dX+x1hHZ7NteP9kq8VFXL80LU6HHhOVLToMHfwHjKq+nBOqOyvLGn2T7Yk4E2Zl73OIv5ks6gzkzIT1hlUazqVPTgarwZHbWT/iK0qOtgNDtnjO4Potm1G2PBQRo=
*/