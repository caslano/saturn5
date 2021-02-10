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
StmIj+Nx1rUVnmSc80yMs4dUWKVcPTnVHNmsyBZ4I0Fy6AQ1QdmbsOI5K9QTU4SLTbesmCjNHS0MWOdj3oKgVTXAoSujoj8ChXjIlqksoUH2TKqH4LVQ0TYlXz0yxLQOQEXX1hgO04J2OcfEm9DVOW21vU7EQ5Qhyzrlr5Rsxz0HXiMrGNkxuPEIlkQwYcKNm1wEswRu7Ciy/WQOwRew/fmAd+n656gNhlFboHdNSwWyaIGtmorR/FHwn9rphpVcwHQWeVdBmKShGzqe6+OZ09hNnPTMgyMYHYPP16jwg+MRjCq2VBKAD9bRiTXBBfWVrrpKslRQqaqNNwpLIHZ8Ab595Rg/CrB4Dw1raMVqVt9CyYWEZcWzb9gFQmqIeO4HYezGxi+szqoup3CqgvZSLD8bPXzGceMZmT29B+9K1EmFcvkBE5RnSVrMr+Ig9j/p2OdOPI3cMHED3/A5iqfO1OFAIBX6PfENNllLV3zdd+oH69dDa2IZRkiwkgQWxZmGXRQhNlir+qIY4mHd61xDYPnR1J95Hi7Jdmv1OmMKQGcDfQST2AayxJZU0tOpwpBFi4Lf0TGBWfSp7beab2ql+ppLQ3RNw3EmXCRJ+J1jPw56hhhXd10Oyy0Mdd+dSNNsOKulah0OWUVJ30O7
*/