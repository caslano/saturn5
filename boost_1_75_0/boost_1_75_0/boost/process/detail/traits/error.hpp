// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_TRAITS_ERROR_HPP_
#define BOOST_PROCESS_DETAIL_TRAITS_ERROR_HPP_

#include <boost/process/detail/config.hpp>
#include <system_error>
#include <boost/process/detail/traits/decl.hpp>



namespace boost { namespace process { namespace detail {

struct error_tag;

template<>
struct initializer_tag<std::error_code>;

}}}



#endif /* BOOST_PROCESS_DETAIL_HANDLER_HPP_ */

/* error.hpp
qa7ZSYlY5MvsfQlB7wb+F9LQ52xTT9ms5/A+8F2WJxvhCXeeM+/vXedx0mTEY5QYatvnxl6O/jopeP6nKgOCgE/k1Nz0tG7KXe9wRxJQ2ed+FCSTJJMYUe49SaaQGRy5s3WWbJk9+S6TtzrKQnMtTmT9dasTLI20isd2mNrNlQW6X2/cUqj7JS3VdnEqufRTakJf2UlIgswfQ9v9r9ytS8oSqfubNtBmYuiY8O976W1G3L/VELqTjDESNt3uIBrjyE5+YB3H10eO6V160s9dH4h8FQK6dicmU5XfSEslsjpcY9IW0YgG/wqEhpW3LMVJNUycy36ybPxY8sCuHgBU8vTnd9NQYbtQDQ31lgz9KRTa+pdIvHh2ZrpNDAZ3CXO99LHBEoxNi0O3B7/oHzASXAizT77qLtUP0WkBXuLyu/HA77sc1g6l4u2MHAzoz8rjzBj1bpcX/WDNXDgPCtsEB+iaZIO0crpJvOGglI+US18p721GtfOD99exIX9F5ykLzTh1NEnLhxLR4T2C+ssrSm8/VlPU3DOp/dbNepfIs5vvFfV8cyMmdF2g9NHvd9oAUGwZBP2K/2lPbUAT+hebSqNntkJJ62Lx5Zz60l6t5VmmBas3i1q0Iopw/CYPx7Hb0UEl8YbXy1/M/vh9L7xudBVHW9WvJXGEnZeth7E5gaFxr0EL/ZnXYVl223mY8PVDNpQGW0pYQ0CIHPWn
*/