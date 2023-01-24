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
j9HfZOTSpxoExjVz4BXwi/faehQSqIF3rYDepW6LZaR/Cff3Wakf3TzD8sEoNMB8fqY4hmQz+cFKmVPo5uHOL5fVzce3lDQwOGkXGyNG3vSoqT/uKWhy+c70Bxok214ZAdQuBSGWDggA5x23xlXkfgQfPq8KMxVGwjunzGKyirpTQQ5nawdd7sPtW8eCcV4weFmRCCT8b/aXmDM4995+AVyjIsOuPyd/nO6HeSS9OiQUsUGnTXINnACH/JedZ37lfwFUhr6+Zu+tW1WDPBJe45VYodybaR1VV0tX3zx2orxGtkXx7gLwy5QgracB/xjuLqtyg738f8sF/6XtgOML9z/aDsTcXFwd7Li+ubm6Otj/u17A/+7v9YJjwUsqdCS0BPaAj0E4HGgNTOjosoENlHWGSBy4b9/f/ZkTKnLTbL/z/8DR6yWzR5dcR7eDntMUIvG4YJ9Nlxl8XwZQIOMVw213F5OxS+Y6XbAalVunkRcTKFMNaDre8Nm+stYO1cjPcKcDT3ldb7lMA47/tvGBO1+2wNXMnsensuP+77WtUPF7wkeN01OCxJCpUt4qj0DCR03nxOkD0mAGxdhoXD+av1uTV7kec7PRMFAx0KXLfwnPCzVk7RUMfp5DEqfkTFGGVjNvXM/BL13fUP3aN0TEDj2lCNu9UPpi9uP90q9ptjwIvYwsEoxgdSNT+mUql2A9AMfnHYuuNp2Txkkg
*/