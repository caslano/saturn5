// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2013 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013 Bruno Lalande, Paris, France.
// Copyright (c) 2013 Mateusz Loskot, London, UK.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_POLICIES_ROBUSTNESS_NO_RESCALE_POLICY_HPP
#define BOOST_GEOMETRY_POLICIES_ROBUSTNESS_NO_RESCALE_POLICY_HPP

#include <stddef.h>

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/policies/robustness/robust_point_type.hpp>
#include <boost/geometry/policies/robustness/segment_ratio.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

// Redudant later.
struct no_rescale_policy
{
    static bool const enabled = false;

    // We don't rescale but return the reference of the input
    template <std::size_t Dimension, typename Value>
    inline Value const& apply(Value const& value) const
    {
        return value;
    }
};

} // namespace detail
#endif


// Implement meta-functions for this policy
template <typename Point>
struct robust_point_type<Point, detail::no_rescale_policy>
{
    // The point itself
    typedef Point type;
};

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_POLICIES_ROBUSTNESS_NO_RESCALE_POLICY_HPP

/* no_rescale_policy.hpp
oYU57aHH8/6JwdDxFeGAFaRvntPEk7f81qa+EemZ4wkXV4sx93ufDYeyhjigfp1ex7vqw2L/WUZI64pzU9zmgL1E13fPPzq2bEoxempIwFp+7AlBf5YhE+wICoy7AiuTaPEDjnVYyhAe8cGSLdaZdQCX8c+fD7WMC7rj1sTNA5MXGk/pkmGslMjMCLaGWUhmJ53F31dkSf2CXCFUOXnb+aWOWAK7wtuDQ1AOgPx0nhs796zmifbsne5jZ2T5qVd2a3d8DvStQo5wUdrMnxz+D8Sv7N5Q9Kn70+PH5VPF008riXgAnpVD494QacpC4eHVfqCF0nWopFWhw5rf2klNYECs5YOZEkwHIrCwKR+gWJP3qL7nNCo843FCedoOAkDoIRYNDbPdf/m2S33du27sLX/z6Oed4/+GRPM0HFQDoobwQjy8qekzPUlvJUip4gaJfEhPBJGqgT2jqvLXfwku67vnBGk/la7KWsvIEwxHTxMCFel/vbOmwrwp5k/+qCCnHEIUtHzjbK+fJUNPw0DoSS5s8JmVOi47nXY1Bq9VO6ZA8Taxw8KigGewEDdGYcnZm8eMOHHkazEP69SNxTElTiTDsW1pAr2B64Fs0fSngN4rcvDgvHSKrDdrDtKg7KkpXbDMO32BXsqGlBO5kuQE4tkwZ40hDSKvas+NtN8KEZBfKbXFgGNZMgGLHFnqtv7XMtdXrY0oWT/5v3Gf
*/