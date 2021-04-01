// Boost.Geometry

// Copyright (c) 2019-2019 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_POLICIES_ROBUSTNESS_RESCALE_POLICY_TYPE_HPP
#define BOOST_GEOMETRY_POLICIES_ROBUSTNESS_RESCALE_POLICY_TYPE_HPP

#include <boost/geometry/policies/robustness/no_rescale_policy.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct no_rescale_policy_tag {};
struct rescale_policy_tag {};

template <typename RobustPolicy>
struct rescale_policy_type
{
    typedef rescale_policy_tag type;
};

// Specialization
template <>
struct rescale_policy_type<no_rescale_policy>
{
    typedef no_rescale_policy_tag type;
};

} // namespace detail
#endif


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_POLICIES_ROBUSTNESS_RESCALE_POLICY_TYPE_HPP

/* rescale_policy_tags.hpp
if7pSwtDW8dIfA+p4Q1KnK4d3XiRypKYGzpbJlwvBW/JmoKNsFdL43AzFCjCbQYjT5i8gxGNXeMnkXkPUOTH2ojnF87zKOgvrOaA/5hQNdqI+CBEBBlYEoYUXt7wIkGU5RFZzb/8Ifk1EwTgYJ7St4pfRgxrPppF85bvfP8hngQdqgyFt94b58P5EMK3rvNpue9BGwyHFZRUgnHLGQAj3WFE2Y/EB/bhLhNYhDjdh07E0Gc6Fg+MBNOV0Dbfco0k+RCG4AD7ZjZFWqM4K0MbyKHk5jWoc9R86Kk/99dyOcaSC1N++42LnW+1JHPH1udqCgL5dxkLQIp4ybYGjP5bqyLqIgAR7tqtJtLqV92KlpmtKssOPzm+xqjhdQGfLjxD+APq/3+cpbnn519CyYq5Gk4yM6liWIMSthQR4YDD6xzKr4iPECbyotW5dMK/LnXD/OhrHT0KTo090v1YXgkiTg5X1/LYHYrC3gGnaJnJNSAGoyXcdfpXl9OcyLNL9AblatXn3IMj2EBc1NW5v/3btAmg7T/SYT4vq/ZVgZWLPLHPM+N2/CxHcl0OLw==
*/