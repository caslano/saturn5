
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
cToRkkuIsWohE1mV7ql0cSM7kH6KC6ASml0kIWw1uvCEeH7MHEytwURIkWhi/j6CQeguJNrsvvi+i9EDZ4KchMrCZPq3BUpt1WC8qR2YqaOsZ+zVB8zriqp2+NJijEOKkK5cOUflQ89+cBjtqaxnbgARRo7hfagicBnCK5xzgS8oK/b2J1x8/Soh4UszGPQZr69z6tQJ/t2f2uTf//m7ybMRFy7d5Imn9nj2O9d48js3OffKK9zYGUKVQ76GHG0h8yOdxKyDSDAmXqGEWMvQlg6Hx63zAARCtBV+jc+fSJ3mnjxc0zcYc9hyoTzcWkuvECFcnfbYan8XQ4DeOednsxky9ALznccVQjuw73vdFgDgjbGkNN7QYQOwhEw6FZlnQAhm0wW1dmidMxgMsU8/xNGtbS4/9BgnT57Af+4sxfROsuMZtYIq1tOL+ECHHn52UVL0NrGLTzK/KFH9Ep2BP5hy5MRTnBqskZkjfOfqGNsLwz4XZcgQFDJmA8Z8YN8IPCQy0CZTECARfyQBixYBMQTofePvi0jiBR4g5hKkbL8o7CmmLzsdg0ja27Q1AS4m+4SQn2tKi21yDUzU+j7NFgBBsCDM3DJfzNBlHdqZVx6TCrK8i2HOkHcxrwJpazMftD2E7Qj7s9LjaxWEpiMwIb267YI7nc6ZTGa8fuEiUgj6/R6D4YAjR7b4+Ifv5Gc++QAq2+BgUvHVJ6dc
*/