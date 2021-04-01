
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
4pdakDqBgi+t3pVkgNcIp/9ItBkmRwRYwCzd/Lebk7rAjbQ3354HuiA8A6WoJiHLd+iALHEzMvJqlOBROYr7LA0utgblhtW4GJdGCLea3LdiZMN2lQw3tvNO/+3Eh/0vjMbyW6bIConYUzkAR9hYlX0Co/eKk88X3LwRSoFymQtJFL9dDTv3yZ1p9xtZgKuoiLgwJKsUYc1iepY+Bda9hWqNzNjiAekVsh5d3WgXASFXxjOuUQRt2hu6gPiugBcv9UavImbQaNZuTOxsYi/y9n1vWK3R2OhRJEeZV6j8jiFjbu99M3VUHFILfrpO6naZB+ea4OcXvrvpQ7qVWLD05dHnpy/8Aq9H0kFBMShkkFeWCUrqmNpjuztw/KjUxNNN6A6T95suH+oeFTsdKUoe4ufeF9oqm9JkBXgaTArn0vLFkj8CIxED4wzFgucjRRyHx+vvit4mM99s3BLbZHWl0nmcmNMr0BMZDHNH7UuuxCczaDtv7MRLrkcuwyHLlgAbmZQyxtQDB4mQDqB/aIUyiCukD1I5oyeQ9VpYPnpwPJDSf2LBC6u1IR6pdg==
*/