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
ulE/jMQTjPkn4/DKxvyTdXiaMf8ka0mI9ffR2ycL8IV4vPB9o/zx/4X4POdu/ySXvxfh9ysvscAf/38Eny5c75+U9DcVX1DzZzvhvfEyIv89sNBPH9fg1yg/gEf6L93wrsrrL/L7B9fiVymfj7v5CQ+p+ke1n5/Bxxvxr2fxcdJ1/fEw9Yux/rE53sza3wi/0zi/O/BRRvmRj1cORp+/9jNeCo8XTvpw9f8pPNa5Sx+u/j+N
*/