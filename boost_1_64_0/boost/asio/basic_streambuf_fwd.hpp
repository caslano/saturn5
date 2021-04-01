//
// basic_streambuf_fwd.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_STREAMBUF_FWD_HPP
#define BOOST_ASIO_BASIC_STREAMBUF_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_NO_IOSTREAM)

#include <memory>

namespace boost {
namespace asio {

template <typename Allocator = std::allocator<char> >
class basic_streambuf;

template <typename Allocator = std::allocator<char> >
class basic_streambuf_ref;

} // namespace asio
} // namespace boost

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#endif // BOOST_ASIO_BASIC_STREAMBUF_FWD_HPP

/* basic_streambuf_fwd.hpp
UxLUZIGQmvCubLJiuRShhOgHUt1VP1z4MSQOOexoOXda4HerKYub694Cb7VEIifJO7JMqTj9kBRZzWt8CjM8zbmVyAnc+7PsyTI/NdCwepA7UEFx7mjD8ZBZ/DOlqfaJOO7jDpCqlyb5y5s+pdJL2GH6RJVQWIFPsKhL8sAqscrc/nnC7biM84FHIJv3SLDH5NT1RUIutrqGCD7p+6RJL7aKt+20YAjCw2MzJyBTQh9Y0vy1Z8jzhf+unOX/OOGpZpvdfK0Z+3aOa8UQwvyyXL3UipVKP/1A6ETx8ecwM+OCdve5Fsu6f7m2nv48arypy0gVf+7o3xVDEvRYc/xZfZR5Reke3bNaoNek6YdgQylmUyztSZ18GzWlIgFXGqx8E/vbrHhC2eClD2OJr80MHWtOGV4Ul/nSDOHffRbUw9jR/kesC3XQ8Xj/1lJfMWrbsEmeNVEBQhCDU37SS7NvIMKqBUn4azsfURnmWQdSMNX7wtSkSouPe/Mz7lhtosMtf7+Yu3hngaka3Y8h9DTDkNUWgqfR2XH9mUfY72It1l8VJ0XzopVHqtKlCg==
*/