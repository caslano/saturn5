//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#include<boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace interprocess {

inline barrier::barrier(unsigned int count)
   : m_threshold(count), m_count(count), m_generation(0)
{
   if (count == 0)
      throw std::invalid_argument("count cannot be zero.");
}

inline barrier::~barrier(){}

inline bool barrier::wait()
{
   scoped_lock<interprocess_mutex> lock(m_mutex);
   unsigned int gen = m_generation;

   if (--m_count == 0){
      m_generation++;
      m_count = m_threshold;
      m_cond.notify_all();
      return true;
   }

   while (gen == m_generation){
      m_cond.wait(lock);
   }
   return false;
}

}  //namespace interprocess {
}  //namespace boost {

/* interprocess_barrier.hpp
jnaO2uWAb85HvUk/VR7Qsa+tyE32vJuvDFy+zx+TtoDyINths9Xm/+8S5vNWV67QH1loxZnKhLjD+QyLlNdZ5+zk/BCrj3EO0g3vznEUrSytNHK+u7p675QnweGBHiHjs8WMvcU7tuqW8gym65qDXqLzUfIVa12i93JXgPEwym5sis3rP8UK5/VPx23ndWqqcPtzr+x71jp3c4jz1C7j3m4Zh/EgUl7qFwzNu2gZeOfG4gy2/WmUQd1LBtt+lyK43RzBJw3Xe8zmYDZdzzFWj45PQOJQW/WJvVq3Va9/qf226qTFZ6vONcNs1d05vRMGXoGv2nzMLzW3Vb/sykkzL541dXa4nf6hlFa4FDx5XxqFnX5jB/JOWnx555qevP9/ze3tl7m9lHHfeuisw0MaB5ze8w+vp1w4q3Nu74M8t6fr3KRv1335eWa7x1N0nu+viM7X6HOedwnDfE2q8mimgV11XiVN51OydD5lCJgNngf2Ud7IvjrPcswWjf8BjR8d65CzblH3qtZ4L9X5quEa/whwoM4bna3nh+p80QidL5oE5oFTdJ7oUrHz1r2tlddzHLhEeT7LNJ7lOp9YCU5Q3tJ88DblS/2ozi9u0PnFT4DTwE8rX2qNzoPer/OeWzVeh//ypej2jK+PUo++0TwPpXvCbu+ch+qch3qfzUN1zkH9789BnYr5p+PMK6Xdxr6ZyAJk/W3/3Xmm9+77Xzji7AGADn//T0+1HO6zQv1e6RJoWpeTAG61+f/2+Pn/ilaWLKossYzcf6kv2PpBh/vuWgnf1cz9t8d9l79XxhLcNaAh7sCrROddM+/fnui/fdE1cAS637Xz5PxzPIeXsU99V2c8o7vkJ8bK1jX2W0TvcWs+sS4jF2scXSwdRHekMy5gud+sTvl83Q5PWBMX4d/1XPNr3e69VhgnofvtXii6P7QetmJ86QnjF3TuzRIJcyQ0HiP2AhfLngaDfPt6ZXu4/0pT0ImLCQZ6BBO7+PgHXd2xId2uE4OB0mBiTCvcgwvQX27rdynw76mgOlXozBBbj6q7wvZUcPdFROfWJj7BVyKNK+1WDkPiqXH5vbw6uNHp37RH4lu+eHALf3qq8BLCR9j6fnRhfITONyV1H7db9yOPZaitjn5cT0Z66hqmz9pr+1/wt1XZW8OuKvp9vVrWzMo5U5skjuj313B1zftmPPuC7psh40mhPTgq2SXPcvbhsMu6mAvPI09j5H6c67/3qrMuXu99coZxP43kKMb+7Pz31vyb9tNI8e6noWn17gVXp2vzR+n78khkG3FaP/OXvQ5raPtzyz3Ut8RLmGGm+0B87lhpI/lem6B1sXtypHFQ6mDbxkFJk1MWMg6qz4Ljuv79a4GmOnw/+AkSnG/IIyNlzZ4D2Zq32aJbHUjm6kORIwh8rFw3FM9IN7/i5z4L4jPtq5esrVxYUVS+YpWzx90zopMdKLeSmvefGu8Ncn5lwNTf9XLOT5BrjOkVusaiFTd5xm0vF52NgSB1dhDyOlfS55PqF5H/VU4d7/eirX824eMdu6k68esu4d7IcPIihKOhtJSKTobGE7DueTE0bn4O92G+tP8vUPjjUL4kVUSOZypeqmj7HwRv0XGtxFb2S31OrmNdv3oVOeFNY8XqCvGva/K/blFx0421/P2Vul2bFe/Y+Xa1PRit7SIPuc1+f6g38gf73h3sYrpSdM8xvyvUa/3QfnczYWeR9y/3ar2+h+fDy/m6vZvf7vGbdl9qTvfCUrXxSImTPRhXV5rHKQnv9o1jJJ9iuuDUm61yPp3+O2DuW+ubj1te36v1/T9D7dpOW29NW6iPs9PQW9Pgbevrdf+8PhpRNrLG5rytD58=
*/