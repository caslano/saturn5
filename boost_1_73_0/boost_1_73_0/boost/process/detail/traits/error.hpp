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
VoJsRpZZFnD2MDh+U8LWBNhejGiBncwKmKS3kcFKI3DYxWVq7PwjwMdAsh7Zb++yethRgJ69P7KuPQ6c16j6lb8C3Gfqmw74uYLn6DfBkl9O1rCj37r2mmm2X1COgo31HbVjcHTfUS8W7uwDkjin0L58NtVU5k4ZyTkpWU8VRocdRFtQFgUJW1AMRcq9uoCXRsJlyDv/j7XrAK+iWNvvzBBAagARDCpF6Ui1IGBMIUDCCawhoKAQQgogJSEJHQQ=
*/