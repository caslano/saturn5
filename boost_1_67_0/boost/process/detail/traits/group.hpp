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
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
*/