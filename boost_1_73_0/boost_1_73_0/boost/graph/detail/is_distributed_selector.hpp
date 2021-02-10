// Copyright 2012 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Jeremiah Willcock
//           Andrew Lumsdaine

// Selector to determine whether a selector is distributedS (can only be true
// if <boost/graph/distributed/selector.hpp> has been included) so that we can
// disable various sequential-graph-only traits specializations for distributed
// graphs.

#ifndef BOOST_GRAPH_DETAIL_IS_DISTRIBUTED_SELECTOR_HPP
#define BOOST_GRAPH_DETAIL_IS_DISTRIBUTED_SELECTOR_HPP

#include <boost/mpl/bool.hpp>

namespace boost
{
namespace detail
{
    template < typename > struct is_distributed_selector : boost::mpl::false_
    {
    };
}
}

#endif // BOOST_GRAPH_DETAIL_IS_DISTRIBUTED_SELECTOR_HPP

/* is_distributed_selector.hpp
QORMvbIGpI3J7DWJni0QIphhJTZEOloG/ymGDK8xWj/o17OkSahBfBoAHg8vOofbbf+aUJcwwCpgVZFEggp3cGkNHe1qmApMadquaCRzIpmY4StjWtOYl9CetXK4b41qap9YatNZq9vriCCAoYkKdq9gcVyQeA0WL0MRhdYhZx23dhNYoxj/+EiFMCU/nUXLFPu6Csj+uyalVpZjOgG2vKb+YEH2GCVjk2DCokUEJAJ0/5xaPxe/yb7GgwN+ECC3JxES0fKhNMN2SgnSckNMNmEdMhjYnLshDusTaDcudIpdQGe4d/DoxbULgugGdg71J/2cIEdISIlMonJV3MLWav2AJiUUBN1JzBMUmkeGOvtXmepFRZ4kBCVe5qQ/VkeuBXSLAUn2AhlRpmYo/7KYEfw6a/VGHelQfh5z0jA0AVzdad0A0cjwcIfY9QnQxWRmRky0gHUTrjeXUkEL20qF7CVPIIYIoPTGb4eDizdvBfMzOtMNVI8W49JKXunuwk8ZR9fq8Va2d9Zbhf2NH41exanEZ41pTrDkTSRRfC//bmCUbzt+Zq9vN36peCxd7PEgW+fcCPA8P0S5jSRWmHtP/tQyf81IV8AAPh3myAgqvLKf5yoofl9KZ/T0B7H9DcR2VEVspdRCzuZykqkQ
*/