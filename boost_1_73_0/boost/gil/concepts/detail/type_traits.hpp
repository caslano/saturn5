//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CONCEPTS_DETAIL_TYPE_TRAITS_HPP
#define BOOST_GIL_CONCEPTS_DETAIL_TYPE_TRAITS_HPP

#include <type_traits>

namespace boost { namespace gil { namespace detail {

// TODO: C++20: deprecate and replace with std::std_remove_cvref
template <typename T>
struct remove_const_and_reference
    : std::remove_const<typename std::remove_reference<T>::type>
{
};

}}} // namespace boost::gil::detail

#endif

/* type_traits.hpp
F1CLCU+EmrwIiUDyKdPBxxTLXA7FAZWgRJu8CIlQzqZDnmlvaHXNs0THTQMkQpDoykgk+PrM5HmSn5goPwSQiIWnWgYkQjnzFDIZk6ofaofxLLUAZCgt44nJjIoWOB4Zu0kx3hxOq2u2eTP0XEC+Z2hAgu896g5e5ckF9SfnF54cZkFSOyDV8MWo+ALHI54tWGWqNuqPs7TKVO6ZkFo8eMTU76hUdCfgkbGOMz2oJXlH1/AU
*/