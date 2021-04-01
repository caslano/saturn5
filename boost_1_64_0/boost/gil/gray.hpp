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
IbR/BKr0vutIA1QqbowYOnmrI9RXcVU3vdpraK3rxjHmmW2sJ5iixoZlbXGbTks8NLB0+rescRzU8iBQ/aawj6JJ5aZiNgdNqTFT7yNKPpkF+osaxC+dbhIuGkg8632/GakVhWxTz95Hf2ktUa9jDeosKaEtW+bWl3vGUf1bBKzQmqa5/MwIk8YUx3lLvJemNXLIb3sWs134jWceC4gf/3fIasWuvHBv76CcQsDyOp3VVlUw3agpMB/m6f0OMAjrMCoUantgGRGzyKambL+QOql+KHHt7QnjRKmafvIdGPx4PQ4VUdnBVIYnJhILiIitVmDF7yRWMTjVU1zu3pYOS8RVJHhNJGrHyiQpVQ0GXiko1wOCimR46Wjpx91YzyEp5+AQOqkR6bohv7LOB+uk03Vz7Z7AspDmTtY8h/LnjP4akVMOoebZYPsqWViY4D7P8rRQ3SBQebUiZXZGMPZOXky3Ep2zFkJdp7tpqfpb/EMBl/SYurpqZlHLVjnvY5lXDp57DPD+t7N+sh9rFEn34goJCECW3Hcj87yok75BjjGwHR/pWfa4HN98ZA==
*/