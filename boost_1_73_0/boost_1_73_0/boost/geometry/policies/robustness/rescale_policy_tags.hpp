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
b5XabHqeP6bEgVTd20EtKu3J2zKslWPCutY5G88FKU8F+9zpJTbaUKiYSl0zjc4vribTP1JaVzqvBGRrW/KVbeuCKnXD5DhnfdNhNMoFsiXUAV5oHwDYBm1ND7aZAruVFwwxr2pvSd0oXaslDKlAVQiN/7Xfz1tXw/t+YXPfz+/C71VhdR/JFZxYqS3ZJlCw1HpOSSRTWtlCl/IGIThs2mWtfZXuvYEpU/StI891LVjQ0+w7t5nmO3pSEaMGHusgL2+NF1Pryq5+EASPglK2zsAQeIBQYUFzSi3ayEXhGPmdiR2nkeD/Tc3e34KsgTP0ajinyfwVLZXXPqUvk8Xp+eWCvgxns+F0cUXnv9NweiVgnyfTE6Rew5gj3jSOPYw70qum1lzsbL7c008OdCkT43I+zk6vLsaz+0ERJ8TJZD78dDaOkyI5YIMMJaISp8xjiYQ34MsgMcYHAg0tenqEosgq5KRGTA83mQu+GSSJ4OS24O5SDjOUo+eKFbJw+BCGld/ScaGCQtVUytFxJ3QEmAOuPWOYSQKkMAuS8O6ieRJ6k26PYhjjbHq+yD5dTs4W2WSa7EIlgD0KUlBhRbIVtyNrDEYXWoXEr7veb51jE2rUszX1Vuq8oBKZDE7l37S5Rq/mFllllPVscRF1
*/