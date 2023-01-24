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
lTgAbTajyIUA8+HVAhXAhztl+Hs38h/OFH9w9SZfuvlveb3z+0yeeZMnBwMevvUYk1aTzvsP0M/8Lm833uaDj3yMx/WneaBzkdvDhBv7MRcHTXYG8IcvXeAH1/pEQYuxarF1eQcEPD8c8PIrGjUZ8hNPpHzqiT5ShyhlWZudK9IyjZ1+g5//bIM/eOH/5+5NoyW7rvu+3znnTjW9uV/PaMwgQYIgOIkUKYmUaFJSNDgaViSKWVGiOE5srUTJB1nO8MVeSVay4vhDsuIviZ3BkmObGiMOoUiJEikOIAGQIAgCjbHRjZ6731jTveecnQ/n3Fu36r0GAcoSEZ+1enW9qlv3Vt06e+///u9pny8+PyZbWSLFxJZg4TfREubpKR8I3LzI2Lq4SnftJm9+4AyirnLxxOOceuhF7nzuLp77wgkuPALnn9ppjR5vJ/rUq10nsMAHzCGCheMPtAs7DDm0eYKowHwM+cWxYVX8Z73gXCiGQktLRtuuRViL5CBKOCAXjRKB9vyxoDDaAr6gBKLyaqo8ZHbsQb5AUPH1WfWhWvjsM3AV5v/FhCAXSqS9sxg9xbp8DjUvRjpeIQT4qvoA1KsJA3qJqYcspOe+wpv/soi/V3vuv+h7xpXn4XM7/OG5r3B59fOYu6/A/hDZzxlNK1ayjCOFZnjH1xmpC+Sqy7nuyzy09hLKlCTmZd6+/g5sdpPzky/xwPG38p4j
*/