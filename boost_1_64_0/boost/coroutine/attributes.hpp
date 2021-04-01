
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
3eYNC5y0HjwmxKVxxzSHpAI0uBgXClc8NUwc91rihNmQDGuYQEDPaG1gQaCgyovyrqXoWBnsDpf2EdNT0gDsc031WaY8o6UEDs9b+meb3ZTLs8j3/r9i0iy1592bRPCbrffuBwcNiFKrrAsNczsaQ2fnl+aJFt1ofmSBsaXaFzrHrdYvozjhPARDz85c0E+lCpBEIhSMscghkyoqi65Wycv4uNoQel24U03u840XK/dwU83ecM1dJXpNuAbjulRRgNY2HY+7XUj5eHqgo7FCQHhJGKQGm/8fmTnyi6gsS9V9SwnsjXaVx60ewZJ7WsNpMvr0yRptrCqGujV9x2TmQxBqaDDi7vT/g84D3LtxeuLAw0Czxv2k53ZGRqT+YI+KhWO8BP4mOUr2BaCCD3Q0kNWXdNPTZIHwPHj4iepaTbTQMDD0IQFrYKCwNzAnQ3BrLfH9Qy5n/4uNMf1NyyeGp4TIba2Qz08nibQFgz8uOlGezk5vS+B5Q15xAxsV8mciF8r0JhUDweDdeD0BOp4NLFxgx0+GP1EwQwLyMZEK1ysjiDcqmSAcPnV8lg==
*/