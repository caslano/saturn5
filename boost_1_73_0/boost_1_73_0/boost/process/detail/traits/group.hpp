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
RAULSr9goViQJnpRUREFlKtwFSyAolyKiti4InZE5b6zO3t29+SA6P/nec5zzk755puvvN83m9nZsH7rpblydWs8mlXS7HOCcwuDd6rCunTXYrqN5qW6K5c6tN3CkfYZzX6/903SvjPlv4d7aZpj7xFtwvbRMM2x+TPVn04tTd///7vGaaXrI/EwgscANjQtxZ/nB81L8ebVqeC4AWyof2GgLnC/wo4pEefP+eV1ueEnok24fyvD05nqte1G0vc=
*/