
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_PROTECTED_FIXEDSIZE_H
#define BOOST_CONTEXT_PROTECTED_FIXEDSIZE_H

extern "C" {
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
}

#include <cmath>
#include <cstddef>
#include <new>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>
#include <boost/context/stack_context.hpp>
#include <boost/context/stack_traits.hpp>

#if defined(BOOST_USE_VALGRIND)
#include <valgrind/valgrind.h>
#endif

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

#if defined(BOOST_CONTEXT_USE_MAP_STACK)
        void * vp = ::mmap( 0, size__, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_STACK, -1, 0);
#elif defined(MAP_ANON)
        void * vp = ::mmap( 0, size__, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
#else
        void * vp = ::mmap( 0, size__, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#endif
        if ( MAP_FAILED == vp) throw std::bad_alloc();

        // conforming to POSIX.1-2001
#if defined(BOOST_DISABLE_ASSERTS)
        ::mprotect( vp, traits_type::page_size(), PROT_NONE);
#else
        const int result( ::mprotect( vp, traits_type::page_size(), PROT_NONE) );
        BOOST_ASSERT( 0 == result);
#endif

        stack_context sctx;
        sctx.size = size__;
        sctx.sp = static_cast< char * >( vp) + sctx.size;
#if defined(BOOST_USE_VALGRIND)
        sctx.valgrind_stack_id = VALGRIND_STACK_REGISTER( sctx.sp, vp);
#endif
        return sctx;
    }

    void deallocate( stack_context & sctx) BOOST_NOEXCEPT_OR_NOTHROW {
        BOOST_ASSERT( sctx.sp);

#if defined(BOOST_USE_VALGRIND)
        VALGRIND_STACK_DEREGISTER( sctx.valgrind_stack_id);
#endif

        void * vp = static_cast< char * >( sctx.sp) - sctx.size;
        // conform to POSIX.4 (POSIX.1b-1993, _POSIX_C_SOURCE=199309L)
        ::munmap( vp, sctx.size);
    }
};

typedef basic_protected_fixedsize_stack< stack_traits > protected_fixedsize_stack;

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_PROTECTED_FIXEDSIZE_H

/* protected_fixedsize_stack.hpp
FPunYRwO3n94Ck/AffQEfq9Ki24X3ELMKf3w3Hv+zKMN+hVzptex5oZyjP+IKY0Swz6M/JPAuSv2vA34rcWiZKZS3JKGZ6PxJByEjldmzk+iTIoq5fCK5DeIe+NYUYnE/dtq9+gEDnKEQYFouKMSMZczBQdYBGy5/9LxMmG1HgVhbzqYRIPxyMHOdSGw2AC5btgHrMKElEYkjHyjxPajaLIX7kPOGUIG8zKZOBOGyWKNIgQOlgwiggCUyKLAnmh5M9ArnohMJFhmi2qJcrUtuIrKPZPKSRRHPeUCZGUWkha39NdKtedQ3SLHkpkNVK1/TQ5Qe9fxBhNY1Y6px5+6m+Xhp67iCyT61NVcXWC3+fz5803i1vl2fWg1bX7pbxgOC15yVZuu5fJO2KxtHCtLO7pKcupJrl8spEK4L90WuCkznJ6K/1lxje1iveKurWyXcoFaGs9dz5pae2Bt21hEEWdoiFwotsptjDmj4DCk1rJSCeZ3lw7PGVgWfmUUS6hoM9V0jFyiBSUavMnXrv8S1EQGEpuNsUWJtjRRvMeYrCrr1DfxS2G+JpgUskp/kH4E32gcBd26HyWsKNAeA+fZYFMIhFd/FvX3nuyfZxNqeXRCO7sa8ZweclL2vs14ibm6h3UDdI32Oqw2gQTZ
*/