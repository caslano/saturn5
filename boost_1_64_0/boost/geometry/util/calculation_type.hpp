// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2012 Bruno Lalande, Paris, France.
// Copyright (c) 2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_CALCULATION_TYPE_HPP
#define BOOST_GEOMETRY_UTIL_CALCULATION_TYPE_HPP

#include <boost/config.hpp>
#include <boost/mpl/if.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/type_traits/is_fundamental.hpp>
#include <boost/type_traits/is_void.hpp>

#include <boost/geometry/util/select_coordinate_type.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{

namespace util
{

namespace detail
{

struct default_integral
{
#ifdef BOOST_HAS_LONG_LONG
    typedef boost::long_long_type type;
#else
    typedef int type;
#endif
};

/*!
\details Selects the most appropriate:
    - if calculation type is specified (not void), that one is used
    - else if type is non-fundamental (user defined e.g. ttmath), that one
    - else if type is floating point, the specified default FP is used
    - else it is integral and the specified default integral is used
 */
template
<
    typename Type,
    typename CalculationType,
    typename DefaultFloatingPointCalculationType,
    typename DefaultIntegralCalculationType
>
struct calculation_type
{
    BOOST_STATIC_ASSERT((
        boost::is_fundamental
            <
                DefaultFloatingPointCalculationType
            >::type::value
        ));
    BOOST_STATIC_ASSERT((
        boost::is_fundamental
            <
                DefaultIntegralCalculationType
            >::type::value
        ));


    typedef typename boost::mpl::if_
        <
            boost::is_void<CalculationType>,
            typename boost::mpl::if_
                <
                    boost::is_floating_point<Type>,
                    typename select_most_precise
                        <
                            DefaultFloatingPointCalculationType,
                            Type
                        >::type,
                    typename select_most_precise
                        <
                            DefaultIntegralCalculationType,
                            Type
                        >::type
                >::type,
            CalculationType
        >::type type;
};

} // namespace detail


namespace calculation_type
{

namespace geometric
{

template
<
    typename Geometry,
    typename CalculationType,
    typename DefaultFloatingPointCalculationType = double,
    typename DefaultIntegralCalculationType = detail::default_integral::type
>
struct unary
{
    typedef typename detail::calculation_type
        <
            typename geometry::coordinate_type<Geometry>::type,
            CalculationType,
            DefaultFloatingPointCalculationType,
            DefaultIntegralCalculationType
        >::type type;
};

template
<
    typename Geometry1,
    typename Geometry2,
    typename CalculationType,
    typename DefaultFloatingPointCalculationType = double,
    typename DefaultIntegralCalculationType = detail::default_integral::type
>
struct binary
{
    typedef typename detail::calculation_type
        <
            typename select_coordinate_type<Geometry1, Geometry2>::type,
            CalculationType,
            DefaultFloatingPointCalculationType,
            DefaultIntegralCalculationType
        >::type type;
};


/*!
\brief calculation type (ternary, for three geometry types)
 */
template
<
    typename Geometry1,
    typename Geometry2,
    typename Geometry3,
    typename CalculationType,
    typename DefaultFloatingPointCalculationType = double,
    typename DefaultIntegralCalculationType = detail::default_integral::type
>
struct ternary
{
    typedef typename detail::calculation_type
        <
            typename select_most_precise
                <
                    typename coordinate_type<Geometry1>::type,
                    typename select_coordinate_type
                        <
                            Geometry2,
                            Geometry3
                        >::type
                >::type,
            CalculationType,
            DefaultFloatingPointCalculationType,
            DefaultIntegralCalculationType
        >::type type;
};

}} // namespace calculation_type::geometric

} // namespace util

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_CALCULATION_TYPE_HPP

/* calculation_type.hpp
jDWX/pHeMYyyjjy9fflkHcWpMlalLFh+iyR0ImwidGc7dkQZtoPEau8/KeOBjO8IN44ZMMx/EGFS/nDsp5Xf2OczWd7Rv13qfIvUeXq0sazeyq5bXX8W3bC69tYr2ZnWv3GMw7dS/ucInQk/JlxN+SNjtPITSRlfJ6P2LTm22utd+pJKvi6Zm1L9O0sra7gyjsQzmEzKKutc7nXGvs7SR8wldV1IuIP/CBmuL6vWw7eeZcyoUqYMyd87NvzbZubvLt8z/OK8u7xSxuKvIXQjlLglfsgw77torXl5GfRlVYbT1Om85tiqUgdpQdXH06Tjlcq+c+j642KVc914rshxqtVpUZBs0xB1/Kk0gpkt+YwYSvzIft5tYlM821Fa43a0VcZkDiae7u+KQfyNoe737Sr/3ScxaXhUkKxL964bpq4b7l0Xqa67baC6Lma0uu7xAdq6aHVdiXedll68ti5ai3u+v7ZulLruV951I9R1G7zrhqvrbvSui1HX2bzrtLJEetdp2+GKUNdFaelletdp6Y3wrtPq6tw12jotvTe0dcNGqusqvOtGBEl79qd+6rqRnmOurMoxt9nkmNuhHV8MiZR1u7CpOp9tPY/DqdpxaONAlDlitXLY+DJgfrzKuFc+p823op0TvcIkD4eMMdM+R3Kea03TDoc5b0+3Ut7jJceg9t7d3kr7x8Z4zgvDuWGTsfw/lu3bRbjCfW5EaueGe6RWPds5q9SZ73PypOR7n+R7t+TrGKrlyzWt9rYl1Ni25ATVoT0oaV19THx74lf21fJ2FLuKat3mUGPbrrVZUw1trvkYwHaGcR4FhvJFyJh0d1/e7mJbdxvcWyufkzEvdXg3s9I+denrbZ/O9NHOG+3crPSu087Nn3nXRWttkXeddr5u8q4bpp6Hr/fW2jaZx8l4HmZr7w4vLDa8HzpI1uUFmY6D0cbPK+dDRpDU4yDv54K6Vq1rBiVRWUWFBbK/9OesnDurW1NY6nwaf0/3bI92DMk4IFe+HEOGa3WyjIn/hgjd8Su8jLTLwrX9JGPs6v4e7Sr1xHFUez0ZttdHnUTUo06M9cz5I/U0iDpKvFypp3d71l5PA6SeDkg99ZJz/SpCvzDSV35jdY/lqfP4/D6eMllSieMZizNyhPyOGmYYB+Nz3EljzXVsPg7D97gW8/EQ9R/vYj5+wvc4CfNxOfWfO9p8nE39x52Yj5vxNR6l/uNpzMfx+B5nYz6+x/f4G/PxT403buZOTz33PRO5fNe628qe+77HU1e9HnKrr/FMvsfNSH8Tud/neCWUV+lvMkz6U0VhS4xG4rFS7udxp8S7HF0S72XpB1CBg3E/TsFXcAYewAz8NdrwN1iCr+KteBDX4mu4AV/HbfgGbsc3tX5Hcj+OW6Qc3n5HyriZTvgRRuJpjMEzUo6P8Tr8BOfhXzEdP8M8PItL8RyW4Re4Cb/U8pd7bNxukv/bUg+/k3r4vdTDHyT/d3ERHsEcPIpr8Bjege/henwfN+MJ3IInUdkPco+Mz5nsh39I/7B/4kD8Gq/Fb3AWfosp+B1m4Pe4BP8l+bvHBd0FTXAnBuMubIo/xmao9IeT+1/Ju7xKf7iWfC4UW+NAbIPjsC1OwMtxJrbDdGyP+RiChdgBpR8f97n6ftkX/h7rEDmO10i59e+x3ko9dMPt2BsfwSj8kdTjo5iMT6EFd6MVn8GV+CyW4HOyvyqayj2l3GOSn+c++4WmcrxK/8uPMAI/xjH4iZT70yA5TjEXP0Mnfo7P4d/wJfwCD+OXeBL/jufxKwwm8/MYgv/ELvg1XoXfYV/8HhPxX5iGQZT/NgzGu7AplmFz3IwtcBu2wifwMnwe2+AvsC0=
*/