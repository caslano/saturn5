// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_TRAITS_GROUP_HPP_
#define BOOST_PROCESS_DETAIL_TRAITS_GROUP_HPP_

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/traits/decl.hpp>



namespace boost { namespace process {

struct group;

namespace detail {


struct group_tag {};

template<>
struct make_initializer_t<group_tag>;


template<> struct initializer_tag_t<::boost::process::group> { typedef group_tag type;};




}}}



#endif /* BOOST_PROCESS_DETAIL_HANDLER_HPP_ */

/* group.hpp
51gBx8pyFkjJ0WT8Pb6KyzLZIKdpqVSlgUwC29rbQtJAN3zawS8hTJ92akL4U6z4aqlz6Jf1ssCX88PCLmE81O38Yfme0F79z3eIlrV2VNSa0Lz1S7FykrCkaSXSblBk8Lg1plN994YyrlGFUgObVCr1Up0nBHjcVRY++7JdcgIOytIRQ0rWvKM9gNFvW3eDj9pnUHUuVdZzHQdUYeqljjFHUokYgbrOMOJN8eNBx1/O+cvK
*/