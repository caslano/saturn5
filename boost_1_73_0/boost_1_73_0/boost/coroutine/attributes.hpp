
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_ATTRIBUTES_H
#define BOOST_COROUTINES_ATTRIBUTES_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/coroutine/flags.hpp>
#include <boost/coroutine/stack_allocator.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {

struct attributes
{
    std::size_t     size;
    flag_unwind_t   do_unwind;

    attributes() BOOST_NOEXCEPT :
        size( stack_allocator::traits_type::default_size() ),
        do_unwind( stack_unwind)
    {}

    explicit attributes( std::size_t size_) BOOST_NOEXCEPT :
        size( size_),
        do_unwind( stack_unwind)
    {}

    explicit attributes( flag_unwind_t do_unwind_) BOOST_NOEXCEPT :
        size( stack_allocator::traits_type::default_size() ),
        do_unwind( do_unwind_)
    {}

    explicit attributes(
            std::size_t size_,
            flag_unwind_t do_unwind_) BOOST_NOEXCEPT :
        size( size_),
        do_unwind( do_unwind_)
    {}
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_ATTRIBUTES_H

/* attributes.hpp
nMcOO3QOBmUMRTYjWdC/OoYq6JW1acg1anPZMSz3GicIkK3UliS/p7rk2lx2bcuFkjBohwqy/QLk+0TjbhyYNFXmTf1kyS6v8In2tYy9dBGHcOUGC8+KqcJxKk2yvCy6BNa3whCzHpI9KS3swWgRXobRdZhFpsm0A+rLtnDY9fthlGanCz9IMet6dwAwh8Qpq79Hhf4gYR1bnMv7iq2GyEaJ54EbJBHOn9N4p4CJF195cQKj8eEEa7izF0QzN8j8+efNrvUvUEsDBAoAAAAIAC1nSlJF+U9flAQAAKEJAAA1AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9ETlNfTE9DQUxfSVA0LjNVVAUAAbZIJGCtVW1P40YQ/u5fMUo/NCDjwIGOo6WnmmAOF2NHsXM0UiRrY6/j7Tled3cNRKX/vbNrh7cicR8uKNjZnZnn2ZlnZp3FAHZ/2MdydDh495Oab4offG6dJoL/RTP1tkOaPkD3h44LfH4H1AievB7SHfgurwcYGq+0xzrV72n6HXALTVL/G2nnRapfcaXz7P3HvNkItioVDMc7cHBy8gn24MP+wbEN56RmtIJY0XpJxcqG09ys/F6S+3tH0s82UAWkcl4ETEomQfJC3RFB
*/