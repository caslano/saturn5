//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_GLOBAL_RESOURCE_HPP
#define BOOST_CONTAINER_PMR_GLOBAL_RESOURCE_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/detail/auto_link.hpp>
#include <boost/container/container_fwd.hpp>

#include <cstddef>

namespace boost {
namespace container {
namespace pmr {

//! <b>Returns</b>: A pointer to a static-duration object of a type derived from
//!   memory_resource that can serve as a resource for allocating memory using
//!   global `operator new` and global `operator delete`. The same value is returned every time this function
//!   is called. For return value p and memory resource r, p->is_equal(r) returns &r == p.
BOOST_CONTAINER_DECL memory_resource* new_delete_resource() BOOST_NOEXCEPT;

//! <b>Returns</b>: A pointer to a static-duration object of a type derived from
//!   memory_resource for which allocate() always throws bad_alloc and for which
//!   deallocate() has no effect. The same value is returned every time this function
//!   is called. For return value p and memory resource r, p->is_equal(r) returns &r == p.
BOOST_CONTAINER_DECL memory_resource* null_memory_resource() BOOST_NOEXCEPT;

//! <b>Effects</b>: If r is non-null, sets the value of the default memory resource
//!   pointer to r, otherwise sets the default memory resource pointer to new_delete_resource().
//!
//! <b>Postconditions</b>: get_default_resource() == r.
//!
//! <b>Returns</b>: The previous value of the default memory resource pointer.
//!
//! <b>Remarks</b>: Calling the set_default_resource and get_default_resource functions shall
//!   not incur a data race. A call to the set_default_resource function shall synchronize
//!   with subsequent calls to the set_default_resource and get_default_resource functions.
BOOST_CONTAINER_DECL memory_resource* set_default_resource(memory_resource* r) BOOST_NOEXCEPT;

//! <b>Returns</b>: The current value of the default
//!   memory resource pointer.
BOOST_CONTAINER_DECL memory_resource* get_default_resource() BOOST_NOEXCEPT;

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_PMR_GLOBAL_RESOURCE_HPP

/* global_resource.hpp
ibhA3KQ2WLFoL/umn9oPGT3LT4Z1dCTfbsmqFKsRxp+tryOzmZnzLFiLMHOeBesi8zLj7yP0K7VEFHMf71ynRcZrMedSsKAwcy4FS1Zypio5Q0rOsJKzUMlZruSsVXLWKzlblZzdSs5eJad7qHNOP5lTziCZ01hKZibHUiaZxYy/w5ijWFippXCosh6U/tUqOeuVnK1Kzm6R05zPw3qZye2hX7GIYu4TnM1SzFbMr1hQsXhmHmGJiiUrlqpYumKZioUUy1EsT7GwYoWKFStWShZgNn/ImxWwOjKbWVvchDmwFjIvM/P79rBOHodjKsYgjxP7eY9NxzgYjrcYEzbLiWMj1q2trFsRd0fp9G5YSFja5Hf+CAuT8TpvWjHtZViJiOs+JS8WVqXE1ZNZzMz1H6xZ5Lzq9rHrYZ3Ctk/4+hFYv2hv75oHwjDPidHL84jUzUtgQTI/s5g/JFwOSyXj7b0064MhsJCwL1/6ywmwMBmv5ef3p62HlQi7cUTmK7BKkfMfKxfPgdUL+zSt8gRYq8hZf8d7xbAuETffd/WNsAElzjqJj6Xod9xtsgCzuWOmboUlkTmN3UwlZ4iM1zJs1u4WWD6ZzeyGia3bYCUizjf9hEmwypOctr9cVz2r5ajYvMFthaxRmDlWwZqFmfN5WKswczyCtQsz13iwTjIvsxXfLJwO6yPzMZvx7KhVMOvk6DjznUtYgIzH/bVg8h2Y40wmQy1DYqOfM05VLF2xTMVCiuUolqdYWLFCxYoVKyXzM6u/4PrlsFoyi1nVTTfdDWskCzJLvuvKp2HdZF5m5juesAGR88j927+HeXw0dpldmnvVH2EBsgCz045Mfh2WKuyL2SXPwHLJeN8PnlY3AZYv2pvx4qIfYSXCpt/enQ2rIvMzu7HwriRYE5mX2ePP+i6EtQt72x9MhvUIM9/Sg0V4H8S8vnsYjflBY3OO9F4kGeKOjmXPGpHFMbNi50ZZApnFzJwnw1JEnNneYWlKXBaZzSxjZugWWL4SV0TmZWZ+rxxWLmox39CAVZL5mU197ukGWKNoL/nZ64KwVlFnYH7SCFi3sNJRP0yDRYSZuQuYfUq0zbr7uu2weDIvs+xjTjkBlkLmVGcGmVOducxknUXMZJ0VSp11Sp3NZD6+rCe6cmFdZE7rtk/kNPNZMPfw6Fr21G1ZAPOT8bj3E4fEwBLIPMz4e8JJzOSYT1EsTbEMxbIUy1YsV7F8xQrInJZ1iYgz+xBYGZmP2dwp9QFYrRJXr1ijWH+PLlxUB2sXtsp6NAPWK9atOb7DXH7n/nnJeNyUpUW3woJkvL3C5WdeAksW9tln58yBZYqc9943JBuWS+ZjtuaUqVNhxWQeZp647CMOGT3fw3IeEzvOteC0s2fDqkwcM7NuYTWK1ZEFma0fM/d2WAeZxYw/+9ojcvJnX/uU9gYUc53qbB5msj0vGZbnsWSNvcvXweKF/fHF/HxYGpnNbOaqHetg2WTeQWPvstF9StTiSknx0n1D/EdfVnUVsfaOj53jWvtlZf8ho/ciWR+GxuZHvyNNZjGrPdd3AFZPFmR2/TL7F1gnmZfZSUti/g7rI/MzM993g3lHRLfHn2cPkPmYhdpHjXXhXJgMfTiB70PIUhVLVyxTsZBiOYrlKRZWrFCxYsVKFStXrFKYuXaCVZNZzPh7RPUijp/XNYq47NPXxMBayQLM2le+F4L1Cdvw5b5pMPs0GmfMzLsRsDgyP7PaLbumwdKEXfNT1UxYrsg59eLb3oMVnqasB2H8HlEpM1vcUyxXrFKxajIfs9euvvMGWBOZzWxI7tZ3YR1kXmb/iMsOwXqVnJ6Ac85AwDlnIpnFbOXNc06FpYo=
*/