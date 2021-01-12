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
kapercqmh4WceE+Zekzryye3MBxOL5mSiJOz8zfE7yScAv+VwCSxdG20ITvLunH90KQspVZYI9YyUYtM2mfRd9wcVHV6GHQdG7OmHBxq0mgq2XDD2+lgRR6RhKlYnOFjz1sotx/OropLt0T3RpN5U3R+sKEm14CxVF26oa0nWT1KqXqCSp7CJxE+Kn/0YoI3h8xOFzRNQhm+UmJjHH/XHhyjrRXh8LrKeFNg+zqvZSxGyqUd
*/