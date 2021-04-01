
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_DETAIL_FORCED_UNWIND_HPP
#define BOOST_COROUTINES2_DETAIL_FORCED_UNWIND_HPP

#include <exception>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {
namespace detail {

struct forced_unwind {};

inline
void * unwind_coroutine( void * data) {
    throw forced_unwind{};
    return data;
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_DETAIL_FORCED_UNWIND_HPP

/* forced_unwind.hpp
GQHWe7MFiBW5Z+5Kd4PL4QkiGjkdIPT2b1dudO/rqOxd0N3jmhsXVjoz9TT9V9VNVvvQhKdp0oOv45l78X4fczKWobnmCJuf6uuyvqsew1qVjy8oi6KPQFVepz1OWK6kbOp/Cy81Bs7bWzbVEDjkhFiH5sS2WQcbXAtxGnU+tpGkmJkbeUOfaMJWkFFKsOau+mAlNvFWV4zyHiVs4LalELW1114pdba/QY7iQJEWV/TRH7XqN/GwK2ttT4Tvxdx956pnOPRprmVxAbbzLvUQSrK9kIMwHkxQANRsW8T3JGI7Mc+kONNBFXQ9yqTPTCVfe9i8d4CtJnCgRMMhZ966OxgNoc/+7e1AGh78OgBsb1iPY0Yfl00X6b+U5CNCCW3ZW7kHWxcpgmiZlBF9etGSKKXAcBmVVMLjky3O0N0QAd9ZJC3MJkgPyMvSUUyboGkre3IOryZQFar0QPCSy86nMohn+nWEuQNOxxoJiqXlRkMtWD7IPB67mRYdeDgLwG1AjfQOHU0NTq950K9TiS+nsSVfD7BkErgfcX3CXoUD2vO3BSWjJktiQE3Xew==
*/