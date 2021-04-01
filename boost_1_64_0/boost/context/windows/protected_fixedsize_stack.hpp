
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
uJo1U3dia3ueMollhwNo/ohuubev9hpR+Nj/wT7fl9UT7F8QOr2W2GoCE2g/qWSAondOtuGDdJtCAIc4WLU8+8pJUeeicaB+yjsRh2Rqs+QGk4ZEpdIC1Up/p5qJom1Bvvkj9b3UgRFieCXy9IHPLQND879CHGjYyTgzj35piw32VsU7t9zDafZVEVADe9bad2DA7q2C3doJ9TUmnRk9eKoZfMdG21xfWIQRxYhM1mD2qE8pvMA7wQWQ7XH6pL07I3TGnmMO3QZfUq9aLy9ORK/H4/YrNzFzVW235mRuTM1o+AiU3ZcYPAP3GUA7VKGqqWLjwlOyADAg5N/yy0QnlcLl58cep5JCEdnnyLfIECNiu68X9R1AJ9pGd0S6TqARh5GpDgS0BniQ9Im2aKEM0mPMJCQtvU7fGBRQQ70UPmLnMyKiMHtNlm7AvM2KL+noIB3lp6I/lSnTnwq0+czanV1IkJVFL1FLurD47gc3zqqkHbFSrZeY5/ab/4dwIhpLodlmly1t1b0tMoIcKtbg7QJdLZwGZnNy6OgXnT49Zsc1+pKD3rQpbmpNqQ==
*/