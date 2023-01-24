
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
        const std::size_t pages(        
            static_cast< std::size_t >(
                std::ceil(
                    static_cast< float >( size_) / traits_type::page_size() ) ) );
        // add one page at bottom that will be used as guard-page
        const std::size_t size__ = ( pages + 1) * traits_type::page_size();

        void * vp = ::VirtualAlloc( 0, size__, MEM_COMMIT, PAGE_READWRITE);
        if ( ! vp) throw std::bad_alloc();

        DWORD old_options;
#if defined(BOOST_DISABLE_ASSERTS)
        ::VirtualProtect(
            vp, traits_type::page_size(), PAGE_READWRITE | PAGE_GUARD /*PAGE_NOACCESS*/, & old_options);
#else
        const BOOL result = ::VirtualProtect(
            vp, traits_type::page_size(), PAGE_READWRITE | PAGE_GUARD /*PAGE_NOACCESS*/, & old_options);
        BOOST_ASSERT( FALSE != result);
#endif

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
w4gpKQiIX+haWqpR6/G9aJ7Y2jBlSr8YUl7Z4vR7TnOzeIPdvQN6SO4ZnIKLd7P99B2Ue2P6ckxVLkAIVK4DQG/sYq73OL2+yfp6j7qqQxZi95KumPG3mPgptXLlswQEwoduT9aGJi5KqQAGYaNb9ru0/xXroAs8S3AlQ8OYPMuCK+I9ZVWxKEt2dva4GDfLc01W5PSKnLPHxrzvwU3Wx0OkPsl/aSTTyT3c2J9T7p3DWodSUnSSfYDQB2CxWHhrbUoBTiAglFL7P/uzP/v2yJS3sW4PAABuHh89JRY2xNaVQmYKWUbCSqTCmijqjekfnrp5GNY6vLT0Lz9E/dWc/PRN6ss7DLOToczceQrtcYVlMvf0+yEnXhiBp4aNKwg7RPqjCBfCTDKvqaogTFISQEGK0J9OBEIpOHKB7BPCI5B4GQeBNARgJPaaX+2bkuGmi0jMFw7AIFpT37m2i48JZr2zxD4AMWDg5FKpb9P2K/EHIp00twyquBjFIFhChHCmEGFGgysWmItbzP7gI2y+71U2Tr6Omjn2vvB+pq/cT18O6buK0k+pqho9yJAynFctFcXBFovZnOs3PPecvSv8cuep65qqrKhNHYCqvYwNodeeqgAEHfpnSbibSEAS6BSipbuL9oYJ95NYBoUOb9C4bjHsuL+/T1VV5HmOlDIQiFlGpnX4zmR5AGVpKEvDzu6EV169FKMQmo31EeP1
*/