//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_SMALL_VECTOR_HPP
#define BOOST_CONTAINER_PMR_SMALL_VECTOR_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/small_vector.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class T, std::size_t N>
using small_vector = boost::container::small_vector<T, N, polymorphic_allocator<T>>;

#endif

//! A portable metafunction to obtain a small_vector
//! that uses a polymorphic allocator
template<class T, std::size_t N>
struct small_vector_of
{
   typedef boost::container::small_vector
      < T, N, polymorphic_allocator<T> > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_SMALL_VECTOR_HPP

/* small_vector.hpp
a6kWuRZb7wZD6+cs9ywEyYKw1wpNUScTLe6tA9xAfUG1cEz9oBWinE8yOogPvFcz8s+FVmi2gk7qWF8dBMKXeUPauObez00DWggDvnYE4KTdblo1RKBSKsx0dxb43gh/85Op+efrx01xzoKyEAKhsr50D2d6f5vxZJO9N/4eg+NXwDvGdpus8HRzQ1l5CmA5Seknniz1GKPIXcGqGZAlKeO9dR59/h6O91ZZPnKZe7sTzl17gMf2O5xe2WKt2GZ9sM2NyfMUKNbyFZ4tr3G332dqDV+4MmErTUgS6Hc93c4auVkKPn/sfW+UovKKTz835tPP7cOgS1oYyqmll0KZHOHlm47bj1/kZDbgZjFFtEOrAJWVAodC4/EoxAh62ufTn5mw+1DF+9/4AO87mfDs+hMcO1byxc+cZvP8h3jzT3+G5c3/g3zlwyx/6V6e/PL11u8SQ321zNSdhtWCQM8pgZZbMJck5A6+RwLC9M5hrYm5AI6q1FSVITHBPzLUpb8z4Z31BYifVdU8gUBL6A5EENpIoKbko7Qv9iAM7xfmTH101eZWC4U0Vz4UNYTL1dC//hcmJFcMlkZsHglpwIdFAOq4/3Q6jZ/tQA7AiweveOsVEUD7Yp7F3oD1687VpASNkvDisc42msqLY3e8fYiQHyb4sxu2qCTqG9X+LLMindmBSlo/moBE5YTAiY0f4HjyH1F6xY17f4t8+SK2
*/