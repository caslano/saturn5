
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
tiMVUkYtKYcA5RAI+/Z9jeMDiSORfFYNf0JgTiBsaZ2ZeFppPMccSCuXufJzn6UqmjOb3dIZd+rUYtyJ5m+pxN2fHtbMJ3/Dgn7xribeQid/517r5E+2fEl1Ktmdq5JxqqY8T5J4mxOrX54/iMlvL413ZXtGf4k3Wyd+syLtkbdpEMkj66n8So0cyS9JC2sdo/O/Ke67E+nymTvUNrfpcycN59aqvfm8/0k/dnSo1JTvLyWO
*/