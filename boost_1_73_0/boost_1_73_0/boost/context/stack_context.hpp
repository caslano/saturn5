
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_STACK_CONTEXT_H
#define BOOST_CONTEXT_STACK_CONTEXT_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {

#if ! defined(BOOST_CONTEXT_NO_CXX11)
struct BOOST_CONTEXT_DECL stack_context {
# if defined(BOOST_USE_SEGMENTED_STACKS)
    typedef void *  segments_context[BOOST_CONTEXT_SEGMENTS];
# endif

    std::size_t             size{ 0 };
    void                *   sp{ nullptr };
# if defined(BOOST_USE_SEGMENTED_STACKS)
    segments_context        segments_ctx{};
# endif
# if defined(BOOST_USE_VALGRIND)
    unsigned                valgrind_stack_id{ 0 };
# endif
};
#else
struct BOOST_CONTEXT_DECL stack_context {
# if defined(BOOST_USE_SEGMENTED_STACKS)
    typedef void *  segments_context[BOOST_CONTEXT_SEGMENTS];
# endif

    std::size_t             size;
    void                *   sp;
# if defined(BOOST_USE_SEGMENTED_STACKS)
    segments_context        segments_ctx;
# endif
# if defined(BOOST_USE_VALGRIND)
    unsigned                valgrind_stack_id;
# endif

    stack_context() :
        size( 0),
        sp( 0)
# if defined(BOOST_USE_SEGMENTED_STACKS)
        , segments_ctx()
# endif
# if defined(BOOST_USE_VALGRIND)
        , valgrind_stack_id( 0)
# endif
        {}
};
#endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_STACK_CONTEXT_H

/* stack_context.hpp
XCZkFDuTNTvZXCZJnnf8aeda3c4UFnk/Z2t2pnIZ7ELx7m9+Mm2Tbmcal9nkMWdGUSvSTg6XwU4dn9gw29Wl25nOZaAH5aUptCLt5HIZ7CCxd9k56fp83U4el5mt9Be5mp18Zj6n+FwErnBHuQ8LuEyyUs75mp1CZt4/aGf2lRPu1/uvGVxGbX8KNTtFXAadDLyHrj5f+C96fmZymb0ucfcLLbTTiGFfVrS2Ci4L0pdfSGcWw1/DUepZvPRE72s=
*/