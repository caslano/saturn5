
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_FCONTEXT_H
#define BOOST_CONTEXT_DETAIL_FCONTEXT_H

#include <boost/config.hpp>
#include <boost/cstdint.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {
namespace detail {

typedef void*   fcontext_t;

struct transfer_t {
    fcontext_t  fctx;
    void    *   data;
};

extern "C" BOOST_CONTEXT_DECL
transfer_t BOOST_CONTEXT_CALLDECL jump_fcontext( fcontext_t const to, void * vp);
extern "C" BOOST_CONTEXT_DECL
fcontext_t BOOST_CONTEXT_CALLDECL make_fcontext( void * sp, std::size_t size, void (* fn)( transfer_t) );

// based on an idea of Giovanni Derreta
extern "C" BOOST_CONTEXT_DECL
transfer_t BOOST_CONTEXT_CALLDECL ontop_fcontext( fcontext_t const to, void * vp, transfer_t (* fn)( transfer_t) );

}}}

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_DETAIL_FCONTEXT_H


/* fcontext.hpp
yzzqAGujyDNVnizyg6xiYixAnq3y7hL3RaH9nBVYKzGUiVuuuiVK/vpbyIjfFtnpIgtLHJkqe6WrI3sUNWR/t1sHzvebt2tcHvxmlM2dWm7msdd11zxq2V4p/j8IDKRc2gTuV7mt1/qe1+FV9ht2c6m7zdTdKvG/NZhJ/FfnO+VGcevKSa7kSedBxd9bvMo9Ien8/LsffogPw54HLdMsDbNUwhRwtW/M/vEUd4+/WasokTLu
*/