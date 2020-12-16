//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_POOL_OPTIONS_HPP
#define BOOST_CONTAINER_PMR_POOL_OPTIONS_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <cstddef>

namespace boost {
namespace container {
namespace pmr {

//! The members of pool_options comprise a set of constructor options for pool resources.
//! The effect of each option on the pool resource behavior is described below:
//!
//! - `std::size_t max_blocks_per_chunk`: The maximum number of blocks that will be allocated
//!   at once from the upstream memory resource to replenish a pool. If the value of
//!   `max_blocks_per_chunk` is zero or is greater than an implementation-defined limit,
//!   that limit is used instead. The implementation may choose to use a smaller value
//!   than is specified in this field and may use different values for different pools.
//!
//! - `std::size_t largest_required_pool_block`: The largest allocation size that is required
//!   to be fulfilled using the pooling mechanism. Attempts to allocate a single block
//!   larger than this threshold will be allocated directly from the upstream memory
//!   resource. If largest_required_pool_block is zero or is greater than an
//!   implementation-defined limit, that limit is used instead. The implementation may
//!   choose a pass-through threshold larger than specified in this field.
struct pool_options
{
   pool_options()
      : max_blocks_per_chunk(0u), largest_required_pool_block(0u)
   {}
   std::size_t max_blocks_per_chunk;
   std::size_t largest_required_pool_block;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_POOL_OPTIONS_HPP

/* pool_options.hpp
1sRYC5iZGP0syU4wC7HHUm94CM3o0m7TxJiFMRtjdjArsWt2bq1DS3Np9yELzETszfCpN6DlgdH+hX2cOgWtRIqrvXqcb9lKJj4rGq1OalM8l0FrYfrXBqYSo5/v1MnEnWHymZb6t0k/b8kGZia2NOr6kWgpkh2ZctcdaOmM5YCZiH0zxG1GKwCjfQjVf3tUwXWT2DXyuslYKWPlohZi4twoWg2YhZiY12hNYDZijrCEU2hdJN+10n6smzFlmbYZGTMxZmHMxphdNvoZsMTSpXmWwpiTsTTG0iWjn+GbAWYh9pnNehAtj8RdJ7VZwFghY8WMlYKpaH7rZo5SSeKup+8lC1bNWC1j+xhrYKyJsRbG2hjrYKwTTCV2R+LELLQeMBux0y2Hn0OzLfe3t++1DkBLBbMQM//0nmK0LDAzsaVZVePQ8sFMPiO/M4X3nQTDPszSj/R7n8tSxsoZq2SsmrFaMDOx0uKuR9GaJJv93sG9aB1gJmK77uqYgdYNZiUmznWhWfL826TvzesAo222BbtPoKWC2YitiZjwLFqOZCN36bPRisFI38mx1HillNhs+rfqYOWMVTJWLZl4fR1aLRO3j7EGxpoYa2GsjbEOxjoZO8NYD2OGFdpjpoKZiIljGzSbFEeXrR1MJba9fO6LaClSm+IcC9pMKU4co6BlgpmJRV8yrTdanmR7Fz50BVox079SxsoZq2SsmrFaavIcZKyBGbNWKc7+0SvXoLWDWYj9edJtKWg9TD7DSn8T72+DpoLRNve5qz5Bs4OZiY2dmT8HzSnFLfx69jNomWC0f+Lzx9BcYFp15jPmZqyIsRLGyhirYKyKmDwnapi4OsnEMRFaPTF5/WsEU4m9/lZnDlrrSmldCU0vQeuSlsM1U1bPRzOs8m/zwRQ1Es0MZiH2xJaccWgOMNqms/qxp/B8ZCoY9uEG6XPuZoKpxMT5CbRMMDOxX8/qOxMtT7LAxNPhaMWiFmLDx939IFqFFHfwuYwVaHWacZlKE+nDjXT/DtbCWBtjHYx1MnaGsR7GDPnapjJmZszKWAJjiYwlgZmIiedxaGlgFmLib3DQssHMxO5+LmY2WoFklz84+QBaqZRPvBcwWpUUt/XYtgfR6pm4FjCVmJjXaB1M/7qlfOLYDc202j9u9P2XbEBLALMQ23ugPQrNKcUV9IrZgzYbjdSCv1fLAcNldBP9ewQwF2P5jLkZK2KshLEyxioYq2KsBkwltvVN/TVo9WAWYg9PvDwRrQ3HE+O2L56D1iXFrRrQcCWausY/X/Sspp1oVjA7sUXDf+1ES5NsTPeOQx6D9z4Fw7mUAefnxTkytGIwldjqR5PeRCsHM6JJ74tayVg1Y7WM7WOsgbEmxloYa2Osg7FOxs4w1sOYYa22qYyZJRPHDGhWJi5BMnHMh5YIphJ7M23OXrSJYBZiYruLlsHky2IsR8onjl/Q8sHMxDa0bNyNViLZ7wuvO4FWJbW5S33NjFYn2eTYJ8vRGqU2782JnYLWLtnglIOBaN1MPmOBf9zjB9PL0WxgNI6+V6cDzESMvv9naoH2eM6U2lyU96ufo2VKtRxZV12AliflE8c9aEUF2tuQCsbqaJ3S+4nXS3HwjgZj0Voly56zvQWtC8xC7CXz1BfQ1HXSMhqRMhstAYz2zxIX/jBaimQDHffuQ5sJRvNt3jN8FlqOZJnzag1ohWBay7aUsUqplj4/u20BWp2Ur3rZmkC0lnXMto7J1wmmtS04I9VybMWBh9CM6/3HeuLK6J+j2ST76sxTH6GlSBabmrYOLR2M5rO33NeBlg1mRJPeYz5XalN8bjVaoRQnfv+AVsy0WSq1KT4/AK1asiX7T80=
*/