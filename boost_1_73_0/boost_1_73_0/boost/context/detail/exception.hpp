
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
/AMi8lj96p79y4RRPzuHpPj+iP0bj708Jn1bMNQtY0/32uJry8/vRPsCh/5lk6F+IBv9awNRv8twoZ8yD/mJiyF/d/79P+Qf8ms4kV8z5bJtLaGejuB6UYC2ssbJQkHTwhlZyp2tYLOtJygjg9NpChTeE+TDjh5iurolgWmKj0qt7OiSVcVsSzTs9dHR1ik/zKVMD0YREZOcQ8vQVF+0czRJGeWkPuEYRUj7mVzUHNh/rnahjAwlJ1aLDlkmUmQ=
*/