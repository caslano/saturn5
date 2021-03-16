
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
5JwO5SZBOMopYpmob+isQrcLwY3p+CZYUylUj+o70Jv6TKXEVD3JFo9g7pFNQvBBM6ZLB1hFfL/3o0V+dkDojjBN4rEK21bpmlpNlcqz6AWwAtY15iP+UNBOxwaI/32ZvDzjn495NdnzNpHFqaaLPcOEsBDOeJTVj7bu1gNwtjI1QcU8V8CVrUvRYE9ISxERz3gam0UsQ7m+eADPToI8k8BMKwQd6RwcCctE5uBDx8IBfWkABVrk8XPTJULCC8Q=
*/