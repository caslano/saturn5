
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
PPOMuUlTNo/HsdAXY3c2mjUip3iU1wVz9Tv7Mdg+nT+K4MMToeoZepRwF52ITfRT2oc2c1159DZ/YkWe2hMGJpFQymiqhsy8YejJRD7pvqqp62zxcysyOr980H2liGbBb876QNBpndNTATavDTrKb5YJ71+ntUpUn7P01zT1LDPo3TxqFWOsIm5agkIXLMMSHEriWuIlXNd3WOP8cuEBUwFR77SdcwnFvoa1/oY4a8w26kXwShfZCWwdRKUK9aLAXlgdZXannZFgpxKJY8TYK4KED4i23Q6H3bHgn9I5WN1cbPbxT5ksf0+1XR1OmLF8qIwb87SfSsVTgbjYIkzVm5wtY6MCUceTpl13aW+iBcIjcX0TjSAxq98DyMOUF8ra3kgRL/JNycxFrJjMKbARPDGhfraIvwcLKMX0l2SjMy5+AsZ+S6OVsfNodaZg8uMYKe/1xa9gh+vprx4O17S1msvlzLXcFNCHQoYUWoRH3ynWiMAfl2OeBMsu+GrSuIc2Px2950YsyjLQRravVhGSTVQu+qm2JtP2FE5jytEPuVcuq0VswcNrDjc8HEveve7cLnAeJt+O4DPPqvKJU4cTM/O98Zm2tN1la4mj5d/8Krq0LFrsGSPe2e2s0SWKac3qIHwaT3MH/PlOFOAuvY32BmkuJ3DeyDlHu8n68ZFrT7fHkj3jXz7jZcnLzSiNSTdXR3iECatbjSvX2rXx
*/