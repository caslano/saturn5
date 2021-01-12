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
Qd7jY08YCq2XAqMM9AfrUEHYCfEyJgXsRzGe4+ehD4nvtA8FJsC9PBV4f4Yvei1jwr99EF33IrZ6DvBLwVf4mdjmBOT+QGJ9JZ8hE8r4Nt/chN0UeTL4XMFv+ixDb2dB29K/OTOYdRd4rHgM990ha/fPZUysZd78KDjDN68C/vu3YsePN8TDbmKLrVn/GCbEAXyIXsSnTjaQb8SOWsWjQ3gvjHXeq6HNqKHSf4H2L4GvkWHj
*/