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
/2BBERdVmQ6zaYilfAF61KnSru8Vyp9nu6mLzEzp2N9k2NVFXKQbCk+0BrM+p/Po5qIsET85urk4i+Kuvn9rtCGUJd4pxSS6uVxmpovMTJmppiSyM0fai3WWaVOsKI0EIAJNU3IFQmYj80SRyCJKhkUewCScqYeCNklEIC5+WJ0mNAiWgR6z9SegR2JeKc7o/wfAHJ/11+CM8f1LkD9vpkiX2wp1VDN/BqlC5XSGq7pmjKddTe1s0OP5DxT0+WA=
*/