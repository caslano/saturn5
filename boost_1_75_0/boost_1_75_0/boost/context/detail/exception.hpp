
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_EXCEPTION_H
#define BOOST_CONTEXT_DETAIL_EXCEPTION_H

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/context/detail/fcontext.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {
namespace detail {

struct forced_unwind {
    fcontext_t  fctx{ nullptr };
#ifndef BOOST_ASSERT_IS_VOID
    bool        caught{ false };
#endif

    forced_unwind() = default;

    forced_unwind( fcontext_t fctx_) :
        fctx( fctx_) {
    }

#ifndef BOOST_ASSERT_IS_VOID
    ~forced_unwind() {
        BOOST_ASSERT( caught);
    }
#endif
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_DETAIL_EXCEPTION_H

/* exception.hpp
wHvvlVLUdW2NMemOSs+O0Az0+163BQCYWvWkjPHx1BgjngjnYTabMRytoZ57mKP37TDrPclO/xonHz1H/9WzYDX9bMi02uP6e36f3juucuzmR5h+8yeQg0EgumbH2al2GJ/9NqOHv8Lei5+gcD/CYE0xN3WcoB1YZKkC9yBtYP1FvDcRYRiEgMgJhOMP91lqHiWaMGAazNGxNvHRNQgqLQgpMRsQ65GpGYYL2X1EgRY25fsHBs9Fje9ctBpSFMA5iNmBXXKx6TVoIzkYCcDkk3rnkZljdmHIC587wdpPXWGt3GFSTfAoKleipMQbifHBh629xzCntgvKsqKsbRh4EljImLQTmrQgLcIcwMxAbwvyLIxFxoGZgpuBOQjPGLy3TdddLwIAgADlECiEXzr5rabv3lgNMbtC0DXoEYW3SeZJWy39Q1eM03ctE32Jj0gvVzsKxcsfrTxrBMMRnD45xJhpAwCrEQClFJPJRBpjrFKqMUXidudv/Ybvfd0WAFDPayVotaQXPpjYhGtSlTVSzRi6dXjpPsYffI1rl2+Srb3EmXedYnJOMj+o2L7rMQ7ufJzTm/cxe+wutBixqKvQ9ks9SC4Ldr/9fob3fp47f+ArXHt+DbH3COM1xQxHXUfWXEmEjjUAsQmFlIEDSGm2QogAAoktTm5nPOjGJvDh2XliD//4HT4CROQBUjlv09ijYfSDWd8WBDkwNB2D
*/