
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
arrfjOB7Fc2dinKORMq93NS5hRNhbAR1bpHvh7mOql9cbNIumRje764FH+7oYVuwVMIEt/MbhBveD14+UccraON6b7itxwXeCm0nREY7fvuKyiThNeMtffybTb8J2l+pk1IPVS6sgzquwzTDvIMmZo7resz+4AepLyb1lMdJOO+cL3EzNU7ni0PGUIdOxLEKy6r6JhsLL79msCnEseOmFqFdAmWJ46hDIZ55q95gHIXxOCYinFBbOBxkQxw7JuoEGywxNtg9EfmEj4l6CAf1yjTwDhyI17qK8Smpb/uAD98k+ewG2TYZ2TZruEBxYcwDYec7MTzLhFOG3jQTP8eEoyb8eRPeD8KaFztGcjA7Rvo2wTDejpGON/EzjJ5PNPGzTPzJJt6Ww6kmfppJf5qJn2Piz7Dym/izTPznTfz3TPx+Jv4c8G22P6P+B33P96FvoXMp0+V7dUZ/tXtdRyoJ47aNGqZ+PfdVu7g/K+OtQhhvKU6xjNV0Pu8CaMsiri0zgxkAcHsWOp83gHS81xvbGtMmYj39MeFlnEcZZe6L1rrOY4ZwGpcqDeCDNC4z4w4bf4X2T6FMJsP3vvKdcUeTnD1+qiSYt9yedaeDrG2DfyoS/3at8LxO9IT7AN7Se91Qh0wv/C6wG4XWLxFfeDocq6+bBf8W4O1w9R4MnkeVuPd13bgws395tfQvE7zPP4AVMqyvm6Fii9cQvJjh6zroBsH1fd0tbMe/cP1Khrekejt9Gje4OsowxytGBz6oI5oK9nfe5PqWctdMb5vAhfds6XNquNr0OW8lWC2NA1Pt67Y0t7am097O/cy2zsQ6enMokdhAPeLtej/BHVBn1uzgjhvdI/uGuYPxxWLSFYf9zq3W6UIz9lP4KOkX61iw2IwFb2C95dAP6w90I2ODqaSLzriWn66HuVKKU4loVDCOrNZxpOyRvRP0UJvjfiWpY5we7zDhPfrQZjp9YJt5j2kjn5Q7U1iPZt89wZQu495r/PFbEI99GsdTw3hnG1Xr7S9m3JfRekRjx1YeUyss30u1T69azjcg1S2CezUZ3tCboPJLUkRwr+aSznWdLd2pVcnmtjjeq+lwEa57omkAtaA5GZ/vjDLgG1G4E0jgfEeD187CKOzEcXxHyFYBMuwBV0/ykltrNscbyOC9eVKOf4RynD2ENof4t2rxqW65dcMCuWyxX/jCeN9HPCg+4o5MHyH7RWRukcO6Ls84vIfEXVKROY/IMMZUvAjv4+7oRbyowACP8u6QFMfZtSBQOsFhX9AJctW6sMilNv4wzg9yvBq5fJMmwu/iHrgend4eFb1hfXnM2PHj4qP/LLh4twXeUYF95iexX0w4Mi8MdYvuEZNx4QvFwbjwGYLhWsezpg/6HPZpub7CPt3i7D7jixovtOw9Ty+pnJAfz7RRr0j+yd6dbIO8D+WIju7pVUFrw7eh0N2Jn4EGtgpMhmxK9USyZd4FLzL/Y2I/e0vD7YrL5E0Yq/9TaOC9T28RDPsJ2yHM602jfP7vSFq98wXb9fckjt9tydG/0PL6QOYS/iX5OqhM7+7RvW517uaKRTW6382FF9WsrltYI3cYUHhx3TIXvxj2P/+H6KV1He/u69pX6Mzzt8SFx/E+uxxzlW3xGLkFt4OE1RoE0/PDH4tune//ZKKc6R3qcfhTCXub/bDWm6hH/QDxbXnlfg9AvilurX6TrzhYv4lEk1chZ6uGlAcSXsgyTk+LN929ET9A2kSPdZcP9DYzvao0PeddJufkO61nGmPKN+HOzeC9paezL7lZ/KXIsKWro9sBGSaybN5S1Uo6EXmGoTw7KAPcz5Rf6H7m7vpy8REQZtuHNDgvshvFK80=
*/