
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
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
*/