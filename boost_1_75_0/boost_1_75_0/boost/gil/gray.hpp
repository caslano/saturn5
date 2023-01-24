//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_GRAY_HPP
#define BOOST_GIL_GRAY_HPP

#include <boost/gil/utilities.hpp>
#include <boost/gil/detail/mp11.hpp>

namespace boost { namespace gil {

/// \ingroup ColorNameModel
/// \brief Gray
struct gray_color_t {};

/// \ingroup ColorSpaceModel
using gray_t = mp11::mp_list<gray_color_t>;

/// \ingroup LayoutModel
using gray_layout_t = layout<gray_t>;

}}  // namespace boost::gil

#endif


/* gray.hpp
/bWIUVx5TEgfWmfISCkZ9ropbYN3a9Vgt9LQ8q4ut6bLbc9cYFYiM2rjd3Fehvshl+xbQWCTmliKKOs+hvX4aOF83ixe6Z5gpuCkta/Cc5Z9UFb+cbIgzSIHDWOZ5u0fxSVzw44ABVJ2qax4Ne0jkxMdXansLBkK7sjewpKQS6vPmlQpOnEBLR8YjnmeUgwQAb+/8u28enG3zhKuxsxPyCDMjFIUGj39PTgtDMkmKWLbtWR3652roNzjHOxOmaTEuMS7Hx1E2PhKQy0Pd/wwkDiH6GNJ4X10TB0gP/QHhM95B7nWDPor9S77nPH8Vv+ev+ZQnbB0D6vZHGVslnuVTvCo8QHdkLGxBdebGfPbruvyIDOWUL0ZKLEKcu/7kQgqO2w6oSncKjmsbvoRQK5xs4L7MZJOg+whK2apQOVm1Vqj+4GMJW/LWYvsARJTErOXs8u1pC4zv9CYQaTOU9niGjOpxFz+G1vkZaCbUniiPHa+qtVy9X4V7ULPMb1NS39Mec5OK7R5qdCZCgsYzFvoFOy44DVr5ZiWs4K3kKWXeLhEMdfZYpen8mg/2qr/Q2X34uq3xOozk34Fc36x8VLgImQUBu8XhtPBU3vlrPyHv+TCg9blhuFBHUI+AhwEDmuGgs4FdriZN6QyTlvaE3Be6iuvFhaoynb6tnrzy1XsrvEtFLY/kvYNKpTXpxeUu4WaNgKmgBwB884gds8Q
*/