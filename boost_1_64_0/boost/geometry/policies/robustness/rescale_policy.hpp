// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2014-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2014-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2015, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_POLICIES_ROBUSTNESS_RESCALE_POLICY_HPP
#define BOOST_GEOMETRY_POLICIES_ROBUSTNESS_RESCALE_POLICY_HPP

#include <cstddef>

#include <boost/geometry/core/coordinate_type.hpp>

#include <boost/geometry/policies/robustness/segment_ratio.hpp>
#include <boost/geometry/policies/robustness/robust_point_type.hpp>

#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename FpPoint, typename IntPoint, typename CalculationType>
struct robust_policy
{
    static bool const enabled = true;

    typedef typename geometry::coordinate_type<IntPoint>::type output_ct;

    robust_policy(FpPoint const& fp_min, IntPoint const& int_min, CalculationType const& the_factor)
        : m_fp_min(fp_min)
        , m_int_min(int_min)
        , m_multiplier(the_factor)
    {
    }

    template <std::size_t Dimension, typename Value>
    inline output_ct apply(Value const& value) const
    {
        // a + (v-b)*f
        CalculationType const a = static_cast<CalculationType>(get<Dimension>(m_int_min));
        CalculationType const b = static_cast<CalculationType>(get<Dimension>(m_fp_min));
        CalculationType const result = a + (value - b) * m_multiplier;

        return geometry::math::rounding_cast<output_ct>(result);
    }

    FpPoint m_fp_min;
    IntPoint m_int_min;
    CalculationType m_multiplier;
};

} // namespace detail
#endif


// Implement meta-functions for this policy

// Define the IntPoint as a robust-point type
template <typename Point, typename FpPoint, typename IntPoint, typename CalculationType>
struct robust_point_type<Point, detail::robust_policy<FpPoint, IntPoint, CalculationType> >
{
    typedef IntPoint type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_POLICIES_ROBUSTNESS_RESCALE_POLICY_HPP

/* rescale_policy.hpp
QWYfRRsnDzccn8nH0t5qp4lVF+pUxlQHB4M9S4SQvinsF/UKcy7X8sVaoIrYm9VHz/CvMc5it7v4SGM5oPuunw5lwWUnqietcbw/3uKmU8+fQP8mOWy2USZ6gqgBzJI0TXKddtk4pcnDLqmSKHvFcfIZvMbFyzLDIf7RDXVW3Sadvg9LnpSzHbmrYJl7ZpMfe2JxQRyRPJJitfSV115nh7a7dJgj5huWrvYKO6/8RP2QMtJwlXV+CaPPszj7kOV/1AmiD/fTLT+FK9stur2jQz+QT66NQx+wnnzmGosmSjo+uv9gAwY9Pl/qx4yN4vB/7MAo29p22Bi3LkMOXddFlREAi261+1Wr/MrtJDrVZZuEoUfj6D6sV4qZB0ESpfSldnUp6H46v9XxsGLgshV+rdTzkesSko3rMm1bLf2Yci1OTOk0V9aQRvlbT9EeJTYN+5WRHjsQa7fpQa6/WUPJUPMreDFKMEkHJ26PcABWOx6pNFNkG/Gn0duF49T/wwZu4kG4sdF4bHMWq4phN7iyycUIeT2PM1DGjHgxAsKy4hVbXYzpS8hlOtuPW2xHhWqSfaQfg+bt5/W2fhyeDkG5jPOWcKcPMz1nYt62xYeJ1nSa7x4+qi353HGzi1He7LL42Ea2V9gflstuY9X6Rudv/TjRzRrIOuGwF8cyr5+OhiI2hDu70cWp5dnZixb664poanOdaXWYpeVLt7/8U4WJIJVVTiHqGZdZsqPF4pfnIyz71R/ZHIddXJ5vLCCOIWNnYvmKE1xZDLbJx/IVMNGZht4zGGvLDkNWi2M9FVpB3GLnM73rOBicUS3PtkWrUp5nXUxHgTCClEcL+zuaY1u8jvNY3Nky5v85l35C21h5L33eg1FKyBLtWQ09tu8VHvQv6XVGP/he9KE8N9o4tpswr3MOL+1Ry7GJVNk8vFz/tHO8VopA6BgV8G7ssc5xZadNrwZVURzWVzf306EnPSZy8kiwzWGnH2faci/3Y1RxEaNVy48dBqbWWIZE4ztz11g0IYfFA7c8JrZbdPh4RKqP5j1qp0c1+b7XeSstPQ/Bd1KstFFc6uPT++4+fkC47M3hxQmcxqAPNT65Gn7f6D0EXpftkpV/1CyadsXmJRYCvl9l04RdhvvEolnyrku2azvfY/O4SDtvnPNdcOgdAEz6KUP+8oucxtmyTSf/SPIrcehwStRWti7Z4HfamN48mnB+6bjpn/cKi499Q9rcJyQdnHubGZB70BprYflWtDmm32Zi+Ea3hbnkYtiQyPLKxvCNcgNzcauDgfueivXA/WXIBH4JleUB4vXZdKmEsUw86JaD7x/zeb6N0b5C03Q2vN2iq9u9TJ+x06tQREx/m5Ne9fa0HvPX2u0gnfvIF8LmrfuL0/bRH8PnkjZNiVu5arD8dvJGybSZmn2LLD72bXzzHK7Qh4sfi2dcrGecnXUxnjF0wSq/Urqg8Jlj6LzNR8voWfLnc+mdedVKnM+oi6HQHYw5Y/czBBv+Al6wRrAPus1Ht3WLbLY23Y0uwOfeFs56LYPtgDbGfZic9/0OjqMu8T464cFEDcmYq45c4yhMjLlg7OFSkw+qZVREjEcsHGNbZx/GjH0BJMYR6cF92AemilOkhSyM63kSjwNz9X4wdn2IUD2l17zzg9OgNSX+OOk58XjbzsIyK/KBFp6b4la8uSfc5MPY94ESPj6RYyDvvXbYGFnyBXklmc8J3bzqmalgCpvViWItD6amDSsh4z8+0Qgo0KgdqlSgTB+qlWWAdm6Pp94g4isA/UEJ+F7L6QeK2GANueETo31JBn1mPeclit7pNXHMKqJatRI3UrSPPziiHW8+WtpW+Y1BxOdQaZo=
*/