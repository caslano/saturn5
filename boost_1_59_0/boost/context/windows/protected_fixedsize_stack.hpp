
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_PROTECTED_FIXEDSIZE_H
#define BOOST_CONTEXT_PROTECTED_FIXEDSIZE_H

extern "C" {
#include <windows.h>
}

#include <cmath>
#include <cstddef>
#include <new>

#include <boost/config.hpp>
#include <boost/core/ignore_unused.hpp>

#include <boost/context/detail/config.hpp>
#include <boost/context/stack_context.hpp>
#include <boost/context/stack_traits.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {

template< typename traitsT >
class basic_protected_fixedsize_stack {
private:
    std::size_t     size_;

public:
    typedef traitsT traits_type;

    basic_protected_fixedsize_stack( std::size_t size = traits_type::default_size() ) BOOST_NOEXCEPT_OR_NOTHROW :
        size_( size) {
    }

    stack_context allocate() {
        // calculate how many pages are required
        const std::size_t pages = (size_ + traits_type::page_size() - 1) / traits_type::page_size();
        // add one page at bottom that will be used as guard-page
        const std::size_t size__ = ( pages + 1) * traits_type::page_size();

        void * vp = ::VirtualAlloc( 0, size__, MEM_COMMIT, PAGE_READWRITE);
        if ( ! vp) throw std::bad_alloc();

        DWORD old_options;
        const BOOL result = ::VirtualProtect(
            vp, traits_type::page_size(), PAGE_READWRITE | PAGE_GUARD /*PAGE_NOACCESS*/, & old_options);
        boost::ignore_unused(result);
        BOOST_ASSERT( FALSE != result);

        stack_context sctx;
        sctx.size = size__;
        sctx.sp = static_cast< char * >( vp) + sctx.size;
        return sctx;
    }

    void deallocate( stack_context & sctx) BOOST_NOEXCEPT_OR_NOTHROW {
        BOOST_ASSERT( sctx.sp);

        void * vp = static_cast< char * >( sctx.sp) - sctx.size;
        ::VirtualFree( vp, 0, MEM_RELEASE);
    }
};

typedef basic_protected_fixedsize_stack< stack_traits > protected_fixedsize_stack;

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_PROTECTED_FIXEDSIZE_H

/* protected_fixedsize_stack.hpp
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
*/