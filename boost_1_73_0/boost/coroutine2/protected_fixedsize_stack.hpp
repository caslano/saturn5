
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_PROTECTED_FIXEDSIZE_H
#define BOOST_COROUTINES2_PROTECTED_FIXEDSIZE_H

#include <exception>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/protected_fixedsize_stack.hpp>

#include <boost/coroutine2/detail/coroutine.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {

using protected_fixedsize_stack = boost::context::protected_fixedsize_stack;

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_PROTECTED_FIXEDSIZE_H

/* protected_fixedsize_stack.hpp
fXf1z0dTzUczzUdL2A62gr1gG3gUbAuHwA7wWNgejpJzlQ8K6HuUvj8ug8dhKrC3VF6rEewJs2Fv2Bn2gV1hX3gk7A9HwAFwNBwE58Ij4RXwaLgcDoMvwuEq7zUCboGj4GfweNiRxDwJe8KTYF84Bs5S+3PgKXA+PBUuh6nk53E9fx7mwRdhPnwVFsBPYSFsTt5KYWt4BmwPy+DxcDo8Cc6Ap8KZ8DR4Njwd/haWwnPgRXAu
*/