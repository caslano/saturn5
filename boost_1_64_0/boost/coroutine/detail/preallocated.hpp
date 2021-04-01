
//          Copyright Oliver Kowalke 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_PREALLOCATED_H
#define BOOST_COROUTINES_DETAIL_PREALLOCATED_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/stack_context.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

struct BOOST_COROUTINES_DECL preallocated {
    void        *   sp;
    std::size_t     size;
    stack_context   sctx;

    preallocated() BOOST_NOEXCEPT :
        sp( 0), size( 0), sctx() {
    }

    preallocated( void * sp_, std::size_t size_, stack_context sctx_) BOOST_NOEXCEPT :
        sp( sp_), size( size_), sctx( sctx_) {
    }
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_PREALLOCATED_H

/* preallocated.hpp
vvBYSZ+dAEMd1LzANoi9XR926QRZsrh3AWbc1DMMpf2//2eGMKCfpDn0e0mxnyySAb+PBnbCXJhh3Kgbjh4DEQhRXrRu0SjTLgTNW8Unv3Mis/Oyb8m2B14czv5R2gaDiAcSVE7/OQkIkHenfYQTW43fBJAJAQo7O8iOeSIilC5vlD+W8/pVAYspKJXCl+9LV2/x9Ay5d89pnil6T1sjVZe1Gek8K5tJnGo8RhB5Z6gbPdrARKGMeiPgSAu29zf1rTmUZ8oTe1zWWce9qW+EOVK+g9IyUyBo0AiFGxD5eHdWlhdAQSc6CcyMFYq8WmYGyOMOL6N55S+cxO+7kSuYLDm98DKCh8zb+HEv2k6SqwO3n+yoijkl4UuItB4E2ZVv9tWYJuhwiqwfmcgXC94b3zKdtzwu3g6s5VEeb3w54qsartIrf8HXGNrs+WqotLliS3dxgMYb+PFuDoE6vYZyeI/+uwwsNaRzaq5agQ9zvoDG4B9HiA8OzUbMxZ3X05Q9UODa3y4TNnCeNgjZRATHcsQ2ETbf0L2IUTPaSiktHegWEvclEkuxNZhdWw==
*/